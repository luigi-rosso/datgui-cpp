#include "NumericRow.hpp"
#include "Gui.hpp"
#include "Text.hpp"
#include <cmath>
#include <limits>


using namespace splitcell::datgui;

static const Color MarkerColor(0, 150, 255, 255);

NumericRow::NumericRow() : m_CacheNumDecimals(2), m_CacheValue(0.0f), m_Data(NULL)
{
	m_TextField.setAccentColor(MarkerColor);
	m_Slider.setAccentColor(MarkerColor);

	m_Slider.setDragCallback([this](float p)
	{
		if(m_Data != NULL)
		{
			float d = m_Data->min() + (m_Data->max()-m_Data->min()) * p;
			setValue(d);
		}
	});

	m_TextField.setDragCallback([this](int drag)
	{
		float step = m_Data->step();
		if(step == std::numeric_limits<float>::max())
		{
			step = 0.01f;
		}
		setValue(m_Data->get()-drag*step);
	});

	m_TextfieldData.setCallback([this](std::string text)
	{
		if(m_Data == NULL)
		{
			return;
		}
		try
		{
			float f = std::stof(text);
			setValue(f);
		}
		catch(const std::invalid_argument& error)
		{
			// Somehow show the error? Do we care?
		}
		catch(const std::out_of_range& error)
		{
			// Somehow show the error? Do we care?
		}
	});
}

void NumericRow::onPlaced()
{
	m_HasRange = m_Data != NULL && m_Data->min() != -std::numeric_limits<float>::max() && m_Data->max() != std::numeric_limits<float>::max();

	if(m_HasRange)
	{
		static const float sliderWidthFactor = 0.75f;

		float availWidth = width() - labelWidth() - Control::Padding*3;

		float sliderWidth = availWidth * sliderWidthFactor;
		float textFieldWidth = availWidth - sliderWidth;

		m_Slider.place(x() + labelWidth() + Gui::LabelPadding, y() + Control::Padding, sliderWidth, height() - Control::Padding*2);
		m_TextField.place(m_Slider.x() + m_Slider.width() + Control::Padding, y() + Control::Padding, textFieldWidth, height() - Control::Padding*2);
	}
	else
	{
		m_TextField.place(x() + labelWidth() + Gui::LabelPadding, y() + Control::Padding, width() - labelWidth() - Control::Padding*2, height() - Control::Padding*2);
	}
}

float NumericRow::height()
{
	return Gui::RowHeight;
}

void NumericRow::setValue(float v)
{
	if(m_Data == NULL)
	{
		return;
	}

	float step = m_Data->step();
	if(step != std::numeric_limits<float>::max())
	{
		v = (float)round(v / m_Data->step()) * m_Data->step();
	}
	m_Data->set(v);
	updateDisplayValue();
}

void NumericRow::updateDisplayValue()
{
	if(m_Data == NULL)
	{
		return;
	}
	m_CacheNumDecimals = m_Data->decimals();

	m_CacheValue = m_Data->get();
	char buffer[256];

	/*float step = m_Data->step();
	if(step != std::numeric_limits<float>::max())
	{
		m_CacheValue = (float)round(m_CacheValue / m_Data->step()) * m_Data->step();
		m_Data->set(m_CacheValue);
	}*/
	if(m_CacheNumDecimals == -1)
	{
		std::snprintf(buffer, sizeof(buffer), "%g", m_CacheValue);
	}
	else if(m_CacheNumDecimals == 0)
	{
		std::snprintf(buffer, sizeof(buffer), "%.0f", m_CacheValue);
	}
	else
	{
		char fmtbuffer[16];
		std::snprintf(fmtbuffer, sizeof(fmtbuffer), "%%.%if", m_CacheNumDecimals);
		std::snprintf(buffer, sizeof(buffer), fmtbuffer, m_CacheValue);
	}

	m_TextfieldData.set(std::string(buffer));
	m_TextField.setData(&m_TextfieldData);
	m_Slider.setData(m_Data);
}

