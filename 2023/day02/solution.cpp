#include <iostream>
#include <fstream>

int main() {
    std::ifstream input("day02/input.txt");

    std::string line;
    long sum = 0;
    int current_game = 1;
    while (std::getline(input, line)) {
        std::cout << line << std::endl;

        int i = 0;

        // skip till :
        while (line[i] != ':') {
            i++;
        }

        // state
        // 0 - space
        // 1 - num
        // 2 - space
        // 3 - type
        int state = 0;

        std::string num_str;
        std::string type;

        int sub_game = 0;
        int red = 0;
        int green = 0;
        int blue = 0;

        bool is_playable = true;

        for (; i < line.size() && is_playable; i++) {
            // find space
            if (state == 0 && line[i] == ' ') {
                state = 1;
            }

            else if (state == 1) {
                if (line[i] == ' ') {
                    state = 3;
                } else {
                    num_str.push_back(line[i]);
                }
            }

            else if (state == 3) {
                if (i >= line.size() || line[i] == ';') {
                    // TODO: eval
                    if (type == "red") {
                        red = std::max(red, std::stoi(num_str));
                    } else if (type == "green") {
                        green = std::max(green, std::stoi(num_str));
                    } else if (type == "blue") {
                        blue = std::max(blue, std::stoi(num_str));
                    }
                    std::cout << type << " = " << num_str << std::endl;
                    num_str = "";
                    type = "";
                    state = 0;

                    std::cout << red << " " << green << " " << blue << std::endl;

                    // if (red > 12 || green > 13 || blue > 14) {
                    //     is_playable = false;
                    // }

                    sub_game++;
                    // red = green = blue = 0;
                } else if (line[i] == ',') {
                    if (type == "red") {
                        red = std::max(red, std::stoi(num_str));
                    } else if (type == "green") {
                        green = std::max(green, std::stoi(num_str));
                    } else if (type == "blue") {
                        blue = std::max(blue, std::stoi(num_str));
                    }
                    // std::cout << type << " += " << num_str << std::endl;
                    num_str = "";
                    type = "";
                    state = 0;
                } else {
                    type.push_back(line[i]);
                }
            }
        }

        // final eval
        if (type == "red") {
            red = std::max(red, std::stoi(num_str));
        } else if (type == "green") {
            green = std::max(green, std::stoi(num_str));
        } else if (type == "blue") {
            blue = std::max(blue, std::stoi(num_str));
        }
        std::cout << type << " = " << num_str << std::endl;
        num_str = "";
        type = "";
        state = 0;

        std::cout << red << " " << green << " " << blue << std::endl;

        // if (red > 12 || green > 13 || blue > 14) {
        //     is_playable = false;
        // }

        std::cout << red * green * blue << std::endl;

        sum += (red * green * blue);

        sub_game++;
        red = green = blue = 0;

        // if (is_playable) {
        //     // std::cout << "Game " << current_game << std::endl;
        //     sum += current_game;
        // }

        current_game++;
    }

    std::cout << sum << std::endl;

    return 0;
}