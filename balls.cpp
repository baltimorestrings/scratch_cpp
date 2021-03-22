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

struct TupleInts {
    int first;
    int second;
    inline bool operator==(TupleInts o) { return (first == o.first && second == o.second); }
};

class Ball {
    private:
        int x, y, dx, dy;
    public:
        Ball(): x(rand()%100), y(rand()%100), dx(rand()%4-2), dy(rand()%4-2) {
            if (dx == 0) dx = 1;
            if (dy == 0) dy = 1;
        }

        Ball(int x, int y, int dx, int dy): x(x), y(y), dx(dx), dy(dy) {}

        TupleInts getPos() {
            return TupleInts{x, y};
        }

        void Move(int width, int height) {
            x += dx;
            y += dy;
            if (x <= 0 || x >= width) {
                dx *= -1;
                x = (x <= 0) ? -x : (width - (x - width));
            }
            if (y <= 0 || y >= height) {
                dy *= -1;
                y = (y <= 0)? -y : (height - (y - height));
            }
        }
};
    

void die(const char *msg) {
    std::cout << msg << std::endl;
    exit(1);
}

int main(int argc, char **argv) {

    TupleInts pos;
    int iWidth{0};
    int iHeight{0};
    std::vector<std::unique_ptr<Ball>> vBalls;
    int iNumBalls{0};

    if (argc < 2)
        die ("Provide a num of balls");
    try {
        iNumBalls = std::atoi(argv[1]);
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
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
            mvaddch(pos.second, pos.first, ' ');
            b->Move(iWidth, iHeight);
            pos = b->getPos();
            mvaddch(pos.second, pos.first, 'O');
        }
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(75));
    }
}
