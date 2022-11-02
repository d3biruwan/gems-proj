#include"gem.h"
#include"game_board.h"

game_board::game_board(unique_ptr<RenderWindow> window) {
    this->window = move(window);
    apple_texture.loadFromFile("Fruits.png", sf::IntRect(0, 0, 32, 32));
    apple_texture.setSmooth(true);
    orange_texture.loadFromFile("Fruits.png", sf::IntRect(0, 32, 32, 32));
    orange_texture.setSmooth(true);
    grape_texture.loadFromFile("Fruits.png", sf::IntRect(96, 0, 32, 32));
    grape_texture.setSmooth(true);
    pea_texture.loadFromFile("Fruits.png", sf::IntRect(32, 0, 32, 32));
    pea_texture.setSmooth(true);
    banana_texture.loadFromFile("Fruits.png", sf::IntRect(64, 32, 32, 32));
    banana_texture.setSmooth(true);


    shared_ptr <gem> ptr;
    size = board_size * board_size;
    for (int i = 0; i < size; ++i) {
        ptr = make_shared<gem>(i, *this);
        gems_field.push_back(move(ptr));
    }

    invisibility_cloak.setFillColor(Color::Black);

}

void game_board::draw() {
    for (int i = 0; i < size; ++i) {
        gems_field[i]->draw();
    }
    window->draw(invisibility_cloak);
}

bool game_board::row_check() {
    for (int i = 0; i < size;) {
        int match_counter = 1;
        for (int j = 1; j < board_size - (i % board_size); j++) {
            if (gems_field[i]->get_fruit() == gems_field[i+j]->get_fruit()) {
                match_counter++;
            }
            else {
                break;
            }
        }
        if (match_counter >= 3) {
            for (int j = match_counter-1; j >= 0; j--) {
                gems_field[i + j]->to_destroy = true;
            }
        }
        i += match_counter;
    }
}

bool game_board::column_check() {
    bool again = false;
    for (int l = 0; l < board_size; l++) {
        for (int i = 0; i < size;) {
            int match_counter = 1;
            for (int j = 1; j < board_size - (i / board_size); j++) {
                if (gems_field[i]->get_fruit() == gems_field[i + j * board_size]->get_fruit()) {
                    match_counter++;
                }
                else {
                    break;
                }
            }
            if (match_counter >= 3) {
                for (int j = match_counter - 1; j >= 0; j--) {
                    gems_field[i + j * board_size]->to_destroy = true;
                }
                again = true;
            }
            i += board_size * match_counter;
        }
    }
    return again;
}

bool game_board::destroy_check() {
    bool again = false;
    if (row_check()) {
        again = true;
    }
    if (column_check()) {
        again = true;
    }
}

void game_board::destroy_gems() {
    for (int l = 0; l < board_size; l++) {
        int destroyed_count = 0;
        for (int i = 0; i < size; i += board_size) {
            if (gems_field[i + l]->to_destroy == false) {
                continue;
            }
            gems_field[i + l]->to_destroy = false;
            for (int k = i + l; k > destroyed_count * board_size + l; k += -board_size) {
                shared_ptr<gem> tmp = gems_field[k - board_size];
                gems_field[k - board_size] = gems_field[k];
                gems_field[k] = tmp;
                auto tmp_pos = gems_field[k]->get_new_position();
                gems_field[k]->set_new_position(gems_field[k - board_size]->get_new_position());
                gems_field[k - board_size]->set_new_position(tmp_pos);

                gems_field[k]->set_velocity(animation_speed);
            }
            int x_index = (destroyed_count * board_size + l) % board_size;
            int y_index = (destroyed_count * board_size + l) / board_size;

            gems_field[destroyed_count * board_size + l]->set_position(Vector2f(100.f + 48.f * x_index, 52.f));
            gems_field[destroyed_count * board_size + l]->set_fruit(Fruit(rand() % 5));
            gems_field[destroyed_count * board_size + l]->set_velocity(animation_speed);
            destroyed_count++;
        }
    }
}

void game_board::destroy_animation() {
    
    vector<int> still_columns;
    int counter = board_size;
    while (counter > 0) {
        for (int k = 0; k < board_size; k++) {
            if (find(still_columns.begin(), still_columns.end(), k) != still_columns.end()) {
                continue;
            }
            for (int i = 0; i < size; i += board_size) {
                if (gems_field[i + k]->get_velocity() == 0.f) {
                    if (i + k < 8) {
                        still_columns.push_back(k);
                        counter--;
                    }
                    break;
                }
                if ((i+board_size<size)&&(gems_field[i + k + board_size]->is_on_board() == false)) {
                    continue;
                }
                gems_field[i + k]->move();
                if (gems_field[i + k]->get_new_position().y == gems_field[i + k]->get_position().y) {
                    gems_field[i + k]->set_velocity(0.f);
                }
            }
        }
        window->clear();
        draw();
        // window.draw(shape);
        window->display();
    }
}

void game_board::board_update() {
    Clock clock;
    while (clock.getElapsedTime().asSeconds() < 1.5) {
        window->clear();
        draw();
        // window.draw(shape);
        window->display();
    }
    destroy_check();
    destroy_gems();
    destroy_animation();
}

