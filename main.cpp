#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;
class GameBoard {
public:
    int width;
    int height;
    GameBoard(int, int);
    void draw();
    void input();


};

GameBoard::GameBoard(int width, int height) {
    this->width = width;
    this->height = height;
}

void GameBoard::draw() {
    system("clear");
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            cout << "# ";
        }
        cout << endl;
    }

}


void GameBoard::input() {

}





int main(int argc, char* argv[]) {
    GameBoard game(20, 20);
    while (true) {
        game.draw();

    }


    return 0;
}