#include <SFML/Graphics.hpp>
#include <iostream>
#include "pixel.h"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(800, 600), "Sand");
    vector<Pixel> pixels;

    vector<RectangleShape> walls;
    
    RectangleShape topRect;
    topRect.setSize(sf::Vector2f(window.getSize().x, 10));
    topRect.setFillColor(sf::Color::White);
    topRect.setPosition(0, 0);

    RectangleShape bottomRect;
    bottomRect.setSize(sf::Vector2f(window.getSize().x, 10));
    bottomRect.setFillColor(sf::Color::White);
    bottomRect.setPosition(0, window.getSize().y - 10);

    RectangleShape leftRect;
    leftRect.setSize(sf::Vector2f(10, window.getSize().y));
    leftRect.setFillColor(sf::Color::White);
    leftRect.setPosition(0, 0);

    RectangleShape rightRect;
    rightRect.setSize(sf::Vector2f(10, window.getSize().y));
    rightRect.setFillColor(sf::Color::White);
    rightRect.setPosition(window.getSize().x - 10, 0);

    walls.push_back(topRect);
    walls.push_back(bottomRect);
    walls.push_back(leftRect);
    walls.push_back(rightRect);


    Clock clock;
    double const fps { 60.0 };
    auto const target { milliseconds (1000.0 / fps) }; 

    bool wasPressed = false;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        if(Mouse::isButtonPressed(Mouse::Left))
        {
            wasPressed = true;
        }
        else if(wasPressed)
        {
            Vector2i mPos = Mouse::getPosition(window);
            Pixel p{Vector2f(mPos.x, mPos.y), Color::Red, 10};
            pixels.push_back(p);
            wasPressed = false;
        }

        Time delta = clock.restart();
        for(auto& p : pixels)
        {
            p.update(delta, walls);
        }

        for(auto& p : pixels)
        {
            p.collision_wall(walls);
        }

        for(auto& p : pixels)
        {
            p.collision_pixel(pixels);
        }

        window.clear();

        for(auto& p : pixels)
        {
            p.render(window);
        }

        for(auto& w : walls)
        {
            window.draw(w);
        }

        window.display();

        sleep(target - clock.getElapsedTime());
    }
    return 0;
}

