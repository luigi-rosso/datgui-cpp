#include "OpenGLRenderer.hpp"
#include "OpenGL.hpp"
#include "MemoryFileReader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace splitcell::datgui;

#include "MemoryFiles/Sprite.vs.h"
static MemoryFile MemoryFileSprite_vs("Sprite.vs", Sprite_vs, Sprite_vs_len);

#include "MemoryFiles/Font.fs.h"
static MemoryFile MemoryFileFont_fs("Font.fs", Font_fs, Font_fs_len);

#include "MemoryFiles/Color.vs.h"
static MemoryFile MemoryFileColor_vs("Color.vs", Color_vs, Color_vs_len);

#include "MemoryFiles/Color.fs.h"
static MemoryFile MemoryFileColor_fs("Color.fs", Color_fs, Color_fs_len);

OpenGLFont::OpenGLFont() : m_Buffer(0), m_Texture(NULL), m_GLTextures(NULL)
{
    glGenBuffers(1, &m_Buffer);
}


OpenGLFont::~OpenGLFont()
{
	delete m_Texture;
}

OpenGLRenderer::OpenGLRenderer() : 
						m_ScreenWidth(0), 
						m_ScreenHeight(0),
						m_ViewportWidth(0),
            			m_ViewportHeight(0),
            			m_ViewportWidthRatio(1.0f),
            			m_ViewportHeightRatio(1.0f),
            			m_LastBoundShader(NULL),
            			m_LastBoundVertexBuffer(0),
            			m_FontScale(1.0f),
            			m_CurrentFont(NULL),
            			m_CurrentFontTexture(0),
            			m_WasBlending(false),
            			m_HadDepthWrites(false),
            			m_LastSFactor(GL_SRC_ALPHA),
                  		m_LastDFactor(GL_ONE)
{
}

OpenGLRenderer::~OpenGLRenderer()
{
	glDeleteBuffers(1, &m_Rect);
}


bool OpenGLRenderer::initialize()
{
	if(!m_ColorShader.load(&MemoryFileColor_vs, &MemoryFileColor_fs,
		{
			ShaderAttribute("VertexPosition", 2, 4, 0)	
		},
		{
			ShaderUniform("ProjectionMatrix"),
			ShaderUniform("WorldMatrix"),
			ShaderUniform("Color"),
			ShaderUniform("Opacity")
		}))
	{
		return false;
	}

	if(!m_FontShader.load(&MemoryFileSprite_vs, &MemoryFileFont_fs,
		{
			ShaderAttribute("VertexPosition", 2, 4, 0),
			ShaderAttribute("VertexTexCoord", 2, 4, 2)	
		},
		{
			ShaderUniform("ProjectionMatrix"),
			ShaderUniform("WorldMatrix"),
			ShaderUniform("Color"),
			ShaderUniform("Opacity"),
			ShaderUniform("TextureSampler")
		}))
	{
		return false;
	}

	float rectData[] =
    {
    	0.0f, 1.0f,
        0.0f, 1.0f,
        
        0.0f, 0.0f,
        0.0f, 0.0f,
        
        
        1.0f, 1.0f,
        1.0f, 1.0f,

        1.0f, 0.0f,
        1.0f, 0.0f
        
    };
    glGenBuffers(1, &m_Rect);
	glBindBuffer(GL_ARRAY_BUFFER, m_Rect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectData), rectData, GL_STATIC_DRAW);
	return true;
}

void OpenGLRenderer::enableDepthWrite()
{
	glDepthMask(GL_TRUE);
}

void OpenGLRenderer::disableDepthWrite()
{
	glDepthMask(GL_FALSE);
}

void OpenGLRenderer::enableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

void OpenGLRenderer::disableDepthTest()
{
	glDisable(GL_DEPTH_TEST);
}

void OpenGLRenderer::enableAdditiveBlending()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
}

void OpenGLRenderer::enableBlending()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void OpenGLRenderer::disableBlending()
{
	glDisable(GL_BLEND);
}

void OpenGLRenderer::setScreenSize(unsigned int width, unsigned int height)
{
	if(m_ScreenWidth == width && m_ScreenHeight == height)
	{
		return;
	}
	m_ScreenWidth = width;
	m_ScreenHeight = height;

	setViewport(0, 0, width, height);
}

void OpenGLRenderer::setViewport(int x, int y, unsigned int width, unsigned int height)
{
	m_ViewportX = x;
	m_ViewportY = y;
 	m_ViewportWidth = width;
	m_ViewportHeight = height;

	m_ViewportWidthRatio = 1.0f/(width/2.0f);
    m_ViewportHeightRatio = 1.0f/(height/2.0f);

	glViewport(m_ViewportX, m_ViewportY, (float)(m_ViewportWidth), (float)(m_ViewportHeight));
	m_OrthoProjection = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.0f, 100.0f);
}

