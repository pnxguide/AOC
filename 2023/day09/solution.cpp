#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::ifstream infile("day09/input");

    long sum = 0;

    std::string line;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);

        std::vector<int> e;

        int x;
        while (ss >> x) {
            e.push_back(x);
        }

        std::reverse(e.begin(), e.end());

        std::vector<std::vector<int>> d;
        d.push_back(e);

        std::vector<int> ee = d.back();

        int delta = 0;

        while (true) {
            bool is_good = true;
            std::vector<int> dd;
            
            int prev = ee[0];
            for (int i = 1; i < ee.size(); i++) {
                int x = ee[i] - ee[i-1];

                if (i > 1) {
                    if (prev != x) {
                        is_good = false;
                    }
                }

                prev = x;

                dd.push_back(x);
            }

            if (is_good) {
                delta = dd.back();
                break;
            } else {
                d.push_back(dd);
                ee = dd;
            }
        }

        for (std::vector<int> ddd : d) {
            delta += ddd.back();
        }

        sum += delta;
    }

    std::cout << sum << std::endl;

    return 0;
}