#ifndef _SPLITCELL_DATGUI_CLOSEROW_HPP_
#define _SPLITCELL_DATGUI_CLOSEROW_HPP_

#ifndef _SPLITCELL_DATGUI_ROW_HPP_
#include "Row.hpp"
#endif


namespace splitcell
{
	namespace datgui
	{
		class CloseRow : public Row
		{
			public:
				float height();

				void draw(Renderer* renderer);
				
				bool onMouseDown(int x, int y);
				bool onMouseUp(int x, int y);
				bool onMouseMove(int x, int y);

				void onPlaced() {}
		};
	}
}
#endif