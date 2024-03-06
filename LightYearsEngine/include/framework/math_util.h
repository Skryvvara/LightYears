#pragma once
#include <SFML/Graphics.hpp>

namespace ly
{
	sf::Vector2f rotation_to_vector(float rotation);
	float degrees_to_radians(float degrees);
	float radians_to_degrees(float radians);

	template<typename T>
	float get_vector_length(const sf::Vector2<T>& vector)
	{
		return std::sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	template<typename T>
	sf::Vector2<T>& scale_vector(sf::Vector2<T>& vectorToScale, float amt)
	{
		vectorToScale.x *= amt;
		vectorToScale.y *= amt;
		return vectorToScale;
	}

	template<typename T>
	sf::Vector2<T>& normalize_vector(sf::Vector2<T>& vector)
	{
		float vectorLength = get_vector_length<T>(vector);
		if (vectorLength == 0.f) return vector;

		scale_vector(vector, 1.0/vectorLength);

		return vector;
	}

	sf::Color lerp_color(const sf::Color& a, const sf::Color& b, float alpha);

	sf::Vector2f lerp_vector(const sf::Vector2f& a, const sf::Vector2f& b, float alpha);

	float lerp_float(float a, float b, float alpha);

	float random_range(float min, float max);
	sf::Vector2f random_unit_vector();
}