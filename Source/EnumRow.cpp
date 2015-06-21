#include "EnumRow.hpp"
#include "Gui.hpp"
#include "Text.hpp"
#include <cmath>

using namespace splitcell::datgui;


static const Color MarkerColor(0, 150, 255, 255);

EnumRow::EnumRow()
{
	m_ComboBox.setAccentColor(MarkerColor);
}

void EnumRow::onPlaced()
{
	m_ComboBox.place(x() + labelWidth() + Gui::LabelPadding, y() + Control::Padding, width() - labelWidth() - Control::Padding*2, height() - Control::Padding*2);
}

float EnumRow::height()
{
	return Gui::RowHeight;
}

void EnumRow::draw(Renderer* renderer)
{
	float h = height();
	renderer->drawRect(x(), y(), width(), h, isMouseOver() ? OverBackgroundColor : BackgroundColor);
	renderer->drawRect(x(), y(), Gui::MarkerWidth, h, MarkerColor);

	renderer->pushClip(x(), y(), labelWidth(), h);
	{
		const char* labelText = label().c_str();
		TextSize labelSize = Text::measure(Gui::font(), labelText);
		Text::draw(renderer, Gui::font(), x() + Gui::MarkerWidth + Gui::LabelPadding, (float)round(y() + h/2.0f - labelSize.height/2.0f + labelSize.maxAscender), labelText, Color(1.0f));
	}
	renderer->popClip();

	m_ComboBox.draw(renderer);

	// Draw separator
	renderer->drawRect(x() + Gui::MarkerWidth, y()+h-1.0f, width() - Gui::MarkerWidth, 1.0f, SeparatorColor);
}

bool EnumRow::onMouseDown(int x, int y)
{
	float gx = x + Row::x();
	float gy = y + Row::y();
	if( gx >= m_ComboBox.x() && 
		gx <= m_ComboBox.x() + m_ComboBox.actualWidth() && 
		gy >= m_ComboBox.y() && 
		gy <= m_ComboBox.y() + m_ComboBox.height() && 
		m_ComboBox.onMouseDown(gx - m_ComboBox.x(), gy - m_ComboBox.y()))
	{
		return true;
	}
	return false;
}

bool EnumRow::onMouseUp(int x, int y)
{
	return false;
}

bool EnumRow::onMouseMove(int x, int y)
{
	return false;
}

void EnumRow::setData(DatGui::Enum* data)
{
	m_Data = data;
	m_ComboBox.setData(data);
}