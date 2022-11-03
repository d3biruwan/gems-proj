#include"game_board.h"
#include"gem.h"

int main()
{
    auto window = make_unique<RenderWindow>(VideoMode(600, 600), "SFML works!", Style::Default);
    game_board board=game_board(move(window));
    /*sf::RectangleShape shape(sf::Vector2f(100,100));
    shape.setFillColor(sf::Color::Green);*/
    bool n = true;
    while (board.board_update(n)) {
        continue;
    }
    board.rebuild();
    while (board.board_update(n)) {
        continue;
    }
    
    while (board.window->isOpen())
    {
        sf::Event event;
        while (board.window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                board.window->close();
        }
        if (Mouse::isButtonPressed(Mouse::Left)) {
            board.mouse_processing();
        }

        board.window->clear();
        board.draw();
       // window.draw(shape);
        board.window->display();
    }

    return 0;
}