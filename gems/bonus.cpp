#include"bonus.h"
#include"game_board.h"

void bonus::set_velocity(const float Vx, const float Vy) {
	v_x = Vx;
	v_y = Vy;
}

void  bonus::set_texture(const Texture& texture) {
	sprite.setTexture(texture);
}

void  bonus::move() {
	sprite.move(v_x, v_y);
}

void  bonus::draw() {
	board->window->draw(sprite);
}

brush::brush(int start_pos, int new_pos, int arr_p, const Fruit& type, game_board& board) {
	this->board = &board;
	brush_type = type;
	arr_pos = arr_p;
	this->start_pos = start_pos;
	this->finish_pos = new_pos;

}


void brush::bonus_resolve() {
	vector<bool> good_places{ true,true,true,true };
	int counter = 4;
	int bad_pos = -1;
	board->gems_field[arr_pos]->set_fruit(brush_type);
	if (arr_pos - board_size - 1 < 0) {
		good_places[0] = false;
		counter--;
	}
	if (arr_pos - board_size + 1 < 0) {
		good_places[1] = false;
		counter--;
	}
	if (arr_pos + board_size - 1 > board->size) {
		good_places[2] = false;
		counter--;
	}
	if (arr_pos + board_size + 1 > board->size) {
		good_places[3] = false;
		counter--;
	}
	if (counter <= 2) {
		if (good_places[0]) {
			board->gems_field[arr_pos - board_size - 1]->set_fruit(brush_type);
		}
		if (good_places[1]) {
			board->gems_field[arr_pos - board_size + 1]->set_fruit(brush_type);

		}
		if (good_places[2]) {
			board->gems_field[arr_pos + board_size - 1]->set_fruit(brush_type);
		}
		if (good_places[3]) {
			board->gems_field[arr_pos + board_size + 1]->set_fruit(brush_type);
		}
		return;
	}
	if (counter == 3) {
		while (true) {
			bad_pos = rand() % 4;
			if (good_places[bad_pos] == false) {
				break;
			}
		}
	}
	int rand1 = rand() % 4;
	int rand2;
	while (true) {
		rand1 = rand() % 4;
		if (rand1 != bad_pos) {
			break;
		}
	}

	while (true) {
		rand2 = rand() % 4;
		if ((rand2 != rand1)&&(rand2!=bad_pos)) {
			break;
		}
	}
	if (rand1 == 0 || rand2 == 0) {
		board->gems_field[arr_pos - board_size - 1]->set_fruit(brush_type);
	}
	if (rand1 == 0 || rand2 == 0) {
		board->gems_field[arr_pos - board_size + 1]->set_fruit(brush_type);
	}
	if (rand1 == 0 || rand2 == 0) {
		board->gems_field[arr_pos + board_size - 1]->set_fruit(brush_type);
	}
	if (rand1 == 0 || rand2 == 0) {
		board->gems_field[arr_pos + board_size + 1]->set_fruit(brush_type);
	}


}

bomb::bomb(int start_pos, int new_pos, int arr_p, game_board& board) {

	this->board = &board;
	arr_pos = arr_p;
	this->start_pos = start_pos;
	this->finish_pos = new_pos;
}

void bomb::bonus_resolve() {
	board->gems_field[arr_pos]->to_destroy = true;
}

const Vector2f bonus:: get_position() {
	return sprite.getPosition();
}

const Vector2f bonus::get_destination() {
	return board->gems_field[finish_pos]->get_position();
}
