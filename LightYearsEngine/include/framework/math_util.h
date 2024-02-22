#pragma once
#include <SFML/Graphics.hpp>

namespace ly {
    sf::Vector2f rotation_to_vector(float rotation);
    float degrees_to_radians(float degrees);
    float radians_to_degrees(float radians);

    template<typename T>
    float get_vector_length(const sf::Vector2<T>& vector) {
        return std::sqrt(vector.x * vector.x + vector.y * vector.y);
    }

    template<typename T>
    sf::Vector2<T>& scale_vector(sf::Vector2<T>& vector, float amount) {
        vector.x *= amount;
        vector.y *= amount;
        return vector;
    }

    template<typename T>
    sf::Vector2<T>& normalize_vector(sf::Vector2<T>& vector) {
        float vector_length = get_vector_length<T>(vector);
        if (vector_length == 0.0f) return vector;

        scale_vector(vector, 1.0f/vector_length);
        return vector;
    }
}