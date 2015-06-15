#include "Text.hpp"

using namespace splitcell::datgui;

std::string Text::fromUTF8(UTF8 utf8)
{
	// 0xxxxxxx
	// 110xxxxx 10xxxxxx
	// 1110xxxx 10xxxxxx 10xxxxxx
	// 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
	// 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
	// 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
	std::string converted;

	// Get number of bytes needed to represent utf8.
	int bits = 1;
	UTF8 test = utf8;
	while(true)
	{
		test >>= 1;
		if(test == 0x00)
		{
			break;
		}
		bits++;
	}

	if(bits <= 7)
	{
		//bytesNeeded = 1;
		converted.append(1, (char)utf8);
	}
	else if(bits <= 11)
	{
		// 2 bytes
		unsigned char c = 0xC0 | (unsigned char)(utf8>>6); // 1110
		converted.append(1, (char)c);

		c = 0x80 | (unsigned char)(utf8&0x3F); // 1110
		converted.append(1, (char)c);
	}
	else if(bits <= 16)
	{
		// 3 bytes
		unsigned char c = 0xE0 | (unsigned char)(utf8>>12); // 1110
		converted.append(1, (char)c);

		c = 0x80 | (unsigned char)((utf8>>6)&0x3F); // 1110
		converted.append(1, (char)c);

		c = 0x80 | (unsigned char)(utf8&0x3F); // 1110
		converted.append(1, (char)c);
	}
	else if(bits <= 21)
	{
		// 4 bytes
		unsigned char c = 0xF0 | (unsigned char)(utf8>>18); // 1110
		converted.append(1, (char)c);

		c = 0x80 | (unsigned char)((utf8>>12)&0x3F); // 1110
		converted.append(1, (char)c);

		c = 0x80 | (unsigned char)((utf8>>6)&0x3F); // 1110
		converted.append(1, (char)c);

		c = 0x80 | (unsigned char)(utf8&0x3F); // 1110
		converted.append(1, (char)c);
	}
	else if(bits <= 26)
	{
		// 5 bytes
		unsigned char c = 0xF8 | (unsigned char)(utf8>>24); // 1110
		converted.append(1, (char)c);

		c = 0x80 | (unsigned char)((utf8>>18)&0x3F); // 1110
		converted.append(1, (char)c);

		c = 0x80 | (unsigned char)((utf8>>12)&0x3F); // 1110
		converted.append(1, (char)c);

		c = 0x80 | (unsigned char)((utf8>>6)&0x3F); // 1110
		converted.append(1, (char)c);

		c = 0x80 | (unsigned char)(utf8&0x3F); // 1110
		converted.append(1, (char)c);
	}
	else
	{
		// need 6 bytes
		unsigned char c = 0xFC | (unsigned char)(utf8>>30); // 1110
		converted.append(1, (char)c);

		c = 0x80 | (unsigned char)((utf8>>24)&0x3F); // 1110
		converted.append(1, (char)c);

		c = 0x80 | (unsigned char)((utf8>>18)&0x3F); // 1110
		converted.append(1, (char)c);

		c = 0x80 | (unsigned char)((utf8>>12)&0x3F); // 1110
		converted.append(1, (char)c);

		c = 0x80 | (unsigned char)((utf8>>6)&0x3F); // 1110
		converted.append(1, (char)c);

		c = 0x80 | (unsigned char)(utf8&0x3F); // 1110
		converted.append(1, (char)c);
	}
	return converted;
}

