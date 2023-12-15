#include <fstream>
#include <iostream>

int main() {
    std::ifstream infile("day13/input");

    std::string line;

    std::vector<std::vector<bool>> board;

    std::vector<int> row, col;

    int sum = 0;
    int xx = 0;

    while (std::getline(infile, line)) {
        if (line == "") {
            xx++;
            row.clear();
            col.clear();

            // old pattern
            int val = 0;
            {
                for (int i = 0; i < board.size(); i++) {
                    int yy = 0;
                    int mul = 1;
                    for (int j = 0; j < board[i].size(); j++) {
                        yy += (board[i][j] * mul);
                        mul *= 2;
                    }
                    row.push_back(yy);
                    // std::cout << yy << " ";
                }
                // std::cout << std::endl;

                for (int i = 0; i < board[0].size(); i++) {
                    int yy = 0;
                    int mul = 1;
                    for (int j = 0; j < board.size(); j++) {
                        yy += (board[j][i] * mul);
                        mul *= 2;
                    }
                    col.push_back(yy);
                    // std::cout << yy << " ";
                }
                // std::cout << std::endl;

                int rrr = 0, ccc = 0;
                for (int i = 0; i < row.size() - 1; i++) {
                    // find dup
                    if (row[i] == row[i + 1]) {
                        bool is_good = true;
                        int cnt = 1;
                        for (int j = 0; i - j >= 0 && i + 1 + j < row.size();
                             j++) {
                            if (row[i - j] != row[i + 1 + j]) {
                                is_good = false;
                                break;
                            }
                        }
                        if (is_good) {
                            rrr = (i + 1);
                            break;
                        }
                    }
                }

                for (int i = 0; i < col.size() - 1; i++) {
                    // find dup
                    if (col[i] == col[i + 1]) {
                        bool is_good = true;
                        int cnt = 1;
                        for (int j = 0; i - j >= 0 && i + 1 + j < col.size();
                             j++) {
                            if (col[i - j] != col[i + 1 + j]) {
                                is_good = false;
                                break;
                            }
                        }
                        if (is_good) {
                            ccc = (i + 1);
                            break;
                        }
                    }
                }

                val = (rrr) * 100 + ccc;
            }

            // std::cout << val << std::endl;

            int nnn = 0;
            for (int iii = 0; iii < board.size(); iii++) {
                for (int jjj = 0; jjj < board[iii].size(); jjj++) {

                    // swap
                    if (board[iii][jjj]) {
                        board[iii][jjj] = false;
                    } else {
                        board[iii][jjj] = true;
                    }

                    // std::cout << iii << " " << jjj << " : " << board[iii][jjj] << std::endl;

                    row.clear();
                    col.clear();

                    for (int i = 0; i < board.size(); i++) {
                        int yy = 0;
                        int mul = 1;
                        for (int j = 0; j < board[i].size(); j++) {
                            yy += (board[i][j] * mul);
                            mul *= 2;
                        }
                        // std::cout << yy << " ";
                        row.push_back(yy);
                    }
                    // std::cout << std::endl;

                    for (int i = 0; i < board[0].size(); i++) {
                        int yy = 0;
                        int mul = 1;
                        for (int j = 0; j < board.size(); j++) {
                            yy += (board[j][i] * mul);
                            mul *= 2;
                        }
                        // std::cout << yy << " ";
                        col.push_back(yy);
                    }
                    // std::cout << std::endl;

                    std::vector<int> rrr, ccc;
                    for (int i = 0; i < row.size() - 1; i++) {
                        // find dup
                        if (row[i] == row[i + 1]) {
                            bool is_good = true;
                            int cnt = 1;
                            for (int j = 0;
                                 i - j >= 0 && i + 1 + j < row.size(); j++) {
                                if (row[i - j] != row[i + 1 + j]) {
                                    is_good = false;
                                    break;
                                }
                            }
                            if (is_good) {
                                rrr.push_back(i + 1);
                            }
                        }
                    }

                    for (int i = 0; i < col.size() - 1; i++) {
                        // find dup
                        if (col[i] == col[i + 1]) {
                            bool is_good = true;
                            int cnt = 1;
                            for (int j = 0;
                                 i - j >= 0 && i + 1 + j < col.size(); j++) {
                                if (col[i - j] != col[i + 1 + j]) {
                                    is_good = false;
                                    break;
                                }
                            }
                            if (is_good) {
                                ccc.push_back(i + 1);
                            }
                        }
                    }

                    // swap
                    if (board[iii][jjj]) {
                        board[iii][jjj] = false;
                    } else {
                        board[iii][jjj] = true;
                    }

                    // std::cout << iii << " " << jjj << " : " << board[iii][jjj] << std::endl;

                    bool is_found = false;
                    for (int rr : rrr) {
                        // std::cout << (rr * 100) << " ";
                        if ((rr * 100) != val && rr > 0) {
                            std::cout << "Board " << xx << std::endl;
                            std::cout << iii << " " << jjj << std::endl;
                            nnn = rr * 100;
                            is_found = true;
                            break;
                        }
                    }

                    for (int cc : ccc) {
                        // std::cout << cc << " ";
                        if (cc != val && cc > 0) {
                            std::cout << "Board " << xx << std::endl;
                            std::cout << iii << " " << jjj << std::endl;
                            nnn = cc;
                            is_found = true;
                            break;
                        }
                    }

                    // std::cout << std::endl;
                    
                    if (is_found) {
                        break;
                    }
                }
                if (nnn > 0 && nnn != val) {
                    break;
                }
            }

            std::cout << nnn << std::endl;

            sum += nnn;
            for (int i = 0; i < board.size(); i++) {
                board[i].clear();
            }
            board.clear();
        } else {
            std::vector<bool> xxxx;
            for (int i = 0; i < line.size(); i++) {
                xxxx.push_back(line[i] == '#');
                // std::cout << (line[i] == '#');
            }
            // std::cout << std::endl;
            board.push_back(xxxx);
        }
    }

    std::cout << sum << std::endl;

    return 0;
}
