#include "enemy/vanguard.h"
#include "weapon/bullet_shooter.h"

namespace ly {
    Vanguard::Vanguard(World* owning_world, const std::string& texture_path, const sf::Vector2f& velocity)
        : EnemySpaceship{owning_world, texture_path},
        _shooter{new BulletShooter{this}} {
        set_velocity(velocity);
        set_actor_rotation(90.0f);
    }

    void Vanguard::begin_play() {
        EnemySpaceship::begin_play();
    }

    void Vanguard::tick(float delta_time) {
        EnemySpaceship::tick(delta_time);
        shoot();
    }

    void Vanguard::shoot() {
        _shooter->shoot();
    }
}
