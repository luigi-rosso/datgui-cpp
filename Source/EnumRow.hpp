#ifndef _SPLITCELL_DATGUI_ENUMROW_HPP_
#define _SPLITCELL_DATGUI_ENUMROW_HPP_

#ifndef _SPLITCELL_DATGUI_ROW_HPP_
#include "Row.hpp"
#endif

#ifndef _SPLITCELL_DATGUI_HPP_
#include "DatGui.hpp"
#endif

#ifndef _SPLITCELL_DATGUI_COMBOBOX_HPP_
#include "ComboBox.hpp"
#endif

namespace splitcell
{
	namespace datgui
	{
		class EnumRow : public Row
		{
			private:
				DatGui::Enum* m_Data;
				ComboBox m_ComboBox;

			public:
				EnumRow();
				void onPlaced();
				float height();

				void draw(Renderer* renderer);
				
				bool onMouseDown(int x, int y);
				bool onMouseUp(int x, int y);
				bool onMouseMove(int x, int y);

				void setData(DatGui::Enum* data);
		};
	}
}
#endif