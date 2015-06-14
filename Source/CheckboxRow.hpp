#ifndef _SPLITCELL_DATGUI_CHECKBOXROW_HPP_
#define _SPLITCELL_DATGUI_CHECKBOXROW_HPP_

#ifndef _SPLITCELL_DATGUI_ROW_HPP_
#include "Row.hpp"
#endif

#ifndef _SPLITCELL_DATGUI_HPP_
#include "DatGui.hpp"
#endif

namespace splitcell
{
	namespace datgui
	{
		class CheckboxRow : public Row
		{
			private:
				Boolean* m_Data;

			public:
				CheckboxRow();
				void onPlaced();
				float height();

				void draw(Renderer* renderer);
				
				bool onMouseDown(int x, int y);
				bool onMouseUp(int x, int y);
				bool onMouseMove(int x, int y);

				void setData(Boolean* data);
		};
	}
}
#endif