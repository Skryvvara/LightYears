#include "framework/core.h"
#include "framework/actor.h"
#include "framework/world.h"
#include "weapon/bullet.h"
#include "weapon/bullet_shooter.h"

namespace ly {
    BulletShooter::BulletShooter(Actor* owner, float cooldown, sf::Vector2f location_offset, float rotation_offset)
        : Shooter{owner},
        cooldown_clock{},
        cooldown_time{cooldown},
        _location_offset{location_offset},
        _rotation_offset{rotation_offset} {

    }

    bool BulletShooter::is_on_cooldown() const {
        return !(cooldown_clock.getElapsedTime().asSeconds() > cooldown_time);
    }

    void BulletShooter::shoot_impl() {
        sf::Vector2f owner_forward_direction = get_owner()->get_actor_forward_direction();
        sf::Vector2f owner_right_direction = get_owner()->get_actor_right_direction();

        cooldown_clock.restart();
        std::weak_ptr<Bullet> new_bullet = 
            get_owner()->get_world()->spawn_actor<Bullet>(
                get_owner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
        new_bullet.lock()->set_actor_location(get_owner()->get_actor_location() + owner_forward_direction * _location_offset.x + owner_right_direction * _location_offset.y);
        new_bullet.lock()->set_actor_rotation(get_owner()->get_actor_rotation() + _rotation_offset);
    }
}