void NumericRow::draw(Renderer* renderer)
{
	if(m_Data != NULL)
	{
		if(m_Data->get() != m_CacheValue || m_Data->decimals() != m_CacheNumDecimals)
		{
			updateDisplayValue();
		}

		// Detect if we now have range and re-align.
		bool hasRange = m_Data->min() != -std::numeric_limits<float>::max() && m_Data->max() != std::numeric_limits<float>::max();
		if(hasRange != m_HasRange)
		{
			onPlaced();
		}
	}

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

	/*unsigned int checkIcon = 61640;
	if(m_Data != NULL && m_Data->get())
	{
		checkIcon = 61770;
	}
	TextSize checkSize = Text::measure(Gui::iconFont(), checkIcon);
	Text::draw(renderer, Gui::iconFont(), (float)round(x() + labelWidth() + Gui::LabelPadding), (float)round(y() + h/2.0f - checkSize.height/2.0f + checkSize.maxAscender), checkIcon, Color(1.0f));*/

	if(m_HasRange)
	{
		m_Slider.draw(renderer);
	}
	m_TextField.draw(renderer);


	// Draw separator
	renderer->drawRect(x() + Gui::MarkerWidth, y()+h-1.0f, width() - Gui::MarkerWidth, 1.0f, SeparatorColor);
}

bool NumericRow::onMouseDown(int x, int y)
{
	float gx = x + Row::x();
	float gy = y + Row::y();
	if( gx >= m_TextField.x() && 
		gx <= m_TextField.x() + m_TextField.width() && 
		gy >= m_TextField.y() && 
		gy <= m_TextField.y() + m_TextField.height() && 
		m_TextField.onMouseDown(gx - m_TextField.x(), gy - m_TextField.y()))
	{
		return true;
	}
	else if(m_HasRange &&
			gx >= m_Slider.x() && 
			gx <= m_Slider.x() + m_Slider.width() && 
			gy >= m_Slider.y() && 
			gy <= m_Slider.y() + m_Slider.height() && 
			m_Slider.onMouseDown(gx - m_Slider.x(), gy - m_Slider.y()))
	{
		return true;
	}
	return false;
}

bool NumericRow::onMouseUp(int x, int y)
{
	float gx = x + Row::x();
	float gy = y + Row::y();
	if( gx >= m_TextField.x() && 
		gx <= m_TextField.x() + m_TextField.width() && 
		gy >= m_TextField.y() && 
		gy <= m_TextField.y() + m_TextField.height() && 
		m_TextField.onMouseUp(gx - m_TextField.x(), gy - m_TextField.y()))
	{
		return true;
	}
	else if(m_HasRange &&
			gx >= m_Slider.x() && 
			gx <= m_Slider.x() + m_Slider.width() && 
			gy >= m_Slider.y() && 
			gy <= m_Slider.y() + m_Slider.height() && 
			m_Slider.onMouseUp(gx - m_Slider.x(), gy - m_Slider.y()))
	{
		return true;
	}
	return false;
}

bool NumericRow::onMouseMove(int x, int y)
{
	float gx = x + Row::x();
	float gy = y + Row::y();
	if( gx >= m_TextField.x() && 
		gx <= m_TextField.x() + m_TextField.width() && 
		gy >= m_TextField.y() && 
		gy <= m_TextField.y() + m_TextField.height() && 
		m_TextField.onMouseMove(gx - m_TextField.x(), gy - m_TextField.y()))
	{
		return true;
	}
	else if(m_HasRange &&
			gx >= m_Slider.x() && 
			gx <= m_Slider.x() + m_Slider.width() && 
			gy >= m_Slider.y() && 
			gy <= m_Slider.y() + m_Slider.height() && 
			m_Slider.onMouseMove(gx - m_Slider.x(), gy - m_Slider.y()))
	{
		return true;
	}
	return false;
}

void NumericRow::setData(DatGui::Numeric* data)
{
	m_Data = data;
	if(data != NULL)
	{
		updateDisplayValue();
	}
	//m_TextField.setData(data);
}
