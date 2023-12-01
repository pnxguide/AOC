#include <iostream>
#include <fstream>
#include <deque>

int main() {
    std::ifstream input("day01/input.txt");

    long sum = 0;

    // Part 1
    // std::string line;
    // while (std::getline(input, line)) {
    //     int first = -1, last = -1;
    //     for (int i = 0; i < line.size(); i++) {
    //         if (line[i] >= '0' & line[i] <= '9') {
    //             if (first == -1) {
    //                 first = line[i] - '0';
    //                 last = line[i] - '0';
    //             } else {
    //                 last = line[i] - '0';
    //             }
    //         }
    //     }
    //     sum += (first * 10) + last;
    // }

    // Part 2
    std::vector<std::string> nums = {
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine"
    };

    int first = 0, last = 0;

    std::string ll;
    while (std::getline(input, ll)) {
        for (int i = 0; i < ll.size(); i++) {
            int kk = 1;
            for (std::string num : nums) {
                bool match = true;
                for (int j = 0; j < num.size(); j++) {
                    if (i+j >= ll.size()) {
                        match = false;
                        break;
                    }
                    if (ll[i+j] != num[j]) {
                        match = false;
                    }
                }
                if (match) {
                    first = kk;
                    break;
                }
                kk++;
            }

            if (kk == 10) {
                if (ll[i] >= '0' & ll[i] <= '9') {
                    first = ll[i] - '0';
                    break;
                }
            } else {
                break;
            }
        }

        for (int i = ll.size() - 1; i >= 0; i--) {
            int kk = 1;
            for (std::string num : nums) {
                bool match = true;
                for (int j = num.size() - 1; j >= 0; j--) {
                    if (i+j >= ll.size()) {
                        match = false;
                        break;
                    }
                    if (ll[i+j] != num[j]) {
                        match = false;
                    }
                }
                if (match) {
                    last = kk;
                    break;
                }
                kk++;
            }

            if (kk == 10) {
                if (ll[i] >= '0' & ll[i] <= '9') {
                    last = ll[i] - '0';
                    break;
                }
            } else {
                break;
            }
        }

        std::cout << (first * 10) + last << std::endl;
        sum += (first * 10) + last;
    }

    std::cout << sum << std::endl;

    return 0;
}