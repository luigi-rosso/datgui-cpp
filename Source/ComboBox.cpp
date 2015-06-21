#include "ComboBox.hpp"
#include "Text.hpp"
#include "Gui.hpp"
#include <cmath>

using namespace splitcell::datgui;

static const float IconWidth = 20.0f;

ComboBox::ComboBox() : m_Data(NULL), m_ActualWidth(0.0f), m_MaxEntryWidth(0.0f), m_MaxTextRenderWidth(0.0f)
{

}

void ComboBox::setData(DatGui::Enum* data)
{
	m_Data = data;

	// Measure width.
	m_ActualWidth = width();

	if(m_Data != NULL)
	{
		m_MaxEntryWidth = 0.0f;
		for(int i = 0; i < m_Data->numEntries(); i++)
		{
			auto* entry = m_Data->entry(i);
			std::string label = entry->label();
			TextSize entryDimensions = Text::measure(Gui::font(), label.c_str());
			if(entryDimensions.width > m_MaxEntryWidth)
			{
				m_MaxEntryWidth = entryDimensions.width;
			}
		}
	}
	m_Popup.setData(data);

	onPlaced();
}

void ComboBox::onPlaced()
{
	m_ActualWidth = std::min(m_MaxEntryWidth+Padding*2.0f+IconWidth, width());
	m_MaxTextRenderWidth = m_ActualWidth-Padding*2.0f-IconWidth;
}

void ComboBox::onSetAccentColor()
{
	m_Popup.setAccentColor(accentColor());
}

void ComboBox::draw(Renderer* renderer)
{
	renderer->drawRect(x(), y(), actualWidth(), height(), BackgroundColor);

	if(m_Data != NULL && m_Data->selection() != NULL)
	{
		std::string label = m_Data->selection()->label();
		TextSize selectionSize = Text::measure(Gui::font(), label.c_str());

		float startX = x() + Padding;
		renderer->pushClip(startX, y(), m_MaxTextRenderWidth, height());
		Text::draw(renderer, Gui::font(), startX, (float)round(y() + height()/2.0f - selectionSize.height/2.0f + selectionSize.maxAscender), label.c_str(), accentColor());
		renderer->popClip();

		unsigned int arrowIcon = 61703/*61655*/;// : 61701/*61658*/;

		TextSize arrowSize = Text::measure(Gui::iconFont(), arrowIcon);
		Text::draw(renderer, Gui::iconFont(), (float)round(startX + m_MaxTextRenderWidth + Padding + IconWidth/2.0f - arrowSize.width/2.0), (float)round(y() + height()/2.0f - arrowSize.height/2.0f + arrowSize.maxAscender), arrowIcon, accentColor());
	}
}

bool ComboBox::onMouseDown(int lx, int ly)
{
	Gui::focus(this);

	if(Gui::isPopup(&m_Popup))
	{
		Gui::closePopup();
		return true;
	}
	// Determine where to place it.

	float spaceBelow = (float)Gui::screenHeight() - (y() + height() + m_Popup.contentHeight());
	float spaceAbove = y() - height() - m_Popup.contentHeight();

	if(spaceBelow > 0.0f)
	{
		// Ideal position, place the popup below the combobox.
		m_Popup.place(x(), y()+height(), m_ActualWidth, m_Popup.contentHeight());
	}
	else if(spaceAbove > 0.0f)
	{
		// Second position, place the popup above the combobox.
		m_Popup.place(x(), y()-m_Popup.contentHeight(), m_ActualWidth, m_Popup.contentHeight());	
	}
	else if(spaceBelow > spaceAbove)
	{
		// Third priority position, place popup below, with scrolling.
		float popupHeight = spaceBelow;
		m_Popup.place(x(), y()+height(), m_ActualWidth, popupHeight);
	}
	else
	{
		// Final catch all, place popup above, with scrolling.
		float popupHeight = spaceAbove;
		m_Popup.place(x(), y()-height()-popupHeight, m_ActualWidth, popupHeight);	
	}
	printf("POP IT UP! %f %f %f %f\n", m_Popup.x(), m_Popup.y(), m_Popup.width(), m_Popup.height());
	Gui::popup(&m_Popup);

	return true;
}

bool ComboBox::onMouseUp(int x, int y)
{
	return false;
}

bool ComboBox::onMouseMove(int x, int y)
{
	return false;
}

bool ComboBox::onKeyDown(Keyboard::Key key)
{
	return false;
}

bool ComboBox::onKeyUp(Keyboard::Key key)
{
	return false;
}


bool ComboBox::onCharInput(unsigned long int utf8)
{
	return false;
}

void ComboBox::onFocus()
{
}

void ComboBox::onBlur()
{
}