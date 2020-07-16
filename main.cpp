#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

void handle_error(bool error_test, std::string error_message)
{
    if (error_test)
    {
        std::cout << std::endl << error_message << std::endl;
        exit(1);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Typing...", sf::Style::Close);
    sf::Image icon;
    icon.loadFromFile("icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    sf::Font font;
    handle_error(!font.loadFromFile("cour.ttf"), "Error loading font");
    sf::Text text;
    sf::Text input;
    text.setFont(font);
    input.setFont(font);
    input.setPosition(0, 100);
    text.setString("Hello World!");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::TextEntered) // Text typed
            {
                if (event.key.code == 8) // Backspace was typed
                    input.setString(input.getString().substring(0, input.getString().getSize() - 1));
                else // Something else was typed
                    input.setString(input.getString() + event.text.unicode);
                std::wcout << std::endl << input.getString().toWideString();
            }
            window.clear(sf::Color::Black);
            window.draw(input);
            window.draw(text);
            window.display();
        }
        
    }

    return 0;
}