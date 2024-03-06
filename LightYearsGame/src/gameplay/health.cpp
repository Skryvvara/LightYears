#include "framework/core.h"
#include "gameplay/health.h"

namespace ly {
    Health::Health(float health, float max_health)
        : _health{health},
        _max_health{max_health} {

    }

    void Health::modify_health(float amount) {
        if (amount == 0) return;
        if (_health == 0) return;

        _health += amount;
        if (_health < 0) {
            _health = 0;
        }

        if (_health > _max_health) {
            _health = _max_health;
        }

        if (amount < 0) {
            take_damage(-amount);
            if (_health <= 0) {
                health_empty();
            }
        }

        on_health_changed.broadcast(amount, _health, _max_health);
    }

    void Health::take_damage(float amount) {
        on_taken_damage.broadcast(amount, _health, _max_health);
    }

    void Health::health_empty() {
        on_death.broadcast();
    }
}