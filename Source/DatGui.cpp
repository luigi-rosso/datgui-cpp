#include "DatGui.hpp"
#include "Gui.hpp"
#include "ActionRow.hpp"
#include "FolderRow.hpp"
#include "CheckboxRow.hpp"
#include "TextRow.hpp"
#include "NumericRow.hpp"

#include <limits>

using namespace splitcell;
using namespace splitcell::datgui;

static Gui* gui = NULL;

DatGui::Data::Data() : m_Opaque(NULL)
{

}

DatGui::Data::~Data()
{
	Row* r = reinterpret_cast<Row*>(m_Opaque);
	delete r;

}

DatGui::Numeric::Numeric() : m_NumDecimals(-1), m_Step(1.0f), m_Min(-std::numeric_limits<float>::max()), m_Max(std::numeric_limits<float>::max())
{

}

void DatGui::Numeric::set(float v)
{
	if(v == m_Value)
	{
		return;
	}
	m_Value = std::max(m_Min, std::min(m_Max, v));
	if(m_ChangeCallback != NULL)
	{
		m_ChangeCallback(v);
	}
}

void DatGui::Numeric::min(float m)
{
	m_Min = m;
	float v = std::max(m_Min, std::min(m_Max, m_Value));
	set(v);
}

float DatGui::Numeric::min()
{
	return m_Min;
}

void DatGui::Numeric::max(float m)
{
	m_Max = m;
	float v = std::max(m_Min, std::min(m_Max, m_Value));
	set(v);
}

float DatGui::Numeric::max()
{
	return m_Max;
}

void DatGui::Numeric::range(float mn, float mx)
{
	m_Min = mn;
	m_Max = mx;
	float v = std::max(m_Min, std::min(m_Max, m_Value));
	set(v);
}

void DatGui::Numeric::decimals(int num)
{
	m_NumDecimals = num;
}

int DatGui::Numeric::decimals()
{
	return m_NumDecimals;
}

void DatGui::Numeric::step(float st)
{
	m_Step = st;
}

float DatGui::Numeric::step()
{
	return m_Step;
}

float DatGui::Numeric::get()
{
	return m_Value;

}
void DatGui::Numeric::setCallback(std::function<void(float)> cb)
{
	m_ChangeCallback = cb;
}

void DatGui::Boolean::set(bool v)
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

bool DatGui::Boolean::get()
{
	return m_Value;
}

void DatGui::Boolean::setCallback(std::function<void(bool)> cb)
{
	m_ChangeCallback = cb;
}

void DatGui::Text::set(std::string v)
{
	if(m_Value == v)
	{
		return;
	}
	m_Value = v;

	if(m_ChangeCallback != NULL)
	{
		m_ChangeCallback(v);
	}
}

std::string DatGui::Text::get()
{
	return m_Value;
}

void DatGui::Text::setCallback(std::function<void(std::string)> cb)
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

bool DatGui::onCharInput(unsigned long int utf8)
{
	if(gui == NULL)
	{
		return false;
	}
	return gui->onCharInput(utf8);
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

void DatGui::Folder::remove(Data* data)
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

DatGui::Action* DatGui::Folder::addAction(std::string label, std::function<void()> callback)
{
	FolderRow* fr = reinterpret_cast<FolderRow*>(m_Opaque);

	Action* a = new Action();
	ActionRow* row = fr->add<ActionRow>();
	row->setLabel(label);
	row->setCallback(callback);
	a->m_Opaque = row;
	return a;
}

DatGui::Action* DatGui::addAction(std::string label, std::function<void()> callback)
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

DatGui::Folder* DatGui::addFolder(std::string label)
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

DatGui::Boolean* DatGui::Folder::addBoolean(std::string label, bool value, std::function<void(bool)> callback)
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

DatGui::Boolean* DatGui::addBoolean(std::string label, bool value, std::function<void(bool)> callback)
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

DatGui::Text* DatGui::addText(std::string label, std::string value, std::function<void(std::string)> callback)
{
	if(gui == NULL)
	{
		return NULL;
	}
	Text* a = new Text();
	a->set(value);
	a->setCallback(callback);

	TextRow* row = gui->add<TextRow>();
	row->setLabel(label);
	row->setData(a);
	a->m_Opaque = row;
	return a;
}

DatGui::Numeric* DatGui::addNumeric(std::string label, float value, std::function<void(float)> callback)
{
	if(gui == NULL)
	{
		return NULL;
	}
	Numeric* a = new Numeric();
	a->set(value);
	a->setCallback(callback);

	NumericRow* row = gui->add<NumericRow>();
	row->setLabel(label);
	row->setData(a);
	a->m_Opaque = row;
	return a;
}