bool OpenGLRenderer::bind(ShaderProgram& program, unsigned int buffer)
{
	if(m_LastBoundShader == &program && m_LastBoundVertexBuffer == buffer)
	{
		// No uniforms or attributes need to be rebound.
		return false;
	}

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	m_LastBoundVertexBuffer = buffer;

	if(m_LastBoundShader != &program)
	{
		// Uniforms will need to rebind.
		if(m_LastBoundShader != NULL)
		{
			m_LastBoundShader->unbind();
		}
		m_LastBoundShader = &program;

		// Thought we could do this before?
		// program.bind();
		// return true;
	}

	// Seems like the attributes always need to be rebound...
	program.bind();

	return true;
}

void OpenGLRenderer::pushState()
{
	glGetBooleanv(GL_BLEND, &m_WasBlending);
	glGetBooleanv(GL_DEPTH_TEST, &m_HadDepthWrites);
	glGetIntegerv(GL_BLEND_SRC_ALPHA, &m_LastSFactor);
	glGetIntegerv(GL_BLEND_DST_ALPHA, &m_LastDFactor);
}

void OpenGLRenderer::popState()
{
	glBlendFunc(m_LastSFactor, m_LastDFactor);
	if(m_HadDepthWrites)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}

	if(m_WasBlending)
	{
		glEnable(GL_BLEND);
	}
	else
	{
		glDisable(GL_BLEND);
	}
}


void OpenGLRenderer::drawRect(float x, float y, float width, float height, const Color& color, float opacity)
{
	glFrontFace(GL_CCW);	
	y = m_ViewportHeight-y-height;
	glm::mat4 world = glm::mat4();
	world = glm::translate(world, glm::vec3(x, y, 0.0f));  
	world = glm::scale(world, glm::vec3(width, height, 1.0f));  

	bind(m_ColorShader, m_Rect);

	glUniformMatrix4fv(m_ColorShader.uniform(0), 1, GL_FALSE, glm::value_ptr(m_OrthoProjection));
	glUniformMatrix4fv(m_ColorShader.uniform(1), 1, GL_FALSE, glm::value_ptr(world));
	glUniform4fv(m_ColorShader.uniform(2), 1, color.values());
	glUniform1f(m_ColorShader.uniform(3), opacity);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glFrontFace(GL_CW);
}

void OpenGLRenderer::setFont(Font* font, const Color& color, float opacity, float scale)
{
	OpenGLFont* glFont = reinterpret_cast<OpenGLFont*>(font);
	bind(m_FontShader, glFont->m_Buffer);

	glUniformMatrix4fv(m_FontShader.uniform(0), 1, GL_FALSE, glm::value_ptr(m_OrthoProjection));
	glUniform4fv(m_FontShader.uniform(2), 1, color.values());
	glUniform1f(m_FontShader.uniform(3), opacity);
	glUniform1i(m_FontShader.uniform(4), 0);
	glActiveTexture(GL_TEXTURE0);
	m_CurrentFontTexture = 0;
	glBindTexture(GL_TEXTURE_2D, glFont->m_GLTextures[0]);

    m_FontScale = scale;
    m_CurrentFont = glFont;
}

void OpenGLRenderer::setFontColor(const Color& color, float opacity)
{
	glUniform4fv(m_FontShader.uniform(2), 1, color.values());
	glUniform1f(m_FontShader.uniform(3), opacity);
}

void OpenGLRenderer::drawGlyph(FontTexture::Glyph* glyph, float x, float y)
{
	if(glyph->BufferIndex == -1)
	{
		return;
	}

	if(m_CurrentFontTexture != glyph->TI)
	{
		m_CurrentFontTexture = glyph->TI;
	    glBindTexture(GL_TEXTURE_2D, m_CurrentFont->m_GLTextures[m_CurrentFontTexture]);
	}

	glm::mat4 world = glm::translate(glm::mat4(), glm::vec3(x, m_ViewportHeight-y-glyph->Height*m_FontScale, 0.0f));  
	if(m_FontScale != 1.0f)
	{
		world = glm::scale(world, glm::vec3(m_FontScale, m_FontScale, 1.0f)); 
	}

	glUniformMatrix4fv(m_FontShader.uniform(1), 1, GL_FALSE, glm::value_ptr(world));
	glDrawArrays(GL_TRIANGLE_STRIP, glyph->BufferIndex*4, 4);
}


void OpenGLRenderer::internalSetClip(Clip &clip)
{
	glEnable(GL_SCISSOR_TEST);
	glScissor(clip.x, m_ViewportHeight-clip.y-clip.h, clip.w < 0 ? 0 : clip.w, clip.h < 0 ? 0 : clip.h);
}

void OpenGLRenderer::internalClearClip()
{
	glDisable(GL_SCISSOR_TEST);
}

