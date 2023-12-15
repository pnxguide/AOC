#include <iostream>
#include <fstream>

int main() {
    std::ifstream infile("day14/input");

    std::vector<std::string> board;

    std::string line;
    while (std::getline(infile, line)) {
        board.push_back(line);
    }

    std::vector<std::vector<std::vector<std::string>>> board_group;
    
    int f = 0;
    for (int iter = 0; iter < 1000000000; iter += 4) {
        std::vector<std::vector<std::string>> boards;

        // up
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                // push up until hit
                if (board[i][j] == 'O') {
                    for (int k = i; k > 0; k--) {
                        if (board[k - 1][j] == '.') {
                            board[k - 1][j] = 'O';
                            board[k][j] = '.';
                        } else {
                            break;
                        }
                    }
                }
            }
        }
        boards.push_back(board);

        // left
        for (int j = 0; j < board[0].size(); j++) {
            for (int i = 0; i < board.size(); i++) {
                // push up until hit
                if (board[i][j] == 'O') {
                    for (int k = j; k > 0; k--) {
                        if (board[i][k - 1] == '.') {
                            board[i][k - 1] = 'O';
                            board[i][k] = '.';
                        } else {
                            break;
                        }
                    }
                }
            }
        }
        boards.push_back(board);

        // down
        for (int i = (board.size() - 1); i >= 0; i--) {
            for (int j = 0; j < board[i].size(); j++) {
                // push up until hit
                if (board[i][j] == 'O') {
                    for (int k = i; k < (board.size() - 1); k++) {
                        if (board[k + 1][j] == '.') {
                            board[k + 1][j] = 'O';
                            board[k][j] = '.';
                        } else {
                            break;
                        }
                    }
                }
            }
        }
        boards.push_back(board);

        // right
        for (int j = (board[0].size() - 1); j >= 0; j--) {
            for (int i = 0; i < board.size(); i++) {
                // push up until hit
                if (board[i][j] == 'O') {
                    for (int k = j; k < (board[i].size() - 1); k++) {
                        if (board[i][k + 1] == '.') {
                            board[i][k + 1] = 'O';
                            board[i][k] = '.';
                        } else {
                            break;
                        }
                    }
                }
            }
        }
        boards.push_back(board);
        
        // if the same as the previous
        // that is the loop start
        bool is_loop = false;
        for (int i = 0; i < board_group.size(); i++) {
            bool is_same = true;
            for (int j = 0; j < board_group[i].size(); j++) {
                for (int k = 0; k < board_group[i][j].size(); k++) {
                    if (boards[j][k] != board_group[i][j][k]) {
                        is_same = false;
                        break;
                    }
                }
                if (!is_same) {
                    break;
                }
            }
            if (is_same) {
                std::cout << i << " & " << board_group.size() << std::endl;
                int head = i;
                int tail = board_group.size();
                int iter_size = tail - head;
                f = i + ((1000000000 - 1 - i) % (iter_size));
                is_loop = true;
                break;
            }
        }

        board_group.push_back(boards);

        if (is_loop) {
            break;
        }
    }

    std::cout << f << std::endl;
    std::vector<std::string> final = board_group[f].back();

    int score = 0;
    for (int i = 0; i < final.size(); i++) {
        for (int j = 0; j < final[i].size(); j++) {
            if (final[i][j] == 'O') {
                score += (final.size() - i);
            }
        }
    }

    for (int i = 0; i < final.size(); i++) {
        std::cout << final[i] << std::endl;
    }

    std::cout << score << std::endl;

    return 0;
}