#include"game_board.h"
#include"gem.h"

int main()
{
    auto window = make_unique<RenderWindow>(VideoMode(600, 600), "SFML works!", Style::Default);
    game_board board(move(window));
    /*sf::RectangleShape shape(sf::Vector2f(100,100));
    shape.setFillColor(sf::Color::Green);*/
    board.board_update();
    while (board.window->isOpen())
    {
        sf::Event event;
        while (board.window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                board.window->close();
        }

        board.window->clear();
        board.draw();
        // window.draw(shape);
        board.window->display();
    }

    return 0;
}