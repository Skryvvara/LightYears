#include "framework/actor.h"
#include "framework/asset_manager.h"
#include "framework/core.h"

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
        LOG("Actor ticking");
    }

    void Actor::render(sf::RenderWindow& window) {
        if (is_pending_destroy()) return;
        
        window.draw(sprite);
    }
}