#pragma once
#include "framework/actor.h"
#include "gameplay/health.h"

namespace ly {
    class Spaceship : public Actor {
        public:
            Spaceship(World* world, const std::string& textuer_path = "");
            virtual void tick(float delta_time) override;
            virtual void begin_play() override;
            void set_velocity(const sf::Vector2f new_velocity);
            sf::Vector2f get_velocity() const { return velocity; };
            virtual void shoot();
            virtual void apply_damage(float amount) override;
        private:
            virtual void on_health_changed(float amount, float health, float max_health);
            virtual void on_taken_damage(float amount, float health, float max_health);
            virtual void on_death();
            sf::Vector2f velocity;
            Health health;
    };
}