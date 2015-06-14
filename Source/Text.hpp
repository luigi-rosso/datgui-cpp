#ifndef _SPLITCELL_DATGUI_TEXT_H_
#define _SPLITCELL_DATGUI_TEXT_H_

#ifndef _SPLITCELL_DATGUI_RENDERER_HPP_
#include "Renderer.hpp"
#endif

#ifndef _SPLITCELL_DATGUI_SIZE_HPP_
#include "Size.hpp"
#endif

namespace splitcell
{
	namespace datgui
	{
		struct TextSize : public Size
		{
			float maxAscender;
			float maxDescender;

			TextSize() : maxAscender(0.0f), maxDescender(0.0f) {}
		};

		struct TextLayout : public TextSize
		{
			std::vector<unsigned int> text;
			std::vector<int> breaks;
			bool hasEllipsis;
			float xOffset;
			TextLayout(float xo=0.0f) : xOffset(xo){}
		};

		struct TextBounds : public Size
		{
			int lines;

			TextBounds() : lines(0) {}
			TextBounds(float w, float h) : Size(w, h) {}
			TextBounds(float w, float h, int l) : Size(w, h), lines(l) {}
		};

		struct Text
		{
			inline static float draw(Renderer* renderer, Font* font, float x, float y, TextLayout& layout, const Color& color, float opacity = 1.0f, float scale = 1.0f)
			{
				if(layout.text.empty())
				{
					return y;
				}
				unsigned int* text = &layout.text[0];
				renderer->setFont(font, color, opacity, scale);

				std::vector<int>::iterator breakItr = layout.breaks.begin();
				std::vector<int>& breaks = layout.breaks;

				int index = 0;
				float originX = x;
				x += layout.xOffset;

				for(unsigned int* t = text; *t != '\0'; t++)
			    {
			    	if(breakItr != breaks.end())
			        {
			        	if(*breakItr == index)
			        	{
			        		x = originX;
			        		y += font->getLineHeight() * scale;
			        		breakItr++;
			        	}
			        }

			        FontTexture::Glyph* glyph = font->getGlyph(*t);
			        if(glyph != NULL)
			        {
			            renderer->drawGlyph(glyph, x+glyph->HorizontalBearingX*scale, y-glyph->HorizontalBearingY*scale);
			            x += glyph->HorizontalAdvance*scale;
			        }
			        index++;
			    }

			    if(layout.hasEllipsis)
			    {
			    	FontTexture::Glyph* glyph = font->getGlyph('.');
			        if(glyph != NULL)
			        {
			        	for(int i = 0; i < 3; i++)
			        	{
			        		renderer->drawGlyph(glyph, x+glyph->HorizontalBearingX*scale, y-glyph->HorizontalBearingY*scale);
			            	x += glyph->HorizontalAdvance*scale;
			            }
			        }
			    }

			    return y;
			}

			inline static float drawCentered(Renderer* renderer, Font* font, float x, float y, TextLayout& layout, const Color& color, float opacity = 1.0f, float scale = 1.0f)
			{
				if(layout.text.empty())
				{
					return y;
				}
				unsigned int* text = &layout.text[0];
				renderer->setFont(font, color, opacity, scale);

				std::vector<int>::iterator breakItr = layout.breaks.begin();
				std::vector<int>& breaks = layout.breaks;

				int index = 0;
				float originX = x;
				x += layout.xOffset;

				std::vector<float> lineWidths;
				float lw = 0.0f;
				for(unsigned int* t = text; *t != '\0'; t++)
			    {
			    	if(breakItr != breaks.end())
			        {
			        	if(*breakItr == index)
			        	{
			        		lineWidths.emplace_back(lw);
			        		lw = 0.0f;
			        		breakItr++;
			        	}
			        }

			        FontTexture::Glyph* glyph = font->getGlyph(*t);
			        if(glyph != NULL)
			        {
			            lw += glyph->HorizontalAdvance*scale;
			        }
			        index++;
			    }
			    lineWidths.emplace_back(lw);

			    index = 0;
			    breakItr = layout.breaks.begin();

			    std::vector<float>::iterator widthItr = lineWidths.begin();
			    lw = *widthItr;
			    x = originX + layout.width/2.0f - lw/2.0f;

				for(unsigned int* t = text; *t != '\0'; t++)
			    {
			    	if(breakItr != breaks.end())
			        {
			        	if(*breakItr == index)
			        	{
			        		widthItr++;
			        		lw = *widthItr;
			        		x = originX + layout.width/2.0f - lw/2.0f;
			        		y += font->getLineHeight() * scale;
			        		breakItr++;
			        	}
			        }

			        FontTexture::Glyph* glyph = font->getGlyph(*t);
			        if(glyph != NULL)
			        {
			            renderer->drawGlyph(glyph, x+glyph->HorizontalBearingX*scale, y-glyph->HorizontalBearingY*scale);
			            x += glyph->HorizontalAdvance*scale;
			        }
			        index++;
			    }

			    if(layout.hasEllipsis)
			    {
			    	FontTexture::Glyph* glyph = font->getGlyph('.');
			        if(glyph != NULL)
			        {
			        	for(int i = 0; i < 3; i++)
			        	{
			        		renderer->drawGlyph(glyph, x+glyph->HorizontalBearingX*scale, y-glyph->HorizontalBearingY*scale);
			            	x += glyph->HorizontalAdvance*scale;
			            }
			        }
			    }

			    return y;
			}


