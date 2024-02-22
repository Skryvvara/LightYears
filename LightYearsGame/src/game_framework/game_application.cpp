#include "game_framework/game_application.h"
#include "framework/world.h"
#include "framework/actor.h"
#include "config.h"

ly::Application* get_application() {
    return new ly::GameApplication{};
}

namespace ly {
    GameApplication::GameApplication()
        : Application{800, 600, "Light Years", sf::Style::Titlebar | sf::Style::Close } {
        std::weak_ptr<World> new_world = load_world<World>();
        new_world.lock()->spawn_actor<Actor>();
        actor_to_destroy = new_world.lock()->spawn_actor<Actor>();
        actor_to_destroy.lock()->set_texture(get_resource_dir() + "SpaceShooterRedux/PNG/playerShip1_blue.png");
        actor_to_destroy.lock()->set_actor_location(sf::Vector2f(400, 300));
        actor_to_destroy.lock()->set_actor_rotation(180);
        counter = 0;
    }

    void GameApplication::tick(float delta_time) {

    }
}