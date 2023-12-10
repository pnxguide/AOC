#include <iostream>
#include <fstream>
#include <deque>

// int main() {
//     std::ifstream infile("day10/input");

//     int size = 140;

//     std::vector<std::string> g;
//     std::string line;
//     for (int i = 0; i < size + 2; i++) {
//         line.push_back('.');
//     }
//     g.push_back(line);

//     line.clear();
//     while (std::getline(infile, line)) {
//         g.push_back("." + line + ".");
//     }

//     line.clear();
//     for (int i = 0; i < size + 2; i++) {
//         line.push_back('.');
//     }
//     g.push_back(line);

//     // construct graph
//     std::vector<std::vector<int>> adj(size * size);
//     int start = 0;

//     for (int i = 1; i <= size; i++) {
//         for (int j = 1; j <= size; j++) {
//             if (g[i-1][j-1] == '.') {
//                 continue;
//             }

//             int id = ((i - 1) * size) + (j - 1);

//             int ul = id - size - 1;
//             int uc = id - size;
//             int ur = id - size + 1;

//             int ll = id - 1;
//             int rr = id + 1;

//             int bl = id + size - 1;
//             int bc = id + size;
//             int br = id + size + 1;

//             switch (g[i-1][j-1]) {
//                 case '|': {
//                     adj[id].push_back(uc);
//                     adj[id].push_back(bc);
//                     break;
//                 }
//                 case '-': {
//                     adj[id].push_back(ll);
//                     adj[id].push_back(rr);
//                     break;
//                 }
//                 case 'L': {
//                     adj[id].push_back(uc);
//                     adj[id].push_back(rr);
//                     break;
//                 }
//                 case 'J': {
//                     adj[id].push_back(uc);
//                     adj[id].push_back(ll);
//                     break;
//                 }
//                 case '7': {
//                     adj[id].push_back(bc);
//                     adj[id].push_back(ll);
//                     break;
//                 }
//                 case 'F': {
//                     adj[id].push_back(bc);
//                     adj[id].push_back(rr);
//                     break;
//                 }
//                 case 'S': {
//                     start = id;

//                     adj[id].push_back(uc);
//                     adj[id].push_back(ll);
//                     break;
//                 }
//             }
//         }
//     }

//     // bfs graph
//     std::vector<int> is_visited(size * size);
//     for (int i = 0; i < is_visited.size(); i++) {
//         is_visited[i] = -1;
//     }
//     std::deque<int> bfs;
//     is_visited[start] = 0;
//     bfs.push_back(start);

//     while (!bfs.empty()) {
//         int cur = bfs.front();
//         bfs.pop_front();

//         // visit neighbors
//         for (int n : adj[cur]) {
//             if (is_visited[n] == -1) {
//                 // visit
//                 bfs.push_back(n);
//                 is_visited[n] = is_visited[cur] + 1;
//             }
//         }
//     }

//     int max = 0;
//     for (int i = 0; i < is_visited.size(); i++) {
//         if (is_visited[i] > max) {
//             max = is_visited[i];
//         }
//     }

//     std::cout << max << std::endl;

//     return 0;
// }

