#ifndef _SPLITCELL_DATGUI_HPP_
#define _SPLITCELL_DATGUI_HPP_

#ifndef _SPLITCELL_DATGUI_KEYBOARD_HPP_
#include "Key.hpp"
#endif

#include <functional>
#include <string>

namespace splitcell
{
	using namespace datgui;

	class DatGui;

	namespace datgui
	{
		class Folder;

		class Data
		{
			friend class splitcell::DatGui;
			friend class splitcell::Folder;
			private:
				void* m_Opaque;

			public:
				Data();
		};

		class Numeric : public Data
		{

		};

		class Action : public Data
		{

		};

		class Folder : public Data
		{
			public:
				Action* add(std::string label, std::function<void()> callback);
		};

		class EnumInt : public Data
		{

		};

		class EnumString : public Data
		{

		};
	}

	class DatGui
	{
		private:
			DatGui();
			~DatGui();

		public:
			static void draw();
			
			static bool initialize(unsigned int screenWidth, unsigned int screenHeight);
			static void resizeScreen(unsigned int screenWidth, unsigned int screenHeight);

			static bool onMouseDown(int x, int y);
			static bool onMouseUp(int x, int y);
			static bool onMouseMove(int x, int y);

			static bool onKeyDown(Keyboard::Key key);
			static bool onKeyUp(Keyboard::Key key);

			static Action* add(std::string label, std::function<void()> callback);
			static Folder* addFolder(std::string label);


	};
}
#endif