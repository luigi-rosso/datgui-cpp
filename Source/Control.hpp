#ifndef _SPLITCELL_DATGUI_CONTROL_HPP_
#define _SPLITCELL_DATGUI_CONTROL_HPP_

#ifndef _SPLITCELL_DATGUI_HPP_
#include "DatGui.hpp"
#endif

#ifndef _SPLITCELL_DATGUI_RENDERER_HPP_
#include "Renderer.hpp"
#endif

namespace splitcell
{
	namespace datgui
	{
		class Control
		{
			public:
				virtual void draw(Renderer* renderer) = 0;

				virtual bool onMouseDown(int x, int y) = 0;
				virtual bool onMouseUp(int x, int y) = 0;
				virtual bool onMouseMove(int x, int y) = 0;

				virtual bool onKeyDown(Keyboard::Key key) = 0;
				virtual bool onKeyUp(Keyboard::Key key) = 0;

				virtual void onFocus() = 0;
				virtual void onBlur() = 0;
		};
	}
}
#endif