#ifndef _SPLITCELL_DATGUI_GUI_HPP_
#define _SPLITCELL_DATGUI_GUI_HPP_

#ifndef _SPLITCELL_DATGUI_HPP_
#include "DatGui.hpp"
#endif

#ifndef _SPLITCELL_DATGUI_RENDERER_HPP_
#include "Renderer.hpp"
#endif

#ifndef _SPLITCELL_DATGUI_ROWCONTAINER_HPP_
#include "RowContainer.hpp"
#endif

#include <chrono>

namespace splitcell
{
	namespace datgui
	{
		class Control;
		class Row;

		class Gui : public RowContainer
		{
			public:
				static const float GuiWidth;
				static const float ColumnWidth;
				static const float LabelColumnWidth;
				static const float GuiPad;
				static const float RowHeight;
				static const float MarkerWidth;
				static const float LabelPadding;

				Gui(unsigned int screenWidth, unsigned int screenHeight);
				~Gui();


			private:
				static Gui* sm_Instance;
				Renderer* m_Renderer;
				Font* m_Font;
				Font* m_IconFont;
				unsigned int m_ScreenWidth;
				unsigned int m_ScreenHeight;
				float m_ScrollOffset;

				Control* m_Focus;
				Control* m_MouseCapture;
				Control* m_Popup;

				bool m_IsHidingRows;
				bool m_DidPopup;

				Row* m_CloseRow;
				std::chrono::time_point<std::chrono::system_clock> m_LastRenderTime;
				float m_ElapsedSeconds;

				void repositionRows();

			protected:
				void onRowsChanged();

			public:
				void resizeScreen(unsigned int screenWidth, unsigned int screenHeight);
				void draw();
				
				bool onMouseDown(int x, int y);
				bool onMouseUp(int x, int y);
				bool onMouseMove(int x, int y);
				bool onMouseWheel(int x, int y, float dy);

				bool onKeyDown(Keyboard::Key key);
				bool onKeyUp(Keyboard::Key key);
				bool onCharInput(unsigned long int utf8);

				static void captureMouse(Control* control);
				static void releaseMouse(Control* control);
				static void focus(Control* control);
				void setRowsHidden(bool hidden);
				bool isHidingRows() { return m_IsHidingRows; }

				static Font* font()
				{
					return sm_Instance->m_Font;
				}

				static Font* iconFont()
				{
					return sm_Instance->m_IconFont;
				}

				static void reposition()
				{
					sm_Instance->repositionRows();
				}

				static void toggleHideRows()
				{
					sm_Instance->setRowsHidden(!sm_Instance->isHidingRows());
				}

				static float elapsedSeconds()
				{
					return sm_Instance->m_ElapsedSeconds;
				}

				static void popup(Control* control);
				static void closePopup(Control* control = NULL);
				static bool isPopup(Control* control);

				static unsigned int screenHeight();
				static unsigned int screenWidth();
		};
	}
}
#endif