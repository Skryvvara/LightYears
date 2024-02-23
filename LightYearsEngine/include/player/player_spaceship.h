#pragma once
#include "spaceship/spaceship.h"

namespace ly {
    class PlayerSpaceship : public Spaceship {
        public:
            PlayerSpaceship(World* world, const std::string& texture_path = "SpaceShooterRedux/PNG/playerShip1_blue.png");
            virtual void tick(float delta_time) override;
            void set_speed(float new_speed) { speed = new_speed; };
            float get_speed() { return speed; };
        private:
            void handle_input();
            void normalize_input();
            void clamp_input_on_edge();
            void consume_input(float delta_time);
            sf::Vector2f move_input;
            float speed;
    };
}