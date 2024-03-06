#pragma once

namespace ly {
    class Actor;
    class Shooter {
    public:
        void shoot();
        virtual bool can_shoot() const { return true; };
        virtual bool is_on_cooldown() const { return false; };
        Actor* get_owner() const { return owner_actor; };
    protected:
        Shooter(Actor* owner);
    private:
        Actor* owner_actor;
        virtual void shoot_impl() {};
    };
}
