#include "framework/core.h"
#include "framework/actor.h"
#include "framework/world.h"
#include "weapon/bullet.h"
#include "weapon/bullet_shooter.h"

namespace ly {
    BulletShooter::BulletShooter(Actor* owner, float cooldown)
        : Shooter{owner},
        cooldown_clock{},
        cooldown_time{cooldown} {

    }

    bool BulletShooter::is_on_cooldown() const {
        return !(cooldown_clock.getElapsedTime().asSeconds() > cooldown_time);
    }

    void BulletShooter::shoot_impl() {
        cooldown_clock.restart();
        std::weak_ptr<Bullet> new_bullet = 
            get_owner()->get_world()->spawn_actor<Bullet>(
                get_owner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
        new_bullet.lock()->set_actor_location(get_owner()->get_actor_location());
        new_bullet.lock()->set_actor_rotation(get_owner()->get_actor_rotation());
    }
}