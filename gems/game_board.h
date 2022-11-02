#pragma once

#include"gem.h"

class game_board {
public:
    unique_ptr<RenderWindow> window;
    vector <shared_ptr<gem>> gems_field;
    int size;
    Texture apple_texture, orange_texture, grape_texture, pea_texture, banana_texture;

    game_board(unique_ptr<RenderWindow> window);
    ~game_board() = default;

    RectangleShape invisibility_cloak=RectangleShape(Vector2f(600.f, 100.f));


    void draw();
    void board_update();
private:
    bool row_check();
    bool column_check();
    bool destroy_check();
    void destroy_gems();
    void destroy_animation();


};