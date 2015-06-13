#include "FontTexture.hpp"
#include <iostream>

using namespace splitcell::datgui;

FontTexture::FontTexture(Glyph* glyphs, unsigned int glyphCount, FontBitmap* maps, int mapCount, int lineHeight, int descender)
{
	m_Maps = maps;
	m_MapCount = mapCount;
	m_Descender = descender;
	m_LineHeight = lineHeight;
	m_Glyphs = glyphs;
	m_GlyphCount = glyphCount;

	unsigned int maxUTF8 = 0;

	int maxWidth = 0;
	int lastMaxWidth = 0;
	m_MaxBearingY = 0;
	m_MaxDescender = 0;

	for(unsigned int i = 0; i < glyphCount; i++)
	{
		Glyph& glyph = glyphs[i];

		if(glyph.HorizontalBearingY > m_MaxBearingY)
		{
			m_MaxBearingY = glyph.HorizontalBearingY;
		}
		if(glyph.Height-glyph.HorizontalBearingY > m_MaxDescender)
		{
			m_MaxDescender = glyph.Height-glyph.HorizontalBearingY;
		}
		if(glyph.HorizontalAdvance > maxWidth)
		{
			lastMaxWidth = maxWidth;
			maxWidth = glyph.HorizontalAdvance;
		}

		if(glyph.UTF8 > maxUTF8)
		{
			maxUTF8 = glyph.UTF8;
		}
	}

	if(lastMaxWidth == 0)
	{
		m_MonoSpacedAdvance = maxWidth;
	}


	if(maxUTF8 == 0)
	{
		m_UTF8 = NULL;
	}
	else
	{
		m_UTF8Count = maxUTF8+1;
		m_UTF8 = new Glyph*[m_UTF8Count];
		memset(m_UTF8, 0, m_UTF8Count*sizeof(Glyph*));
		for(unsigned int i = 0; i < glyphCount; i++)
		{
			m_UTF8[glyphs[i].UTF8] = &(glyphs[i]);
		}
	}
}

void FontTexture::deleteTextureData()
{
	if(m_Maps == NULL)
	{
		return;
	}
	for(int i = 0; i < m_MapCount; i++)
	{
		delete [] m_Maps[i].data;
	}
	delete [] m_Maps;
	m_Maps = NULL;
	m_MapCount = 0;
}

FontTexture::~FontTexture()
{
	deleteTextureData();
	delete [] m_Glyphs;
	delete [] m_UTF8;
}