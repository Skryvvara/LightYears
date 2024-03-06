#include "spaceship/spaceship.h"

namespace ly {
    Spaceship::Spaceship(World* world, const std::string& texture_path)
        : Actor{world, texture_path} {

    }

    void Spaceship::tick(float delta_time) {
        Actor::tick(delta_time);
        add_actor_location_offset(get_velocity() * delta_time);
    }

    void Spaceship::begin_play() {
        Actor::begin_play();

        set_enable_physics(true);
    }

    void Spaceship::set_velocity(sf::Vector2f new_velocity) {
        velocity = new_velocity;
    }

    void Spaceship::shoot() {
        
    }
}