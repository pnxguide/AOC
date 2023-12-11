#include <iostream>
#include <fstream>

int main() {
    std::ifstream infile("day11/input");

    std::vector<std::pair<int, int>> galaxies;
    std::vector<std::string> bb;

    std::string line;
    while (std::getline(infile, line)) {
        bb.push_back(line);
    }

    std::vector<bool> expand_x(140);
    std::vector<bool> expand_y(140);

    // expand vertically
    for (int i = 0; i < bb.size(); i++) {
        bool no_galaxy = true;
        for (int j = 0; j < bb[i].size(); j++) {
            if (bb[i][j] == '#') {
                no_galaxy = false;
                break;
            }
        }
        if (no_galaxy) {
            expand_y[i] = true;
            // std::cout << "expand y: " << i << std::endl;
        }
    }

    // expand horizontally
    for (int i = 0; i < bb[0].size(); i++) {
        bool no_galaxy = true;
        for (int j = 0; j < bb.size(); j++) {
            if (bb[j][i] == '#') {
                no_galaxy = false;
                break;
            }
        }
        if (no_galaxy) {
            expand_x[i] = true;
            // std::cout << "expand x: " << i << std::endl;
        }
    }

    // get galaxy coordinate
    for (int i = 0; i < bb.size(); i++) {
        for (int j = 0; j < bb[i].size(); j++) {
            if (bb[i][j] == '#') {
                galaxies.push_back(std::make_pair(i, j));
            }
        }
    }

    long add = 1000000 - 1;

    // manhattan dist
    long sum = 0;
    for (int i = 0; i < galaxies.size(); i++) {
        for (int j = i+1; j < galaxies.size(); j++) {
            long x1 = std::max(galaxies[i].first, galaxies[j].first);
            long x2 = std::min(galaxies[i].first, galaxies[j].first);

            for (int xx = x2; xx < x1; xx++) {
                if (expand_y[xx]) {
                    sum += add;
                }
            }

            long y1 = std::max(galaxies[i].second, galaxies[j].second);
            long y2 = std::min(galaxies[i].second, galaxies[j].second);

            for (int yy = y2; yy < y1; yy++) {
                if (expand_x[yy]) {
                    sum += add;
                }
            }

            sum += (x1 - x2) + (y1 - y2);
        }
    }

    std::cout << sum << std::endl;

    return 0;
}