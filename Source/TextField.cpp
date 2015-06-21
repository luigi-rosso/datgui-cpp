#include "TextField.hpp"
#include "Text.hpp"
#include "Gui.hpp"
#include <cmath>

using namespace splitcell::datgui;

static const float TextPad = 2.0f;

TextField::TextField() : m_Data(NULL), m_Offset(0.0f), m_SelectedIndex(0), m_IsDraggingCursor(false), m_SelectionStartIndex(-1), m_SelectionEndIndex(-1), m_MouseDownSeconds(0.0f), m_IsShiftPressed(false), m_DragLastY(0)
{

}

void TextField::setData(DatGui::Text* data)
{
	m_Data = data;
	if(m_Data != NULL)
	{
		m_TextCache = m_Data->get();
	}
}

void TextField::draw(Renderer* renderer)
{
	// TODO: Track if user changed data.

	float cursorWidth = 1.0f;
	float cursorHeight = (float)round(height() * 0.75f);

	renderer->drawRect(x(), y(), width(), height(), BackgroundColor);

	float startX = x() + m_Offset + TextPad;
	renderer->pushClip(x(), y(), width(), height());
	
	const char* val_c = m_TextCache.c_str();
	float cursorY = (float)round(y() + height()/2.0f - cursorHeight/2.0f);

	float discardIntPart;
	float cursorOpacity = std::modf(Gui::elapsedSeconds() - m_MouseDownSeconds, &discardIntPart);

	if(cursorOpacity > 0.5f)
	{
		cursorOpacity = 1.0f - (cursorOpacity-0.5f) * 2.0f;
	}
	else
	{
		cursorOpacity *= 2.0f;
	}
	cursorOpacity = std::pow(cursorOpacity, 0.75f);

	if(m_SelectionStartIndex != -1 && isFocused())
	{
		TextSize startMeasure = Text::measure(Gui::font(), val_c, m_SelectionStartIndex);
		TextSize endMeasure = Text::measure(Gui::font(), val_c, m_SelectionEndIndex);
		if(m_SelectionEndIndex > m_SelectionStartIndex)
		{
			renderer->drawRect(startX+startMeasure.width, cursorY, endMeasure.width-startMeasure.width, cursorHeight, Color(0, 150, 255, 200));
		}
		else
		{
			renderer->drawRect(startX+endMeasure.width, cursorY, startMeasure.width-endMeasure.width, cursorHeight, Color(0, 150, 255, 200));
		}
	}
	
	Text::draw(renderer, Gui::font(), startX, (float)round(y() + height() - Padding), val_c, isFocused() ? Color(1.0f) : accentColor());

	if(isFocused())
	{
		TextSize cursorDimensions = Text::measure(Gui::font(), val_c, m_SelectedIndex);
		renderer->drawRect(startX + cursorDimensions.width, cursorY, cursorWidth, cursorHeight, Color(1.0f), cursorOpacity);
	}
	renderer->popClip();
}

bool TextField::onMouseDown(int x, int y)
{
	Gui::focus(this);

	Gui::captureMouse(this);
	m_IsDraggingCursor = true;
	m_DragLastY = y;
	float ds = Gui::elapsedSeconds()-0.5f;
	bool selectAll = false;
	if((ds - m_MouseDownSeconds) < 0.25f)
	{
		selectAll = true;
	}
	m_MouseDownSeconds = ds;

	if(selectAll)
	{
		m_SelectedIndex = m_TextCache.size();
		m_SelectionStartIndex = 0;
		m_SelectionEndIndex = m_SelectedIndex;
	}
	else
	{
		float startX = m_Offset + 2;
		m_SelectedIndex = Text::characterIndex(Gui::font(), m_TextCache.c_str(), x - startX);
		m_SelectionStartIndex = m_SelectionEndIndex = -1;
	}
	return true;
}

bool TextField::onMouseUp(int x, int y)
{
	m_IsDraggingCursor = false;
	return false;
}

void TextField::setDragCallback(std::function<void(int)> callback)
{
	m_DragCallback = callback;
}

bool TextField::onMouseMove(int x, int y)
{
	if(m_IsDraggingCursor)
	{
		if(m_DragCallback != NULL)
		{
			m_DragCallback(y - m_DragLastY);
			m_DragLastY = y;
		}

		m_MouseDownSeconds = Gui::elapsedSeconds()-0.5f;
		float startX = m_Offset + 2;
		int nextSelectedIndex = Text::characterIndex(Gui::font(), m_TextCache.c_str(), x - startX);
		if(m_SelectionStartIndex == -1 && m_SelectedIndex != nextSelectedIndex)
		{
			m_SelectionStartIndex = m_SelectedIndex;
		}
		
		if(m_SelectionStartIndex != -1)
		{
			m_SelectionEndIndex = nextSelectedIndex;
		}
		m_SelectedIndex = nextSelectedIndex;
		
		ensureCursorVisible();
		return true;
	}
	return false;
}

