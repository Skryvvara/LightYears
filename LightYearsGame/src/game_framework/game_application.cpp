#include "game_framework/game_application.h"
#include "framework/world.h"
#include "framework/actor.h"

ly::Application* get_application() {
    return new ly::GameApplication{};
}

namespace ly {
    GameApplication::GameApplication() {
        std::weak_ptr<World> new_world = load_world<World>();
        new_world.lock()->spawn_actor<Actor>();
        actor_to_destroy = new_world.lock()->spawn_actor<Actor>();
        counter = 0;
    }

    void GameApplication::tick(float delta_time) {
        counter += delta_time;
        if (counter > 2.0f)
        {
            if (!actor_to_destroy.expired()) {
                actor_to_destroy.lock()->destroy();
            }
        }
    }
}