#pragma once
#include "framework/delegate.h"

namespace ly {
    class Health {
        public:
            Health(float health, float max_health);
            void modify_health(float amount);
            float get_health() const { return _health; };
            float get_max_health() const { return _max_health; };

            Delegate<float, float, float> on_health_changed;
            Delegate<float, float, float> on_taken_damage;
            Delegate<> on_death;
        private:
            void take_damage(float amount);
            void health_empty();
            float _health;
            float _max_health;
    };
}