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
            void set_actor_location(const sf::Vector2f& new_location);
            void set_actor_rotation(float new_rotation);
            void add_actor_location_offset(const sf::Vector2f& offset);
            void add_actor_rotation_offset(float offset);
            sf::Vector2f get_actor_location() const;
            float get_actor_rotation() const;
            sf::Vector2f get_actor_forward_direction() const;
            sf::Vector2f get_actor_right_direction() const;
            virtual void begin_play();
            virtual void tick(float delta_time);
        private:
            void center_pivot();
            World* owning_world;
            bool began_play;

            sf::Sprite sprite;
            std::shared_ptr<sf::Texture> texture;
    };
}