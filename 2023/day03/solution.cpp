#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

bool is_number(char x) {
    return x >= '0' && x <= '9';
}

int main() {
    std::ifstream input_file("day03/input.txt");

    std::vector<std::string> a;

    // input
    std::string cur_line;
    while (std::getline(input_file, cur_line)) {
        a.push_back("." + cur_line + ".");
    }

    std::vector<std::string> aa;
    std::string xxxx;
    for (int i = 0; i < a[1].size(); i++) {
        xxxx.push_back('.');
    }
    aa.push_back(xxxx);
    for (std::string aaa : a) {
        aa.push_back(aaa);
    }
    aa.push_back(xxxx);
    a = aa;

    long sum = 0;

    // // process
    // for (int i = 0; i < a.size(); i++) {
    //     for (int j = 0; j < a[i].size(); j++) {
    //         // scan for number
    //         if (a[i][j] >= '0' && a[i][j] <= '9') {
    //             // std::cout << a[i][j] << " " << std::endl;

    //             // this must be the most-significant digit
    //             // scan for all the digits
    //             bool is_good = true;
    //             std::string token;
    //             // if digit starts
    //             while (a[i][j] >= '0' && a[i][j] <= '9') {
    //                 // check if there's any symbol around

    //                 // if first digit
    //                 // check left
    //                 if (j-1 >= 0) {
    //                     if (!(a[i][j-1] >= '0' && a[i][j-1] <= '9')) {
    //                         // std::cout << a[i][j-1];
    //                         is_good &= (a[i][j-1] == '.');

    //                         if (i-1 >= 0 && j-1 >= 0) {
    //                             // std::cout << a[i-1][j-1];
    //                             is_good &= (a[i-1][j-1] == '.');
    //                         }

    //                         if (i+1 < a[i].size() && j-1 >= 0) {
    //                             // std::cout << a[i+1][j-1];
    //                             is_good &= (a[i+1][j-1] == '.');
    //                         }
    //                     }
    //                 }
                    
    //                 // check up and down
    //                 // if (i-1 >= 0 && j-1 >= 0) {
    //                 //     std::cout << a[i-1][j-1];
    //                 //     is_good &= (a[i-1][j-1] == '.');
    //                 // }

    //                 // if (i-1 >= 0 && j+1 < a[i].size()) {
    //                 //     std::cout << a[i-1][j+1];
    //                 //     is_good &= (a[i-1][j+1] == '.');
    //                 // }

    //                 if (i-1 >= 0) {
    //                     // std::cout << a[i-1][j];
    //                     is_good &= (a[i-1][j] == '.');
    //                 }

    //                 if (i+1 < a[i].size()) {
    //                     // std::cout << a[i+1][j];
    //                     is_good &= (a[i+1][j] == '.');
    //                 }
                    
    //                 // if (i+1 < a[i].size() && j-1 >= 0) {
    //                 //     std::cout << a[i+1][j-1];
    //                 //     is_good &= (a[i+1][j-1] == '.');
    //                 // }

    //                 // if (i+1 < a[i].size() && j+1 < a[i].size()) {
    //                 //     std::cout << a[i+1][j+1];
    //                 //     is_good &= (a[i+1][j+1] == '.');
    //                 // }
                    
    //                 // if last
    //                 // check right
    //                 if (j+1 < a[i].size()) {
    //                     if (!(a[i][j+1] >= '0' && a[i][j+1] <= '9')) {
    //                         // std::cout << a[i][j+1];
    //                         is_good &= (a[i][j+1] == '.');
    //                     }

    //                     if (i-1 >= 0 && j+1 < a[i].size()) {
    //                         // std::cout << a[i-1][j+1];
    //                         is_good &= (a[i-1][j+1] == '.');
    //                     }

    //                     if (i+1 < a[i].size() && j+1 < a[i].size()) {
    //                         // std::cout << a[i+1][j+1];
    //                         is_good &= (a[i+1][j+1] == '.');
    //                     }
    //                 }

    //                 // std::cout << std::endl;
                    
    //                 token.push_back(a[i][j]);
                    
    //                 // move to next digit
    //                 j++;
    //             }

    //             // std::cout << token << std::endl;

    //             if (!is_good) {
    //                 sum += std::stoi(token);
    //                 // std::cout << token << std::endl;
    //             }
    //         }
    //     }
    // }

    // process
    for (int i = 1; i < a.size() - 1; i++) {
        for (int j = 1; j < a[i].size() - 1; j++) {
            std::vector<std::string> t;

            // scan for gear
            if (a[i][j] == '*') {
                // search for adjacent numbers
                // there could be 8 cases of number
                // either up-left/up-right or up
                // left/right
                // either down-left/down-right or down

                // scan top
                if (is_number(a[i-1][j-1]) || is_number(a[i-1][j]) || is_number(a[i-1][j+1])) {
                    std::deque<char> x;
                    x.push_back(a[i-1][j]);

                    // check left
                    int p = j-1;
                    while (p > 0 && is_number(a[i-1][p])) {
                        x.push_front(a[i-1][p]);
                        p--;
                    }

                    // check right
                    p = j+1;
                    while (p <= a[i].size() && is_number(a[i-1][p])) {
                        x.push_back(a[i-1][p]);
                        p++;
                    }

                    std::string yy = "";
                    // put to list (split if needed)
                    for (char xxx : x) {
                        if (!is_number(xxx)) {
                            if (yy != "") t.push_back(yy);
                            yy = "";
                        } else {
                            yy.push_back(xxx);
                        }
                    }
                    if (yy != "") t.push_back(yy);
                }

                // scan middle
                if (is_number(a[i][j-1]) || is_number(a[i][j]) || is_number(a[i][j+1])) {
                    std::deque<char> x;
                    x.push_back(a[i][j]);

                    // check left
                    int p = j-1;
                    while (p > 0 && is_number(a[i][p])) {
                        x.push_front(a[i][p]);
                        p--;
                    }

                    // check right
                    p = j+1;
                    while (p <= a[i].size() && is_number(a[i][p])) {
                        x.push_back(a[i][p]);
                        p++;
                    }

                    std::string yy = "";
                    // put to list (split if needed)
                    for (char xxx : x) {
                        if (!is_number(xxx)) {
                            if (yy != "") t.push_back(yy);
                            yy = "";
                        } else {
                            yy.push_back(xxx);
                        }
                    }
                    if (yy != "") t.push_back(yy);
                }

                // scan bottom
                if (is_number(a[i+1][j-1]) || is_number(a[i+1][j]) || is_number(a[i+1][j+1])) {
                    std::deque<char> x;
                    x.push_back(a[i+1][j]);

                    // check left
                    int p = j-1;
                    while (p > 0 && is_number(a[i+1][p])) {
                        x.push_front(a[i+1][p]);
                        p--;
                    }

                    // check right
                    p = j+1;
                    while (p <= a[i].size() && is_number(a[i+1][p])) {
                        x.push_back(a[i+1][p]);
                        p++;
                    }

                    std::string yy = "";
                    // put to list (split if needed)
                    for (char xxx : x) {
                        if (!is_number(xxx)) {
                            if (yy != "") t.push_back(yy);
                            yy = "";
                        } else {
                            yy.push_back(xxx);
                        }
                    }
                    if (yy != "") t.push_back(yy);
                }

                // if (t.size() == 2) {
                //     sum += (std::stoi(t[0]) * std::stoi(t[1]));
                // }
                // std::cout << t.size() << std::endl;

                if (t.size() == 2) {
                    // std::cout << t[0] << " " << t[1] << std::endl;
                    sum += (std::stoi(t[0]) * std::stoi(t[1]));
                }

                // for (std::string xxxxx : t) {
                //     std::cout << xxxxx << std::endl;
                // } 
            }
        }
    }

    std::cout << sum << std::endl;

    return 0;
}