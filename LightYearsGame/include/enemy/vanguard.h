#pragma once
#include <memory>
#include "enemy/enemy_spaceship.h"

namespace ly {
    class BulletShooter;
    class Vanguard : public EnemySpaceship {
        public:
            Vanguard(World* owning_world, 
                const std::string& texture_path = "SpaceShooterRedux/PNG/Enemies/enemyBlack3.png",
                const sf::Vector2f& velocity = {0.0f, 200.0f});

            virtual void begin_play() override;
            virtual void tick(float delta_time) override;
        private:
            virtual void shoot() override;
            std::unique_ptr<BulletShooter> _shooter;
    };
}