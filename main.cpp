#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(800, 800), "SFML works!");
    RectangleShape rect(Vector2f(100.0f, 100.0f));
    rect.setFillColor(Color::Green);
    rect.setPosition(Vector2f(0, 0));
    Time t0 = milliseconds(0);
    Clock clock;
    Vector2f rect_position(0, 0);

    std::cout << sf::VideoMode::getDesktopMode().width << ", " << sf::VideoMode::getDesktopMode().height;

    while (window.isOpen())
    {
        Time t1 = clock.getElapsedTime();
        int dt = t1.asMilliseconds() - t0.asMilliseconds();
        t0 = t1;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            rect.setPosition(rect.getPosition().x + 1 * dt, rect.getPosition().y);
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            rect.setPosition(rect.getPosition().x - 1 * dt, rect.getPosition().y);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            rect.setPosition(rect.getPosition().x, rect.getPosition().y + 1 * dt);
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            rect.setPosition(rect.getPosition().x, rect.getPosition().y - 1 * dt);
        }

        window.clear();
        window.draw(rect);
        window.display();
    }

    return 0;
}