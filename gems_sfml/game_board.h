#pragma once
#pragma once

#include"gem.h"

class game_board {
public:
    unique_ptr<RenderWindow> window;
    vector <shared_ptr<gem>> gems_field;
    int size;
    Texture apple_texture, orange_texture, grape_texture, pea_texture, banana_texture;

    game_board(unique_ptr<RenderWindow> window);
    /*game_board(const game_board&);*/
    ~game_board() = default;

    RectangleShape invisibility_cloak = RectangleShape(Vector2f(600.f, 100.f));


    void draw();
    bool board_update(float time = 0.f);
    const vector <int> get_neighboured_gems(int);
    void swap(int, int);
private:
    void swap_animation(int, int);
    bool row_check();
    bool column_check();
    bool destroy_check();
    void destroy_gems();
    void destroy_animation();


};