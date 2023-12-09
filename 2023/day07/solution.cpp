#include <iostream>
#include <fstream>

int main() {
    std::ifstream infile("day07/input");

    std::vector<int> ranks;
    std::vector<int> bids;

    std::vector<std::tuple<int, int, std::vector<int>>> cards;
    std::string card;
    std::vector<int> val;
    while (infile >> card) {
        int d5 = -1, d4 = -1, d3 = -1;
        std::vector<int> d2;
        std::vector<int> d1;

        int bid;
        infile >> bid;

        std::vector<int> l(5);
        for (int i = 0; i < 5; i++) {
            switch (card[i]) {
                case 'A': {
                    l[i] = 12;
                    break;
                }
                case 'K': {
                    l[i] = 11;
                    break;
                }
                case 'Q': {
                    l[i] = 10;
                    break;
                }
                case 'T': {
                    l[i] = 9;
                    break;
                }
                case '9': {
                    l[i] = 8;
                    break;
                }
                case '8': {
                    l[i] = 7;
                    break;
                }
                case '7': {
                    l[i] = 6;
                    break;
                }
                case '6': {
                    l[i] = 5;
                    break;
                }
                case '5': {
                    l[i] = 4;
                    break;
                }
                case '4': {
                    l[i] = 3;
                    break;
                }
                case '3': {
                    l[i] = 2;
                    break;
                }
                case '2': {
                    l[i] = 1;
                    break;
                }
                case 'J': {
                    l[i] = 0;
                    break;
                }
            }
        }

        std::vector<int> cnt(13);
        for (int i = 0; i < 5; i++) {
            cnt[l[i]]++;
        }

        int max_idx = 1;
        for (int i = 1; i < 13; i++) {
            if (cnt[i] > cnt[max_idx]) {
                max_idx = i;
            }
        }

        cnt[max_idx] += cnt[0];
        cnt[0] = 0;

        int type = 0;
        for (int i = 0; i < 13; i++) {
            if (cnt[i] == 5) {
                type = std::max(type, 6);
            } else if (cnt[i] == 4) {
                type = std::max(type, 5);
            } else if (cnt[i] == 3) {
                type = std::max(type, 3);
                for (int j = 0; j < 13; j++) {
                    if (cnt[j] == 2) {
                        type = std::max(type, 4);
                        break;
                    }
                }
            } else if (cnt[i] == 2) {
                type = std::max(type, 1);
                for (int j = 0; j < 13; j++) {
                    if (i != j && cnt[j] == 2) {
                        type = std::max(type, 2);
                        break;
                    }
                }
            } else if (cnt[i] == 1) {
                type = std::max(type, 0);
            }
        }
        
        cards.push_back(std::make_tuple(type, bid, l));
    }

    std::sort(cards.begin(), cards.end(), [](const std::tuple<int, int, std::vector<int>> l, const std::tuple<int, int, std::vector<int>> r) {
        std::vector<int> ll, rr;
        ll = std::get<2>(l);
        rr = std::get<2>(r);
        
        int lt, rt;
        lt = std::get<0>(l);
        rt = std::get<0>(r);

        if (lt == rt) {
            for (int i = 0; i < 5; i++) {
                if (ll[i] == rr[i]) continue;
                else return ll[i] < rr[i];
            }
        }

        return lt < rt;
    });

    long s = 0;
    for (int i = 0; i < cards.size(); i++) {
        s += (i + 1) * std::get<1>(cards[i]);
    }

    std::cout << s << std::endl;

    return 0;
}