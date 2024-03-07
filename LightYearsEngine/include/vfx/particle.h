#pragma once
#include "framework/actor.h"

namespace ly {
    class Particle : public Actor {
        public:
            Particle(World* owning_world, const std::string& texture_path);
            virtual void begin_play() override;
            virtual void tick(float delta_time) override;

            void random_velocity(float min, float max);
            void random_size(float min, float max);
            void random_life_time(float min, float max);
        private:
            void move(float delta_time);
            void fade(float delta_time);

            sf::Vector2f velocity;
            float life_time;
            sf::Clock timer;
    };
}