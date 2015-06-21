#ifndef _SPLITCELL_DATGUI_COMBOBOXPOPUP_HPP_
#define _SPLITCELL_DATGUI_COMBOBOXPOPUP_HPP_

#ifndef _SPLITCELL_DATGUI_CONTROL_HPP_
#include "Control.hpp"
#endif

#ifndef _SPLITCELL_DATGUI_HPP_
#include "DatGui.hpp"
#endif

namespace splitcell
{
	namespace datgui
	{
		class ComboBoxPopup : public Control
		{
			private:
				DatGui::Enum* m_Data;
				float m_ScrollOffset;
			public:
				ComboBoxPopup();
				void draw(Renderer* renderer);

				bool onMouseDown(int x, int y);
				bool onMouseUp(int x, int y);
				bool onMouseMove(int x, int y);
				bool onMouseWheel(int x, int y, float dy);

				bool onKeyDown(Keyboard::Key key);
				bool onKeyUp(Keyboard::Key key);
				bool onCharInput(unsigned long int utf8);

				void onFocus();
				void onBlur();
				void onPlaced();

				void setData(DatGui::Enum* data);

				float contentHeight();
		};
	}
}
#endif