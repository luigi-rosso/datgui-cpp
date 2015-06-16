#include "NumericRow.hpp"
#include "Gui.hpp"
#include "Text.hpp"
#include <cmath>

using namespace splitcell::datgui;

static const Color MarkerColor(0, 150, 255, 255);

NumericRow::NumericRow() : m_CacheNumDecimals(2), m_Data(NULL)
{
	m_TextField.setAccentColor(MarkerColor);

	m_TextField.setDragCallback([this](int drag)
	{
		m_Data->set(m_Data->get()-drag*m_Data->step());
		updateDisplayValue();
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
			m_Data->set(f);
			updateDisplayValue();
		}
		catch(const std::invalid_argument& error)
		{
			// Somehow show the error? Do we care?
		}
	});
}

void NumericRow::onPlaced()
{
	m_TextField.place(x() + labelWidth() + Gui::LabelPadding, y() + Control::Padding, width() - labelWidth() - Control::Padding*2, height() - Control::Padding*2);
}

float NumericRow::height()
{
	return Gui::RowHeight;
}

void NumericRow::updateDisplayValue()
{
	if(m_Data == NULL)
	{
		return;
	}
	m_CacheNumDecimals = m_Data->decimals();


	char buffer[256];

	if(m_CacheNumDecimals == -1)
	{
		std::snprintf(buffer, sizeof(buffer), "%g", m_Data->get());
	}
	else if(m_CacheNumDecimals == 0)
	{
		std::snprintf(buffer, sizeof(buffer), "%.0f", m_Data->get());
	}
	else
	{
		char fmtbuffer[16];
		std::snprintf(fmtbuffer, sizeof(fmtbuffer), "%%.%if", m_CacheNumDecimals);
		std::snprintf(buffer, sizeof(buffer), fmtbuffer, m_Data->get());
	}

	m_TextfieldData.set(std::string(buffer));
	m_TextField.setData(&m_TextfieldData);
}

void NumericRow::draw(Renderer* renderer)
{
	if(m_Data != NULL && m_Data->decimals() != m_CacheNumDecimals)
	{
		updateDisplayValue();
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
