#ifndef _SPLITCELL_GUI_HPP_
#define _SPLITCELL_GUI_HPP_

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
		class Gui
		{
			public:
				Gui(unsigned int screenWidth, unsigned int screenHeight);
				~Gui();

			private:
				Renderer* m_Renderer;
				Font* m_Font;
				unsigned int m_ScreenWidth;
				unsigned int m_ScreenHeight;

			public:
				void resizeScreen(unsigned int screenWidth, unsigned int screenHeight);
				void draw();
				
				bool onMouseDown(int x, int y);
				bool onMouseUp(int x, int y);
				bool onMouseMove(int x, int y);

				bool onKeyDown(Keyboard::Key key);
				bool onKeyUp(Keyboard::Key key);
		};
	}
}
#endif