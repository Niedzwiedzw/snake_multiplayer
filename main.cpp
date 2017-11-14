#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <deque>
#include <ctime>
#include <ncurses.h>

using namespace std;





//constants
char UP = 'w';
char DOWN = 's';
char LEFT = 'a';
char RIGHT = 'd';
int TICK = 200000;


//Board
class Snake;
class GameBoard;
class Apple;
class GameBoard {
public:
    int size;
    vector<vector<int>> board_matrix;
    vector<Snake*> snakes;
    vector<Apple*> apples;

    GameBoard(int);
    void draw();
    void input();
    void logic();
    void flush();

    void spawn_snake();
    void spawn_apple();
    vector<int> random_free_pos();
};


//Snake
class Snake {
public:
    int head_x;
    int head_y;
    int length;
    int speed_x;
    int speed_y;
    Snake(GameBoard*);
    deque<vector<int>> tail;
    void move();
};


class Apple {
public:
    int pos_x;
    int pos_y;
    GameBoard* game;
    Apple(GameBoard*);
};

GameBoard::GameBoard(int size) {
    this->size = size;
    for (int x = 0; x < this->size; x++) {
        vector<int> row;
        for (int y = 0; y < this->size; y++) {
            row.push_back(0);
        }
        this->board_matrix.push_back(row);
    }
}



void GameBoard::draw() {
    system("clear");
    char print_buffor;
    for (vector<int> row: this->board_matrix) {
        for (int cell: row) {
            switch (cell) {
                case 5:
                    print_buffor = '#';
                    break;
                case 1:
                    print_buffor = 'X';
                    break;
                case 4:
                    print_buffor = '@';
                    break;
                default: print_buffor = ' ';
            }
            cout << print_buffor << " ";
        }
        cout << endl;
    }
    cout << "\n\nsnake position: \nx: " << this->snakes[0]->head_x << " y:"<< this->snakes[0]->head_y;
    cout << "\nilosc graczy: " << this->snakes.size() << endl;
}


void GameBoard::spawn_snake() {
    this->snakes.push_back(new Snake(this));
}

void GameBoard::spawn_apple() {
    this->apples.push_back(new Apple(this));
}


void GameBoard::input() {
    if (getch()=='w'){
        cout << "W";
    }

}

void GameBoard::logic() {
    for (Snake* snake: this->snakes) {
        snake->move();
    }

}


void GameBoard::flush() {
    for (int y = 0; y < this->size; y++) {
        for (int x = 0; x < this->size; x++) {
            if (x == 0  || y == 0 || y == this->size-1 || x == this->size-1) {
                this->board_matrix[x][y] = 5;
            } else {
                this->board_matrix[x][y] = 0;
            }
        }
    }
    for (Snake* snake: this->snakes) {
        for (vector<int> block: snake->tail) {
            this->board_matrix[block[0]][block[1]] = 1;
        }
    }

    for (Apple* apple: this->apples) {
        this->board_matrix[apple->pos_x][apple->pos_y] = 4;
    }
}


Snake::Snake(GameBoard* board) {
    srand( (unsigned int)time(nullptr) );
    vector<int> free_pos = board->random_free_pos();
    this->head_x = free_pos[0];
    this->head_y = 1 + free_pos[1];
    this->speed_x = 1;
    this->speed_y = 0;
    this->length = 1;
}




void Snake::move() {
    this->head_x = this->head_x + this->speed_x;
    this->head_y = this->head_y + this->speed_y;
    vector<int> head;

    head.push_back(this->head_x);
    head.push_back(this->head_y);
    this->tail.push_front(head);
    if (this->tail.size() > this->length) {
        this->tail.pop_back();
    }
}

Apple::Apple(GameBoard* game) {
    this->game = game;
    vector<int> free_pos = game->random_free_pos();
    this->pos_x = free_pos[0];
    this->pos_y = free_pos[1];
}

vector<int> GameBoard::random_free_pos() {
    while (true) {
        srand( (unsigned int)time(nullptr) );

        int pos_x = 1 + (rand() % (this->size-2));
        int pos_y = 1 + (rand() % (this->size-2));

        vector<int> free_pos;
        free_pos.push_back(pos_x);
        free_pos.push_back(pos_y);

        return free_pos;
    }
}



int main(int argc, char* argv[]) {
    GameBoard game(20);
    game.spawn_snake();
    game.spawn_apple();


    while (true) {
        game.flush();
        game.input();
        game.logic();
        game.draw();
        usleep(TICK);
    }

    return 0;
}