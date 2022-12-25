#include <algorithm>
#include <cassert>
#include <deque>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

void tokenize(const std::string &s, const char delim, std::vector<std::string> &out) {
    std::string::size_type beg = 0;
    for (auto end = 0; (end = s.find(delim, end)) != std::string::npos; ++end) {
        out.push_back(s.substr(beg, end - beg));
        beg = end + 1;
    }

    out.push_back(s.substr(beg));
}

void solve_A() {
    // Read an input file
    std::ifstream input_file("day24/input.txt");
    std::string line;
}

void solve_B() {
    // Read an input file
    std::ifstream input_file("day24/input.txt");
    std::string line;
}

int main() {
    solve_A();
    // solve_B();
    return 0;
}