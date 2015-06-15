#ifndef _SPLITCELL_DATGUI_RENDERER_HPP_
#define _SPLITCELL_DATGUI_RENDERER_HPP_

#ifndef _SPLITCELL_DATGUI_FONTTEXTURE_HPP_
#include "FontTexture.hpp"
#endif

#ifndef _SPLITCELL_DATGUI_COLOR_HPP_
#include "Color.hpp"
#endif

#ifndef _SPLITCELL_DATGUI_MEMORYFILE_HPP_
#include "MemoryFile.hpp"
#endif

#include <vector>

namespace splitcell
{
	namespace datgui
	{
		class Font
		{
			public:
				virtual ~Font(){}
				virtual FontTexture::Glyph* getGlyph(unsigned int utf8) = 0;
				virtual int getMaxBearingY() = 0;
				virtual int getMaxDescender() = 0;
				virtual int getDescender() = 0;
				virtual int getLineHeight() = 0;
				virtual bool isMonoSpaced() = 0;
				virtual int monoSpacedAdvance() = 0;
		};

		class Renderer
		{
			public:
				virtual ~Renderer() {}
				virtual bool initialize() = 0;
				virtual void setScreenSize(unsigned int width, unsigned int height) = 0;
				virtual void drawRect(float x, float y, float width, float height, const Color& color, float opacity = 1.0f) = 0;

				virtual void setFont(Font* font, const Color& color, float opacity = 1.0f, float scale = 1.0f) = 0;
                virtual void setFontColor(const Color& color, float opacity = 1.0f) = 0;
                virtual void drawGlyph(FontTexture::Glyph* glyph, float x, float y) = 0;
                virtual Font* makeFont(MemoryFile* file) = 0;

				virtual void enableBlending() = 0;
				virtual void enableAdditiveBlending() = 0;
				virtual void disableBlending() = 0;
				virtual void enableDepthTest() = 0;
				virtual void disableDepthTest() = 0;
				virtual void enableDepthWrite() = 0;
				virtual void disableDepthWrite() = 0;

				virtual unsigned int screenWidth() = 0;
				virtual unsigned int screenHeight() = 0;

				virtual void pushState() = 0;
				virtual void popState() = 0;

            public:
				struct Clip
				{
				    int x, y, w, h;
				    Clip(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {}
				    Clip() : x(0), y(0), w(0), h(0) {}
				};

                std::vector<Clip> m_Clips;
                virtual void internalSetClip(Clip &clip) = 0;
                virtual void internalClearClip() = 0;

				void setClip(int x, int y, int w, int h)
				{
				    m_Clips.clear();

				    Clip clip(x,y,w,h);
				    m_Clips.push_back(clip);
				    internalSetClip(clip);
				}

				void pushClip(int x, int y, int w, int h)
				{
				    if(m_Clips.empty())
				    {
				          m_Clips.push_back(Clip(0,0,screenWidth(),screenHeight()));
				    }
				    Clip& lastClip = m_Clips[m_Clips.size()-1];
				    Clip clip;
				    if(lastClip.x > x)
				    {
				          clip.x = lastClip.x;
				    }
				    else
				    {
				          clip.x = x;
				    }

				    if(lastClip.y > y)
				    {
				          clip.y = lastClip.y;
				    }
				    else
				    {
				          clip.y = y;
				    }

				    if(lastClip.x+lastClip.w < x+w)
				    {
				          clip.w = (lastClip.x+lastClip.w)-x;
				    }
				    else
				    {
				          clip.w = (x+w)-x;
				    }

				    if(lastClip.y+lastClip.h < y+h)
				    {
				          clip.h = (lastClip.y+lastClip.h)-y;
				    }
				    else
				    {
				          clip.h = (y+h)-y;
				    }
				    m_Clips.push_back(clip);
				    internalSetClip(clip);
				}

				void popClip()
				{
					int cs = m_Clips.size();
				    if(cs < 2)
				    {
				          return;
				    }
				    else if(cs == 2)
				    {
				    	clearClip();
				    	return;
				    }
				    m_Clips.erase(m_Clips.end()-1);
				    Clip& lastClip = m_Clips[m_Clips.size()-1];
				    internalSetClip(lastClip);
				}

				void clearClip()
				{
				    m_Clips.clear();
				    internalClearClip();
				}
		};
	}
}
#endif