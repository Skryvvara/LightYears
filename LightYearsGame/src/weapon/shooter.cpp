#include "framework/actor.h"
#include "weapon/shooter.h"
#include "framework/core.h"

namespace ly {
    Shooter::Shooter(Actor* owner) 
        : owner_actor{owner} {

    }

    void Shooter::shoot() {
        if (can_shoot() && !is_on_cooldown()) {
            shoot_impl();
        }
    }
}