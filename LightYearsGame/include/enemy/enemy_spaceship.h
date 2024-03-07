#pragma once
#include "spaceship/spaceship.h"

namespace ly {
    class EnemySpaceship : public Spaceship {
        public:
            EnemySpaceship(World* owning_world, const std::string& texture_path, float collision_damage = 200.0f);
            virtual void tick(float delta_time) override;
        private:
            virtual void on_begin_overlap(Actor* target) override;
            virtual void on_end_overlap(Actor* target) override;

            float _collision_damage;
    };
}