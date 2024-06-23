#include"game_board.h"
#include"gem.h"

int main()
{
    auto window = make_unique<RenderWindow>(VideoMode(600, 600), "SFML works!", Style::Default);
    game_board board(move(window));
    /*sf::RectangleShape shape(sf::Vector2f(100,100));
    shape.setFillColor(sf::Color::Green);*/
    board.board_update(1.5);
    while (board.window->isOpen())
    {
        sf::Event event;
        while (board.window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                board.window->close();
            if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left) ) {
                Vector2f m_pos(event.mouseButton.x, event.mouseButton.y);
                int size = board.gems_field.size();
                for (int i = 0; i < size; i++) {
                    shared_ptr <gem> current_gem(board.gems_field[i]);
                    if (current_gem->contains_point(m_pos)) {
                        int index1 = i;

                        vector <int> neighbours = board.get_neighboured_gems(index1);
                        int n_count = neighbours.size();

                        current_gem->make_bigger();
                        board.window->clear();
                        board.draw();
                        board.window->display();
                        while (board.window->waitEvent(event)) {
                            if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
                                m_pos = Vector2f(event.mouseButton.x, event.mouseButton.y);
                                for (auto &neighbour : neighbours) {
                                    if (board.gems_field[neighbour]->contains_point(m_pos)) {

                                        current_gem->make_smaller();
                                        board.swap(index1, neighbour);
                                        bool flag = board.board_update(0.1);
                                        if (!flag)
                                            board.swap(index1, neighbour);
                                        break;
                                    }
                                   
                                }
                                current_gem->make_smaller();
                                break;
                            }
                        }
                        break;
                    }
                }
            }
        }

        board.window->clear();
        board.draw();
        // window.draw(shape);
        board.window->display();
    }

    return 0;
}