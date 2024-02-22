#include <SFML/System.hpp>
#include "player/player_spaceship.h"
#include "framework/core.h"
#include "framework/math_util.h"

#define KEY_DOWN(key) sf::Keyboard::isKeyPressed(sf::Keyboard::key)

#define MOVE_UP W
#define MOVE_DOWN S
#define MOVE_LEFT A
#define MOVE_RIGHT D

namespace ly {
    PlayerSpaceship::PlayerSpaceship(World* world, const std::string& path)
        : Spaceship{world, path},
        move_input{},
        speed{200} {

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

        normalize_input();
    }

    void PlayerSpaceship::normalize_input() {
        normalize_vector(move_input);
        LOG("move input is now: %f, %f", move_input.x, move_input.y);
    }

    void PlayerSpaceship::consume_input(float delta_time) {
        set_velocity(move_input * speed);
        move_input.x = move_input.y = 0.0f;
    }
}