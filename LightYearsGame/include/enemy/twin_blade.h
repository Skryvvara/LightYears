#pragma once
#include <memory>
#include "enemy/enemy_spaceship.h"

namespace ly {
    class BulletShooter;
    class TwinBlade : public EnemySpaceship {
        public:
            TwinBlade(World* owning_world, 
                const std::string& texture_path = "SpaceShooterRedux/PNG/Enemies/enemyBlack5.png",
                const sf::Vector2f& velocity = {0.0f, 120.0f});

            virtual void begin_play() override;
            virtual void tick(float delta_time) override;
        private:
            virtual void shoot() override;
            std::unique_ptr<BulletShooter> _shooter_left;
            std::unique_ptr<BulletShooter> _shooter_right;
    };
}
