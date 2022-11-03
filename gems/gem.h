#pragma once

#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <SFML/Graphics.hpp>

#define board_size 8
#define animation_speed 0.25f
#define sprite_size 48
#define max_bonus 2

using namespace std;
using namespace sf;

enum Fruit {
    apple,
    orange,
    grape,
    pea,
    banana
};

class game_board;

class gem {
public:
    gem(int, game_board&);
    ~gem() = default;

    const Vector2f get_position();
    const Vector2f get_new_position();
    const Fruit get_fruit();
    const float get_velocity() ;
    bool is_on_board();
    
    void move();
    void move_x();
   // void set_position(const Vector2f&);
    void set_new_position(const Vector2f&);
    void set_position(const Vector2f&);
    void set_velocity(const float);
    void set_fruit(const Fruit&);
    void set_scale(const float);

    bool to_destroy = false;

    void draw();

protected:
    float velocity = 0.0;
    game_board* board = NULL;
    int arr_pos;
    float x_pos, y_pos;
    float x_new_pos = 0.f, y_new_pos = 0.f;
    Fruit fruit;
    sf::Sprite sprite;
};