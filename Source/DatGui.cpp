#include "DatGui.hpp"
#include "Gui.hpp"

using namespace splitcell;
using namespace splitcell::datgui;

static Gui* gui = NULL;

DatGui::DatGui()
{

}

DatGui::~DatGui()
{

}

bool DatGui::initialize(unsigned int screenWidth, unsigned int screenHeight)
{
	if(gui != NULL)
	{
		return false;
	}
	gui = new Gui(screenWidth, screenHeight);
	
	return true;
}

void DatGui::resizeScreen(unsigned int screenWidth, unsigned int screenHeight)
{
	if(gui != NULL)
	{
		gui->resizeScreen(screenWidth, screenHeight);
	}
}

void DatGui::draw()
{
	if(gui != NULL)
	{
		gui->draw();
	}
}

bool DatGui::onMouseDown(int x, int y)
{
	if(gui == NULL)
	{
		return false;
	}
	return gui->onMouseDown(x, y);
}

bool DatGui::onMouseUp(int x, int y)
{
	if(gui == NULL)
	{
		return false;
	}
	return gui->onMouseDown(x, y);
}

bool DatGui::onMouseMove(int x, int y)
{
	if(gui == NULL)
	{
		return false;
	}
	return gui->onMouseMove(x, y);
}

bool DatGui::onKeyDown(Keyboard::Key key)
{
	if(gui == NULL)
	{
		return false;
	}
	return gui->onKeyDown(key);
}

bool DatGui::onKeyUp(Keyboard::Key key)
{
	if(gui == NULL)
	{
		return false;
	}
	return gui->onKeyUp(key);
}