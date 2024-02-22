#pragma once
#include "framework/object.h"

namespace ly {
    class World;
    class Actor : public Object {
        public:
            Actor(World* world);
            virtual ~Actor();

            void begin_play_internal();
            virtual void begin_play();
            virtual void tick(float delta_time);
        private:
            World* owning_world;
            bool began_play;
    };
}