
#include <iostream>
#include <unistd.h>
#include <vector>
#include <deque>
#include <ncurses.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <thread>

using namespace std;




//constants
constexpr int UP = 65;
constexpr int DOWN = 66;
constexpr int LEFT = 68;
constexpr int RIGHT = 67;

int TICK = 200000;

// Returns true on success, or false if there was an error
//bool setSocketBlockingEnabled(int fd, bool blocking) {
//    int flags = fcntl(fd, F_GETFL, 0);
//    if (flags < 0) return false;
//    flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
//    return fcntl(fd, F_SETFL, flags) == 0;
//
//}
int kbhit() {
    cbreak();
    noecho();
    nodelay(stdscr, true);
    scrollok(stdscr, false);
    int ch = getch();
    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

//Board
class Snake;
class GameBoard;
class Apple;
class Server {
public:
    Server(GameBoard*);
    GameBoard* gameBoard;
    void keepConnection();
    char str;
    int listen_fd;
    int comm_fd;
    struct sockaddr_in servaddr;
};

Server::Server(GameBoard* game) {
    this->gameBoard = game;
    this->listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    bzero( &this->servaddr, sizeof(this->servaddr));

    this->servaddr.sin_family = AF_INET;
    this->servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    this->servaddr.sin_port = htons(22000);

    bind(this->listen_fd, (struct sockaddr *) &this->servaddr, sizeof(this->servaddr));

    listen(this->listen_fd, 10);

    this->comm_fd = accept(this->listen_fd, (struct sockaddr*) nullptr, nullptr);
}

void Server::keepConnection() {
    cbreak();
    noecho();
    nodelay(stdscr, true);
    scrollok(stdscr, false);
    while (true) {
        read(this->comm_fd, &this->str, 1);
        if (this->str != '0') {
            addch(this->str);
            write(this->comm_fd, &this->str, 1);
            this->str = '0';
            refresh();
        }
    }
}

class Client {
public:
    Client(GameBoard*);
    GameBoard* game;
    void keepConnection();
    int sockfd;
    int n;
    char sendline;
    char recvline;
    struct sockaddr_in servaddr;
};

Client::Client(GameBoard* game) {
    this->sockfd=socket(AF_INET,SOCK_STREAM,0);
//    setSocketBlockingEnabled(this->sockfd, false);
    bzero(&this->servaddr,sizeof this->servaddr);

    this->servaddr.sin_family=AF_INET;
    this->servaddr.sin_port=htons(22000);

    inet_pton(AF_INET,"127.0.0.1",&(this->servaddr.sin_addr));

    connect(this->sockfd,(struct sockaddr *)&this->servaddr,sizeof(this->servaddr));
}

void Client::keepConnection() {
    cbreak();
    noecho();
    nodelay(stdscr, true);
    scrollok(stdscr, false);
    this->sendline = '0';
    while(true) {

        if (kbhit()) {
            if (getch() == 27) {

                printw("YEAAAH");
                getch();
                switch(getch()) {
                    case UP:
                        printw("YEAAAH DO GOOORYYYYY");
                        this->sendline = 'u';
                        break;
                    case DOWN:

                        printw("YEAAAH DO NA DOOLL");

                        this->sendline = 'd';
                        break;

                    case LEFT:

                        printw("YEAAAH DO LEWEGO");

                        this->sendline = 'l';
                        break;

                    case RIGHT:

                        printw("YEAAAH DO PRAWEGOO");

                        this->sendline = 'r';
                        break;
                }
            }
        }
        if (this->sendline != '0') {
            write(this->sockfd, &this->sendline, 1);
            read(this->sockfd, &this->recvline, 1);
            if (this->sendline == this->recvline) {
                this->sendline = '0';
                printw(&this->recvline);
                this->recvline = '0';

                refresh();
            }
        }
    }
}

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
    int head_y;
    int head_x;
    int length;
    int speed_x;
    int speed_y;
    int _board_size;
    Snake(GameBoard*);
    deque<vector<int>> tail;
    void move();
    vector<int> nextStep();
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
    clear();
    cbreak();
    noecho();
    nodelay(stdscr, true);
    scrollok(stdscr, false);
    string print_buffor;
    for (vector<int> row: this->board_matrix) {
        for (int cell: row) {
            switch (cell) {
                case 5:
                    print_buffor = "#";
                    break;
                case 1:
                    print_buffor = "X";
                    break;
                case 4:
                    print_buffor = "@";
                    break;
                default: print_buffor = " ";
            }
//            cout << print_buffor << " ";
            printw(print_buffor.c_str());
            printw(" ");

            refresh();
        }
//        cout << endl;
//        char newline = '\n';
        printw("\n");
        refresh();
    }
//    cout << "\n\nsnake position: \nx: " << this->snakes[0]->head_y << " y:"<< this->snakes[0]->head_x;
//    cout << "\nilosc graczy: " << this->snakes.size() << endl;
}


