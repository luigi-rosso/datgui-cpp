#ifndef _SPLITCELL_DATGUI_TEXTROW_HPP_
#define _SPLITCELL_DATGUI_TEXTROW_HPP_

#ifndef _SPLITCELL_DATGUI_ROW_HPP_
#include "Row.hpp"
#endif

#ifndef _SPLITCELL_DATGUI_HPP_
#include "DatGui.hpp"
#endif

#ifndef _SPLITCELL_DATGUI_TEXTFIELD_HPP_
#include "TextField.hpp"
#endif

namespace splitcell
{
	namespace datgui
	{
		class TextRow : public Row
		{
			private:
				DatGui::Text* m_Data;
				TextField m_TextField;

			public:
				TextRow();
				void onPlaced();
				float height();

				void draw(Renderer* renderer);
				
				bool onMouseDown(int x, int y);
				bool onMouseUp(int x, int y);
				bool onMouseMove(int x, int y);

				void setData(DatGui::Text* data);
		};
	}
}
#endif