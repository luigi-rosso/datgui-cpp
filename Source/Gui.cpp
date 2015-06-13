#include "Gui.hpp"
#include "OpenGLRenderer.hpp"
#include "Text.hpp"

using namespace splitcell::datgui;

#include "MemoryFiles/Terminus.ttf16.cache.h"
static MemoryFile MemoryFileTerminus_ttf16_cache("Terminus.ttf16.cache", Terminus_ttf16_cache, Terminus_ttf16_cache_len);

Gui::Gui(unsigned int screenWidth, unsigned int screenHeight) : m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight)
{
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
		m_Font = m_Renderer->makeFont(&MemoryFileTerminus_ttf16_cache);
	}
}

Gui::~Gui()
{
	delete m_Font;
	delete m_Renderer;
}

void Gui::resizeScreen(unsigned int screenWidth, unsigned int screenHeight)
{
	if(m_Renderer != NULL)
	{
		m_ScreenWidth = screenWidth;
		m_ScreenHeight = screenHeight;
		m_Renderer->setScreenSize(screenWidth, screenHeight);	
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

	static const float GuiWidth = 250.0f;
	static const float GuiPad = 20.0f;

	float x = (float)round(m_ScreenWidth - GuiWidth - GuiPad);
	
	m_Renderer->drawRect(x, 0.0f, GuiWidth, m_ScreenHeight, Color(0, 0, 0, 255), 1.0f);

	Text::draw(m_Renderer, m_Font, x, 100.0f, "Testing...", Color(1.0f));

	m_Renderer->popState();
}

bool Gui::onMouseDown(int x, int y)
{
	return false;
}

bool onMouseUp(int x, int y)
{
	return false;
}

bool Gui::onMouseMove(int x, int y)
{
	return false;
}

bool Gui::onKeyDown(Keyboard::Key key)
{
	return false;
}

bool Gui::onKeyUp(Keyboard::Key key)
{
	return false;
}