#ifndef _SPLITCELL_DATGUI_SIZE_HPP_
#define _SPLITCELL_DATGUI_SIZE_HPP_

namespace splitcell
{
	namespace datgui
	{
		struct Size
		{
			float width;
			float height;

			Size() : width(0.0f), height(0.0f){}
			Size(float w, float h) : width(w), height(h){}
		};
	}
}
#endif