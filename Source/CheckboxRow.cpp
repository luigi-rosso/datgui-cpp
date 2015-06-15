#include "CheckboxRow.hpp"
#include "Gui.hpp"
#include "Text.hpp"
#include <cmath>

using namespace splitcell::datgui;

CheckboxRow::CheckboxRow() : m_Data(NULL)
{

}

void CheckboxRow::onPlaced()
{

}

float CheckboxRow::height()
{
	return Gui::RowHeight;
}

void CheckboxRow::draw(Renderer* renderer)
{
	static const Color MarkerColor(128, 103, 135, 255);

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

	unsigned int checkIcon = 61640;
	if(m_Data != NULL && m_Data->get())
	{
		checkIcon = 61770;
	}
	TextSize checkSize = Text::measure(Gui::iconFont(), checkIcon);
	Text::draw(renderer, Gui::iconFont(), (float)round(x() + labelWidth() + Gui::LabelPadding), (float)round(y() + h/2.0f - checkSize.height/2.0f + checkSize.maxAscender), checkIcon, Color(1.0f));

	// Draw separator
	renderer->drawRect(x() + Gui::MarkerWidth, y()+h-1.0f, width() - Gui::MarkerWidth, 1.0f, SeparatorColor);
}

bool CheckboxRow::onMouseDown(int x, int y)
{
	if(m_Data != NULL)
	{
		Gui::focus(NULL);
		m_Data->set(!m_Data->get());
		return true;
	}
	return false;
}

bool CheckboxRow::onMouseUp(int x, int y)
{
	return false;
}

bool CheckboxRow::onMouseMove(int x, int y)
{
	return false;
}

void CheckboxRow::setData(DatGui::Boolean* data)
{
	m_Data = data;
}
