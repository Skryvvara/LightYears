#include "framework/application.h"
#include "framework/world.h"
#include "framework/actor.h"
#include "framework/core.h"
#include "gameplay/game_stage.h"

namespace ly {
    World::World(Application* app)
        : owning_app{app},
        began_play{false},
        actors{},
        pending_actors{},
        stages{},
        _current_stage_index{-1} {
    }

    World::~World() {

    }

    void World::begin_play_internal() {
        if (!began_play) {
            began_play = true;
            begin_play();
            init_game_stages();
            next_game_stage();
        }
    }

    void World::begin_play() {
        
    }

    void World::tick_internal(float delta_time) {
        for (std::shared_ptr<Actor> actor : pending_actors) {
            actors.push_back(actor);
            actor->begin_play_internal();
        }
        pending_actors.clear();

        for (auto iter = actors.begin(); iter != actors.end();) {
            iter->get()->tick_internal(delta_time);
            ++iter; 
        }

        if (_current_stage_index >= 0 && _current_stage_index < stages.size()) {
            stages[_current_stage_index]->tick(delta_time);
        }

        tick(delta_time);
    }

    void World::render(sf::RenderWindow& window) {
        for (auto& actor : actors) {
            actor->render(window);
        }
    }

    void World::tick(float delta_time) {
    }

    sf::Vector2u World::get_window_size() const {
        return owning_app->get_window_size();
    }

    void World::clean_cycle() {
        for (auto iter = actors.begin(); iter != actors.end();) {
            if (iter->get()->is_pending_destroy()) {
                iter = actors.erase(iter);
            } else {
                ++iter;
            }
        }

        for (auto iter = stages.begin(); iter != stages.end();) {
            if (iter->get()->is_finished()) {
                iter = stages.erase(iter);
            } else {
                ++iter;
            }
        }
    }

    void World::add_game_stage(const std::shared_ptr<GameStage>& new_stage) {
        if (!new_stage) return;

        stages.push_back(new_stage);
    }

    void World::init_game_stages() {

    }

    void World::all_game_stages_finished() {

    }

    void World::next_game_stage() {
        ++_current_stage_index;
        if (_current_stage_index >= 0 && _current_stage_index < stages.size()) {
            stages[_current_stage_index]->on_stage_finished.bind_action(get_weak_ref(), &World::next_game_stage);
            stages[_current_stage_index]->begin_play();
        } else {
            all_game_stages_finished();
        }
    }
}