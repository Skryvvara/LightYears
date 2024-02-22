#pragma once
#include <framework/application.h>
#include <player/player_spaceship.h>

namespace ly {
    class PlayerSpaceship;
    class GameApplication : public Application {
        public:
            GameApplication();
            virtual void tick(float delta_time) override;
        private:
            std::weak_ptr<PlayerSpaceship> test_player;
    };
}