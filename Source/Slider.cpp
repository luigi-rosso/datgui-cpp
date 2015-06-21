#include "Slider.hpp"
#include "Text.hpp"
#include "Gui.hpp"
#include <cmath>

using namespace splitcell::datgui;

Slider::Slider() : m_Data(NULL), m_IsDraggingCursor(false)
{

}

void Slider::setData(DatGui::Numeric* data)
{
	m_Data = data;
}

void Slider::draw(Renderer* renderer)
{
	renderer->drawRect(x(), y(), width(), height(), BackgroundColor);

	if(m_Data != NULL)
	{
		float p = (m_Data->get()-m_Data->min())/(m_Data->max()-m_Data->min());

		renderer->drawRect(x(), y(), (float)round(width()*p), height(), accentColor());
	}
}

bool Slider::onMouseDown(int x, int y)
{
	Gui::focus(this);

	Gui::captureMouse(this);
	m_IsDraggingCursor = true;

	float p = x/width();
	if(m_DragCallback != NULL)
	{
		m_DragCallback(p);
	}

	return true;
}

bool Slider::onMouseUp(int x, int y)
{
	m_IsDraggingCursor = false;
	return false;
}

void Slider::setDragCallback(std::function<void(float)> callback)
{
	m_DragCallback = callback;
}

bool Slider::onMouseMove(int x, int y)
{
	if(m_IsDraggingCursor)
	{
		float p = x/width();

		if(m_DragCallback != NULL)
		{
			m_DragCallback(p);
		}
		return true;
	}
	return false;
}

bool Slider::onKeyDown(Keyboard::Key key)
{
	return false;
}

bool Slider::onKeyUp(Keyboard::Key key)
{
	return false;
}


bool Slider::onCharInput(unsigned long int utf8)
{
	return false;
}

void Slider::onFocus()
{
}

void Slider::onBlur()
{
}