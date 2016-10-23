#include <GLFW/glfw3.h>
#include <stdio.h>
#include <datgui/DatGui.hpp>

void error_callback(int error, const char* description)
{
    puts(description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        return;
    }

    splitcell::datgui::Keyboard::Key dkey;

    switch(key)
    {
    	case GLFW_KEY_A:
    		dkey = splitcell::datgui::Keyboard::A;
    		break;
    	case GLFW_KEY_B:
    		dkey = splitcell::datgui::Keyboard::B;
    		break;
    	case GLFW_KEY_C:
    		dkey = splitcell::datgui::Keyboard::C;
    		break;
    	case GLFW_KEY_D:
    		dkey = splitcell::datgui::Keyboard::D;
    		break;
    	case GLFW_KEY_E:
    		dkey = splitcell::datgui::Keyboard::E;
    		break;
    	case GLFW_KEY_F:
    		dkey = splitcell::datgui::Keyboard::G;
    		break;
    	case GLFW_KEY_G:
    		dkey = splitcell::datgui::Keyboard::G;
    		break;
    	case GLFW_KEY_H:
    		dkey = splitcell::datgui::Keyboard::H;
    		break;
    	case GLFW_KEY_I:
    		dkey = splitcell::datgui::Keyboard::I;
    		break;
    	case GLFW_KEY_J:
    		dkey = splitcell::datgui::Keyboard::J;
    		break;
    	case GLFW_KEY_K:
    		dkey = splitcell::datgui::Keyboard::K;
    		break;
    	case GLFW_KEY_L:
    		dkey = splitcell::datgui::Keyboard::L;
    		break;
    	case GLFW_KEY_M:
    		dkey = splitcell::datgui::Keyboard::M;
    		break;
    	case GLFW_KEY_N:
    		dkey = splitcell::datgui::Keyboard::N;
    		break;
    	case GLFW_KEY_O:
    		dkey = splitcell::datgui::Keyboard::O;
    		break;
    	case GLFW_KEY_P:
    		dkey = splitcell::datgui::Keyboard::P;
    		break;
    	case GLFW_KEY_Q:
    		dkey = splitcell::datgui::Keyboard::Q;
    		break;
    	case GLFW_KEY_R:
    		dkey = splitcell::datgui::Keyboard::R;
    		break;
    	case GLFW_KEY_S:
    		dkey = splitcell::datgui::Keyboard::S;
    		break;
    	case GLFW_KEY_T:
    		dkey = splitcell::datgui::Keyboard::T;
    		break;
    	case GLFW_KEY_U:
    		dkey = splitcell::datgui::Keyboard::U;
    		break;
    	case GLFW_KEY_V:
    		dkey = splitcell::datgui::Keyboard::V;
    		break;
    	case GLFW_KEY_W:
    		dkey = splitcell::datgui::Keyboard::W;
    		break;
    	case GLFW_KEY_X:
    		dkey = splitcell::datgui::Keyboard::X;
    		break;
    	case GLFW_KEY_Y:
    		dkey = splitcell::datgui::Keyboard::Y;
    		break;
    	case GLFW_KEY_Z:
    		dkey = splitcell::datgui::Keyboard::Z;
    		break;

    	case GLFW_KEY_0:
    		dkey = splitcell::datgui::Keyboard::Num0;
    		break;
    	case GLFW_KEY_1:
    		dkey = splitcell::datgui::Keyboard::Num1;
    		break;
    	case GLFW_KEY_2:
    		dkey = splitcell::datgui::Keyboard::Num2;
    		break;
    	case GLFW_KEY_3:
    		dkey = splitcell::datgui::Keyboard::Num3;
    		break;
    	case GLFW_KEY_4:
    		dkey = splitcell::datgui::Keyboard::Num4;
    		break;
    	case GLFW_KEY_5:
    		dkey = splitcell::datgui::Keyboard::Num5;
    		break;
    	case GLFW_KEY_6:
    		dkey = splitcell::datgui::Keyboard::Num6;
    		break;
    	case GLFW_KEY_7:
    		dkey = splitcell::datgui::Keyboard::Num7;
    		break;
    	case GLFW_KEY_8:
    		dkey = splitcell::datgui::Keyboard::Num8;
    		break;
    	case GLFW_KEY_9:
    		dkey = splitcell::datgui::Keyboard::Num9;
    		break;


    	case GLFW_KEY_ESCAPE:
    		dkey = splitcell::datgui::Keyboard::Escape;
    		break;
    	case GLFW_KEY_LEFT_CONTROL:
    		dkey = splitcell::datgui::Keyboard::LControl;
    		break;
    	case GLFW_KEY_LEFT_SHIFT:
    		dkey = splitcell::datgui::Keyboard::LShift;
    		break;
    	case GLFW_KEY_LEFT_ALT:
    		dkey = splitcell::datgui::Keyboard::LAlt;
    		break;
    	case GLFW_KEY_LEFT_SUPER:
    		dkey = splitcell::datgui::Keyboard::LSystem;
    		break;
    	case GLFW_KEY_RIGHT_CONTROL:
    		dkey = splitcell::datgui::Keyboard::RControl;
    		break;
    	case GLFW_KEY_RIGHT_SHIFT:
    		dkey = splitcell::datgui::Keyboard::RShift;
    		break;
    	case GLFW_KEY_RIGHT_ALT:
    		dkey = splitcell::datgui::Keyboard::RAlt;
    		break;
    	case GLFW_KEY_RIGHT_SUPER:
    		dkey = splitcell::datgui::Keyboard::RSystem;
    		break;
    	case GLFW_KEY_MENU:
    		dkey = splitcell::datgui::Keyboard::Menu;
    		break;

    	case GLFW_KEY_LEFT_BRACKET:
    		dkey = splitcell::datgui::Keyboard::LBracket;
    		break;
    	case GLFW_KEY_RIGHT_BRACKET:
    		dkey = splitcell::datgui::Keyboard::RBracket;
    		break;
    	case GLFW_KEY_SEMICOLON:
    		dkey = splitcell::datgui::Keyboard::SemiColon;
    		break;
    	case GLFW_KEY_COMMA:
    		dkey = splitcell::datgui::Keyboard::Comma;
    		break;
    	case GLFW_KEY_PERIOD:
    		dkey = splitcell::datgui::Keyboard::Period;
    		break;
    	case GLFW_KEY_APOSTROPHE:
    		dkey = splitcell::datgui::Keyboard::Quote;
    		break;
    	case GLFW_KEY_SLASH:
    		dkey = splitcell::datgui::Keyboard::Slash;
    		break;
    	case GLFW_KEY_BACKSLASH:
    		dkey = splitcell::datgui::Keyboard::BackSlash;
    		break;
    	case GLFW_KEY_GRAVE_ACCENT:
    		dkey = splitcell::datgui::Keyboard::Tilde;
    		break;
    	case GLFW_KEY_EQUAL:
    		dkey = splitcell::datgui::Keyboard::Equal;
    		break;
    	case GLFW_KEY_MINUS:
    		dkey = splitcell::datgui::Keyboard::Dash;
    		break;
    	case GLFW_KEY_SPACE:
    		dkey = splitcell::datgui::Keyboard::Space;
    		break;
    	case GLFW_KEY_ENTER:
    		dkey = splitcell::datgui::Keyboard::Return;
    		break;
    	case GLFW_KEY_BACKSPACE:
    		dkey = splitcell::datgui::Keyboard::Back;
    		break;
    	case GLFW_KEY_TAB:
    		dkey = splitcell::datgui::Keyboard::Tab;
    		break;
    	case GLFW_KEY_PAGE_UP:
    		dkey = splitcell::datgui::Keyboard::PageUp;
    		break;
    	case GLFW_KEY_PAGE_DOWN:
    		dkey = splitcell::datgui::Keyboard::PageDown;
    		break;
    	case GLFW_KEY_END:
    		dkey = splitcell::datgui::Keyboard::End;
    		break;
    	case GLFW_KEY_HOME:
    		dkey = splitcell::datgui::Keyboard::Home;
    		break;
    	case GLFW_KEY_INSERT:
    		dkey = splitcell::datgui::Keyboard::Insert;
    		break;
    	case GLFW_KEY_DELETE:
    		dkey = splitcell::datgui::Keyboard::Delete;
    		break;
    	case GLFW_KEY_KP_ADD:
    		dkey = splitcell::datgui::Keyboard::Add;
    		break;
    	case GLFW_KEY_KP_SUBTRACT:
    		dkey = splitcell::datgui::Keyboard::Subtract;
    		break;
    	case GLFW_KEY_KP_MULTIPLY:
    		dkey = splitcell::datgui::Keyboard::Multiply;
    		break;
    	case GLFW_KEY_KP_DIVIDE:
    		dkey = splitcell::datgui::Keyboard::Divide;
    		break;
    	case GLFW_KEY_LEFT:
    		dkey = splitcell::datgui::Keyboard::Left;
    		break;
    	case GLFW_KEY_RIGHT:
    		dkey = splitcell::datgui::Keyboard::Right;
    		break;
    	case GLFW_KEY_DOWN:
    		dkey = splitcell::datgui::Keyboard::Down;
    		break;
    	case GLFW_KEY_UP:
    		dkey = splitcell::datgui::Keyboard::Up;
    		break;
    	case GLFW_KEY_KP_0:
    		dkey = splitcell::datgui::Keyboard::Numpad0;
    		break;
    	case GLFW_KEY_KP_1:
    		dkey = splitcell::datgui::Keyboard::Numpad1;
    		break;
    	case GLFW_KEY_KP_2:
    		dkey = splitcell::datgui::Keyboard::Numpad2;
    		break;
    	case GLFW_KEY_KP_3:
    		dkey = splitcell::datgui::Keyboard::Numpad3;
    		break;
    	case GLFW_KEY_KP_4:
    		dkey = splitcell::datgui::Keyboard::Numpad4;
    		break;
    	case GLFW_KEY_KP_5:
    		dkey = splitcell::datgui::Keyboard::Numpad5;
    		break;
    	case GLFW_KEY_KP_6:
    		dkey = splitcell::datgui::Keyboard::Numpad6;
    		break;
    	case GLFW_KEY_KP_7:
    		dkey = splitcell::datgui::Keyboard::Numpad7;
    		break;
    	case GLFW_KEY_KP_8:
    		dkey = splitcell::datgui::Keyboard::Numpad8;
    		break;
    	case GLFW_KEY_KP_9:
    		dkey = splitcell::datgui::Keyboard::Numpad9;
    		break;
    	case GLFW_KEY_F1:
    		dkey = splitcell::datgui::Keyboard::F1;
    		break;
    	case GLFW_KEY_F2:
    		dkey = splitcell::datgui::Keyboard::F2;
    		break;
    	case GLFW_KEY_F3:
    		dkey = splitcell::datgui::Keyboard::F3;
    		break;
    	case GLFW_KEY_F4:
    		dkey = splitcell::datgui::Keyboard::F4;
    		break;
    	case GLFW_KEY_F5:
    		dkey = splitcell::datgui::Keyboard::F5;
    		break;
    	case GLFW_KEY_F6:
    		dkey = splitcell::datgui::Keyboard::F6;
    		break;
    	case GLFW_KEY_F7:
    		dkey = splitcell::datgui::Keyboard::F7;
    		break;
    	case GLFW_KEY_F8:
    		dkey = splitcell::datgui::Keyboard::F8;
    		break;
    	case GLFW_KEY_F9:
    		dkey = splitcell::datgui::Keyboard::F9;
    		break;
    	case GLFW_KEY_F10:
    		dkey = splitcell::datgui::Keyboard::F10;
    		break;
    	case GLFW_KEY_F11:
    		dkey = splitcell::datgui::Keyboard::F11;
    		break;
    	case GLFW_KEY_F12:
    		dkey = splitcell::datgui::Keyboard::F12;
    		break;
    	case GLFW_KEY_F13:
    		dkey = splitcell::datgui::Keyboard::F13;
    		break;
    	case GLFW_KEY_F14:
    		dkey = splitcell::datgui::Keyboard::F14;
    		break;
    	case GLFW_KEY_F15:
    		dkey = splitcell::datgui::Keyboard::F15;
    		break;
    	case GLFW_KEY_PAUSE:
    		dkey = splitcell::datgui::Keyboard::Pause;
    		break;
    }

    if(action == GLFW_PRESS)
    {
    	splitcell::DatGui::onKeyDown(dkey);
    	
    }
    else if(action == GLFW_RELEASE)
    {
    	splitcell::DatGui::onKeyUp(dkey);
    }
    //splitcell::DatGui::onCharInput(event.text.unicode);

}

