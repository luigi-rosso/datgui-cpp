#include "FolderRow.hpp"
#include "Gui.hpp"
#include "Text.hpp"
#include <cmath>

using namespace splitcell::datgui;

FolderRow::FolderRow() : m_IsOpen(false), m_LastY(0.0f)
{

}

float FolderRow::height()
{
	return m_IsOpen ? m_Rows.size() * Gui::RowHeight + Gui::RowHeight : Gui::RowHeight;
}

void FolderRow::draw(Renderer* renderer)
{
	static const Color MarkerColor(200, 0, 0, 255);
	const Color FolderBackgroundColor(0, 0, 0, 255);
	const Color FolderOverBackgroundColor(20, 20, 20, 240);

	float h = Gui::RowHeight;
	renderer->drawRect(x(), y(), width(), h, isMouseOver() && m_LastY <= Gui::RowHeight ? FolderOverBackgroundColor : FolderBackgroundColor);
	//renderer->drawRect(x(), y(), Gui::MarkerWidth, h, MarkerColor);

	unsigned int arrowIcon = m_IsOpen ? 61703/*61655*/ : 61701/*61658*/;

	TextSize arrowSize = Text::measure(Gui::iconFont(), arrowIcon);
	Text::draw(renderer, Gui::iconFont(), (float)round(x() + Gui::MarkerWidth + 3.0f), (float)round(y() + h/2.0f - arrowSize.height/2.0f + arrowSize.maxAscender), arrowIcon, Color(1.0f));

	const char* labelText = label().c_str();
	TextSize labelSize = Text::measure(Gui::font(), labelText);
	Text::draw(renderer, Gui::font(), (float)round(x() + Gui::MarkerWidth + 3.0f + arrowSize.width + 6.0f), (float)round(y() + h/2.0f - labelSize.height/2.0f + labelSize.maxAscender), labelText, Color(1.0f));


	// Draw separator
	renderer->drawRect(x() + Gui::MarkerWidth, y()+h-1.0f, width() - Gui::MarkerWidth, 1.0f, SeparatorColor);

	if(m_IsOpen)
	{
		RowContainer::draw(renderer);
	}
}

bool FolderRow::onMouseDown(int x, int y)
{
	if(y < Gui::RowHeight)
	{
		m_IsOpen = !m_IsOpen;
		Gui::reposition();
		return true;
	}
	return RowContainer::onMouseDown(x + Row::x(), y + Row::y());
}

void FolderRow::onMouseLeave()
{
	Row::onMouseLeave();
	RowContainer::forceMouseLeave();
}

bool FolderRow::onMouseUp(int x, int y)
{
	return RowContainer::onMouseUp(x + Row::x(), y + Row::y());
}

bool FolderRow::onMouseMove(int x, int y)
{
	m_LastY = y;
	return RowContainer::onMouseMove(x + Row::x(), y + Row::y());
}

void FolderRow::onRowsChanged()
{
	Gui::reposition();
}

void FolderRow::onPlaced()
{
	float folderRowIndent = 5.0f;
	RowContainer::repositionRows(x()+folderRowIndent, y()+Gui::RowHeight, width()-folderRowIndent, labelWidth());
}