#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <datgui/DatGui.hpp>

int main(int argc, char** argv)
{
	sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.stencilBits = 8;
    contextSettings.antialiasingLevel = 0;
    float screenScale = 1.0f;

    sf::RenderWindow window(sf::VideoMode(640, 480), "splitcell - datgui", sf::Style::Default, contextSettings);

    window.setVerticalSyncEnabled(true);

    sf::Vector2u size = window.getSize();

    splitcell::DatGui::initialize(size.x, size.y);


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
        printf("Text changde to: %s\n", val.c_str());
    });


    folder->remove(b);

    sf::Clock clock;
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
               case sf::Event::KeyPressed:
                    splitcell::DatGui::onKeyDown((splitcell::datgui::Keyboard::Key)event.key.code);
                    break;
                case sf::Event::KeyReleased:
                    splitcell::DatGui::onKeyUp((splitcell::datgui::Keyboard::Key)event.key.code);
                    break;
                case sf::Event::TextEntered:
                    splitcell::DatGui::onCharInput(event.text.unicode);
                    break;
                 /*case sf::Event::MouseButtonPressed:
                {
                    SplitCell::Mouse::Button buttonType;
                    switch(event.mouseButton.button)
                    {
                        case sf::Mouse::Left:
                            buttonType = SplitCell::Mouse::Left;
                            break;
                        case sf::Mouse::Right:
                            buttonType = SplitCell::Mouse::Right;
                            break;
                        case sf::Mouse::Middle:
                            buttonType = SplitCell::Mouse::Middle;
                            break;
                    }
                    
                    application.OnMouseDown(buttonType, event.mouseButton.x, event.mouseButton.y);
                    break;
                }
                case sf::Event::MouseButtonReleased:
                {
                    SplitCell::Mouse::Button buttonType;
                    switch(event.mouseButton.button)
                    {
                        case sf::Mouse::Left:
                            buttonType = SplitCell::Mouse::Left;
                            break;
                        case sf::Mouse::Right:
                            buttonType = SplitCell::Mouse::Right;
                            break;
                        case sf::Mouse::Middle:
                            buttonType = SplitCell::Mouse::Middle;
                            break;
                    }
                    
                    application.OnMouseUp(buttonType, event.mouseButton.x, event.mouseButton.y);
                    break;
                }*/
                case sf::Event::MouseButtonPressed:
                {
                    //touch.set(event.mouseButton.x, event.mouseButton.y);
                    //application.onTouchDown(&touch, 1, NULL, 0);
                    splitcell::DatGui::onMouseDown(event.mouseButton.x, event.mouseButton.y);
                    break;
                }
                case sf::Event::MouseButtonReleased:
                {
                    //touch.set(event.mouseButton.x, event.mouseButton.y);
                    //application.onTouchUp(&touch, 1, NULL, 0);
                    splitcell::DatGui::onMouseUp(event.mouseButton.x, event.mouseButton.y);
                    break;
                }
                case sf::Event::MouseMoved:
                    splitcell::DatGui::onMouseMove(event.mouseMove.x, event.mouseMove.y);
                    break;
                case sf::Event::Resized:
                	splitcell::DatGui::resizeScreen(event.size.width, event.size.height);
                    break;
                default:
                    break;
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        
        sf::Time elapsed = clock.restart();
        window.clear(sf::Color(200, 200, 200, 255));
        
        splitcell::DatGui::draw();
        //application.advance(elapsed.asSeconds());
        //application.render(elapsed.asSeconds());
        
        
        // Update the window
        window.display();
    }
	return 0;
}