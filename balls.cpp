#include <vector>
#include <chrono>
#include <thread>
#include <signal.h>
#include <iostream>
#include <curses.h>

void signalCallbackHandler(int signum) {
    endwin();
    std::cout << "Exiting" << std::endl;
    exit(0);
}

struct PositionTuple {
    int x;
    int y;
    inline bool operator==(PositionTuple o) { return (x == o.x && y == o.y); }
};

class Ball {
    private:
        static const char chars[];
        PositionTuple pos;
        int dx, dy;
        char c;
    public:
        Ball(): pos{rand()%100, rand()%100}, dx(rand()%4-2), dy(rand()%4-2) {
            if (dx == 0) dx = 1;
            if (dy == 0) dy = 1;
            c = Ball::chars[rand() % strlen(Ball::chars)];
        }

        Ball(int x, int y, int dx, int dy, char c): pos{x,y}, dx(dx), dy(dy), c(c) {}

        const PositionTuple& getPos() {
            return pos;
        }

        void Move(int width, int height) {
            pos.x += dx;
            pos.y += dy;
            if (pos.x <= 0 || pos.x >= width) {
                dx *= -1;
                pos.x = (pos.x <= 0) ? -pos.x : (width - (pos.x - width));
            }
            if (pos.y <= 0 || pos.y >= height) {
                dy *= -1;
                pos.y = (pos.y <= 0)? -pos.y : (height - (pos.y - height));
            }
        }

        const char& getChar() { return c; }
};
    
const char Ball::chars[] = {'*', 'O', 'o', '.', '$', '@', '#', '+'};

void die(const char *msg) {
    std::cout << msg << std::endl;
    exit(1);
}

int main(int argc, char **argv) {

    PositionTuple pos;
    int iWidth{0};
    int iHeight{0};
    std::vector<std::unique_ptr<Ball>> vBalls;
    int iNumBalls{0};

    if (argc < 2)
        die ("Provide a num of balls");
    try {
        iNumBalls = std::stoi(argv[1]);
    } catch (std::exception const &e) {
        die("Invalid number provided.");
    }
    // init
    srand(time(0));
    signal(SIGINT, signalCallbackHandler);
    for (int i = 0; i < iNumBalls; ++i)
        vBalls.push_back(std::make_unique<Ball>());

    // curses screen init
    initscr();
    curs_set(0);
    refresh();
    cbreak();
    noecho();
    clear();
    getmaxyx(stdscr, iHeight, iWidth);

    while(true) {
        // main loop
        for (auto &b : vBalls) {
            pos = b->getPos();
            mvaddch(pos.y, pos.x, ' ');
            b->Move(iWidth, iHeight);
            pos = b->getPos();
            mvaddch(pos.y, pos.x, b->getChar());
        }
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(75));
    }
}
