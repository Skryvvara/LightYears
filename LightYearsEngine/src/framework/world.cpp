#include "framework/world.h"
#include "framework/core.h"

namespace ly {
    World::World(Application* app)
        : owning_app{app},
        began_play{false} {
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
        tick(delta_time);
    }

    void World::tick(float delta_time) {
        LOG("Tick at frame rate %f", 1.0f/delta_time);
    }
}