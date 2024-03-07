#pragma once
#include <memory>
#include "framework/world.h"
#include "framework/timer_manager.h"

namespace ly {
    class PlayerSpaceship;
    class GameLevel1 : public World {
        public:
            GameLevel1(Application* owning_application);
        private:
            virtual void begin_play() override;
            void timer_callback();
            std::weak_ptr<PlayerSpaceship> player;
            TimerHandle test_index;
    };
}