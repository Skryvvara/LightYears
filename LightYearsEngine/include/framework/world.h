#pragma once

namespace ly {
    class Application;
    class World {
        public:
            World(Application* app);

            void begin_play_internal();
            void tick_internal(float delta_time);

            virtual ~World();
        private:
            void begin_play();
            void tick(float delta_time);
            Application* owning_app;
            bool began_play;
    };
}