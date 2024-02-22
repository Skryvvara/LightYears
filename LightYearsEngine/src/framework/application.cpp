#include <stdio.h>
#include "framework/application.h"
#include "framework/core.h"
#include "framework/world.h"

namespace ly {
    Application::Application() 
        : render_window{sf::VideoMode(800, 600), "LightYearsGame"},
        tick_clock{},
        target_framerate{60.0f},
        current_world{nullptr}
    {

    }

    void Application::tick_internal(float delta_time) {
        tick(delta_time);
        if (current_world) {
            current_world->tick_internal(delta_time);
        }
    }

    void Application::tick(float delta_time) {
        LOG("Ticking at framerate: %f", 1.0f/delta_time);
    }

    void Application::render_internal() {
        render_window.clear();

        render();

        render_window.display();
    }

    void Application::render() {
        sf::CircleShape circle{ 50 };
        circle.setFillColor(sf::Color::Yellow);
        circle.setOrigin(50, 50);
        circle.setPosition(render_window.getSize().x/2.0f, render_window.getSize().y/2.0f);
        render_window.draw(circle);
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