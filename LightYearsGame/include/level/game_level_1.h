#pragma once
#include <memory>
#include "framework/world.h"

namespace ly {
    class PlayerSpaceship;
    class GameLevel1 : public World {
        public:
            GameLevel1(Application* owning_application);
        private:
            std::weak_ptr<PlayerSpaceship> player;
    };
}