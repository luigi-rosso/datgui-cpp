#include "Row.hpp"

using namespace splitcell::datgui;

const Color Row::BackgroundColor(7, 7, 7, 230);
const Color Row::OverBackgroundColor(20, 20, 20, 230);
const Color Row::SeparatorColor(40, 40, 40, 230);


Row::Row() :
		m_X(0.0f),
		m_Y(0.0f),
		m_Width(0.0f),
		m_LabelWidth(0.0f),
		m_IsMouseOver(false),
		m_IsHidden(false)
{

}

void Row::place(float x, float y, float width, float labelWidth)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_LabelWidth = labelWidth;

	onPlaced();
}