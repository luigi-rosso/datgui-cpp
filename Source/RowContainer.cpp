#include "RowContainer.hpp"
#include "Row.hpp"

using namespace splitcell::datgui;

RowContainer::RowContainer() : m_MouseOverRow(NULL)
{

}

void RowContainer::repositionRows(float x, float y, float width, float labelWidth)
{
	for(auto row : m_Rows)
	{
		if(!row->isHidden())
		{
			row->place(x, y, width, labelWidth);
			y += row->height();
		}
	}
}

void RowContainer::addRow(Row* row)
{
	m_Rows.push_back(row);
	onRowsChanged();
}

void RowContainer::insertRow(int index, Row* row)
{
	m_Rows.insert(m_Rows.begin()+index, row);
	onRowsChanged();
}

void RowContainer::removeRow(Row* row)
{
	for(auto itr = m_Rows.begin(); itr != m_Rows.end(); itr++)
	{
		if(*itr == row)
		{
			m_Rows.erase(itr);
			break;
		}
	}
	onRowsChanged();
}

bool RowContainer::onMouseDown(int x, int y)
{
	for(auto row : m_Rows)
	{
		if(!row->isHidden() && x >= row->x() && x <= row->x() + row->width() && y >= row->y() && y <= row->y() + row->height())
		{
			return row->onMouseDown(x - row->x(), y - row->y());
		}
	}
	return false;
}

bool RowContainer::onMouseUp(int x, int y)
{
	for(auto row : m_Rows)
	{
		if(!row->isHidden() && x >= row->x() && x <= row->x() + row->width() && y >= row->y() && y <= row->y() + row->height())
		{
			return row->onMouseUp(x - row->x(), y - row->y());
		}
	}
	return false;
}

bool RowContainer::onMouseMove(int x, int y)
{
	for(auto row : m_Rows)
	{
		if(!row->isHidden() && x >= row->x() && x <= row->x() + row->width() && y >= row->y() && y <= row->y() + row->height())
		{
			if(m_MouseOverRow != row)
			{
				if(m_MouseOverRow != NULL)
				{
					m_MouseOverRow->onMouseLeave();
				}

				row->onMouseEnter();

				m_MouseOverRow = row;
			}
			return row->onMouseMove(x - row->x(), y - row->y());
		}
	}

	if(m_MouseOverRow != NULL)
	{
		m_MouseOverRow->onMouseLeave();
		m_MouseOverRow = NULL;
	}
	return false;
}

void RowContainer::forceMouseLeave()
{
	if(m_MouseOverRow != NULL)
	{
		m_MouseOverRow->onMouseLeave();
		m_MouseOverRow = NULL;
	}
}

void RowContainer::draw(Renderer* renderer)
{
	for(auto row : m_Rows)
	{
		if(row->isHidden())
		{
			continue;
		}
		row->draw(renderer);
	}
}