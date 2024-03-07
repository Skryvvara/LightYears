#include "enemy/enemy_spaceship.h"

namespace ly {
    EnemySpaceship::EnemySpaceship(World* owning_world, const std::string& texture_path, float collision_damage)
        : Spaceship{owning_world, texture_path} {
        _collision_damage = collision_damage;
        set_team_id(2);
    }

    void EnemySpaceship::tick(float delta_time) {
        Spaceship::tick(delta_time);

        if (is_out_of_window_bounds(get_actor_global_bounds().width)) {
            destroy();
        }
    }

    void EnemySpaceship::on_begin_overlap(Actor* target) {
        Spaceship::on_begin_overlap(target);

        if (is_target_hostile(target)) {
            target->apply_damage(_collision_damage);
        }
    }
}