int main() {
    std::ifstream infile("day10/input");

    int size = 140 * 3;

    std::vector<std::string> g;
    std::string line = "";
    for (int i = 0; i < size + 2; i++) {
        line.push_back('.');
    }
    g.push_back(line);

    line.clear();
    while (std::getline(infile, line)) {
        std::string first = ".", second = ".", third = ".";
        for (int i = 0; i < line.size(); i++) {
            switch (line[i]) {
                case '|': {
                    first   += ".|.";
                    second  += ".|.";
                    third   += ".|.";
                    break;
                }
                case '-': {
                    first   += "...";
                    second  += "---";
                    third   += "...";
                    break;
                }
                case 'L': {
                    first   += ".|.";
                    second  += ".L-";
                    third   += "...";
                    break;
                }
                case 'J': {
                    first   += ".|.";
                    second  += "-J.";
                    third   += "...";
                    break;
                }
                case '7': {
                    first   += "...";
                    second  += "-7.";
                    third   += ".|.";
                    break;
                }
                case 'F': {
                    first   += "...";
                    second  += ".F-";
                    third   += ".|.";
                    break;
                }
                case 'S': {
                    first   += ".|.";
                    second  += "-S.";
                    third   += "...";
                    break;
                }
                case '.': {
                    first   += "...";
                    second  += "...";
                    third   += "...";
                    break;
                }
            }
        }
        first += ".";
        second += ".";
        third += ".";
        g.push_back(first);
        g.push_back(second);
        g.push_back(third);
    }

    line.clear();
    for (int i = 0; i < size + 2; i++) {
        line.push_back('.');
    }
    g.push_back(line);

    // prune
    while (true) {
        bool is_changed = false;

        for (int i = 1; i < size - 1; i++) {
            for (int j = 1; j < size - 1; j++) {
                if (g[i][j] == '.') {
                    continue;
                }

                bool should_change = false;

                switch (g[i][j]) {
                    case '|': {
                        should_change = (g[i-1][j] == '.' || g[i+1][j] == '.');
                        break;
                    }
                    case '-': {
                        should_change = (g[i][j-1] == '.' || g[i][j+1] == '.');
                        break;
                    }
                    case 'L': {
                        should_change = (g[i-1][j] == '.' || g[i][j+1] == '.');
                        break;
                    }
                    case 'J': {
                        should_change = (g[i-1][j] == '.' || g[i][j-1] == '.');
                        break;
                    }
                    case '7': {
                        should_change = (g[i+1][j] == '.' || g[i][j-1] == '.');
                        break;
                    }
                    case 'F': {
                        should_change = (g[i+1][j] == '.' || g[i][j+1] == '.');
                        break;
                    }
                }
                
                if (should_change) {
                    g[i][j] = '.';
                    is_changed = true;
                }
            }
        }

        if (!is_changed) {
            break;
        }
    }

    // prune 2nd
    std::vector<bool> is_visited(g.size() * g.size());
    std::deque<int> x;
    std::deque<int> y;
    x.push_back(164);
    y.push_back(47);

    int sss = g.size();

    while (!x.empty()) {
        int xx = x.front();
        int yy = y.front();
        x.pop_front();
        y.pop_front();

        is_visited[xx * sss + yy] = true;
        // std::cout << xx << " " << yy << std::endl;

        switch (g[xx][yy]) {
            case '|': {
                if (g[xx-1][yy] != '.' && g[xx-1][yy] != 'X' && !is_visited[(xx-1) * sss + yy]) {
                    x.push_back(xx-1); y.push_back(yy);
                    is_visited[(xx-1) * sss + yy] = true;
                }
                if (g[xx+1][yy] != '.' && g[xx+1][yy] != 'X' && !is_visited[(xx+1) * sss + yy]) {
                    x.push_back(xx+1); y.push_back(yy);
                    is_visited[(xx+1) * sss + yy] = true;
                }
                break;
            }
            case '-': {
                if (g[xx][yy-1] != '.' && g[xx][yy-1] != 'X' && !is_visited[(xx) * sss + (yy-1)]) {
                    x.push_back(xx); y.push_back(yy-1);
                    is_visited[(xx) * sss + (yy-1)] = true;
                }
                if (g[xx][yy+1] != '.' && g[xx][yy+1] != 'X' && !is_visited[(xx) * sss + (yy+1)]) {
                    x.push_back(xx); y.push_back(yy+1);
                    is_visited[(xx) * sss + (yy+1)] = true;
                }
                break;
            }
            case 'L': {
                if (g[xx-1][yy] != '.' && g[xx-1][yy] != 'X' && !is_visited[(xx-1) * sss + yy]) {
                    x.push_back(xx-1); y.push_back(yy);
                    is_visited[(xx-1) * sss + yy] = true;
                }
                if (g[xx][yy+1] != '.' && g[xx][yy+1] != 'X' && !is_visited[(xx) * sss + (yy+1)]) {
                    x.push_back(xx); y.push_back(yy+1);
                    is_visited[(xx) * sss + (yy+1)] = true;
                }
                break;
            }
            case 'S':
            case 'J': {
                if (g[xx-1][yy] != '.' && g[xx-1][yy] != 'X' && !is_visited[(xx-1) * sss + yy]) {
                    x.push_back(xx-1); y.push_back(yy);
                    is_visited[(xx-1) * sss + yy] = true;
                }
                if (g[xx][yy-1] != '.' && g[xx][yy-1] != 'X' && !is_visited[(xx) * sss + (yy-1)]) {
                    x.push_back(xx); y.push_back(yy-1);
                    is_visited[(xx) * sss + (yy-1)] = true;
                }
                break;
            }
            case '7': {
                if (g[xx+1][yy] != '.' && g[xx+1][yy] != 'X' && !is_visited[(xx+1) * sss + yy]) {
                    x.push_back(xx+1); y.push_back(yy);
                    is_visited[(xx+1) * sss + yy] = true;
                }
                if (g[xx][yy-1] != '.' && g[xx][yy-1] != 'X' && !is_visited[(xx) * sss + (yy-1)]) {
                    x.push_back(xx); y.push_back(yy-1);
                    is_visited[(xx) * sss + (yy-1)] = true;
                }
                break;
            }
            case 'F': {
                if (g[xx+1][yy] != '.' && g[xx+1][yy] != 'X' && !is_visited[(xx+1) * sss + yy]) {
                    x.push_back(xx+1); y.push_back(yy);
                    is_visited[(xx+1) * sss + yy] = true;
                }
                if (g[xx][yy+1] != '.' && g[xx][yy+1] != 'X' && !is_visited[(xx) * sss + (yy+1)]) {
                    x.push_back(xx); y.push_back(yy+1);
                    is_visited[(xx) * sss + (yy+1)] = true;
                }
                break;
            }
        }

        g[xx][yy] = 'X';
    }

    // if not X = .
    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g.size(); j++) {
            if (g[i][j] != 'X') {
                g[i][j] = '.';
            }
        }
    }

    // flood fill
    x.push_back(164);
    y.push_back(48);

    while (!x.empty()) {
        int xx = x.front();
        int yy = y.front();
        x.pop_front();
        y.pop_front();

        g[xx][yy] = 'I';

        if ((xx-1) >= 0 && (yy-1) >= 0 && g[xx-1][yy-1] == '.') {
            x.push_back(xx-1);
            y.push_back(yy-1);
            g[xx-1][yy-1] = 'I';
        }

        if ((xx-1) >= 0 && g[xx-1][yy] == '.') {
            x.push_back(xx-1);
            y.push_back(yy);
            g[xx-1][yy] = 'I';
        }

        if ((xx-1) >= 0 && (yy+1) < g.size() && g[xx-1][yy+1] == '.') {
            x.push_back(xx-1);
            y.push_back(yy+1);
            g[xx-1][yy+1] = 'I';
        }


        if ((yy-1) >= 0 && g[xx][yy-1] == '.') {
            x.push_back(xx);
            y.push_back(yy-1);
            g[xx][yy-1] = 'I';
        }

        if ((yy+1) < g.size() && g[xx][yy+1] == '.') {
            x.push_back(xx);
            y.push_back(yy+1);
            g[xx][yy+1] = 'I';
        }


        if ((xx+1) < g.size() && (yy-1) >= 0 && g[xx+1][yy-1] == '.') {
            x.push_back(xx+1);
            y.push_back(yy-1);
            g[xx+1][yy-1] = 'I';
        }

        if ((xx+1) < g.size() && g[xx+1][yy] == '.') {
            x.push_back(xx+1);
            y.push_back(yy);
            g[xx+1][yy] = 'I';
        }

        if ((xx+1) < g.size() && (yy+1) < g.size() && g[xx+1][yy+1] == '.') {
            x.push_back(xx+1);
            y.push_back(yy+1);
            g[xx+1][yy+1] = 'I';
        }
    }
  
    int cnt = 0;
    for (int i = 1; i < size - 1; i++) {
        for (int j = 1; j < size - 1; j++) {
            if (g[i][j] == 'I') {
                if (g[i-1][j-1] == 'I' && g[i-1][j] == 'I' && g[i-1][j+1] == 'I' &&
                    g[i][j-1] == 'I' && g[i][j] == 'I' && g[i][j+1] == 'I' &&
                    g[i+1][j-1] == 'I' && g[i+1][j] == 'I' && g[i+1][j+1] == 'I') {
                    cnt++;
                    std::cout << "I";
                } else {
                    std::cout << ".";
                }
            } else {
                std::cout << g[i][j];
            }
        }
        std::cout << std::endl;
    }

    std::cout << cnt / 9 << std::endl;

    return 0;
}