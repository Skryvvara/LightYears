#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "framework/object.h"

namespace ly {
    class Actor;
    class Application;
    class GameStage;
    class World : public Object {
        public:
            World(Application* app);

            void begin_play_internal();
            void tick_internal(float delta_time);
            void render(sf::RenderWindow& window);

            virtual ~World();

            template<typename ActorType, typename... Args>
            std::weak_ptr<ActorType> spawn_actor(Args... args) {
                std::shared_ptr<ActorType> new_actor{ new ActorType(this, args...) };
                pending_actors.push_back(new_actor);
                return new_actor;
            }

            sf::Vector2u get_window_size() const;
            void clean_cycle();

            void add_game_stage(const std::shared_ptr<GameStage>& new_stage);
        private:
            virtual void begin_play();
            virtual void tick(float delta_time);
            virtual void init_game_stages();
            virtual void all_game_stages_finished();
            void next_game_stage();

            Application* owning_app;
            bool began_play;

            std::vector<std::shared_ptr<Actor>> actors;
            std::vector<std::shared_ptr<Actor>> pending_actors;
            std::vector<std::shared_ptr<GameStage>> stages;
            int _current_stage_index;
    };
}