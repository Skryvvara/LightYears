#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "framework/object.h"

class b2Body;

namespace ly {
    class World;
    class Actor : public Object {
        public:
            Actor(World* world, const std::string& texture_path = "");
            virtual ~Actor();

            virtual void destroy() override;

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
            sf::FloatRect get_actor_global_bounds() const;
            
            virtual void begin_play();
            virtual void tick(float delta_time);
            sf::Vector2u get_window_size() const;
            const World* get_world() const { return owning_world; };
            World* get_world() { return owning_world; };

            bool is_out_of_window_bounds(float allowance = 10.0f) const;
            void set_enable_physics(bool enable);

            virtual void on_begin_overlap(Actor* target);
            virtual void on_end_overlap(Actor* target);
            
            unsigned char get_team_id() const { return team_id; };
            void set_team_id(unsigned char new_team_id);
            static unsigned char get_neutral_team_id() { return neutral_team_id; };

            bool is_target_hostile(Actor* target) const;

            virtual void apply_damage(float amount);

            const sf::Sprite& get_sprite() const { return sprite; };
            sf::Sprite& get_sprite() { return sprite; };
        private:
            void center_pivot();
            void initialize_physics();
            void disable_physics();
            void update_physics_body_transform();
            World* owning_world;
            bool began_play;

            sf::Sprite sprite;
            std::shared_ptr<sf::Texture> texture;
            b2Body* physics_body;
            bool physics_enabled;

            unsigned char team_id;
            const static unsigned char neutral_team_id = 255;
    };
}