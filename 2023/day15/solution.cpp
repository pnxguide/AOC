#include <iostream>
#include <fstream>

int main() {
    std::ifstream infile("day15/input");

    std::vector<std::string> list;

    char line[30000];
    infile >> line;
    char *token = std::strtok(line, ",");
    while (token) {
        std::string tk(token);
        list.push_back(tk);
        token = std::strtok(nullptr, ",");
    }

    std::vector<std::vector<std::pair<std::string, int>>> boxes(256);

    for (std::string str : list) {
        std::string key;

        bool is_add = (str.back() != '-');

        int i = 0, val = -1;
        for (; str[i] != '=' && str[i] != '-'; i++) {
            key.push_back(str[i]);
        }

        int hash = 0;
        for (char ch : key) {
            hash += ch;
            hash *= 17;
            hash %= 256;
        }

        if (is_add) {
            i++;
            std::string val_str;
            for (; i < str.size(); i++) {
                val_str.push_back(str[i]);
            }
            val = std::stoi(val_str);

            bool is_existed = false;
            for (int i = 0; i < boxes[hash].size(); i++) {
                if (boxes[hash][i].first == key) {
                    boxes[hash][i].second = val;
                    is_existed = true;
                    break;
                }
            }
            if (!is_existed) {
                boxes[hash].push_back({key, val});
            }
        } else {
            std::vector<std::pair<std::string, int>> new_box;
            for (int i = 0; i < boxes[hash].size(); i++) {
                if (boxes[hash][i].first != key) {
                    new_box.push_back(boxes[hash][i]);
                }
            }
            boxes[hash] = new_box;
        }
        // std::cout << key << " : " << val << std::endl;
    }

    int sum = 0;
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < boxes[i].size(); j++) {
            std::cout << boxes[i][j].first << ": " << (i+1) << " * " << (j+1) << " * " << boxes[i][j].second << std::endl;
            sum += ((i+1) * (j+1) * boxes[i][j].second);
        }
    }
    std::cout << sum << std::endl;

    return 0;
}