void character_callback(GLFWwindow* window, unsigned int codepoint)
{
	splitcell::DatGui::onCharInput(codepoint);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	splitcell::DatGui::onMouseMove(xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
    if (action == GLFW_PRESS)
    {
    	splitcell::DatGui::onMouseDown(xpos, ypos);
    }
    else if(action == GLFW_RELEASE)
    {
    	splitcell::DatGui::onMouseUp(xpos, ypos);	
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	splitcell::DatGui::onMouseWheel(xpos, ypos, xoffset);
}

int main(int argc, char** argv)
{
	if(!glfwInit())
	{
		return 0;
	}
	
	glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    int initialWindowWidth = 640;
    int initialWindowHeight = 480;

	GLFWwindow* window = glfwCreateWindow(initialWindowWidth, initialWindowHeight, "datgui", NULL, NULL);
	if (!window)
	{
		// Window or OpenGL context creation failed
		printf("Failed to make window or GL.\n");
		glfwTerminate();
		return 0;
	}

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCharCallback(window, character_callback);

	glfwMakeContextCurrent(window);

	// Enable VSYNC.
	glfwSwapInterval(1);

	// --
    // -- Set up DatGui and add some entries.
    // --

    splitcell::DatGui::initialize(initialWindowWidth, initialWindowHeight);


    splitcell::DatGui::addAction("explode", []()
    {
        printf("HIT ACTION\n");
    });
    auto folder = splitcell::DatGui::addFolder("Explosions");

    folder->addAction("explode 3", []()
    {
        printf("HIT ACTION 3\n");
    });

    auto b = folder->addBoolean("show mesh", true);

    folder->addAction("explode 4", []()
    {
        printf("HIT ACTION 4\n");
    });


    folder->addBoolean("displayOutline", false, [](bool changedTo)
    {
        printf("Checkbox changd to: %i\n", changedTo ? 1 : 0);
    });
    
    folder->addText("message", "test", [](std::string val)
    {
        printf("Message changed to: %s\n", val.c_str());
    });

    auto n2 = folder->addNumeric("percent", 0.0f, [](float val)
    {
        printf("percent changed to: %f\n", val);
    });
    n2->decimals(-1);
    n2->step(1.0f);
    n2->range(0.0f, 100.0f);

    folder->addEnum("Speed", { { "Stopped", 0.0f }, { "Slow", 0.1f }, { "Fast", 5.0f } }, 0.0f, [](splitcell::DatGui::Enum::Entry* entry)
    {
        printf("speed: %f\n", entry->value());
    } );

    folder->remove(b);

    splitcell::DatGui::addAction("explode 2", []()
    {
        printf("HIT ACTION 2\n");
    });

    splitcell::DatGui::addBoolean("displayOutline", false, [](bool changedTo)
    {
        printf("Checkbox changd to: %i\n", changedTo ? 1 : 0);
    });
    
    splitcell::DatGui::addText("message", "test", [](std::string val)
    {
        printf("Message changed to: %s\n", val.c_str());
    });

    auto n = splitcell::DatGui::addNumeric("pi", 3.145f, [](float val)
    {
        printf("PI changed to: %f\n", val);
    });
    n->decimals(-1);
    n->step(0.1f);
    n = splitcell::DatGui::addNumeric("percent", 0.0f, [](float val)
    {
        printf("percent changed to: %f\n", val);
    });
    n->decimals(-1);
    n->step(1.0f);
    n->range(0.0f, 100.0f);

    splitcell::DatGui::addEnum("Speed", { { "Stopped", 0.0f }, { "Slow", 0.1f }, { "Fast", 5.0f }, { "Faster", 5.0f }, { "Fasterest", 5.0f } }, 0.0f, [](splitcell::DatGui::Enum::Entry* entry)
    {
        printf("speed: %f\n", entry->value());
    } );


    int width = initialWindowWidth, height = initialWindowHeight;
    int lastWidth = width, lastHeight = height;
	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);
		if(width != lastWidth || height != lastHeight)
		{
			lastWidth = width;
			lastHeight = height;
			splitcell::DatGui::resizeScreen(width, height);
		}
		glViewport(0, 0, width, height);
		glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

		glClear(GL_COLOR_BUFFER_BIT);
		
		splitcell::DatGui::draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}