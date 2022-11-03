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
    bool combinations_processing();
    bool board_update(bool&);
    void change_gems(int, int);
    int find_pressed_gem(const Vector2i&);
    void mouse_processing();
    bool rebuild();
private:
    bool row_check();
    bool column_check();
    bool destroy_check();
    void destroy_gems();
    void destroy_animation();
    bool is_playable();
    bool find_in_rows();
    bool find_in_columns();
    void change_gems_process(int pos1, int pos2);
};