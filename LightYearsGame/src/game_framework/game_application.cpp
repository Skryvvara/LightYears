#include "game_framework/game_application.h"
#include "framework/world.h"
#include "framework/actor.h"
#include "framework/asset_manager.h"
#include "config.h"

ly::Application* get_application() {
    return new ly::GameApplication{};
}

namespace ly {
    GameApplication::GameApplication()
        : Application{800, 600, "Light Years", sf::Style::Titlebar | sf::Style::Close } {
        AssetManager::get().set_asset_root_dir(get_resource_dir());

        std::weak_ptr<World> new_world = load_world<World>();
        test_player = new_world.lock()->spawn_actor<PlayerSpaceship>();
        test_player.lock()->set_actor_location(sf::Vector2f(400, 300));
        test_player.lock()->set_actor_rotation(-90.0f);

        std::weak_ptr<Spaceship> test_spaceship = new_world.lock()->spawn_actor<Spaceship>();
        test_spaceship.lock()->set_texture("SpaceShooterRedux/PNG/playerShip1_red.png");
        test_spaceship.lock()->set_actor_location(sf::Vector2f(400, 100));
    }

    void GameApplication::tick(float delta_time) {

    }
}