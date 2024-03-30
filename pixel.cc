#include "pixel.h"
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;
using namespace sf;

Pixel::Pixel(sf::Vector2f position, sf::Color color, float size)
: gravity{0.0f}, accel{0.0f, 0.0f}, restitutionCoeff{0.85f}, mass{1.0f}, velocity{0.0f, 0.0f}
{
    pixel.setRadius(size);
    pixel.setPosition(position);
    pixel.setFillColor(color);
}

void Pixel::update(sf::Time delta, std::vector<sf::RectangleShape> &walls)
{
    gravity += 9.81f * delta.asSeconds();
    velocity.x += accel.x * delta.asSeconds();
    velocity.y += accel.y * delta.asSeconds() + gravity;
    pixel.move(velocity.x * delta.asSeconds(), velocity.y * delta.asSeconds());
}

void Pixel::collision_wall(std::vector<RectangleShape> &walls)
{
    for (auto &wall : walls)
    {
        sf::FloatRect intersection;
        if (pixel.getGlobalBounds().intersects(wall.getGlobalBounds(), intersection))
        {
            // Calculate the collision normal and overlap
            sf::Vector2f collisionNormal;
            float overlap;
            if (intersection.width < intersection.height)
            {
                // Collision is on the x-axis
                collisionNormal = sf::Vector2f((pixel.getPosition().x < wall.getPosition().x) ? -1 : 1, 0);
                overlap = intersection.width;
            }
            else
            {
                // Collision is on the y-axis
                collisionNormal = sf::Vector2f(0, (pixel.getPosition().y < wall.getPosition().y) ? -1 : 1);
                overlap = intersection.height;
            }

            // Move the pixel out of the wall
            pixel.move(overlap * collisionNormal);

            // Calculate the impulse
            float relativeVelocity = (collisionNormal.x * velocity.x) + (collisionNormal.y * velocity.y);
            if (relativeVelocity < 0)
            {
                float impulse = -(1 + restitutionCoeff) * relativeVelocity;
                velocity += impulse * collisionNormal / mass;
            }
        }
    }
}

void Pixel::collision_pixel(std::vector<Pixel> &other)
{
    for (auto &pixel : other)
    {
        if (this != &pixel)
        {
            Vector2f direction = pixel.pixel.getPosition() - this->pixel.getPosition();
            float distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
            float overlap = (pixel.pixel.getRadius() + this->pixel.getRadius()) - distance;
            if (overlap > 0)
            {
                Vector2f collisionNormal = direction / distance;
                this->pixel.move(-overlap * collisionNormal);
                pixel.pixel.move(overlap * collisionNormal);

                float relativeVelocity = (collisionNormal.x * (this->velocity.x - pixel.velocity.x)) 
                                        + (collisionNormal.y * (this->velocity.y - pixel.velocity.y));
                if (relativeVelocity < 0)
                {
                    float impulse = -(1 + restitutionCoeff) * relativeVelocity;
                    this->velocity += impulse * collisionNormal * (pixel.mass / (this->mass + pixel.mass));
                    pixel.velocity -= impulse * collisionNormal * (this->mass / (this->mass + pixel.mass));
                }
            }
        }
    }
}

void Pixel::render(sf::RenderWindow &window)
{
    window.draw(pixel);
}
