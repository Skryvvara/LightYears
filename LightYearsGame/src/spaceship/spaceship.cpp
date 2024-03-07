#include <memory>
#include "spaceship/spaceship.h"
#include "framework/core.h"
#include "framework/math_util.h"
#include "vfx/explosion.h"

namespace ly {
    Spaceship::Spaceship(World* world, const std::string& texture_path)
        : Actor{world, texture_path},
        health{100, 100},
        blink_time{0.0f},
        blink_duration{0.2f},
        blink_color_offset{255, 0, 0, 255} {
    }

    void Spaceship::tick(float delta_time) {
        Actor::tick(delta_time);
        add_actor_location_offset(get_velocity() * delta_time);
        update_blink(delta_time);
    }

    void Spaceship::begin_play() {
        Actor::begin_play();

        set_enable_physics(true);
        health.on_health_changed.bind_action(get_weak_ref(), &Spaceship::on_health_changed);
        health.on_taken_damage.bind_action(get_weak_ref(), &Spaceship::on_taken_damage);
        health.on_death.bind_action(get_weak_ref(), &Spaceship::on_death);
    }

    void Spaceship::set_velocity(sf::Vector2f new_velocity) {
        velocity = new_velocity;
    }

    void Spaceship::shoot() {
        
    }

    void Spaceship::apply_damage(float amount) {
        health.modify_health(-amount);
    }

    void Spaceship::on_health_changed(float amount, float health, float max_health) {
        
    }

    void Spaceship::on_taken_damage(float amount, float health, float max_health) {
        blink();
    }

    void Spaceship::on_death() {
        Explosion* explosion = new Explosion();
        explosion->spawn_explosion(get_world(), get_actor_location());

        destroy();
        delete explosion;
    }

    void Spaceship::blink() {
        if (blink_time == 0) {
            blink_time = blink_duration;
        }
    }

    void Spaceship::update_blink(float delta_time) {
        if (blink_time > 0) {
            blink_time -= delta_time;
            blink_time = blink_time > 0 ? blink_time : 0.0f;

            get_sprite().setColor(lerp_color(sf::Color::White, blink_color_offset, blink_time));
        }
    }
}