bool TextField::onKeyDown(Keyboard::Key key)
{
	if(m_Data == NULL)
	{
		return false;
	}
	switch(key)
	{
		case Keyboard::LShift:
		case Keyboard::RShift:
			m_IsShiftPressed = true;
			return true;
		case Keyboard::Left:
		{
			int nextSelectedIndex = std::max(0, std::min((int)m_Data->get().size(), m_SelectedIndex - 1));

			if(m_IsShiftPressed)
			{
				if(m_SelectionStartIndex == -1 && m_SelectedIndex != nextSelectedIndex)
				{
					m_SelectionStartIndex = m_SelectedIndex;
				}
				
				if(m_SelectionStartIndex != -1)
				{
					m_SelectionEndIndex = nextSelectedIndex;
				}
			}
			else
			{
				m_SelectionStartIndex = m_SelectionEndIndex = -1;
			}
			m_SelectedIndex = nextSelectedIndex;
			
			ensureCursorVisible();
			return true;
		}
		case Keyboard::Right:
		{
			int nextSelectedIndex = std::max(0, std::min((int)m_Data->get().size(), m_SelectedIndex + 1));
			if(m_IsShiftPressed)
			{
				if(m_SelectionStartIndex == -1 && m_SelectedIndex != nextSelectedIndex)
				{
					m_SelectionStartIndex = m_SelectedIndex;
				}
				
				if(m_SelectionStartIndex != -1)
				{
					m_SelectionEndIndex = nextSelectedIndex;
				}
			}
			else
			{
				m_SelectionStartIndex = m_SelectionEndIndex = -1;
			}
			
			m_SelectedIndex = nextSelectedIndex;

			ensureCursorVisible();
			return true;
		}
		case Keyboard::Back:
			if(!eraseSelection() && m_SelectedIndex > 0)
			{
				m_TextCache.erase(m_TextCache.begin()+m_SelectedIndex-1);
				m_SelectedIndex--;
				ensureCursorVisible();
			}
			return true;

		case Keyboard::Delete:
			if(!eraseSelection() && m_SelectedIndex < (int)m_Data->get().size())
			{
				m_TextCache.erase(m_TextCache.begin()+m_SelectedIndex);
				ensureCursorVisible();
			}
			return true;

		default:
			break;
	}
	return false;
}

bool TextField::onKeyUp(Keyboard::Key key)
{
	if(m_Data == NULL)
	{
		return false;
	}
	switch(key)
	{
		case Keyboard::LShift:
		case Keyboard::RShift:
			m_IsShiftPressed = false;
			return true;
		case Keyboard::Return:
			Gui::focus(NULL);
			return true;
		default:
			break;
	}

	return false;
}

void TextField::ensureCursorVisible()
{
	TextSize cursorDimensions = Text::measure(Gui::font(), m_TextCache.c_str(), m_SelectedIndex);

	float x = m_Offset + cursorDimensions.width;
	float max = width() - TextPad*2.0f;
	if(x < 0.0f)
	{
		m_Offset += -x;
	}
	else if(x > max)
	{
		m_Offset += max-x;
	}

}

bool TextField::eraseSelection()
{
	if(m_SelectionStartIndex != -1)
	{
		if(m_SelectionEndIndex > m_SelectionStartIndex)
		{
			m_SelectedIndex = m_SelectionStartIndex;
			m_TextCache.erase(m_TextCache.begin() + m_SelectionStartIndex, m_TextCache.begin() + m_SelectionEndIndex);
		}
		else
		{
			m_SelectedIndex = m_SelectionEndIndex;
			m_TextCache.erase(m_TextCache.begin() + m_SelectionEndIndex, m_TextCache.begin() + m_SelectionStartIndex);
		}
		m_SelectionStartIndex = m_SelectionEndIndex = -1;
		return true;
	}
	return false;
}

void TextField::injectText(std::string text)
{
	eraseSelection();

	m_TextCache.insert(m_SelectedIndex, text);
	m_SelectedIndex += text.size();
	ensureCursorVisible();
}

bool TextField::onCharInput(unsigned long int utf8)
{
	switch(utf8)
	{
		case 8: // Backspace
		case 127: // Erase
		case 10: // Enter
			return false;
		default:
			break;
	}
	printf("CHAR INPUT: %lu\n", utf8);
	injectText(Text::fromUTF8(utf8));
	return true;
}

void TextField::onFocus()
{
	if(m_Data != NULL)
	{
		m_TextCache = m_Data->get();
	}
}

void TextField::onBlur()
{
	if(m_Data != NULL)
	{
		m_Data->set(m_TextCache);
	}
}