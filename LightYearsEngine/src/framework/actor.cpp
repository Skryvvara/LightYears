#include "framework/actor.h"
#include "framework/asset_manager.h"
#include "framework/core.h"
#include "framework/math_util.h"
#include "framework/world.h"
namespace ly {
    Actor::Actor(World* world, const std::string& texture_path)
        : owning_world{world}, 
        began_play{false},
        sprite{},
        texture{} {
            
        set_texture(texture_path);
    }

    Actor::~Actor() {
        LOG("Actor destroyed");
    }

    void Actor::set_texture(const std::string& texture_path) {
        AssetManager& asset_manager = AssetManager::get();

        texture = asset_manager.load_texture(texture_path);
        if (!texture) return;
        sprite.setTexture(*texture);

        int texture_width = texture->getSize().x;
        int texture_height = texture->getSize().y;
        sprite.setTextureRect(sf::IntRect{sf::Vector2i{}, 
            sf::Vector2i{texture_width, texture_height}});
        center_pivot();
    }

    void Actor::begin_play_internal() {
        if (!began_play) {
            began_play = true;
            begin_play();
        }
    }

    void Actor::begin_play() {
        LOG("Actor begin play");
    }

    void Actor::tick_internal(float delta_time) {
        if (is_pending_destroy()) return;
        
        tick(delta_time);
    }

    void Actor::tick(float delta_time) {
    }

    void Actor::render(sf::RenderWindow& window) {
        if (is_pending_destroy()) return;
        
        window.draw(sprite);
    }

    void Actor::set_actor_location(const sf::Vector2f& new_location) {
        sprite.setPosition(new_location);
    }

    void Actor::add_actor_location_offset(const sf::Vector2f& offset) {
        set_actor_location(get_actor_location() + offset);
    }

    void Actor::set_actor_rotation(float new_rotation) {
        sprite.setRotation(new_rotation);
    }

    void Actor::add_actor_rotation_offset(float offset) {
        set_actor_rotation(get_actor_rotation() + offset);
    }

    sf::Vector2f Actor::get_actor_location() const
    {
        return sprite.getPosition();
    }

    float Actor::get_actor_rotation() const {
        return sprite.getRotation();
    }

    sf::Vector2f Actor::get_actor_forward_direction() const {
        return rotation_to_vector(get_actor_rotation());
    }

    sf::Vector2f Actor::get_actor_right_direction() const {
        return rotation_to_vector(get_actor_rotation() + 90.0f);
    }

    sf::FloatRect Actor::get_actor_global_bounds() const {
        return sprite.getGlobalBounds();
    }

    void Actor::center_pivot() {
        sf::FloatRect bounds = sprite.getGlobalBounds();
        sprite.setOrigin(bounds.width/2.0f, bounds.height/2.0f);
    }

    sf::Vector2u Actor::get_window_size() const {
        return owning_world->get_window_size();
    }

    bool Actor::is_out_of_window_bounds() const {
        float window_width = get_world()->get_window_size().x;
        float window_height = get_world()->get_window_size().y;

        float width = get_actor_global_bounds().width;
        float height = get_actor_global_bounds().height;

        sf::Vector2f location = get_actor_location();

        if (location.x < -width) {
            return true;
        }

        if (location.x > window_width + width) {
            return true;
        }

        if (location.y < -height) {
            return true;
        }

        if (location.y > window_height + height) {
            return true;
        }

        return false;
    }
}