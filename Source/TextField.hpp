#ifndef _SPLITCELL_DATGUI_TEXTFIELD_HPP_
#define _SPLITCELL_DATGUI_TEXTFIELD_HPP_

#ifndef _SPLITCELL_DATGUI_CONTROL_HPP_
#include "Control.hpp"
#endif

namespace splitcell
{
	namespace datgui
	{
		class TextField
		{
			public:
				void draw(Renderer* renderer);

				bool onMouseDown(int x, int y);
				bool onMouseUp(int x, int y);
				bool onMouseMove(int x, int y);

				bool onKeyDown(Keyboard::Key key);
				bool onKeyUp(Keyboard::Key key);

				void onFocus();
				void onBlur();
		};
	}
}
#endif