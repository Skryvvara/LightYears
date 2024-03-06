#pragma once
#include "framework/actor.h"

namespace ly {
    class Bullet : public Actor {
    public:
        Bullet(World* world, Actor* actor_owner, const std::string& texture_path, float set_speed = 600.0f, float set_damage = 10.0f);
        void set_speed(float new_speed);
        void set_damage(float new_damage);
        virtual void tick(float delta_time) override;
        virtual void begin_play() override;
    private:
        void move(float delta_time);
        Actor* actor_owner;
        World* owning_world;
        float speed;
        float damage;
    };
}