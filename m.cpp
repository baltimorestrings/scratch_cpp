#include <iostream>

void addTo(std::string* toChange, const char* source) {
    toChange->append(source, strlen(source));
}
int main(int argc, char** argv) {
    return 0;
}
