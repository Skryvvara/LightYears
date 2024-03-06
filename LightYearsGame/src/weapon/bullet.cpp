#include "framework/core.h"
#include "weapon/bullet.h"

namespace ly {
    Bullet::Bullet(World* world, Actor* actor_owner, const std::string& texture_path, float set_speed, float set_damage) 
        : Actor{world, texture_path},
        actor_owner{actor_owner},
        speed{set_speed},
        damage{set_damage} {
        set_team_id(actor_owner->get_team_id());
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

    void Bullet::begin_play() {
        Actor::begin_play();

        set_enable_physics(true);
    }

    void Bullet::on_begin_overlap(Actor* target) {
        LOG("%d, %d, %d", is_target_hostile(target), get_team_id(), target->get_team_id());
        if (is_target_hostile(target)) {
            target->apply_damage(get_damage());
            destroy();
        }
    }

    void Bullet::move(float delta_time) {
        add_actor_location_offset(get_actor_forward_direction() * speed * delta_time);
    }
}