void GameBoard::spawn_snake() {
    this->snakes.push_back(new Snake(this));
}

void GameBoard::spawn_apple() {
    if(!this->apples.empty()) {
        this->apples.pop_back();
    }
    this->apples.push_back(new Apple(this));
}

void GameBoard::input() {


    cbreak();
    noecho();
    nodelay(stdscr, true);
    scrollok(stdscr, false);
    if (kbhit()) {
        if (getch() == 27) {
            getch();
            switch(getch()) {
                case UP:
                    if (this->snakes[0]->speed_y != 1) {
                        this->snakes[0]->speed_x = 0;
                        this->snakes[0]->speed_y = -1;
                    }
                    break;
                case DOWN:
                    if (this->snakes[0]->speed_y != -1) {
                        this->snakes[0]->speed_x = 0;
                        this->snakes[0]->speed_y = 1;
                    }
                    break;

                case LEFT:
                    if (this->snakes[0]->speed_x != 1) {
                        this->snakes[0]->speed_x = -1;
                        this->snakes[0]->speed_y = 0;
                    }
                    break;

                case RIGHT:
                    if (this->snakes[0]->speed_x != -1) {
                        this->snakes[0]->speed_x = 1;
                        this->snakes[0]->speed_y = 0;
                    }
                    break;
            }
        }
        printw(""+(char)getch());
//        cout << getch();
        refresh();
    } else {
        refresh();
    }
}




void GameBoard::logic() {
    for (Snake* snake: this->snakes) {
        snake->move();

        if (snake->head_y == this->apples[0]->pos_x && snake->head_x == this->apples[0]->pos_y){
            snake->length++;
            this->spawn_apple();
        }
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
    this->head_y = free_pos[0];
    this->head_x = free_pos[1];
    this->speed_x = 1;
    this->speed_y = 0;
    this->length = 1;
    this->_board_size = board->size;
}


vector<int> Snake::nextStep() {
    vector<int> next_step;
    next_step.push_back(this->head_y+this->speed_x);
    next_step.push_back(this->head_x+this->speed_y);

    int size = this->_board_size;
    if (next_step[0] > size-2) {
        next_step[0] = 1;
    }
    if (next_step[0] < 1) {
        next_step[0] = size-2;
    }
    if (next_step[1] > size-2) {
        next_step[1] = 1;
    }
    if (next_step[1] < 1) {
        next_step[1] = size-2;
    }
    return next_step;
}


void Snake::move() {
    this->head_y = this->nextStep()[0];
    this->head_x = this->nextStep()[1];
    vector<int> head;

    head.push_back(this->head_y);
    head.push_back(this->head_x);
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
    int gamemode = -1;

    while (true) {
        cout << "Wybierz tryb rozgrywki\n\n\n1 - serwer\n2 - klient\n\n >> ";
        cin >> gamemode;
        if (gamemode != 1 && gamemode != 2) {
            cout << "Niepoprawny wybor...\n\n";
        } else {
            break;
        }
    }

    initscr();

    GameBoard game(20);
//    game.spawn_snake();
//    game.spawn_apple();

    if (gamemode == 1) {
        Server server(&game);
        thread serverThread(&Server::keepConnection, server);
        serverThread.join();

    } else {
        Client client(&game);
        thread clientThread (&Client::keepConnection, client);
        clientThread.join();
    }

//    while (true) {
//        game.flush();
//        game.input();
//        game.logic();
//        game.draw();
//        usleep(TICK);
//    }


    return 0;
}