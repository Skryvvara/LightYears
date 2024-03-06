#pragma once
#include <box2d/b2_world.h>
#include <memory>
#include <unordered_set>

namespace ly {
    class Actor;

    class PhysicsContactListener : public b2ContactListener {
        virtual void BeginContact(b2Contact* contact) override;
        virtual void EndContact(b2Contact* contact) override;
    };

    class Physics {
        public:
            static Physics& get();
            void step(float delta_time);
            b2Body* add_listener(Actor* listener);
            void remove_listener(b2Body* body);
            float get_physics_scale() const { return physics_scale; };
            static void clean_up();
        protected:
            Physics();
        private:
            void clean_cycle();
            static std::unique_ptr<Physics> instance;
            b2World physics_world;
            float physics_scale;

            int velocity_iterations;
            int position_iterations;

            PhysicsContactListener contact_listener;
            std::unordered_set<b2Body*> pending_remove_listeners;
    };
}