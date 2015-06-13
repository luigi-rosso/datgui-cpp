#ifndef _SPLITCELL_DATGUI_ACTIONROW_HPP_
#define _SPLITCELL_DATGUI_ACTIONROW_HPP_

#ifndef _SPLITCELL_DATGUI_ROW_HPP_
#include "Row.hpp"
#endif


namespace splitcell
{
	namespace datgui
	{
		class ActionRow : public Row
		{
			private:
				std::function<void()> m_Callback;

			public:
				void onPlaced();
				float height();

				void draw(Renderer* renderer);
				
				bool onMouseDown(int x, int y);
				bool onMouseUp(int x, int y);
				bool onMouseMove(int x, int y);

				void setCallback(std::function<void()> callback);
		};
	}
}
#endif