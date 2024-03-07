#include "framework/core.h"
#include "level/game_level_1.h"
#include "player/player_spaceship.h"
#include "enemy/vanguard.h"

namespace ly {
    GameLevel1::GameLevel1(Application* owning_application)
        : World{owning_application} {
        player = spawn_actor<PlayerSpaceship>();
        player.lock()->set_actor_location(sf::Vector2f(400, 300));
        player.lock()->set_actor_rotation(-90.0f);

        std::weak_ptr<Vanguard> test_spaceship = spawn_actor<Vanguard>();
        test_spaceship.lock()->set_actor_location(sf::Vector2f(400, 100));
    }

    void GameLevel1::begin_play() {
        test_index = TimerManager::get().set_timer(get_weak_ref(), &GameLevel1::timer_callback, 3, true);
    }

    void GameLevel1::timer_callback() {
        LOG("TICK");
        TimerManager::get().clear_timer(test_index);
    }
}