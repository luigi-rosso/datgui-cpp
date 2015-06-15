#include "TextField.hpp"
#include "Text.hpp"
#include "Gui.hpp"
#include <cmath>

using namespace splitcell::datgui;

static const float TextPad = 2.0f;

TextField::TextField() : m_Data(NULL), m_Offset(0.0f), m_SelectedIndex(0), m_IsDraggingCursor(false)
{

}

void TextField::setData(DatGui::Text* data)
{
	m_Data = data;
}

void TextField::draw(Renderer* renderer)
{
	// TODO: Track if user changed data.

	float cursorWidth = 1.0f;
	float cursorHeight = (float)round(height() * 0.75f);

	renderer->drawRect(x(), y(), width(), height(), BackgroundColor);

	float startX = x() + m_Offset + TextPad;
	renderer->pushClip(x(), y(), width(), height());
	if(m_Data != NULL)
	{
		std::string val = m_Data->get();
		Text::draw(renderer, Gui::font(), startX, (float)round(y() + height() - Padding), val.c_str(), isFocused() ? Color(1.0f) : accentColor());

		if(isFocused())
		{
			TextSize cursorDimensions = Text::measure(Gui::font(), val.c_str(), m_SelectedIndex);
			renderer->drawRect(startX + cursorDimensions.width, (float)round(y() + height()/2.0f - cursorHeight/2.0f), cursorWidth, cursorHeight, Color(1.0f));
		}
	}
	renderer->popClip();
}

bool TextField::onMouseDown(int x, int y)
{
	Gui::focus(this);

	Gui::captureMouse(this);
	m_IsDraggingCursor = true;

	if(m_Data != NULL)
	{
		std::string val = m_Data->get();
		float startX = m_Offset + 2;
		m_SelectedIndex = Text::characterIndex(Gui::font(), val.c_str(), x - startX);
	}
	return true;
}

bool TextField::onMouseUp(int x, int y)
{
	m_IsDraggingCursor = false;
	return false;
}

bool TextField::onMouseMove(int x, int y)
{
	if(m_IsDraggingCursor && m_Data != NULL)
	{
		std::string val = m_Data->get();
		float startX = m_Offset + 2;
		m_SelectedIndex = Text::characterIndex(Gui::font(), val.c_str(), x - startX);
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
		case Keyboard::Left:
			m_SelectedIndex = std::max(0, std::min((int)m_Data->get().size(), m_SelectedIndex - 1));
			ensureCursorVisible();
			return true;
		case Keyboard::Right:
			m_SelectedIndex = std::max(0, std::min((int)m_Data->get().size(), m_SelectedIndex + 1));
			ensureCursorVisible();
			return true;
		case Keyboard::Back:
			if(m_SelectedIndex > 0)
			{
				std::string val = m_Data->get();
				val.erase(val.begin()+m_SelectedIndex-1);
				m_Data->set(val);
				m_SelectedIndex--;
				ensureCursorVisible();
			}
			break;
	}
	return false;
}

bool TextField::onKeyUp(Keyboard::Key key)
{
	return false;
}

void TextField::ensureCursorVisible()
{
	std::string val = m_Data->get();
	TextSize cursorDimensions = Text::measure(Gui::font(), val.c_str(), m_SelectedIndex);

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

void TextField::injectText(std::string text)
{
	std::string val = m_Data->get();
	val.insert(m_SelectedIndex, text);
	m_SelectedIndex += text.size();
	m_Data->set(val);
	ensureCursorVisible();
}

bool TextField::onCharInput(unsigned long int utf8)
{
	switch(utf8)
	{
		case 8: // Backspace
			return false;
			break;
	}
	printf("CHAR INPUT: %i\n", utf8);
	injectText(Text::fromUTF8(utf8));
	return true;
}

void TextField::onFocus()
{

}

void TextField::onBlur()
{

}