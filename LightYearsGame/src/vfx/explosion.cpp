#include <memory>
#include "framework/math_util.h"
#include "framework/world.h"
#include "vfx/explosion.h"
#include "vfx/particle.h"

namespace ly {
    Explosion::Explosion(int particle_amount, 
        float life_time_min, float life_time_max,
        float size_min, float size_max,
        float velocity_min, float velocity_max,
        const sf::Color& particle_color,
        const std::vector<std::string>& texture_paths) {
        _particle_amount = particle_amount;

        _life_time_min = life_time_min;
        _life_time_max = life_time_max;

        _size_min = size_min;
        _size_max = size_max;

        _velocity_min = velocity_min;
        _velocity_max = velocity_max;

        _particle_color = particle_color;
        _texture_paths = texture_paths;
    }

    void Explosion::spawn_explosion(World* world, const sf::Vector2f& location) {
        if (!world) return;

        for (int i = 0; i < _particle_amount; i++) {
            std::string particle_texture_path = _texture_paths[(int)random_range(0, _texture_paths.size())];
            std::weak_ptr<Particle> new_particle = world->spawn_actor<Particle>(particle_texture_path);

            new_particle.lock()->random_life_time(_life_time_min, _life_time_max);
            new_particle.lock()->set_actor_location(location);
            new_particle.lock()->random_size(_size_min, _size_max);
            new_particle.lock()->random_velocity(_velocity_min, _velocity_max);
            new_particle.lock()->get_sprite().setColor(_particle_color);
        }
    }
}