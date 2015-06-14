#include "DatGui.hpp"
#include "Gui.hpp"
#include "ActionRow.hpp"
#include "FolderRow.hpp"
#include "CheckboxRow.hpp"

using namespace splitcell;
using namespace splitcell::datgui;

static Gui* gui = NULL;

Data::Data() : m_Opaque(NULL)
{

}

Data::~Data()
{
	Row* r = reinterpret_cast<Row*>(m_Opaque);
	delete r;

}

void Boolean::set(bool v)
{
	if(v == m_Value)
	{
		return;
	}
	m_Value = v;
	if(m_ChangeCallback != NULL)
	{
		m_ChangeCallback(v);
	}
}

bool Boolean::get()
{
	return m_Value;
}

void Boolean::setCallback(std::function<void(bool)> cb)
{
	m_ChangeCallback = cb;
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

void Folder::remove(Data* data)
{
	Row* row = reinterpret_cast<Row*>(data->m_Opaque);
	FolderRow* fr = reinterpret_cast<FolderRow*>(m_Opaque);
	if(fr != NULL)
	{
		fr->removeRow(row);
	}
	delete data;
}

void DatGui::remove(Data* data)
{
	Row* row = reinterpret_cast<Row*>(data->m_Opaque);
	if(gui != NULL)
	{
		gui->removeRow(row);
	}
	delete data;
}

Action* Folder::addAction(std::string label, std::function<void()> callback)
{
	FolderRow* fr = reinterpret_cast<FolderRow*>(m_Opaque);

	Action* a = new Action();
	ActionRow* row = fr->add<ActionRow>();
	row->setLabel(label);
	row->setCallback(callback);
	a->m_Opaque = row;
	return a;
}

Action* DatGui::addAction(std::string label, std::function<void()> callback)
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

Boolean* Folder::addBoolean(std::string label, bool value, std::function<void(bool)> callback)
{
	FolderRow* fr = reinterpret_cast<FolderRow*>(m_Opaque);

	Boolean* a = new Boolean();
	a->set(value);
	a->setCallback(callback);

	CheckboxRow* row = fr->add<CheckboxRow>();
	row->setLabel(label);
	row->setData(a);
	a->m_Opaque = row;
	return a;
}

Boolean* DatGui::addBoolean(std::string label, bool value, std::function<void(bool)> callback)
{
	if(gui == NULL)
	{
		return NULL;
	}
	Boolean* a = new Boolean();
	a->set(value);
	a->setCallback(callback);

	CheckboxRow* row = gui->add<CheckboxRow>();
	row->setLabel(label);
	row->setData(a);
	a->m_Opaque = row;
	return a;
}