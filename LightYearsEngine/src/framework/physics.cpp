#include <box2d/b2_body.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

#include "framework/actor.h"
#include "framework/physics.h"
#include "framework/math_util.h"
#include "framework/core.h"

namespace ly {
    std::unique_ptr<Physics> Physics::instance{nullptr};
    
    Physics::Physics()
        : physics_world{b2Vec2{0, 0}},
        physics_scale{0.01f},
        velocity_iterations{8},
        position_iterations{3},
        contact_listener{},
        pending_remove_listeners{} {
    
        physics_world.SetContactListener(&contact_listener);
        physics_world.SetAllowSleeping(false);
    }

    Physics& Physics::get() {
        if (!instance) {
            instance = std::move(std::unique_ptr<Physics>{new Physics});
        }

        return *instance;
    }

    void Physics::step(float delta_time) {
        clean_cycle();
        physics_world.Step(delta_time, velocity_iterations, position_iterations);
    }

    b2Body* Physics::add_listener(Actor* listener) {
        if (listener->is_pending_destroy()) return nullptr;

        b2BodyDef body_definition;
        body_definition.type = b2_dynamicBody;

        body_definition.userData.pointer = reinterpret_cast<uintptr_t>(listener);
        body_definition.position.Set(
            listener->get_actor_location().x * get_physics_scale(), 
            listener->get_actor_location().y * get_physics_scale());

        body_definition.angle = degrees_to_radians(listener->get_actor_rotation());

        b2Body* body = physics_world.CreateBody(&body_definition);

        b2PolygonShape shape;
        auto bounds = listener->get_actor_global_bounds();
        shape.SetAsBox(bounds.width/2.0f * get_physics_scale(), bounds.height/2.0f * get_physics_scale());

        b2FixtureDef fixture_definition;
        fixture_definition.shape = &shape;
        fixture_definition.density = 1.0f;
        fixture_definition.friction = 0.3f;
        fixture_definition.isSensor = true;

        body->CreateFixture(&fixture_definition);

        return body;
    }

    void Physics::remove_listener(b2Body* body) {
        pending_remove_listeners.insert(body);
    }

    void Physics::clean_cycle() {
        for (auto listener : pending_remove_listeners) {
            physics_world.DestroyBody(listener);
        }
        pending_remove_listeners.clear();
    }

    void Physics::clean_up() {
        instance = std::move(std::unique_ptr<Physics>{new Physics});
    }

    void PhysicsContactListener::BeginContact(b2Contact* contact) {
        Actor* actor_a = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        Actor* actor_b = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

        if (actor_a && !actor_a->is_pending_destroy()) {
            actor_a->on_begin_overlap(actor_b);
        }

        if (actor_b && !actor_b->is_pending_destroy()) {
            actor_b->on_begin_overlap(actor_a);
        }
    }

    void PhysicsContactListener::EndContact(b2Contact* contact) {
        Actor* actor_a = nullptr;
        Actor* actor_b = nullptr;

        if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody()) {
            actor_a = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        }

        if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody()) {
            actor_b = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
        }

        if (actor_a && !actor_a->is_pending_destroy()) {
            actor_a->on_end_overlap(actor_b);
        }

        if (actor_b && !actor_b->is_pending_destroy()) {
            actor_b->on_end_overlap(actor_a);
        }
    }
}