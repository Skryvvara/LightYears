#include "framework/math_util.h"

#define PI 3.1415926535

namespace ly {
    sf::Vector2f rotation_to_vector(float rotation) {
        float radians = degrees_to_radians(rotation);
        return sf::Vector2f(std::cos(radians), std::sin(radians));
    }

    float degrees_to_radians(float degrees) {
        return degrees * (PI / 180.0f);
    }

    float radians_to_degrees(float radians) {
        return radians * (180.0f / PI);
    }
}