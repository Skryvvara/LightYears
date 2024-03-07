#include "framework/math_util.h"
#include "vfx/particle.h"

namespace ly {
    Particle::Particle(World* owning_world, const std::string& texture_path)
        : Actor{owning_world, texture_path},
        velocity{},
        life_time{1.0f},
        timer{} {

    }

    void Particle::begin_play() {
        Actor::begin_play();
        set_enable_physics(false);
    }

    void Particle::tick(float delta_time) {
        Actor::tick(delta_time);
        move(delta_time);
        fade(delta_time);

        if (timer.getElapsedTime().asSeconds() >= life_time) {
            destroy();
        }
    }

    void Particle::random_velocity(float min, float max) {
        velocity = random_unit_vector() * random_range(min, max);
    }

    void Particle::random_size(float min, float max) {
        float random_scale = random_range(min, max);
        get_sprite().setScale(random_scale, random_scale);
    }

    void Particle::random_life_time(float min, float max) {
        life_time = random_range(min, max);
    }

    void Particle::move(float delta_time) {
        add_actor_location_offset(velocity * delta_time);
    }

    void Particle::fade(float delta_time) {
        float elapsed_time = timer.getElapsedTime().asSeconds();
        get_sprite().setColor(lerp_color(get_sprite().getColor(), sf::Color{255, 255, 255, 0}, elapsed_time/life_time));
        get_sprite().setScale(lerp_vector(get_sprite().getScale(), sf::Vector2f{0, 0}, elapsed_time/life_time));
    }
}