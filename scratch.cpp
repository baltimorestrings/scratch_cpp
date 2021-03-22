#include <unordered_set>
#include <thread>
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <forward_list>
#include <map>
#include <unordered_map>
#include <unistd.h>
#include <list>
using std::cout; using std::endl;
using std::cin; using std::vector;
using std::string;

void die(const char * s) {
    cout << s << endl;
    exit(1);
}
class pre {
    public:
        virtual void speak() { cout << "hey from pre!\n";}
};

class subpre : public pre {
    public:
        void speak() {cout <<"subpre\n"; }
};

struct T {
    int i;
    int j;
};

struct TwoInts {
    int first;
    int second;
    inline bool operator ==(const TwoInts other) { return (first == other.first && second == other.second); }
};
int main(int argc, char **argv) {
    TwoInts a{1,2};
    TwoInts b{1,2};
    if (a == b) {std::cout << "equal!" << std::endl;}


}