			inline static unsigned int nextUTF8(const char*& text)
			{
				unsigned int c = *text;
				// 0xxxxxxx
				// 110xxxxx 10xxxxxx
				// 1110xxxx 10xxxxxx 10xxxxxx
				// 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
				// 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
				// 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx

				if((c&(1<<7)) != 0)
				{
					int bit = 6;
					do
					{
						if((c&(1<<bit)) == 0)
						{
							break;
						}
						bit--;
					}while(bit > 1);

					int bytes = 7-bit;
					switch(bytes)
					{
						case 2:
							c = ((c & (1 | (1<<1) | (1<<2) | (1<<3) | (1<<4))) << 6) | 
								 (text[1] & (1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5)));
							break;
						case 3:
							c = ((c & (1 | (1<<1) | (1<<2) | (1<<3))) << 12) | 
								((text[1] & (1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5))) << 6) | 
								 (text[2] & (1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5)));
							break;
						case 4:
							c = ((c & (1 | (1<<1) | (1<<2))) << 18) | 
								((text[1] & (1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5))) << 12) | 
								((text[2] & (1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5))) << 6) | 
								 (text[3] & (1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5)));
							break;
						case 5:
							c = ((c & (1 | (1<<1))) << 24) | 
								((text[1] & (1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5))) << 18) | 
								((text[2] & (1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5))) << 12) | 
								((text[3] & (1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5))) << 6) | 
								 (text[4] & (1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5)));
							break;
						case 6:
							c = ((c & 1) << 30) | 
								((text[1] & (1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5))) << 24) | 
								((text[2] & (1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5))) << 18) | 
								((text[3] & (1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5))) << 12) | 
								((text[4] & (1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5))) << 6) | 
								 (text[5] & (1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5)));
							break;
					}
					text += bytes;
				}
				else
				{
					text++;
				}
				return c;
			}

			inline static float draw(Renderer* renderer, Font* font, float x, float y, const char* text, const Color& color, float opacity = 1.0f, float scale = 1.0f)
			{
				renderer->setFont(font, color, opacity, scale);
				
				while(true)
				{
					unsigned int t = nextUTF8(text);
					if(t == '\0')
					{
						break;
					}

					FontTexture::Glyph* glyph = font->getGlyph(t);
			        if(glyph != NULL)
			        {
			            renderer->drawGlyph(glyph, x+glyph->HorizontalBearingX*scale, y-glyph->HorizontalBearingY*scale);
			            x += glyph->HorizontalAdvance*scale;
			        }
				}

			    return x;
			}

			inline static float draw(Renderer* renderer, Font* font, float x, float y, unsigned int t, const Color& color, float opacity = 1.0f, float scale = 1.0f)
			{
				renderer->setFont(font, color, opacity, scale);
				
				FontTexture::Glyph* glyph = font->getGlyph(t);
				if(glyph != NULL)
				{
				    renderer->drawGlyph(glyph, x+glyph->HorizontalBearingX*scale, y-glyph->HorizontalBearingY*scale);
				    x += glyph->HorizontalAdvance*scale;
				}

			    return x;
			}

			inline static TextSize measure(Font* font, const char* text)
			{
				TextSize size;

				float top = 0.0f;
				float bottom = 0.0f;
				float x = 0.0f;

				while(true)
				{
					unsigned int t = nextUTF8(text);
					if(t == '\0')
					{
						break;
					}
			        FontTexture::Glyph* glyph = font->getGlyph(t);
			        if(glyph != NULL)
			        {
			        	if(glyph->HorizontalBearingY > top)
			        	{
			        		top = glyph->HorizontalBearingY;
			        	}
			        	float b = glyph->Height - glyph->HorizontalBearingY;
			        	if(b > bottom)
			        	{
			        		bottom = b;
			        	}
			            //renderer->drawGlyph(glyph, x+glyph->HorizontalBearingX*scale, y-glyph->HorizontalBearingY*scale);
			            x += glyph->HorizontalAdvance;
			        }
			    }

			    size.width = x;
			    size.height = top+bottom;
			    size.maxAscender = top;
			    size.maxDescender = bottom;

			    return size;
			}

			inline static TextSize measure(Font* font, unsigned int t)
			{
				TextSize size;

				float top = 0.0f;
				float bottom = 0.0f;
				float x = 0.0f;

				FontTexture::Glyph* glyph = font->getGlyph(t);
				if(glyph != NULL)
				{
					if(glyph->HorizontalBearingY > top)
					{
						top = glyph->HorizontalBearingY;
					}
					float b = glyph->Height - glyph->HorizontalBearingY;
					if(b > bottom)
					{
						bottom = b;
					}
				    x += glyph->HorizontalAdvance;
				}

			    size.width = x;
			    size.height = top+bottom;
			    size.maxAscender = top;
			    size.maxDescender = bottom;

			    return size;
			}

			static TextLayout layout(Font* font, const char* originalText, TextBounds availableSize, float xOffset = 0.0f);
		};
	}
}

#endif
