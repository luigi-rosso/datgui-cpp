#include "ActionRow.hpp"
#include "Gui.hpp"
#include "Text.hpp"
#include <cmath>

using namespace splitcell::datgui;


void ActionRow::onPlaced()
{

}

float ActionRow::height()
{
	return Gui::RowHeight;
}

void ActionRow::draw(Renderer* renderer)
{
	static const Color MarkerColor(200, 0, 0, 255);

	float h = height();
	renderer->drawRect(x(), y(), width(), h, isMouseOver() ? OverBackgroundColor : BackgroundColor);
	renderer->drawRect(x(), y(), Gui::MarkerWidth, h, MarkerColor);

	const char* labelText = label().c_str();
	TextSize labelSize = Text::measure(Gui::font(), labelText);


	Text::draw(renderer, Gui::font(), x() + Gui::MarkerWidth + Gui::LabelPadding, (float)round(y() + h/2.0f - labelSize.height/2.0f + labelSize.maxAscender), labelText, Color(1.0f));

	// Draw separator
	renderer->drawRect(x() + Gui::MarkerWidth, y()+h-1.0f, width() - Gui::MarkerWidth, 1.0f, SeparatorColor);
}

bool ActionRow::onMouseDown(int x, int y)
{
	if(m_Callback)
	{
		m_Callback();
		return true;
	}
	return false;
}

bool ActionRow::onMouseUp(int x, int y)
{
	return false;
}

bool ActionRow::onMouseMove(int x, int y)
{
	return false;
}

void ActionRow::setCallback(std::function<void()> callback)
{
	m_Callback = callback;
}
