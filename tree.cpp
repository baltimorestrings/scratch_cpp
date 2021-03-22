#include<iostream>
#include<vector>
using std::cout;
using std::cin;
using std::vector;
using std::endl;
using std::string;

struct Node {
    Node *left;
    Node *right;
    int data;
};

void addPaths(const Node &current, vector<int> pathSoFar, vector<vector <int>> &accumulator) {
    pathSoFar.push_back(current.data);
    if (current.left == nullptr && current.right == nullptr) {
        accumulator.push_back(pathSoFar);
    }
    if (current.left != nullptr)
        addPaths(*current.left, pathSoFar, accumulator);
    if (current.right != nullptr)
        addPaths(*current.right, pathSoFar, accumulator);
}

vector<vector <int>> getAllPaths(const Node& head) {
    vector< vector<int>> vPaths;
    vector<int> path{};
    addPaths(head, path, vPaths);
    return vPaths;
}

void test(const Node &i) {
}
int main(int argc, char **argv) {
    Node c1 {nullptr, nullptr, 5};
    Node c2 {nullptr, nullptr, 10};
    Node b {&c1, &c2, 100};
    Node a {nullptr, &b, 3};
    Node z {&a, nullptr, 4};
    Node current{&z, nullptr, 0};
    
    auto paths = getAllPaths(current);
    for (auto path : paths) {
        copy(path.begin(), path.end() - 1, std::ostream_iterator<int>(cout, "->"));
        cout << *(path.end() - 1) << endl;
    }

}