Font* OpenGLRenderer::makeFont(MemoryFile* file)
{
	OpenGLFont* font = new OpenGLFont();

	MemoryFileReader reader(file);

	int lineHeight = reader.readInt();
	int descender = reader.readInt();
	
	unsigned int numGlyphs = reader.readUnsignedInt();
	FontTexture::Glyph* glyphData = new FontTexture::Glyph[numGlyphs];

	for(unsigned int i = 0; i < numGlyphs; i++)
	{
		FontTexture::Glyph& glyph = glyphData[i];

		glyph.BufferIndex = -1;
		reader.read(glyph.Index);
		reader.read(glyph.Width);
		reader.read(glyph.Height);
		reader.read(glyph.HorizontalBearingX);
		reader.read(glyph.HorizontalBearingY);
		reader.read(glyph.HorizontalAdvance);
		reader.read(glyph.VerticalBearingX);
		reader.read(glyph.VerticalBearingY);
		reader.read(glyph.VerticalAdvance);
		reader.read(glyph.UTF8);

		reader.read(glyph.U);
		reader.read(glyph.V);
		reader.read(glyph.VS);
		reader.read(glyph.US);
		reader.read(glyph.TI);

		reader.read(glyph.KerningPairsCount);
		if(glyph.KerningPairsCount == 0)
		{
			glyph.KerningPairs = NULL;
		}
		else
		{
			glyph.KerningPairs = new FontTexture::Kern[glyph.KerningPairsCount];
			for(unsigned int j = 0; j < glyph.KerningPairsCount; j++)
			{
				FontTexture::Kern& kern = glyph.KerningPairs[j];
				reader.read(kern.UTF8);
				reader.read(kern.X);
				reader.read(kern.Y);
			}
		}
	}

	unsigned int numTextures = reader.readUnsignedInt();
	FontBitmap* bmps = new FontBitmap[numTextures];

	for(unsigned int i = 0; i < numTextures; i++)
	{
		FontBitmap& bmp = bmps[i];
		reader.read(bmp.width);
		reader.read(bmp.height);

		bmp.data = new unsigned char[bmp.width*bmp.height];
		memset(bmp.data, 0, bmp.width*bmp.height);


		unsigned int read = reader.read(bmp.data, bmp.width*bmp.height);
		if(read != bmp.width*bmp.height)
		{
			printf("OpenGLRenderer::makeFont - Failed to read texture dat.\n");
		}
	}

	FontTexture* fontTexture = font->m_Texture = new FontTexture(glyphData, numGlyphs, bmps, numTextures, lineHeight, descender);

	// Update m_GLTextures
	font->m_GLTextures = new unsigned int[fontTexture->numBitmaps()];
	glGenTextures(fontTexture->numBitmaps(), font->m_GLTextures);
	for(int i = 0; i < fontTexture->numBitmaps(); i++)
	{
	    glBindTexture(GL_TEXTURE_2D, font->m_GLTextures[i]);
	    
	    glTexImage2D(GL_TEXTURE_2D,
	                 0,
	                 GL_ALPHA,
	                 fontTexture->getWidth(i), fontTexture->getHeight(i),
	                 0,
	                 GL_ALPHA,
	                 GL_UNSIGNED_BYTE,
	                 fontTexture->getBytes(i));
	    
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	    
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	

	}

    int glyphCount = fontTexture->getGlyphCount();
	int glyphBufferCount = 0;
	
	FontTexture::Glyph* glyphs = fontTexture->getGlyphs();

	// Count number of valid glyphs that will go into the buffer.
	for(int i = 0; i < glyphCount; i++)
	{
		FontTexture::Glyph &glyph = glyphs[i];
		if(glyph.Width == 0 || glyph.Height == 0)
		{
			continue;
		}
		glyphBufferCount++;
	}

	int dataSize = glyphBufferCount * 16;
	float* data = new float[dataSize];
	int bufferIndex = 0;
	// Iterate and build the buffer.
	for(int i = 0; i < glyphCount; i++)
	{
		FontTexture::Glyph &glyph = glyphs[i];
		if(glyph.Width == 0 || glyph.Height == 0)
		{
			continue;
		}

		glyph.BufferIndex = bufferIndex;
		int baseIndex = bufferIndex * 16;
		bufferIndex++;

		data[baseIndex+4] = 0.0f;
		data[baseIndex+5] = 0.0f;
		data[baseIndex+6] = glyph.U;
		data[baseIndex+7] = glyph.V;
		

		data[baseIndex+0] = 0.0f;
		data[baseIndex+1] = glyph.Height;
		data[baseIndex+2] = glyph.U;
		data[baseIndex+3] = glyph.V + glyph.VS;

		data[baseIndex+12] = glyph.Width;
		data[baseIndex+13] = 0.0f;
		data[baseIndex+14] = glyph.U + glyph.US;
		data[baseIndex+15] = glyph.V;

		data[baseIndex+8] = glyph.Width;
		data[baseIndex+9] = glyph.Height;
		data[baseIndex+10] = glyph.U + glyph.US;
		data[baseIndex+11] = glyph.V + glyph.VS;
	}


	glBindBuffer(GL_ARRAY_BUFFER, font->m_Buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * dataSize, data, GL_STATIC_DRAW);


	// Clean up.
    delete [] data;
    fontTexture->deleteTextureData();
	return font;
}