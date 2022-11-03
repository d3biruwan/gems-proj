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
	bool again = false;
	for (int i = 0; i < size;) {
		int match_counter = 1;
		for (int j = 1; j < board_size - (i % board_size); j++) {
			if (gems_field[i]->get_fruit() == gems_field[i + j]->get_fruit()) {
				match_counter++;
			}
			else {
				break;
			}
		}
		if (match_counter >= 3) {
			for (int j = match_counter - 1; j >= 0; j--) {
				gems_field[i + j]->to_destroy = true;
			}
			again = true;
		}
		i += match_counter;
	}
	return again;
}

bool game_board::column_check() {
	bool again = false;
	for (int l = 0; l < board_size; l++) {
		for (int i = 0; i < size;) {
			int match_counter = 1;
			for (int j = 1; j < board_size - (i / board_size); j++) {
				if (gems_field[i + l]->get_fruit() == gems_field[i + j * board_size + l]->get_fruit()) {
					match_counter++;
				}
				else {
					break;
				}
			}
			if (match_counter >= 3) {
				for (int j = match_counter - 1; j >= 0; j--) {
					gems_field[i + j * board_size + l]->to_destroy = true;
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
	return again;
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
				if ((i + board_size < size) && (gems_field[i + k + board_size]->is_on_board() == false)) {
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

bool game_board::find_in_rows() {
	for (int i = 0; i < size;) {
		int match_counter = 1;
		for (int j = 1; j < board_size - (i % board_size); j++) {
			if (gems_field[i]->get_fruit() == gems_field[i + j]->get_fruit()) {
				match_counter++;
			}
			else {
				break;
			}
		}
		if (match_counter == 2) {
			if ((i % board_size > 1) && (gems_field[i - 2]->get_fruit() == gems_field[i]->get_fruit())) {
				return true;
			}
			if ((i % board_size < board_size - 3) && (gems_field[i + 3]->get_fruit() == gems_field[i]->get_fruit())) {
				return true;
			}
		}
		i += match_counter;
	}

	return false;
}

bool game_board::find_in_columns() {
	for (int l = 0; l < board_size; l++) {
		for (int i = 0; i < size;) {
			int match_counter = 1;
			for (int j = 1; j < board_size - (i / board_size); j++) {
				if (gems_field[i + l]->get_fruit() == gems_field[i + j * board_size + l]->get_fruit()) {
					match_counter++;
				}
				else {
					break;
				}
			}
			if (match_counter == 2) {
				if ((i >= 2 * board_size) && (gems_field[i + l]->get_fruit() == gems_field[i + l - 2 * board_size]->get_fruit())) {
					return true;
				}
				if ((i <= 4 * board_size) && (gems_field[i + l]->get_fruit() == gems_field[i + l + 3 * board_size]->get_fruit())) {
					return true;
				}
			}
			i += board_size * match_counter;
		}
	}
	return false;
}

bool game_board::is_playable() {
	if ((find_in_rows()) || (find_in_columns())) {
		return true;
	}
}

bool game_board::rebuild() {
	if (is_playable()) {
		return false;
	}
	for (auto& element : gems_field) {
		element->set_fruit(Fruit(rand() % 5));
	}
	return true;
}

bool game_board::combinations_processing() {
	bool again = false;
	Clock clock;
	while (clock.getElapsedTime().asSeconds() < 0.5) {
		window->clear();
		draw();
		// window.draw(shape);
		window->display();
	}
	again = destroy_check();
	if (again == false) {
		return false;
	}
	destroy_gems();
	destroy_animation();
	return again;
}

bool game_board::board_update(bool& was_successful) {
	int count = 0;
	while (combinations_processing()) {
		count++;
	}
	if (count == 0) {
		was_successful = false;
		return false;
	}
	was_successful = true;
	return rebuild();
}

void game_board::change_gems_process(int pos1, int pos2) {
	gems_field[pos1]->set_new_position(gems_field[pos2]->get_position());
	gems_field[pos2]->set_new_position(gems_field[pos1]->get_position());
	auto tmp = gems_field[pos1];
	gems_field[pos1] = gems_field[pos2];
	gems_field[pos2] = tmp;
	int flag = 1;
	if (pos1 < pos2) {
		gems_field[pos1]->set_velocity(-animation_speed);
		gems_field[pos2]->set_velocity(animation_speed);
	}
	else {
		gems_field[pos2]->set_velocity(-animation_speed);
		gems_field[pos1]->set_velocity(animation_speed);
	}
	
	while (flag) {
		if (gems_field[pos1]->get_position() == gems_field[pos1]->get_new_position()) {
			gems_field[pos1]->set_velocity(0.f);
			gems_field[pos2]->set_velocity(0.f);
			flag = 0;
		}

		if (fabs(pos2 - pos1) > 1) {
			gems_field[pos1]->move();
			gems_field[pos2]->move();
		}
		else {
			gems_field[pos1]->move_x();
			gems_field[pos2]->move_x();
		}

		window->clear();
		draw();
		window->display();
	}
}

void game_board::change_gems(int pos1, int pos2) {
	int counter = 0;
	bool successful_change = false;
	change_gems_process(pos1, pos2);
	while (board_update(successful_change)) {
		counter++;
	}
	if ((counter != 0)||(successful_change==true)) {
		return;
	}
	change_gems_process(pos1, pos2);
}

int game_board::find_pressed_gem(const Vector2i& pos) {
	for (int i = 0; i < gems_field.size();i++) {
		auto& element = gems_field[i];
		if ((element->get_position().x <= pos.x) && (element->get_position().x + sprite_size>=pos.x)) {
			if ((element->get_position().y <= pos.y) && (element->get_position().y + sprite_size >= pos.y))
				return i;
		}
	}
	return -1;
}

void game_board::mouse_processing() {
	Vector2i localPosition1 = Mouse::getPosition(*window);
	Vector2i localPosition2;

	int pos1 = find_pressed_gem(localPosition1);
	int pos2;
	if (pos1 == -1) {
		return;
	}
	gems_field[pos1]->set_scale(1.25f);
	Clock clock;
	while(clock.getElapsedTime().asSeconds()<0.3) {
		continue;
	}
	while (true) {
		window->clear();
		draw();
		window->display();
		if (Mouse::isButtonPressed(Mouse::Left)) {
			localPosition2 = Mouse::getPosition(*window);
			pos2 = find_pressed_gem(localPosition2);
			if (pos2 == -1) {
				gems_field[pos1]->set_scale(0.8f);
				return;
			}
			if ((fabs(pos1 - pos2) != 1) && (fabs(pos1 - pos2) != 8)) {
				gems_field[pos1]->set_scale(0.8f);
				return;
			}
			break;
		}
	}
	gems_field[pos1]->set_scale(0.8f);
	change_gems(pos1, pos2);
}
