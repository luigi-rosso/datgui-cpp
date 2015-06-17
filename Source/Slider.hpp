#ifndef _SPLITCELL_DATGUI_SLIDER_HPP_
#define _SPLITCELL_DATGUI_SLIDER_HPP_

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
		class Slider : public Control
		{
			private:
				DatGui::Numeric* m_Data;
				bool m_IsDraggingCursor;

				std::function<void(float)> m_DragCallback;

			public:
				Slider();
				void draw(Renderer* renderer);

				bool onMouseDown(int x, int y);
				bool onMouseUp(int x, int y);
				bool onMouseMove(int x, int y);

				bool onKeyDown(Keyboard::Key key);
				bool onKeyUp(Keyboard::Key key);
				bool onCharInput(unsigned long int utf8);

				void onFocus();
				void onBlur();

				void setData(DatGui::Numeric* data);
				void setDragCallback(std::function<void(float)> callback);
		};
	}
}
#endif