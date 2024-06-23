#pragma once

#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <SFML/Graphics.hpp>

#define board_size 8
#define animation_speed 0.0625f

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
    const Vector2f get_velocity();
    bool is_on_board();

    void move();
    // void set_position(const Vector2f&);
    void set_new_position(const Vector2f&);
    void set_position(const Vector2f&);
    void set_velocity(const Vector2f&);
    void set_fruit(const Fruit&);
    bool contains_point(const Vector2f&);

    bool to_destroy = false;

    void draw();
    void make_bigger();
    void make_smaller();
protected:
    Vector2f velocity = Vector2f(0.0, 0.0);
    game_board* board = NULL;
    int arr_pos;
    float x_pos, y_pos;
    float x_new_pos = 0.f, y_new_pos = 0.f;
    Fruit fruit;
    sf::Sprite sprite;
};