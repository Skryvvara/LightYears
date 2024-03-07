#include "framework/core.h"
#include "gameplay/game_stage.h"

namespace ly {
    GameStage::GameStage(World* world) {
        _world = world;
        _is_finished = false;
    }

    void GameStage::begin_play() {
        
    }

    void GameStage::end_play() {
        
    }

    void GameStage::tick(float delta_time) {
        
    }

    void GameStage::end_stage() {
        _is_finished = true;
        end_play();
        on_stage_finished.broadcast();
    }
}
