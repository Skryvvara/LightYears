#pragma once
#include <map>
#include <SFML/Graphics.hpp>

namespace ly {
    class World;
    class Explosion {
        public:
            Explosion(int particle_amount = 20, 
                float life_time_min = 0.5f, float life_time_max = 1.5f,
                float size_min = 1, float size_max = 2,
                float velocity_min = 200, float velocity_max = 400,
                const sf::Color& particle_color = sf::Color{255, 128, 0, 255},
                const std::vector<std::string>& texture_paths = {
                "SpaceShooterRedux/PNG/Effects/star1.png",
                "SpaceShooterRedux/PNG/Effects/star2.png",
                "SpaceShooterRedux/PNG/Effects/star3.png"});
            void spawn_explosion(World* world, const sf::Vector2f& location);
        private:
            int _particle_amount;

            float _life_time_min;
            float _life_time_max;
            
            float _size_min;
            float _size_max;

            float _velocity_min;
            float _velocity_max;
            
            sf::Color _particle_color;
            std::vector<std::string> _texture_paths;
    };
}