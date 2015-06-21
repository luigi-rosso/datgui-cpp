#include "Control.hpp"

using namespace splitcell::datgui;

const Color Control::BackgroundColor(60, 60, 60, 240);
const Color Control::OverBackgroundColor(70, 70, 70, 240);
const float Control::Padding = 5.0f;

Control::Control() :
		m_X(0.0f),
		m_Y(0.0f),
		m_Width(0.0f),
		m_Height(0.0f),
		m_IsFocused(false)
{

}

void Control::place(float x, float y, float width, float height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;

	onPlaced();
}