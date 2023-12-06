#include <iostream>
#include <fstream>

int main() {
    // std::ifstream in("day06/input");

    // std::vector<int> t, d;

    // std::string tk;
    // int current_state = 0;
    // while(in >> tk) {
    //     if (tk == "Time:") {
    //         current_state = 1;
    //     } else if (tk == "Distance:") {
    //         current_state = 2;
    //     } else {
    //         int x;
    //         x = std::stoi(tk);
    //         if (current_state == 1) {
    //             t.push_back(x);
    //         } else if (current_state == 2) {
    //             d.push_back(x);
    //         }
    //     }
    // }

    // int cnt = t.size();
    // long mul = 1;
    // for (int i = 0; i < cnt; i++) {
    //     int c = 0;
    //     for (int j = 1; j <= t[i]; j++) {
    //         int dist = (t[i] - j) * j;
    //         if (dist > d[i]) {
    //             c++;
    //         }
    //     }
    //     std::cout << c << std::endl;
    //     mul *= c;
    // }

    // std::cout << mul << std::endl;

    long t = 63789468;
    long d = 411127420471035;

    // long t = 71530;
    // long d = 940200;

    long c = 0;
    bool increasing = true;
    for (int j = 1; j <= t; j++) {
        long dist = (t - j) * j;
        if (dist > d) {
            c++;
            increasing = false;
        } else if (!increasing) {
            break;
        }
    }
    std::cout << c << std::endl;

    return 0;
}