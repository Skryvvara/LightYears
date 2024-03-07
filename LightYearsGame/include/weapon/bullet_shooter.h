#pragma once
#include <SFML/System.hpp>
#include "weapon/shooter.h"

namespace ly {
    class BulletShooter : public Shooter {
    public:
        BulletShooter(Actor* owner, float cooldown = 1.0f, sf::Vector2f location_offset = {0.0f, 0.0f}, float rotation_offset = 0.0f);
        virtual bool is_on_cooldown() const override;
    private:
        virtual void shoot_impl() override;
        sf::Clock cooldown_clock;
        sf::Vector2f _location_offset;
        float _rotation_offset;
        float cooldown_time;
    };
}
