#ifndef _SPLITCELL_DATGUI_COMBOBOX_HPP_
#define _SPLITCELL_DATGUI_COMBOBOX_HPP_

#ifndef _SPLITCELL_DATGUI_CONTROL_HPP_
#include "Control.hpp"
#endif

#ifndef _SPLITCELL_DATGUI_COMBOBOXPOPUP_HPP_
#include "ComboBoxPopup.hpp"
#endif

#ifndef _SPLITCELL_DATGUI_HPP_
#include "DatGui.hpp"
#endif

namespace splitcell
{
	namespace datgui
	{
		class ComboBox : public Control
		{
			private:
				DatGui::Enum* m_Data;
				ComboBoxPopup m_Popup;
				float m_ActualWidth;
				float m_MaxEntryWidth;
				float m_MaxTextRenderWidth;

			public:
				ComboBox();
				void draw(Renderer* renderer);

				bool onMouseDown(int x, int y);
				bool onMouseUp(int x, int y);
				bool onMouseMove(int x, int y);

				bool onKeyDown(Keyboard::Key key);
				bool onKeyUp(Keyboard::Key key);
				bool onCharInput(unsigned long int utf8);

				void onFocus();
				void onBlur();
				void onPlaced();

				void setData(DatGui::Enum* data);

				float actualWidth() { return m_ActualWidth; }

			private:
				void onSetAccentColor();
		};
	}
}
#endif