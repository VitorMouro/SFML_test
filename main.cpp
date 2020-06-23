#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "A game");
    sf::Time t0 = sf::milliseconds(0);
    sf::Clock clock;
    sf::Font font;
    sf::Text text1;
    sf::Image icon;
    font.loadFromFile("consola.ttf");
    text1.setFont(font);
    text1.setCharacterSize(30);
    text1.setStyle(sf::Text::Regular);
    text1.setFillColor(sf::Color::White);
    text1.setString("Teste");
    text1.setPosition(sf::Vector2f(400, 400));
    icon.loadFromFile("icon.png");
    window.setIcon(64, 64, icon.getPixelsPtr());
    
    std::cout << sf::VideoMode::getDesktopMode().width << ", " << sf::VideoMode::getDesktopMode().height;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time t1 = clock.getElapsedTime();
        sf::Time delta = t1 - t0;
        t0 = t1;

        window.clear();
        window.draw(text1);
        window.display();
    }

    return 0;
}