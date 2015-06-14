#include "Control.hpp"

using namespace splitcell::datgui;

Control::Control() :
		m_X(0.0f),
		m_Y(0.0f),
		m_Width(0.0f),
		m_Height(0.0f)
{

}

void Control::place(float x, float y, float width, float height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
}