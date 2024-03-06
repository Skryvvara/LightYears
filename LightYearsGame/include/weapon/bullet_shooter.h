#pragma once
#include <SFML/System.hpp>
#include "weapon/shooter.h"

namespace ly {
    class BulletShooter : public Shooter {
    public:
        BulletShooter(Actor* owner, float cooldown = 1.0f);
        virtual bool is_on_cooldown() const override;
    private:
        virtual void shoot_impl() override;
        sf::Clock cooldown_clock;
        float cooldown_time;
    };
}
