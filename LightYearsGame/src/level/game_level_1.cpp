#include <memory>
#include "framework/core.h"
#include "level/game_level_1.h"
#include "player/player_spaceship.h"
#include "gameplay/game_stage.h"
#include "enemy/vanguard_stage.h"

namespace ly {
    GameLevel1::GameLevel1(Application* owning_application)
        : World{owning_application} {
        player = spawn_actor<PlayerSpaceship>();
        player.lock()->set_actor_location(sf::Vector2f(400, 300));
        player.lock()->set_actor_rotation(-90.0f);
    }

    void GameLevel1::begin_play() {
    }

    void GameLevel1::init_game_stages() {
        add_game_stage(std::shared_ptr<VanguardStage>{new VanguardStage{this}});
    }
}