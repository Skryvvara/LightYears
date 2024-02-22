#pragma once
#include <SFML/Graphics.hpp>
#include "framework/world.h"

namespace ly {
    class Application {
    public:
        Application();
        void run();

        template<typename WorldType>
        std::weak_ptr<WorldType> load_world() {
            std::shared_ptr<WorldType> new_world{new WorldType{this} };
            current_world = new_world;
            current_world->begin_play_internal();
            return new_world;
        }
    private:
        void tick_internal(float delta_time);
        void render_internal();

        virtual void tick(float delta_time);
        virtual void render();

        sf::RenderWindow render_window;
        sf::Clock tick_clock;
        float target_framerate;

        std::shared_ptr<World> current_world;
    };
}