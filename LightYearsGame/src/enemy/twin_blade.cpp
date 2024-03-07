#include "enemy/twin_blade.h"
#include "weapon/bullet_shooter.h"

namespace ly {
    TwinBlade::TwinBlade(World* owning_world, const std::string& texture_path, const sf::Vector2f& velocity)
        : EnemySpaceship{owning_world, texture_path},
        _shooter_left{new BulletShooter{this, 1.0f, {50.0f, 20.0f}}},
        _shooter_right{new BulletShooter{this, 1.0f, {50.0f, -20.0f}}} {
        set_velocity(velocity);
        set_actor_rotation(90.0f);
    }

    void TwinBlade::begin_play() {
        EnemySpaceship::begin_play();
    }

    void TwinBlade::tick(float delta_time) {
        EnemySpaceship::tick(delta_time);
        shoot();
    }

    void TwinBlade::shoot() {
        _shooter_left->shoot();
        _shooter_right->shoot();
    }
}
