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

	class DatGui
	{
		public:
			class Folder;

			class Data
			{
				friend class DatGui;
				friend class Folder;
				protected:
					void* m_Opaque;

				protected:
					Data();
					virtual ~Data();
			};

			class Numeric : public Data
			{

			};

			class Boolean : public Data
			{
				private:
					bool m_Value;
					std::function<void(bool)> m_ChangeCallback;

				public:
					void set(bool v);
					bool get();
					void setCallback(std::function<void(bool)> cb);
			};

			class Action : public Data
			{
			};

			class Text : public Data
			{
				private:
					std::string m_Value;
					std::function<void(std::string)> m_ChangeCallback;

				public:
					void set(std::string v);
					std::string get();
					void setCallback(std::function<void(std::string)> cb);
			};

			class Folder : public Data
			{
				public:
					Action* addAction(std::string label, std::function<void()> callback);
					Boolean* addBoolean(std::string label, bool value, std::function<void(bool)> callback = NULL);
					void remove(Data* data);
			};

			class EnumInt : public Data
			{

			};

			class EnumString : public Data
			{

			};

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
			static bool onCharInput(unsigned long int utf8);

			static Action* addAction(std::string label, std::function<void()> callback);
			static Boolean* addBoolean(std::string label, bool value, std::function<void(bool)> callback = NULL);
			static Text* addText(std::string label, std::string value, std::function<void(std::string)> callback = NULL);
			static Folder* addFolder(std::string label);

			static void remove(Data* data);


	};
}
#endif