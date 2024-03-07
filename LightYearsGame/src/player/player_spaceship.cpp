#include <SFML/System.hpp>
#include "player/player_spaceship.h"
#include "framework/core.h"
#include "framework/math_util.h"

#define KEY_DOWN(key) sf::Keyboard::isKeyPressed(sf::Keyboard::key)

#define MOVE_UP W
#define MOVE_DOWN S
#define MOVE_LEFT A
#define MOVE_RIGHT D
#define MOVE_SHOOT Space

namespace ly {
    PlayerSpaceship::PlayerSpaceship(World* world, const std::string& path)
        : Spaceship{world, path},
        move_input{},
        speed{300},
        shooter{new BulletShooter{this, 0.1f}} {
        set_team_id(1);
    }

    void PlayerSpaceship::tick(float delta_time) {
        Spaceship::tick(delta_time);
        handle_input();
        consume_input(delta_time);
    }

    void PlayerSpaceship::handle_input() {
        if(KEY_DOWN(MOVE_UP)) {
            move_input.y = -1.0f;
        } 
        
        if (KEY_DOWN(MOVE_DOWN)) {
            move_input.y = 1.0f;
        } 
        
        if (KEY_DOWN(MOVE_LEFT)) {
            move_input.x = -1.0f;
        } 
        
        if (KEY_DOWN(MOVE_RIGHT)) {
            move_input.x = 1.0f;
        }

        clamp_input_on_edge();
        normalize_input();

        if (KEY_DOWN(MOVE_SHOOT)) {
            shoot();
        }
    }

    void PlayerSpaceship::normalize_input() {
        normalize_vector(move_input);
    }

    void PlayerSpaceship::clamp_input_on_edge() {
        sf::Vector2f actor_location = get_actor_location();
        if (actor_location.x < 0 && move_input.x == -1) {
            move_input.x = 0.0f;
        }

        if (actor_location.x > get_window_size().x && move_input.x == 1.f) {
            move_input.x = 0.0f;
        }

        if (actor_location.y < 0 && move_input.y == -1) {
            move_input.y = 0.0f;
        }

        if (actor_location.y > get_window_size().y && move_input.y == 1.f) {
            move_input.y = 0.0f;
        }
    }

    void PlayerSpaceship::consume_input(float delta_time) {
        set_velocity(move_input * speed);
        move_input.x = move_input.y = 0.0f;
    }

    void PlayerSpaceship::shoot() {
        if (shooter) {
            shooter->shoot();
        }
    }
}