#ifndef _SPLITCELL_DATGUI_GLRENDERER_HPP_
#define _SPLITCELL_DATGUI_GLRENDERER_HPP_

#ifndef _SPLITCELL_DATGUI_RENDERER_HPP_
#include "Renderer.hpp"
#endif

#ifndef _SPLITCELL_DATGUI_SHADERPROGRAM_HPP_
#include "ShaderProgram.hpp"
#endif

#include <glm/glm.hpp>

namespace splitcell
{
      namespace datgui
      {
            class OpenGLRenderer;
            class OpenGLFont : public Font
            {
                  friend class OpenGLRenderer;

                  private:
                        unsigned int m_Buffer;
                        FontTexture* m_Texture;
                        unsigned int* m_GLTextures;

                        OpenGLFont();
                        ~OpenGLFont();

                  public:

                        bool isLoaded()
                        {
                            return m_Buffer != 0;
                        }
                        
                        FontTexture::Glyph* getGlyph(unsigned int utf8)
                        {
                            return m_Texture->getGlyph(utf8);
                        }

                        int getMaxBearingY()
                        {
                            return m_Texture->getMaxBearingY();
                        }
                    
                        int getMaxDescender()
                        {
                            return m_Texture->getMaxDescender();
                        }
                        
                        int getDescender()
                        {
                            return m_Texture->getDescender();
                        }

                        int getLineHeight()
                        {
                            return m_Texture->getLineHeight();
                        }

                        bool isMonoSpaced()
                        {
                            return m_Texture->isMonoSpaced();
                        }

                        int monoSpacedAdvance()
                        {
                            return m_Texture->monoSpacedAdvance();
                        }
            };

      	class OpenGLRenderer : public Renderer
      	{
              private:
                  unsigned int m_ScreenWidth;
                  unsigned int m_ScreenHeight;

                  int m_ViewportX;
                  int m_ViewportY;
                  unsigned int m_ViewportWidth;
                  unsigned int m_ViewportHeight;
                  float m_ViewportWidthRatio;
                  float m_ViewportHeightRatio;

                  glm::mat4 m_OrthoProjection;

                  unsigned int m_Rect;

                  ShaderProgram* m_LastBoundShader;
                  unsigned int m_LastBoundVertexBuffer;

                  ShaderProgram m_ColorShader;
                  ShaderProgram m_FontShader;

                  glm::mat4 m_FontTransform;
                  float m_FontScale;
                  OpenGLFont* m_CurrentFont;
                  unsigned int m_CurrentFontTexture;

                  unsigned char m_WasBlending;
                  unsigned char m_HadDepthWrites;
                  int m_LastSFactor;
                  int m_LastDFactor;
                  
                  void setViewport(int x, int y, unsigned int width, unsigned int height);

              public:
                  OpenGLRenderer();
                  ~OpenGLRenderer();
                  
                  bool initialize();
                  void setScreenSize(unsigned int width, unsigned int height);
                  void drawRect(float x, float y, float width, float height, const Color& color, float opacity = 1.0f);

                  bool bind(ShaderProgram& program, unsigned int buffer);

                  unsigned int screenWidth() { return m_ScreenWidth; }
                  unsigned int screenHeight() { return m_ScreenHeight; }

                  int viewportX() { return m_ViewportX; }
                  int viewportY() { return m_ViewportY; }
                  unsigned int viewportWidth() { return m_ViewportWidth; }
                  unsigned int viewportHeight() { return m_ViewportHeight; }

                  // Font related methods.
                  void setFont(Font* font, const Color& color, float opacity = 1.0f, float scale = 1.0f);
                  void setFontColor(const Color& color, float opacity = 1.0f);
                  void drawGlyph(FontTexture::Glyph* glyph, float x, float y);
                  Font* makeFont(MemoryFile* file);
                  
                  void enableBlending();
                  void enableDepthWrite();
                  void disableDepthWrite();
                  void enableAdditiveBlending();
                  void disableBlending();
                  void enableDepthTest();
                  void disableDepthTest();
                  void pushState();
                  void popState();

            private:
                  void internalSetClip(Clip &clip);
                  void internalClearClip();
      	};
      }
}
#endif