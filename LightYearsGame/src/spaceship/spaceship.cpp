#include <memory>
#include "spaceship/spaceship.h"
#include "framework/core.h"

namespace ly {
    Spaceship::Spaceship(World* world, const std::string& texture_path)
        : Actor{world, texture_path},
        health{100, 100} {
    }

    void Spaceship::tick(float delta_time) {
        Actor::tick(delta_time);
        add_actor_location_offset(get_velocity() * delta_time);
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
        LOG("taken %f damage, %f/%f", amount, health, max_health);
    }

    void Spaceship::on_death() {
        destroy();
    }
}