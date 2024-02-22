#include "framework/actor.h"
#include "framework/core.h"

namespace ly {
    Actor::Actor(World* world)
        : owning_world{world}, 
        began_play{false} {

    }

    Actor::~Actor() {
        
    }

    void Actor::begin_play_internal() {
        if (!began_play) {
            began_play = true;
            begin_play();
        }
    }

    void Actor::begin_play() {
        LOG("Actor begin play");
    }

    void Actor::tick(float delta_time) {
        LOG("Actor ticking");
    }
}