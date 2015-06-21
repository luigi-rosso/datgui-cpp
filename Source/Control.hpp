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
			private:
				float m_X;
				float m_Y;
				float m_Width;
				float m_Height;
				Color m_AccentColor;
				bool m_IsFocused;

			public:
				static const Color BackgroundColor;
				static const Color OverBackgroundColor;
				static const float Padding;

				Control();
				void place(float x, float y, float width, float height);

				virtual void draw(Renderer* renderer) = 0;

				virtual bool onMouseDown(int x, int y) = 0;
				virtual bool onMouseUp(int x, int y) = 0;
				virtual bool onMouseMove(int x, int y) = 0;
				virtual bool onMouseWheel(int x, int y, int dy) { return false; }

				virtual bool onKeyDown(Keyboard::Key key) = 0;
				virtual bool onKeyUp(Keyboard::Key key) = 0;
				virtual bool onCharInput(unsigned long int utf8) = 0;

				virtual void onFocus() = 0;
				virtual void onBlur() = 0;
				virtual void onPlaced() {}

				void focus() { m_IsFocused = true; onFocus(); }
				void blur() { m_IsFocused = false; onBlur(); }

				float x() { return m_X; }
				float y() { return m_Y; }
				float width() { return m_Width; }
				float height() { return m_Height; }
				Color accentColor() { return m_AccentColor; }
				void setAccentColor(Color c) { m_AccentColor = c; onSetAccentColor(); }
				bool isFocused() { return m_IsFocused; }

			private:
				virtual void onSetAccentColor() {}
		};
	}
}
#endif