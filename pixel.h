#ifndef PIXEL
#define PIXEL

#include <SFML/Graphics.hpp>

class Pixel
{
public:
    Pixel(sf::Vector2f position, sf::Color color, float size);
    ~Pixel() = default;

    void update(sf::Time delta, std::vector<sf::RectangleShape>& walls);
    void render(sf::RenderWindow& window);
    void collision_wall(std::vector<sf::RectangleShape>& walls);
    void collision_pixel(std::vector<Pixel>& other);

private:
    sf::CircleShape pixel;
    float gravity;
    sf::Vector2f accel;
    float restitutionCoeff;
    float mass; 
    sf::Vector2f velocity;
};


#endif