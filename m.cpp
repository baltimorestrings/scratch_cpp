#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cctype>
#include <algorithm>
using std::cout; using std::endl;
using std::cin; using std::vector;
using std::string;

typedef vector<string> vecS;

string::size_type findLongestStr(const vector<string>& s) {
    int max = 0;
    for (string::size_type i = 0; i < s.size(); ++i)
        max = s[i].length() > max ? s[i].length() : max;
    return max;
}

vector<string> vcat(const vector<string>& s, const vector<string>& s2) {
    vector<string> ret = s;
    for (vector<string>::const_iterator i = s2.begin(); i != s2.end(); ++i)
        ret.push_back(*i);
    return ret;
}

vector<string> frame(const vector<string>& s) {
    string::size_type width = findLongestStr(s) + 4;
    vector<string> frame;
    frame.push_back(string(width,'*') + "\n");
    for (auto i : s) {
        frame.push_back("* " + i +  string(width - 4- i.length(), ' ') + " *\n" );
    }
    frame.push_back(string(width,'*') + "\n");
    return frame;
}

vecS split(const string& s) {
    int i =0;
    vecS ret;
    string::size_type sLen = s.size();
    while (i <= sLen) {
        while (isspace(s[i]) && ++i <= sLen);
        int j = i;
        while (!isspace(s[j]) && ++j <= sLen);
        if (i < sLen) {
            ret.push_back(s.substr(i, j-i));
            i = j+1;
        }
    }
    return ret;
}

void die(const char * s) {
    cout << s << endl;
    exit(1);
}

int main(int argc, char **argv) {
    std::fstream file;
    string fileLine;
    vector<string> fileLines;
    vector<string> fileLines2;

    if (argc <= 2)
        die("Please supply 2 filenames");
    file.open(argv[1], std::ios::in);
    if (!file.is_open())
        die("Issues opening file");
    while(getline(file,  fileLine))
        fileLines.push_back(fileLine);
    file.close();
    file.open(argv[2], std::ios::in);
    if (!file.is_open())
        die("Issues opening file");
    while(getline(file,  fileLine))
        fileLines2.push_back(fileLine);
    file.close();
    vector<string> f = frame(fileLines);
    vector<string> f2 = frame(fileLines2);
    vector<string> f3 = vcat(f, f2);
    for(vector<string>::const_iterator s = f3.begin(); s != f3.end(); s++)
        cout << *s;
}