TextLayout Text::layout(Font* font, const char* originalText, TextBounds availableSize, float xOffset)
{
	// Layout needs to conver the entire buffer to UTF8...
	TextLayout txtLayout(xOffset);

	while(true)
	{
		UTF8 t = nextUTF8(originalText);
		txtLayout.text.push_back(t);
		if(t == '\0')
		{
			break;
		}
	}
	if(txtLayout.text.empty())
	{
		return txtLayout;
	}

	UTF8* text = &txtLayout.text[0];
	std::vector<int>& breaks = txtLayout.breaks;

	float maxWidth = availableSize.width;
//		    float maxHeight = availableSize.height;
    int maxLines = availableSize.lines;

    float x = xOffset;
    bool hasEllipsis = false;
    float top = 0.0f;

    UTF8* end = NULL;

    UTF8* wordIndex = text;
    int wordWidth = 0;
    float maxLineWidth = 0;

    UTF8* current;
    for(current = text; *current != '\0'; current++)
    {
    	UTF8 c = *current;
    	bool isWhiteSpace = false;
    	switch(c)
    	{
    		case 32:	// Space
    		case 9:	 	// Tab
    			c = 32;

    			wordIndex = current+1;
    			wordWidth = 0;
    			isWhiteSpace = true;
    			break;
    		case '\n':
    			wordIndex = current+1;
    			wordWidth = 0;
    			isWhiteSpace = true;
    			x = 0;
    			breaks.push_back((int)(current-text));
    			break;
    	}

    	FontTexture::Glyph* glyph = font->getGlyph(c);
    	if(glyph == NULL)
    	{
    		continue;
    	}

    	x += glyph->HorizontalAdvance;
    	//if(!isWhiteSpace)
    	{
    		wordWidth += glyph->HorizontalAdvance;

    		if(x > maxWidth)
    		{
    			if(breaks.size() == (size_t)(maxLines-1))
    			{
    				int sub = 3;
    				UTF8* idx = current-sub-1;
    				if(idx > text)
    				{
    					// Keep going back until we find a word (remove all final punct)
    					while(idx > text)
    					{
    						UTF8 sc = *idx;
    						switch(sc)
    						{
    							// White space and symbols.
								case 0x21: //!
								case 0x22: //"
								case 0x23: //#
								case 0x24: //$
								case 0x25: //%
								case 0x26: //&
								case 0x27: //'
								case 0x28: //(
								case 0x29: //)
								case 0x2a: //*
								case 0x2b: //+
								case 0x2c: //,
								case 0x2d: //-
								case 0x2e: //.
								case 0x2f: ///

								case 0x3a: //:
								case 0x3b: //;
								case 0x3c: //<
								case 0x3d: //=
								case 0x3e: //>
								case 0x3f: //?
								case 0x40: //@

								case 0x5b: //[
								case 0x5c: //\ backslash
								case 0x5d: //]
								case 0x5e: //^
								case 0x5f: //_
								case 0x60: //`

								case 0x7b: //{
								case 0x7c: //|
								case 0x7d: //}
								case 0x7e: //~

								case 32:
								case 9:
									sub++;
									idx = current-sub-1;
									break;

								default:
									// Break condition.
									idx = text;
									break;
    						}
    					}

    					if(sub == 3)
						{
							int preSub = sub;

							// Cut off any word that was truncated.
							idx = current-sub-1;
							while(idx > text)
							{
								UTF8 sc = *idx;
								switch(sc)
								{
									case 0x21: //!
									case 0x22: //"
									case 0x23: //#
									case 0x24: //$
									case 0x25: //%
									case 0x26: //&
									case 0x27: //'
									case 0x28: //(
									case 0x29: //)
									case 0x2a: //*
									case 0x2b: //+
									case 0x2c: //,
									case 0x2d: //-
									case 0x2e: //.
									case 0x2f: ///

									case 0x3a: //:
									case 0x3b: //;
									case 0x3c: //<
									case 0x3d: //=
									case 0x3e: //>
									case 0x3f: //?
									case 0x40: //@

									case 0x5b: //[
									case 0x5c: //\ backslash
									case 0x5d: //]
									case 0x5e: //^
									case 0x5f: //_
									case 0x60: //`

									case 0x7b: //{
									case 0x7c: //|
									case 0x7d: //}
									case 0x7e: //~

									case 32:
									case 9:
										// Break condition.
										idx = text;
										break;

									default:
										sub++;
										idx = current-sub-1;
										break;
								}
							}

							// Cut off white space or punctuation.
							idx = current-sub-1;
							while(idx > text)
							{
								UTF8 sc = *idx;
								switch(sc)
								{
									case 0x21: //!
									case 0x22: //"
									case 0x23: //#
									case 0x24: //$
									case 0x25: //%
									case 0x26: //&
									case 0x27: //'
									case 0x28: //(
									case 0x29: //)
									case 0x2a: //*
									case 0x2b: //+
									case 0x2c: //,
									case 0x2d: //-
									case 0x2e: //.
									case 0x2f: ///

									case 0x3a: //:
									case 0x3b: //;
									case 0x3c: //<
									case 0x3d: //=
									case 0x3e: //>
									case 0x3f: //?
									case 0x40: //@

									case 0x5b: //[
									case 0x5c: //\ backslash
									case 0x5d: //]
									case 0x5e: //^
									case 0x5f: //_
									case 0x60: //`

									case 0x7b: //{
									case 0x7c: //|
									case 0x7d: //}
									case 0x7e: //~

									case 32:
									case 9:
										sub++;
										idx = current-sub-1;
										break;

									default:
										// Break condition.
										idx = text;
										break;	
								}
							}

							// make sure the whole word we found isn't before the end of the previous line
							if(breaks.size() != 0 && (current-sub)-text <= breaks[breaks.size()-1])
							{
								sub = preSub;
							}
						}
						else if(breaks.size() != 0 && (current-sub)-text <= breaks[breaks.size()-1])
						{
							sub = 3;
						}

						hasEllipsis = true;
						end = current-sub;
    				}
    				break;
    			}
    			else if(wordWidth > maxWidth)
    			{
    				breaks.push_back(current-text);
    				x = glyph->HorizontalAdvance;
    			}
    			else
    			{
    				breaks.push_back(wordIndex-text);
    				x = wordWidth;
    			}
    		}
    		else
    		{
    			if(x > maxLineWidth)
    			{
    				maxLineWidth = x;
    			}
    		}
    	}
    }
    if(!hasEllipsis)
    {
    	end = current;
    }

    current = text;
    
	int firstBreak = breaks.size() > 0 ? breaks[0] : end-text;
    for(int i = 0; i < firstBreak; i++)
    {
    	UTF8 c = *current;
    	current++;

    	FontTexture::Glyph* glyph = font->getGlyph(c);
    	if(glyph == NULL)
    	{
    		continue;
    	}

    	if(glyph->HorizontalBearingY > top)
    	{
    		top = glyph->HorizontalBearingY;
    	}
    }

    /*
    int lastBreak = breaks[breaks.size()-1];
    int len = end-text;
    current = text[lastBreak];
    for(int i = lastBreak; i < len; i++)
    {
    	char c = *current;
    	current++;

    	FontTexture::Glyph* glyph = font->getGlyph(c);
    	if(glyph == NULL)
    	{
    		continue;
    	}

    	if(glyph->HorizontalBearingY > top)
    	{
    		top = glyph->HorizontalBearingY;
    	}
    }*/

	maxLineWidth = 0.0f;
	int index = 0;
	x = 0;
	std::vector<int>::iterator breakItr = breaks.begin();
	bool isLastLine = false;
	float bottom = 0.0f;
	float lastTop = 0.0f;

	if(breakItr == breaks.end())
	{
		isLastLine = true;
	}
	for(UTF8* t = text; *t != '\0' && t < end; t++)
    {
    	if(breakItr != breaks.end())
        {
        	if(*breakItr == index)
        	{
        		x = 0;
        		breakItr++;
        		isLastLine = breakItr == breaks.end();
        	}
        }

        FontTexture::Glyph* glyph = font->getGlyph(*t);
        if(glyph != NULL)
        {
            x += glyph->HorizontalAdvance;
            if(x > maxLineWidth)
            {
            	maxLineWidth = x;
            }
            if(isLastLine)
            {
            	if(glyph->HorizontalBearingY > lastTop)
	        	{
	        		lastTop = glyph->HorizontalBearingY;
	        	}
            	float b = glyph->Height - glyph->HorizontalBearingY;
	        	if(b > bottom)
	        	{
	        		bottom = b;
	        	}
            }
        }
        index++;
    }

    if(hasEllipsis)
    {
    	FontTexture::Glyph* glyph = font->getGlyph('.');
        if(glyph != NULL)
        {
        	for(int i = 0; i < 3; i++)
        	{
            	x += glyph->HorizontalAdvance;
            }
            if(x > maxLineWidth)
            {
            	maxLineWidth = x;
            }
        }
    }
    
    txtLayout.maxAscender = top;
    txtLayout.hasEllipsis = hasEllipsis;
    txtLayout.width = maxLineWidth;
	txtLayout.height = (breaks.size())*font->getLineHeight()+lastTop+bottom;//-font->getDescender();

    txtLayout.text.erase(txtLayout.text.begin()+(end-text)+1, txtLayout.text.end());// = std::string(text, );
    *(txtLayout.text.end()-1) = '\0';

	return txtLayout;
}