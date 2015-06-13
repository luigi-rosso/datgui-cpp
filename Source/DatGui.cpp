#include "DatGui.hpp"
#include "Gui.hpp"
#include "ActionRow.hpp"
#include "FolderRow.hpp"

using namespace splitcell;
using namespace splitcell::datgui;

static Gui* gui = NULL;

Data::Data() : m_Opaque(NULL)
{

}

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
	return gui->onMouseUp(x, y);
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

Action* Folder::add(std::string label, std::function<void()> callback)
{
	FolderRow* fr = reinterpret_cast<FolderRow*>(m_Opaque);

	Action* a = new Action();
	ActionRow* row = fr->add<ActionRow>();
	row->setLabel(label);
	row->setCallback(callback);
	a->m_Opaque = row;
	return a;
}

Action* DatGui::add(std::string label, std::function<void()> callback)
{
	if(gui == NULL)
	{
		return NULL;
	}
	Action* a = new Action();
	ActionRow* row = gui->add<ActionRow>();
	row->setLabel(label);
	row->setCallback(callback);
	a->m_Opaque = row;
	return a;
}

Folder* DatGui::addFolder(std::string label)
{
	if(gui == NULL)
	{
		return NULL;
	}
	Folder* a = new Folder();
	FolderRow* row = gui->add<FolderRow>();
	row->setLabel(label);
	a->m_Opaque = row;
	return a;
}