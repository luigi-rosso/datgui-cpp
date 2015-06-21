#ifndef _SPLITCELL_DATGUI_ROW_HPP_
#define _SPLITCELL_DATGUI_ROW_HPP_

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
		class Row
		{
			private:
				float m_X;
				float m_Y;
				float m_Width;
				float m_LabelWidth;
				std::string m_Label;
				bool m_IsMouseOver;
				bool m_IsHidden;

			public:
				static const Color BackgroundColor;
				static const Color OverBackgroundColor;
				static const Color SeparatorColor;
				Row();
				virtual ~Row() {}

				void place(float x, float y, float width, float labelWidth);

				virtual void onPlaced() = 0;
				virtual float height() = 0;

				virtual void draw(Renderer* renderer) = 0;
				
				virtual bool onMouseDown(int x, int y) = 0;
				virtual bool onMouseUp(int x, int y) = 0;
				virtual bool onMouseMove(int x, int y) = 0;
				virtual bool onMouseWheel(int x, int y, float d) { return false; }
				virtual void onMouseEnter() { m_IsMouseOver = true; }
				virtual void onMouseLeave() { m_IsMouseOver = false; }

				bool isMouseOver() { return m_IsMouseOver; }

				float x() { return m_X; }
				float y() { return m_Y; }
				float width() { return m_Width; }
				float labelWidth() { return m_LabelWidth; }

				void setLabel(std::string label) { m_Label = label; }

				std::string& label() { return m_Label; }

				bool isHidden() { return m_IsHidden; }
				void hide(bool h) { m_IsHidden = h; }
		};
	}
}
#endif