#include <iostream>
#include <string>

using namespace std;
class GameWindow {
public:
    int width;
    int height;
    GameWindow(int, int);
};

GameWindow::GameWindow(int width, int height) {
    this->width = width;
    this->height = height;
}



int main() {
    GameWindow game(500, 500);

    cout << game.height << game.width;


    return 0;
}