#include"gem.h"
#include"game_board.h"

gem::gem(int arr_pos, game_board& board) {
    this->board = &board;
    this->arr_pos = arr_pos;
    int x_index = arr_pos % board_size;
    int y_index = arr_pos / board_size;

   /* x_pos = 100. + 48. * x_index;
    y_pos = 100. + 48. * y_index;*/

    set_position(Vector2f(100.f + 48.f * x_index, 100.f + 48.f * y_index));
    set_new_position(Vector2f(100.f + 48.f * x_index, 100.f + 48.f * y_index));

    fruit = Fruit(rand() % 5);

    switch (fruit) {
    case apple:
        sprite.setTexture(this->board->apple_texture);
        break;
    case orange:
        sprite.setTexture(this->board->orange_texture);
        break;
    case grape:
        sprite.setTexture(this->board->grape_texture);
        break;
    case pea:
        sprite.setTexture(this->board->pea_texture);
        break;
    case banana:
        sprite.setTexture(this->board->banana_texture);
        break;
    }
    sprite.setScale(1.5, 1.5);
   // sprite.setPosition(x_pos, y_pos);

}

void gem::draw() {
    board->window->draw(sprite);
}

const Fruit gem::get_fruit() {
    return fruit;
}

const float gem::get_velocity() {
    return velocity;
}

const Vector2f gem::get_new_position() {
    return Vector2f(x_new_pos, y_new_pos);
}

const Vector2f gem::get_position() {
    return Vector2f(x_pos, y_pos);
}


void gem::set_new_position(const Vector2f& new_pos) {
    x_new_pos = new_pos.x;
    y_new_pos = new_pos.y;
}

void gem::set_velocity(const float vel) {
    velocity = vel;
}

void gem::set_position(const Vector2f& pos) {
    x_pos = pos.x;
    y_pos = pos.y;
    sprite.setPosition(x_pos, y_pos);
}

void gem::set_fruit(const Fruit& fr) {
    fruit = fr;
    switch (fruit) {
    case apple:
        sprite.setTexture(this->board->apple_texture);
        break;
    case orange:
        sprite.setTexture(this->board->orange_texture);
        break;
    case grape:
        sprite.setTexture(this->board->grape_texture);
        break;
    case pea:
        sprite.setTexture(this->board->pea_texture);
        break;
    case banana:
        sprite.setTexture(this->board->banana_texture);
        break;
    }
}

void gem::set_scale(const float scale) {
    sprite.scale(scale, scale);
}

void gem::move() {
    sprite.move(0, get_velocity());
    y_pos = sprite.getPosition().y;
}

void gem::move_x() {
    sprite.move(get_velocity(), 0);
    x_pos = sprite.getPosition().x;
}

bool gem::is_on_board() {
    if (get_position().y >= 100) {
        return true;
    }
    return false;
}