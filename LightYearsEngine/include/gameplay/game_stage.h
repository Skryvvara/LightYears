#pragma once
#include "framework/object.h"
#include "framework/delegate.h"

namespace ly {
    class World;
    class GameStage : public Object {
        public:
            GameStage(World* world);

            virtual void begin_play();
            virtual void tick(float delta_time);
            void end_stage();

            bool is_finished() const { return _is_finished; };

            const World* get_world() const { return _world; };
            World* get_world() { return _world; };

            Delegate<> on_stage_finished;
        private:
            virtual void end_play();

            World* _world;
            bool _is_finished;
    };
}
