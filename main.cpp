#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <vector>

using namespace std;


//constants
char UP = 'w';
char DOWN = 's';
char LEFT = 'a';
char RIGHT = 'd';


//Board

class Snake;
class GameBoard;
class GameBoard {
public:
    int size;
    vector<vector<int>> board_matrix;
    vector<Snake> snakes;
    GameBoard(int);
    void draw();
    void input();
    void logic();
    void flush();


};
//Snake
class Snake {
public:
    int head_x;
    int head_y;
    int length;
    int speed_x;
    int speed_y;
    Snake(GameBoard);
    vector<vector<int>> tail;
    void move();
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
}


void GameBoard::input() {

}

void GameBoard::logic() {

}

void GameBoard::flush() {
    for (int y = 0; y < this->size; y++) {
        for (int x = 0; x < this->size; x++) {
            if (x == 0  || y == 0 || y == this->size-1 || x == this->size-1) {
                this->board_matrix[x][y] = 5;
            }
        }
    }
}




Snake::Snake(GameBoard board) {
    this->head_x = 1 + rand() % board.size-2;
    this->head_x = 1 + rand() % board.size-2;
    this->speed_x = 1;
    this->speed_y = 0;
    board.snakes.push_back(this);
}


void Snake::move() {
    this->head_x = this->head_x + this->speed_x;
    this->head_y = this->head_y + this->speed_y;
}



int main(int argc, char* argv[]) {
    GameBoard game(20);


    while (true) {
        game.flush();
        game.input();
        game.logic();
        game.draw();
        usleep(20000);
    }



    return 0;
}