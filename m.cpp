#include <iostream>
#include <vector>
using namespace std;

void die(const char* msg) {
    cout << msg;
    exit(1);
}

class T{
    private:
        int i;
    public:
        T() { std::cout << "making a T!"; }
        int getI() { return i; }
        void setI(int i) { this->i = i; }
};

int main(int argc, char** argv) {
    // C way of dymamic allocation
    T *a = (T *) malloc(sizeof(T));
    a->setI(5);
    std::cout << a->getI() << std::endl;
    free(a);

    // C++ way 
    T *b = new T;
    b->setI(10);
    std::cout << b->getI() << std::endl;
    free(b);
}
