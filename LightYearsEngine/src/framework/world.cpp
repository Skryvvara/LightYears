#include "framework/application.h"
#include "framework/world.h"
#include "framework/actor.h"
#include "framework/core.h"

namespace ly {
    World::World(Application* app)
        : owning_app{app},
        began_play{false},
        actors{},
        pending_actors{} {
    }

    World::~World() {

    }

    void World::begin_play_internal() {
        if (!began_play) {
            began_play = true;
            begin_play();
        }
    }

    void World::begin_play() {
        LOG("began play");
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
    }
}