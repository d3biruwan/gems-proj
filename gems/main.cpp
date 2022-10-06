
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <SFML/Graphics.hpp>

#define board_size 8


using namespace std;

enum Fruit {
    apple,
    orange,
    grape,
    pea,
    banana
};

//const sf::Color gems_colors[] = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Cyan };

class gem {
public:
    int arr_pos;
    double x_pos, y_pos;
    Fruit fruit;
   // double size;
    sf::Sprite sprite;

    gem(int arr_pos, vector <sf::Texture>& textures);
    sf::Vector2f get_position();
    void draw(sf::RenderWindow& parent);
    ~gem()=default;
};
 

class game_board {
public:
    vector <unique_ptr<gem>> gems_field;
    int size;
    vector<sf::Texture> textures;

    game_board();
    void draw(sf::RenderWindow& parent);
    ~game_board()=default;


};

game_board::game_board() {
    sf::Texture apple_texture, orange_texture, grape_texture, pea_texture, banana_texture;
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

    textures.push_back(apple_texture);
    textures.push_back(orange_texture);
    textures.push_back(grape_texture);
    textures.push_back(pea_texture);
    textures.push_back(banana_texture);

  
    unique_ptr <gem> ptr;
    size = board_size * board_size;
    for (int i = 0; i < size; ++i) {
        ptr = make_unique<gem>(i,textures);
        gems_field.push_back(move(ptr));
    }
}

void game_board::draw(sf::RenderWindow& parent) {
    for (int i = 0; i < size; ++i) {
        gems_field[i]->draw(parent);
    }
}

gem::gem(int arr_pos, vector <sf::Texture>& textures) {
    this->arr_pos = arr_pos;
    int x_index = arr_pos % 8;
    int y_index = arr_pos / 8;
    
    x_pos = 100. + 48. * x_index;
    y_pos = 100. + 48. * y_index;
   

    fruit = Fruit(rand() % 5);

    switch (fruit) {
    case apple:
        sprite.setTexture(textures[0]);
        break;
    case orange:
        sprite.setTexture(textures[1]);
        break;
    case grape:
        sprite.setTexture(textures[2]);
        break;
    case pea:
        sprite.setTexture(textures[3]);
        break;
    case banana:
        sprite.setTexture(textures[4]);
        break;
    }
    sprite.setScale(1.5, 1.5);
    sprite.setPosition(x_pos, y_pos);
    
}

//void gem::set_position(){}; для изменения позиции спрайта  


void gem::draw(sf::RenderWindow& parent) {
    parent.draw(sprite);
}

int main()
{
    game_board board=game_board();
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!",sf::Style::Default);
    /*sf::RectangleShape shape(sf::Vector2f(100,100));
    shape.setFillColor(sf::Color::Green);*/

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close(); 
        }

        window.clear();
        board.draw(window);
       // window.draw(shape);
        window.display();
    }

    return 0;
}