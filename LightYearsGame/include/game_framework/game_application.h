#pragma once
#include <framework/application.h>

namespace ly {
    class Actor;
    class GameApplication : public Application {
        public:
            GameApplication();
            virtual void tick(float delta_time) override;
        private:
            float counter;
            std::weak_ptr<Actor> actor_to_destroy;
    };
}