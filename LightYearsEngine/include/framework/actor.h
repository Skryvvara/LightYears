#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "framework/object.h"

namespace ly {
    class World;
    class Actor : public Object {
        public:
            Actor(World* world, const std::string& texture_path = "");
            virtual ~Actor();

            void begin_play_internal();
            void set_texture(const std::string& texture_path);
            void render(sf::RenderWindow& window);
            void tick_internal(float delta_time);
            virtual void begin_play();
            virtual void tick(float delta_time);
        private:
            World* owning_world;
            bool began_play;

            sf::Sprite sprite;
            std::shared_ptr<sf::Texture> texture;
    };
}