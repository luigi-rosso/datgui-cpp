#ifndef _SPLITCELL_DATGUI_TEXTFIELD_HPP_
#define _SPLITCELL_DATGUI_TEXTFIELD_HPP_

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
		class TextField : public Control
		{
			private:
				DatGui::Text* m_Data;
				float m_Offset;
				int m_SelectedIndex;
				bool m_IsDraggingCursor;
				int m_SelectionStartIndex;
				int m_SelectionEndIndex;

				void injectText(std::string text);
				void ensureCursorVisible();
				bool eraseSelection();

				float m_MouseDownSeconds;
				float m_IsShiftPressed;

			public:
				TextField();
				void draw(Renderer* renderer);

				bool onMouseDown(int x, int y);
				bool onMouseUp(int x, int y);
				bool onMouseMove(int x, int y);

				bool onKeyDown(Keyboard::Key key);
				bool onKeyUp(Keyboard::Key key);
				bool onCharInput(unsigned long int utf8);

				void onFocus();
				void onBlur();

				void setData(DatGui::Text* data);
		};
	}
}
#endif