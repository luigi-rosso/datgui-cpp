#ifndef _SPLITCELL_DATGUI_ROWCONTAINER_HPP_
#define _SPLITCELL_DATGUI_ROWCONTAINER_HPP_

#include <vector>

namespace splitcell
{
	namespace datgui
	{
		class Row;
		class Renderer;
		
		class RowContainer
		{
			private:
				Row* m_MouseOverRow;
			protected:
				std::vector<Row*> m_Rows;

				void addRow(Row* row);
				void insertRow(int index, Row* row);
				void repositionRows(float x, float y, float width, float labelWidth);

				virtual void onRowsChanged() = 0;

				bool onMouseDown(int x, int y);
				bool onMouseUp(int x, int y);
				bool onMouseMove(int x, int y);

				void forceMouseLeave();
				void draw(Renderer* renderer);
			public:
				RowContainer();

				template<typename T>
				T* add()
				{
					T* row = new T();
					addRow(row);
					return row;
				}

				template<typename T>
				T* insert(int index)
				{
					T* row = new T();
					insertRow(index, row);
					return row;
				}

				void removeRow(Row* row);
		};
	}
}
#endif