#include <box2d/b2_body.h>

#include "framework/actor.h"
#include "framework/asset_manager.h"
#include "framework/core.h"
#include "framework/math_util.h"
#include "framework/physics.h"
#include "framework/world.h"

namespace ly {
    Actor::Actor(World* world, const std::string& texture_path)
        : owning_world{world}, 
        began_play{false},
        sprite{},
        texture{},
        physics_body{nullptr},
        physics_enabled{false},
        team_id{get_neutral_team_id()} {
            
        set_texture(texture_path);
    }

    Actor::~Actor() {
        
    }

    void Actor::destroy() {
        disable_physics();
        Object::destroy();
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
        update_physics_body_transform();
    }

    void Actor::add_actor_location_offset(const sf::Vector2f& offset) {
        set_actor_location(get_actor_location() + offset);
    }

    void Actor::set_actor_rotation(float new_rotation) {
        sprite.setRotation(new_rotation);
        update_physics_body_transform();
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

    void Actor::set_enable_physics(bool enable) {
        physics_enabled = enable;
        if (physics_enabled) {
            initialize_physics();
        } else {
            disable_physics();
        }
    }

    void Actor::initialize_physics() {
        if (!physics_body) {
            physics_body = Physics::get().add_listener(this);
        }
    }

    void Actor::disable_physics() {
        if (physics_body) {
            Physics::get().remove_listener(physics_body);
            physics_body = nullptr;
        }
    }

    void Actor::update_physics_body_transform() {
        if (physics_body) {
            float physics_scale = Physics::get().get_physics_scale();
            b2Vec2 location{get_actor_location().x * physics_scale, get_actor_location().y * physics_scale};
            float rotation = degrees_to_radians(get_actor_rotation());

            physics_body->SetTransform(location, rotation);
        }
    }

    void Actor::on_begin_overlap(Actor* other) {

    }

    void Actor::on_end_overlap(Actor* other) {
        
    }

    void Actor::set_team_id(unsigned char new_team_id) {
        team_id = new_team_id;
    }

    bool Actor::is_target_hostile(Actor* target) const {
        if (get_team_id() == get_neutral_team_id() || target->get_team_id() == get_neutral_team_id()) {
            return false;
        }

        return get_team_id() != target->get_team_id();
    }

    void Actor::apply_damage(float amount) {
        
    }
}