#include <iostream>
#include <fstream>
#include <unordered_map>

int main() {
    std::ifstream infile("day08/input");

    int cnt = 0;
    std::unordered_map<std::string, int> idx;

    std::vector<int> l(1000);
    std::vector<int> r(1000);

    std::string dir;
    infile >> dir;

    std::vector<bool> dd;
    for (char d : dir) {
        dd.push_back(d == 'L');
    }

    std::vector<int> ss;
    std::vector<bool> dst(1000, false);

    std::string tk_s, tk_e, tk_dl, tk_dr;
    while (infile >> tk_s >> tk_e >> tk_dl >> tk_dr) {
        int s, dl, dr;

        if (idx.count(tk_s) == 0) {
            idx[tk_s] = cnt++;

            if (tk_s[2] == 'A') {
                ss.push_back(idx[tk_s]);
            } else if (tk_s[2] == 'Z') {
                dst[idx[tk_s]] = true;
            }
        }
        
        tk_dl = tk_dl.substr(1, tk_dl.size() - 2);
        if (idx.count(tk_dl) == 0) {
            idx[tk_dl] = cnt++;
            if (tk_dl[2] == 'A') {
                ss.push_back(idx[tk_s]);
            } else if (tk_dl[2] == 'Z') {
                dst[idx[tk_dl]] = true;
            }
        }

        tk_dr = tk_dr.substr(0, tk_dr.size() - 1);
        if (idx.count(tk_dr) == 0) {
            idx[tk_dr] = cnt++;
            if (tk_dr[2] == 'A') {
                ss.push_back(idx[tk_s]);
            } else if (tk_dr[2] == 'Z') {
                dst[idx[tk_dr]] = true;
            }
        }

        s = idx[tk_s];
        dl = idx[tk_dl];
        dr = idx[tk_dr];

        l[s] = dl;
        r[s] = dr;
    }

    int sum = 0;
    int target = ss.size();

    int prev = 0;

    std::vector<int> ss_init = ss;

    while (true) {
        for (bool is_left : dd) {
            for (int i = 0; i < 6; i++) {
                if (is_left) {
                    // left
                    ss[i] = l[ss[i]];
                } else {
                    // right
                    ss[i] = r[ss[i]];
                }

                if (dst[ss[i]]) {
                    std::cout << (i+1) << " " << ss[i] << " " << sum << std::endl;
                }
            }
            sum++;
        }
    }

    // LCM all the gaps = Result

    return 0;
}