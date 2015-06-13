#ifndef _SPLITCELL_DATGUI_FOLDERROW_HPP_
#define _SPLITCELL_DATGUI_FOLDERROW_HPP_

#ifndef _SPLITCELL_DATGUI_ROW_HPP_
#include "Row.hpp"
#endif

#ifndef _SPLITCELL_DATGUI_ROWCONTAINER_HPP_
#include "RowContainer.hpp"
#endif

namespace splitcell
{
	namespace datgui
	{
		class FolderRow : public Row, public RowContainer
		{
			private:
				bool m_IsOpen;
				float m_LastY;
			public:
				FolderRow();

				float height();

				void draw(Renderer* renderer);
				
				bool onMouseDown(int x, int y);
				bool onMouseUp(int x, int y);
				bool onMouseMove(int x, int y);
				void onPlaced();
				void onMouseLeave();

			protected:
				void onRowsChanged();
		};
	}
}
#endif