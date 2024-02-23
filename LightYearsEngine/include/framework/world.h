#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

namespace ly {
    class Actor;
    class Application;
    class World {
        public:
            World(Application* app);

            void begin_play_internal();
            void tick_internal(float delta_time);
            void render(sf::RenderWindow& window);

            virtual ~World();

            template<typename ActorType>
            std::weak_ptr<ActorType> spawn_actor() {
                std::shared_ptr<ActorType> new_actor{ new ActorType{this} };
                pending_actors.push_back(new_actor);
                return new_actor;
            }

            sf::Vector2u get_window_size() const;
        private:
            void begin_play();
            void tick(float delta_time);
            Application* owning_app;
            bool began_play;

            std::vector<std::shared_ptr<Actor>> actors;
            std::vector<std::shared_ptr<Actor>> pending_actors;
    };
}