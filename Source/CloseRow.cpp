#include "CloseRow.hpp"
#include "Gui.hpp"
#include "Text.hpp"
#include <cmath>

using namespace splitcell::datgui;


float CloseRow::height()
{
	return Gui::RowHeight;
}

void CloseRow::draw(Renderer* renderer)
{
	//static const Color MarkerColor(200, 0, 0, 25
	const Color CloseBackgroundColor(0, 0, 0, 255);
	const Color CloseOverBackgroundColor(20, 20, 20, 240);

	float h = height();
	renderer->drawRect(x(), y(), width(), h, isMouseOver() ? CloseOverBackgroundColor : CloseBackgroundColor);
	//renderer->drawRect(x(), y(), Gui::MarkerWidth, h, MarkerColor);

	const char* labelText = label().c_str();
	TextSize labelSize = Text::measure(Gui::font(), labelText);


	Text::draw(renderer, Gui::font(), (float)round(x() + width()/2.0f - labelSize.width/2.0f), (float)round(y() + h/2.0f - labelSize.height/2.0f + labelSize.maxAscender), labelText, Color(1.0f));

	// Draw separator
	//renderer->drawRect(x() + Gui::MarkerWidth, y()+h-1.0f, width() - Gui::MarkerWidth, 1.0f, SeparatorColor);
}

bool CloseRow::onMouseDown(int x, int y)
{
	Gui::focus(NULL);
	Gui::toggleHideRows();
	return true;
}

bool CloseRow::onMouseUp(int x, int y)
{
	return false;
}

bool CloseRow::onMouseMove(int x, int y)
{
	return false;
}
