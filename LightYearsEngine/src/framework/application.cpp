#include <stdio.h>
#include "framework/application.h"
#include "framework/asset_manager.h"
#include "framework/core.h"
#include "framework/world.h"

namespace ly {
    Application::Application(unsigned int width, unsigned int height, const std::string& title, sf::Uint32 style) 
        : render_window{sf::VideoMode(width, height), title, style},
        tick_clock{},
        target_framerate{60.0f},
        current_world{nullptr},
        clean_clock{},
        clean_interval{2.0f}
    {

    }

    void Application::tick_internal(float delta_time) {
        tick(delta_time);
        if (current_world) {
            current_world->tick_internal(delta_time);
        }

        if (clean_clock.getElapsedTime().asSeconds() >= clean_interval) {
            clean_clock.restart();
            AssetManager::get().clean_cycle();
            if (current_world) {
                current_world->clean_cycle();
            }
        }
    }

    void Application::tick(float delta_time) {
    }

    void Application::render_internal() {
        render_window.clear();

        render();

        render_window.display();
    }

    void Application::render() {
        if (current_world) {
            current_world->render(render_window);
        }
    }

    void Application::run() {
        tick_clock.restart();
        float accumulated_time = 0.0f;
        float target_delta_time = 1.0f / target_framerate;

        while (render_window.isOpen()) {
            sf::Event window_event;
            while (render_window.pollEvent(window_event)) {
                if (window_event.type == sf::Event::EventType::Closed) {
                    render_window.close();
                }
            }

            accumulated_time += tick_clock.restart().asSeconds();
            while (accumulated_time >= target_delta_time) {
                accumulated_time -= target_delta_time;
                tick_internal(target_delta_time);
                render_internal();
            }
        }
    }
}