#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream input_file("day04/input");

    std::string line;
    
    int card = 0;
    int state = 1;
    int cur_cnt = 0;

    int sum = 0;

    std::vector<int> winning;
    std::vector<int> wins(189);
    
    while (input_file >> line) {
        if (state == 1 && line == "Card") {
            wins[card] = cur_cnt;

            input_file >> line;
            line.pop_back();
            card = std::stoi(line);

            // if (cur_cnt > 0) {
            //     sum += std::pow(2, cur_cnt - 1);
            // }

            

            state = 0;
            cur_cnt = 0;
            winning.clear();
        } else {
            if (state == 0) {
                if (line == "|") {
                    state = 1;
                } else {
                    int key = std::stoi(line);
                    winning.push_back(key);
                }
            } else if (state == 1) {
                int val = std::stoi(line);
                if (std::find(winning.begin(), winning.end(), val) != winning.end()) {
                    cur_cnt++;
                }
            }
        }
    }

    std::vector<int> cnt(189);
    for (int i = 1; i <= card; i++) {
        cnt[i] += 1;
        for (int j = 0; j < wins[i]; j++) {
            if ((i+1+j) > card) {
                break;
            }
            cnt[i+1+j] += cnt[i];
        }
        sum += cnt[i];
    }

    // for (int i : cnt) {
    //     std::cout << i << " ";
    // }
    // std::cout << std::endl;

    std::cout << sum << std::endl;

    return 0;
}