#pragma once
#include "framework/actor.h"

namespace ly {
    class Spaceship : public Actor {
        public:
            Spaceship(World* world, const std::string& textuer_path = "");
            virtual void tick(float delta_time) override;
            virtual void begin_play() override;
            void set_velocity(const sf::Vector2f new_velocity);
            sf::Vector2f get_velocity() const { return velocity; };
            virtual void shoot();
        private:
            sf::Vector2f velocity;
    };
}