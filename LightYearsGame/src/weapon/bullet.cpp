#include "framework/core.h"
#include "weapon/bullet.h"

namespace ly {
    Bullet::Bullet(World* world, Actor* actor_owner, const std::string& texture_path, float set_speed, float set_damage) 
        : Actor{world, texture_path},
        actor_owner{actor_owner},
        speed{set_speed},
        damage{set_damage} {

    }

    void Bullet::set_speed(float new_speed) {
        speed = new_speed;
    }

    void Bullet::set_damage(float new_damage) {
        damage = new_damage;
    }

    void Bullet::tick(float delta_time) {
        Actor::tick(delta_time);
        move(delta_time);
        if (is_out_of_window_bounds()) {
            destroy();
        }
    }

    void Bullet::move(float delta_time) {
        add_actor_location_offset(get_actor_forward_direction() * speed * delta_time);
    }
}