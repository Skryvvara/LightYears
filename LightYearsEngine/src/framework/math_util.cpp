#include "framework/math_util.h"
#include "framework/core.h"

namespace ly {
	const float PI = 3.1415926535;

	sf::Vector2f rotation_to_vector(float rotation)
	{
		float radians = degrees_to_radians(rotation);
		return sf::Vector2f(std::cos(radians), std::sin(radians));
	}

	float degrees_to_radians(float degrees)
	{
		return degrees * (PI / 180.f);
	}

	float radians_to_degrees(float radians)
	{
		return radians * (180.f / PI);
	}

	float lerp_float(float a, float b, float alpha)
	{
		if (alpha > 1) alpha = 1;
		if (alpha < 0) alpha = 0;

		return a + (b - a) * alpha;
	}

	sf::Color lerp_color(const sf::Color& a, const sf::Color& b, float alpha)
	{
		int lerpR = lerp_float(a.r, b.r, alpha);
		int lerpG = lerp_float(a.g, b.g, alpha);
		int lerpB = lerp_float(a.b, b.b, alpha);
		int lerpA = lerp_float(a.a, b.a, alpha);

		return sf::Color(lerpR, lerpG, lerpB, lerpA);
	}

	sf::Vector2f lerp_vector(const sf::Vector2f& a, const sf::Vector2f& b, float alpha)
	{
		float lerpX = lerp_float(a.x, b.x, alpha);
		float lerpY = lerp_float(a.y, b.y, alpha);
		return sf::Vector2f(lerpX, lerpY);

	}
}