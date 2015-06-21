#ifndef _SPLITCELL_DATGUI_HPP_
#define _SPLITCELL_DATGUI_HPP_

#ifndef _SPLITCELL_DATGUI_KEYBOARD_HPP_
#include "Key.hpp"
#endif

#include <functional>
#include <string>
#include <vector>

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
				friend class DatGui;
				private:
					float m_Value;
					int m_NumDecimals;
					float m_Step;
					float m_Min;
					float m_Max;

					std::function<void(float)> m_ChangeCallback;
					Numeric();
				public:
					void set(float v);
					float get();
					void setCallback(std::function<void(float)> cb);

					void decimals(int num);
					int decimals();

					void step(float st);
					float step();

					void min(float m);
					float min();
					void max(float m);
					float max();
					void range(float mn, float mx);
			};

			class Boolean : public Data
			{
				friend class DatGui;
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
				friend class DatGui;
			};

			class Text : public Data
			{
				friend class DatGui;
				private:
					std::string m_Value;
					std::function<void(std::string)> m_ChangeCallback;

				public:
					void set(std::string v);
					std::string get();
					void setCallback(std::function<void(std::string)> cb);
			};

			class Enum : public Data
			{
				friend class DatGui;
				public:
					class Entry
					{
						friend class DatGui;
						private:
							std::string m_Label;
							float m_Value;
						public:
							Entry(std::string lbl, float val);
							Entry(std::string lbl);
							std::string label();
							float value();
					};
				private:
					std::vector<Entry> m_Entries;
					std::function<void(Enum::Entry*)> m_ChangeCallback;
					Entry* m_SelectedEntry;
					Enum();

				public:
					int numEntries();
					Entry* entry(int index);

					float value();
					Entry* selection();
					void setValue(float v);
					void setValue(std::string v);
					void setCallback(std::function<void(Enum::Entry*)> cb);
			};

			class Folder : public Data
			{
				friend class DatGui;
				public:
					Action* addAction(std::string label, std::function<void()> callback);
					Boolean* addBoolean(std::string label, bool value, std::function<void(bool)> callback = NULL);
					Text* addText(std::string label, std::string value, std::function<void(std::string)> callback = NULL);
					Numeric* addNumeric(std::string label, float value, std::function<void(float)> callback = NULL);
					Enum* addEnum(std::string label, std::vector<Enum::Entry> entries, float selectedValue = 0.0f, std::function<void(Enum::Entry*)> callback = NULL);
					void remove(Data* data);
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
			static Numeric* addNumeric(std::string label, float value, std::function<void(float)> callback = NULL);
			static Enum* addEnum(std::string label, std::vector<Enum::Entry> entries, float selectedValue = 0.0f, std::function<void(Enum::Entry*)> callback = NULL);
			static Folder* addFolder(std::string label);

			static void remove(Data* data);


	};
}
#endif