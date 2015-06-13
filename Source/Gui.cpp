#include "Gui.hpp"
#include "OpenGLRenderer.hpp"
#include "Text.hpp"
#include "Row.hpp"
#include "Control.hpp"
#include "CloseRow.hpp"

using namespace splitcell::datgui;

#include "MemoryFiles/Volter__28Goldfish_29.ttf9.cache.h"
static MemoryFile FontMemoryFile("Volter__28Goldfish_29.ttf9.cache", Volter__28Goldfish_29_ttf9_cache, Volter__28Goldfish_29_ttf9_cache_len);

const float Gui::GuiWidth = 250.0f;
const float Gui::LabelColumnWidth = 75.0f;
const float Gui::GuiPad = 20.0f;
const float Gui::RowHeight = 25.0f;
const float Gui::MarkerWidth = 2.0f;
Gui* Gui::sm_Instance = NULL;

Gui::Gui(unsigned int screenWidth, unsigned int screenHeight) : m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight), m_Focus(NULL), m_MouseCapture(NULL), m_IsHidingRows(false)
{
	sm_Instance = this;
	// Instance a different renderer here if wanted.
	m_Renderer = new OpenGLRenderer();
	if(!m_Renderer->initialize())
	{
		printf("Gui::Gui - failed to initialize renderer.\n");
		delete m_Renderer;
		m_Renderer = NULL;
	}
	else
	{
		m_Renderer->setScreenSize(m_ScreenWidth, m_ScreenHeight);

		// Instance members.
		m_Font = m_Renderer->makeFont(&FontMemoryFile);
	}

	m_CloseRow = add<CloseRow>();
	m_CloseRow->setLabel("Close Controls");
}

Gui::~Gui()
{
	delete m_Font;
	delete m_Renderer;
}

void Gui::setRowsHidden(bool hidden)
{
	m_IsHidingRows = hidden;

	for(auto row : m_Rows)
	{
		row->hide(hidden && row != m_Rows.back());
	}

	m_CloseRow->setLabel(hidden ? "Open Controls" : "Close Controls");

	repositionRows();
}

void Gui::repositionRows()
{
	float x = (float)round(m_ScreenWidth - GuiWidth - GuiPad);
	float y = 0.0f;

	RowContainer::repositionRows(x, y, GuiWidth, LabelColumnWidth);
}

void Gui::onRowsChanged()
{
	// Ugly way to push the close row to the end.
	if(m_CloseRow != NULL)
	{
		for(auto itr = m_Rows.begin(); itr != m_Rows.end(); itr++)
		{
			if(*itr == m_CloseRow)
			{
				m_Rows.erase(itr);
				m_Rows.push_back(m_CloseRow);
				break;
			}
		}
		
	}
	repositionRows();
}

void Gui::resizeScreen(unsigned int screenWidth, unsigned int screenHeight)
{
	if(m_Renderer != NULL)
	{
		m_ScreenWidth = screenWidth;
		m_ScreenHeight = screenHeight;
		m_Renderer->setScreenSize(screenWidth, screenHeight);
		repositionRows();
	}
}

void Gui::draw()
{
	if(m_Renderer == NULL)
	{
		return;
	}

	m_Renderer->pushState();

	m_Renderer->enableBlending();
	m_Renderer->disableDepthWrite();

	RowContainer::draw(m_Renderer);

	m_Renderer->popState();
}

bool Gui::onMouseDown(int x, int y)
{
	if(m_MouseCapture != NULL && m_MouseCapture->onMouseDown(x, y))
	{
		return true;
	}

	return RowContainer::onMouseDown(x,y);
}

bool Gui::onMouseUp(int x, int y)
{
	if(m_MouseCapture != NULL && m_MouseCapture->onMouseUp(x, y))
	{
		return true;
	}
	return RowContainer::onMouseUp(x,y);
}

bool Gui::onMouseMove(int x, int y)
{
	if(m_MouseCapture != NULL && m_MouseCapture->onMouseMove(x, y))
	{
		return true;
	}
	return RowContainer::onMouseMove(x,y);
}

bool Gui::onKeyDown(Keyboard::Key key)
{
	if(m_Focus != NULL && m_Focus->onKeyDown(key))
	{
		return true;
	}
	return false;
}

bool Gui::onKeyUp(Keyboard::Key key)
{
	if(m_Focus != NULL && m_Focus->onKeyUp(key))
	{
		return true;
	}
	return false;
}

void Gui::captureMouse(Control* control)
{
	m_MouseCapture = control;
}

void Gui::releaseMouse(Control* control)
{
	if(m_MouseCapture == control)
	{
		m_MouseCapture = NULL;
	}
}

void Gui::focus(Control* control)
{
	if(control == m_Focus)
	{
		return;
	}
	if(m_Focus != NULL)
	{
		m_Focus->onBlur();
	}
	m_Focus = control;
	if(m_Focus != NULL)
	{
		m_Focus->onFocus();
	}
}