#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

struct Pincel {
    sf::Font font;
    sf::Text text;
    sf::RenderWindow& window;

    Pincel(sf::RenderWindow& window) : window(window) {
        if(!font.loadFromFile("font/Ubuntu-Regular.ttf")) {
            std::cout << "Erro ao carregar fonte\n" << std::endl;
        }
        text.setFont(font);
    }

    void write(std::string str, int x, int y, int size, sf::Color color) {
        text.setString(str);
        text.setPosition(x, y);
        text.setCharacterSize(size);
        text.setFillColor(color);
        window.draw(text);
    }
};

struct Bubble {
    static const int radius { 10 };
    int x;
    int y;
    char letter;
    int speed;
    bool alive { true };


    Bubble(int x, int y, char letter, int speed) {
        this->x = x;
        this->y = y;
        this->letter = letter;
        this->speed = speed;
    }

    void update() {
        this->y += this->speed;
    }

    void draw(sf::RenderWindow& window) {
        sf::CircleShape bubble(Bubble::radius);
        bubble.setPosition(x, y);
        bubble.setFillColor(sf::Color::White);
        window.draw(bubble);

        static Pincel pincel(window);
        pincel.write(std::string(1, letter), x + 0.2 * Bubble::radius, y, Bubble::radius * 2, sf::Color::Black);
    }
};



struct Board {
    sf::RenderWindow& window;
    std::vector<Bubble> bubbles;
    Pincel pincel;
    
    int score { 0 };
    int missing_score { 0 };

    Board(sf::RenderWindow& window) : window(window), pincel(window) {
        bubbles.push_back(Bubble(100, 100, 'A', 1));
        bubbles.push_back(Bubble(200, 100, 'B', 2));
        bubbles.push_back(Bubble(300, 100, 'C', 3));
    }

    void update() {
        if(this->check_new_bubble()) {
            this->add_new_bubble();
        }

        for(auto& bubble : bubbles) {
            bubble.update();
        }

        this->mark_outside_bubbles();
        this->remove_dead_bubbles();

    }
    void remove_dead_bubbles() {
        std::vector<Bubble> vivas;
        
        for(auto& bubble : bubbles) {
            if(bubble.alive) {
                vivas.push_back(bubble);
            }
        }
        
        this->bubbles = vivas;
    }

    void mark_outside_bubbles() {
        for(auto& bubble : bubbles) {
            if(bubble.y + 2 * Bubble::radius > (int) this->window.getSize().y) {
                if(bubble.alive) {
                    bubble.alive = false;
                    this->missing_score ++;
                }
            }
        }
    }

    void mark_score(char letter) {
        for(auto& bubble : bubbles) {
            if(bubble.letter == letter) {
                bubble.alive = false;
                this->score ++;
                break;
            }
        }
    }

    bool check_new_bubble() {
        static const int new_bubble_timeout { 30 };
        static int new_bubble_timer { 0 };

        new_bubble_timer--;
        if(new_bubble_timer <= 0) {
            new_bubble_timer = new_bubble_timeout;
            return true;
        }
        return false;
    }

    void add_new_bubble() {
        int x = rand() % ((int) this->window.getSize().x - 2 * Bubble::radius);
        int y = - 2 * Bubble::radius;
        int speed = rand() % 4 + 1;
        char letter = rand() % 26 + 'A';
        bubbles.push_back(Bubble(x, y, letter, speed));
    }

    void draw() {
        pincel.write("Score: " + std::to_string(this->score) + " : Missings " + std::to_string(this->missing_score), 10, 10, 20, sf::Color::White);
        pincel.write("Size: " + std::to_string(this->bubbles.size()), 10, 30, 20, sf::Color::White);

        for(auto& bubble : bubbles) {
            bubble.draw(window);
        }
    }
};

struct Game {
    sf::RenderWindow window;
    Board board;

    std::function<void()> update_func;

    Game() : window(sf::VideoMode(800, 600), "SFML works!"), board(window)
    {
        this->update_func = [&]() {
            this->gameplay();
        };
        window.setFramerateLimit(60);
    }

    void process_events() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                char code = static_cast<char>(event.text.unicode);
                code = toupper(code);
                board.mark_score(code);
            }
        }
    }
    void gameplay() {
        board.update();
        window.clear(sf::Color::Black);
        board.draw();
        window.display();
        if(board.missing_score > 15) {
            this->update_func = [&]() {
                this->gameover();
            };
        }
    }

    void gameover() {
        static Pincel pincel(window);
        
        window.clear(sf::Color::Black);
        pincel.write("Game Over", 100, 100, 100, sf::Color::White);
        window.display();
    }

    void main_loop() {
        while (window.isOpen()) {
            process_events();
            update_func();
        }
    }
};




int main() {
    Game game;
    game.main_loop();
    return 0;
}