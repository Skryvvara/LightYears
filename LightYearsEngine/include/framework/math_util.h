#pragma once
#include <SFML/Graphics.hpp>

namespace ly {
    sf::Vector2f rotation_to_vector(float rotation);
    float degrees_to_radians(float degrees);
    float radians_to_degrees(float radians);
}