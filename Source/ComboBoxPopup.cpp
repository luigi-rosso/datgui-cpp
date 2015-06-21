#include "ComboBoxPopup.hpp"
#include "Text.hpp"
#include "Gui.hpp"
#include <cmath>

using namespace splitcell::datgui;

static const float RowPadding = 10.0f;

ComboBoxPopup::ComboBoxPopup() : m_Data(NULL), m_ScrollOffset(0.0f)
{

}

void ComboBoxPopup::setData(DatGui::Enum* data)
{
	m_Data = data;
}

float ComboBoxPopup::contentHeight()
{
	if(m_Data == NULL)
	{
		return 0.0f;
	}
	return (Gui::font()->getLineHeight()+RowPadding) * m_Data->numEntries() + Padding*2.0f;
}

void ComboBoxPopup::onPlaced()
{
}

void ComboBoxPopup::draw(Renderer* renderer)
{
	float scrollRange = height()-contentHeight();
	m_ScrollOffset = std::min(0.0f, std::max(scrollRange, m_ScrollOffset));
	renderer->drawRect(x(), y(), width(), height(), BackgroundColor);

	if(m_Data == NULL)
	{
		return;
	}

	float startX = x() + Padding;
	float currentY = y() + Padding + m_ScrollOffset;
	renderer->pushClip(startX, y(), width()-Padding*2.0f, height());

	float lineHeight = (float)Gui::font()->getLineHeight() + RowPadding;

	unsigned int icon = 61452;
	float iconScale = 0.65f;

	TextSize iconSize = Text::measure(Gui::iconFont(), icon);
	startX += iconSize.width * iconScale + Padding;

	for(int i = 0; i < m_Data->numEntries(); i++)
	{
		auto entry = m_Data->entry(i);

		std::string label = entry->label();
		TextSize textSize = Text::measure(Gui::font(), label.c_str());
		Text::draw(renderer, Gui::font(), startX, (float)round(currentY + lineHeight/2.0f - textSize.height/2.0f + textSize.maxAscender), label.c_str(), accentColor());

		if(m_Data->selection() == entry)
		{
			Text::draw(renderer, Gui::iconFont(), (float)round(x() + Padding), (float)round(currentY + lineHeight/2.0f - iconSize.height*iconScale/2.0f + iconSize.maxAscender*iconScale), icon, accentColor(), 1.0f, iconScale);
		}
		currentY += lineHeight;
	}
	renderer->popClip();
}

bool ComboBoxPopup::onMouseDown(int x, int y)
{
	if(m_Data == NULL || m_Data->numEntries() == 0)
	{
		return false;
	}
	float lineHeight = (float)Gui::font()->getLineHeight() + RowPadding;
	int idx = (int)((y - Padding) / lineHeight);
	idx = std::min(m_Data->numEntries()-1, std::max(0, idx));

	m_Data->setValue(m_Data->entry(idx)->value());
	Gui::closePopup();
	return true;
}

bool ComboBoxPopup::onMouseUp(int x, int y)
{
	return false;
}

bool ComboBoxPopup::onMouseMove(int x, int y)
{
	return true;
}

bool ComboBoxPopup::onMouseWheel(int x, int y, float dy)
{
	m_ScrollOffset += dy;
	return true;
}

bool ComboBoxPopup::onKeyDown(Keyboard::Key key)
{
	return false;
}

bool ComboBoxPopup::onKeyUp(Keyboard::Key key)
{
	return false;
}


bool ComboBoxPopup::onCharInput(unsigned long int utf8)
{
	return false;
}

void ComboBoxPopup::onFocus()
{
}

void ComboBoxPopup::onBlur()
{
}