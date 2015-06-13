#ifndef _SPLITCELL_DATGUI_FONTTEXTURE_HPP_
#define _SPLITCELL_DATGUI_FONTTEXTURE_HPP_

namespace splitcell
{
	namespace datgui
	{
		struct FontBitmap
		{
			unsigned char* data;
			unsigned int width;
			unsigned int height;
		};

		class FontTexture
		{
			public:
				struct Kern
				{
					unsigned int UTF8;
					int X;
					int Y;
				};

				struct Glyph
				{
					int Index;
					int BufferIndex;
					int Width;
					int Height;
					int HorizontalBearingX;
					int HorizontalBearingY;
					int HorizontalAdvance;
					int VerticalBearingX;
					int VerticalBearingY;
					int VerticalAdvance;
					unsigned int UTF8;

					float U;
					float V;
					float US;
					float VS;
					int TI;

					Kern* KerningPairs;
					unsigned int KerningPairsCount;
				};

			private:
				Glyph* m_Glyphs;
				Glyph** m_UTF8;
				unsigned int m_GlyphCount;
				unsigned int m_UTF8Count;
				int m_MonoSpacedAdvance;

				FontBitmap* m_Maps;
				unsigned int m_MapCount;

				int m_LineHeight;
				int m_Descender;
				int m_MaxBearingY;
				int m_MaxDescender;

			public:
				FontTexture(Glyph* glyphs, unsigned int glyphCount, FontBitmap* maps, int mapCount, int lineHeight, int descender);
				~FontTexture();

				inline int getDescender()
				{
					return m_Descender;
				}
				
				inline int getLineHeight()
				{
					return m_LineHeight;
				}

				inline int getMaxBearingY()
				{
					return m_MaxBearingY;
				}

				inline int getMaxDescender()
				{
					return m_MaxDescender;
				}

				inline Glyph* getGlyphs()
				{
					return m_Glyphs;
				}

				inline Glyph* getGlyph(unsigned int utf8)
				{
					return utf8 < m_UTF8Count ? m_UTF8[utf8] : 0;
				}

				inline int getGlyphCount()
				{
					return m_GlyphCount;
				}

				inline unsigned int numBitmaps()
				{
					return m_MapCount;
				}


				inline unsigned int getWidth(int idx)
				{
					return m_Maps[idx].width;
				}

				inline unsigned int getHeight(int idx)
				{
					return m_Maps[idx].height;
				}

				inline unsigned char* getBytes(int idx)
				{
					return m_Maps[idx].data;
				}

				inline bool isMonoSpaced()
				{
					return m_MonoSpacedAdvance != 0;
				}

				inline int monoSpacedAdvance()
				{
					return m_MonoSpacedAdvance;
				}

				void deleteTextureData();
		};
	}
}
#endif