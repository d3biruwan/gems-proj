#pragma once
#include"gem.h"

class bonus {
public:
	bonus() = default;
	~bonus() = default;

	void set_velocity(const float, const float);
	void set_texture(const Texture&);

	const Vector2f get_position();
	const Vector2f get_destination();

	void move();

	void draw();

	virtual void bonus_resolve() = 0;

protected:
	Sprite sprite;
	game_board* board = NULL;
	int start_pos = 0, finish_pos = 0;
	int arr_pos = 0;
	float v_x = 0.f, v_y = 0.f;
};

class brush:public bonus {
public:
	brush(int, int, int,const Fruit&, game_board&);
	~brush() = default;

	void bonus_resolve() override;
private:
	Fruit brush_type;
};

class bomb :public bonus {
public:
	bomb(int, int, int, game_board&);
	~bomb() = default;

	void bonus_resolve() override;


};