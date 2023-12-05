#include <fstream>
#include <iostream>
#include <unordered_map>
#include <deque>

// int main() {
//     std::ifstream in("day05/input");

//     // range
//     std::vector<std::pair<long, long>> s2s_r, s2f_r, f2w_r, w2l_r, l2t_r,
//     t2h_r, h2l_r;

//     // incrementer
//     std::vector<long> s2s, s2f, f2w, w2l, l2t, t2h, h2l;

//     // remove the first token
//     std::string tk;
//     in >> tk;

//     // get seed
//     std::vector<long> seeds;

//     int state = 0;
//     while (in >> tk) {
//         if (tk[0] >= '0' && tk[0] <= '9') {
//             long d = std::stol(tk);
//             if (state == 0) {
//                 seeds.push_back(d);
//             } else {
//                 long s, r;
//                 in >> s;
//                 in >> r;
//                 switch(state) {
//                     case 1: {
//                         s2s_r.push_back({s, s+r});
//                         s2s.push_back({d-s});
//                         break;
//                     }
//                     case 2: {
//                         s2f_r.push_back({s, s+r});
//                         s2f.push_back({d-s});
//                         break;
//                     }
//                     case 3: {
//                         f2w_r.push_back({s, s+r});
//                         f2w.push_back({d-s});
//                         break;
//                     }
//                     case 4: {
//                         w2l_r.push_back({s, s+r});
//                         w2l.push_back({d-s});
//                         break;
//                     }
//                     case 5: {
//                         l2t_r.push_back({s, s+r});
//                         l2t.push_back({d-s});
//                         break;
//                     }
//                     case 6: {
//                         t2h_r.push_back({s, s+r});
//                         t2h.push_back({d-s});
//                         break;
//                     }
//                     case 7: {
//                         h2l_r.push_back({s, s+r});
//                         h2l.push_back({d-s});
//                         break;
//                     }
//                 }
//             }
//         } else {
//             state++;
//             while (tk != "map:") {
//                 in >> tk;
//             }
//         }
//     }

//     long min = LONG_MAX;
//     for (long seed : seeds) {
//         long val = seed;

//         for (int i = 0; i < s2s_r.size(); i++) {
//             if (val >= s2s_r[i].first && val < s2s_r[i].second) {
//                 val += s2s[i];
//                 break;
//             }
//         }

//         for (int i = 0; i < s2f_r.size(); i++) {
//             if (val >= s2f_r[i].first && val < s2f_r[i].second) {
//                 val += s2f[i];
//                 break;
//             }
//         }

//         for (int i = 0; i < f2w_r.size(); i++) {
//             if (val >= f2w_r[i].first && val < f2w_r[i].second) {
//                 val += f2w[i];
//                 break;
//             }
//         }

//         for (int i = 0; i < w2l_r.size(); i++) {
//             if (val >= w2l_r[i].first && val < w2l_r[i].second) {
//                 val += w2l[i];
//                 break;
//             }
//         }

//         for (int i = 0; i < l2t_r.size(); i++) {
//             if (val >= l2t_r[i].first && val < l2t_r[i].second) {
//                 val += l2t[i];
//                 break;
//             }
//         }

//         for (int i = 0; i < t2h_r.size(); i++) {
//             if (val >= t2h_r[i].first && val < t2h_r[i].second) {
//                 val += t2h[i];
//                 break;
//             }
//         }

//         for (int i = 0; i < h2l_r.size(); i++) {
//             if (val >= h2l_r[i].first && val < h2l_r[i].second) {
//                 val += h2l[i];
//                 break;
//             }
//         }

//         if (val < min) {
//             std::cout << "seed: " << seed << std::endl;
//             min = val;
//         }
//     }

//     std::cout << "min: " << min << std::endl;

//     return 0;
// }

int main() {
    std::ifstream in("day05/input");

    // range
    std::vector<std::tuple<long, long, long>> s2s, s2f, f2w, w2l, l2t, t2h, h2l;

    // remove the first token
    std::string tk;
    in >> tk;

    // get seed
    std::vector<std::pair<long, long>> seeds;

    int state = 0;
    while (in >> tk) {
        if (tk[0] >= '0' && tk[0] <= '9') {
            long d = std::stol(tk);
            if (state == 0) {
                long dr;
                in >> dr;
                seeds.push_back({d, d + dr - 1});
            } else {
                long s, r;
                in >> s;
                in >> r;
                switch (state) {
                    case 1: {
                        s2s.push_back({s, s + r - 1, d - s});
                        break;
                    }
                    case 2: {
                        s2f.push_back({s, s + r - 1, d - s});
                        break;
                    }
                    case 3: {
                        f2w.push_back({s, s + r - 1, d - s});
                        break;
                    }
                    case 4: {
                        w2l.push_back({s, s + r - 1, d - s});
                        break;
                    }
                    case 5: {
                        l2t.push_back({s, s + r - 1, d - s});
                        break;
                    }
                    case 6: {
                        t2h.push_back({s, s + r - 1, d - s});
                        break;
                    }
                    case 7: {
                        h2l.push_back({s, s + r - 1, d - s});
                        break;
                    }
                }
            }
        } else {
            state++;
            while (tk != "map:") {
                in >> tk;
            }
        }
    }

    // sort range
    auto sorter = [](auto const &t1, auto const &t2) {
        return std::get<0>(t1) < std::get<0>(t2);
    };

    std::sort(std::begin(s2s), std::end(s2s), sorter);

    std::sort(std::begin(s2f), std::end(s2f), sorter);

    std::sort(std::begin(f2w), std::end(f2w), sorter);

    std::sort(std::begin(w2l), std::end(w2l), sorter);

    std::sort(std::begin(l2t), std::end(l2t), sorter);

    std::sort(std::begin(t2h), std::end(t2h), sorter);

    std::sort(std::begin(h2l), std::end(h2l), sorter);

    long min = LONG_MAX;
    for (std::pair<long, long> seed : seeds) {
        std::deque<std::pair<long, long>> vr, new_vr, rem;
        vr.push_back(seed);

        std::vector<std::tuple<long, long, long>> tt = s2s;
        for (std::tuple<long, long, long> t : tt) {
            long st = std::get<0>(t);
            long en = std::get<1>(t);
            long delta = std::get<2>(t);

            for (std::pair<long, long> cur : vr) {
                long cur_st = cur.first;
                long cur_en = cur.second;

                // left overlap
                if (cur_st < st && cur_st < en && cur_en >= st && cur_en <= en) {
                    rem.push_back({cur_st, st - 1});
                    new_vr.push_back({en + delta, cur_en + delta});
                }

                // right overlap
                else if (cur_st >= st && cur_st < en && cur_en > st && cur_en > en) {
                    rem.push_back({en + 1, cur_en});
                    new_vr.push_back({cur_st + delta, en + delta});
                }

                // in between
                else if (cur_st >= st && cur_st <= en && cur_en >= st && cur_en <= en) {
                    new_vr.push_back({cur_st + delta, cur_en + delta});
                }

                // larger
                else if (cur_st < st && cur_st < en && cur_en > st && cur_en > en) {
                    rem.push_back({cur_st, st - 1});
                    rem.push_back({en + 1, cur_en});
                    new_vr.push_back({st + delta, en + delta});
                }

                else {
                    rem.push_back(cur);
                }
            }

            vr = rem;
            rem.clear();
        }
        for (std::pair<long, long> cur : new_vr) {
            vr.push_back(cur);
        }
        new_vr.clear();

        tt = s2f;
        for (std::tuple<long, long, long> t : tt) {
            long st = std::get<0>(t);
            long en = std::get<1>(t);
            long delta = std::get<2>(t);

            for (std::pair<long, long> cur : vr) {
                long cur_st = cur.first;
                long cur_en = cur.second;

                // left overlap
                if (cur_st < st && cur_st < en && cur_en >= st && cur_en <= en) {
                    rem.push_back({cur_st, st - 1});
                    new_vr.push_back({en + delta, cur_en + delta});
                }

                // right overlap
                else if (cur_st >= st && cur_st < en && cur_en > st && cur_en > en) {
                    rem.push_back({en + 1, cur_en});
                    new_vr.push_back({cur_st + delta, en + delta});
                }

                // in between
                else if (cur_st >= st && cur_st <= en && cur_en >= st && cur_en <= en) {
                    new_vr.push_back({cur_st + delta, cur_en + delta});
                }

                // larger
                else if (cur_st < st && cur_st < en && cur_en > st && cur_en > en) {
                    rem.push_back({cur_st, st - 1});
                    rem.push_back({en + 1, cur_en});
                    new_vr.push_back({st + delta, en + delta});
                }

                else {
                    rem.push_back(cur);
                }
            }

            vr = rem;
            rem.clear();
        }
        for (std::pair<long, long> cur : new_vr) {
            vr.push_back(cur);
        }
        new_vr.clear();

        tt = f2w;
        for (std::tuple<long, long, long> t : tt) {
            long st = std::get<0>(t);
            long en = std::get<1>(t);
            long delta = std::get<2>(t);

            for (std::pair<long, long> cur : vr) {
                long cur_st = cur.first;
                long cur_en = cur.second;

                // left overlap
                if (cur_st < st && cur_st < en && cur_en >= st && cur_en <= en) {
                    rem.push_back({cur_st, st - 1});
                    new_vr.push_back({en + delta, cur_en + delta});
                }

                // right overlap
                else if (cur_st >= st && cur_st < en && cur_en > st && cur_en > en) {
                    rem.push_back({en + 1, cur_en});
                    new_vr.push_back({cur_st + delta, en + delta});
                }

                // in between
                else if (cur_st >= st && cur_st <= en && cur_en >= st && cur_en <= en) {
                    new_vr.push_back({cur_st + delta, cur_en + delta});
                }

                // larger
                else if (cur_st < st && cur_st < en && cur_en > st && cur_en > en) {
                    rem.push_back({cur_st, st - 1});
                    rem.push_back({en + 1, cur_en});
                    new_vr.push_back({st + delta, en + delta});
                }

                else {
                    rem.push_back(cur);
                }
            }

            vr = rem;
            rem.clear();
        }
        for (std::pair<long, long> cur : new_vr) {
            vr.push_back(cur);
        }
        new_vr.clear();

        tt = w2l;
        for (std::tuple<long, long, long> t : tt) {
            long st = std::get<0>(t);
            long en = std::get<1>(t);
            long delta = std::get<2>(t);

            for (std::pair<long, long> cur : vr) {
                long cur_st = cur.first;
                long cur_en = cur.second;

                // left overlap
                if (cur_st < st && cur_st < en && cur_en >= st && cur_en <= en) {
                    rem.push_back({cur_st, st - 1});
                    new_vr.push_back({en + delta, cur_en + delta});
                }

                // right overlap
                else if (cur_st >= st && cur_st < en && cur_en > st && cur_en > en) {
                    rem.push_back({en + 1, cur_en});
                    new_vr.push_back({cur_st + delta, en + delta});
                }

                // in between
                else if (cur_st >= st && cur_st <= en && cur_en >= st && cur_en <= en) {
                    new_vr.push_back({cur_st + delta, cur_en + delta});
                }

                // larger
                else if (cur_st < st && cur_st < en && cur_en > st && cur_en > en) {
                    rem.push_back({cur_st, st - 1});
                    rem.push_back({en + 1, cur_en});
                    new_vr.push_back({st + delta, en + delta});
                }

                else {
                    rem.push_back(cur);
                }
            }

            vr = rem;
            rem.clear();
        }
        for (std::pair<long, long> cur : new_vr) {
            vr.push_back(cur);
        }
        new_vr.clear();

        tt = l2t;
        for (std::tuple<long, long, long> t : tt) {
            long st = std::get<0>(t);
            long en = std::get<1>(t);
            long delta = std::get<2>(t);

            for (std::pair<long, long> cur : vr) {
                long cur_st = cur.first;
                long cur_en = cur.second;

                // left overlap
                if (cur_st < st && cur_st < en && cur_en >= st && cur_en <= en) {
                    rem.push_back({cur_st, st - 1});
                    new_vr.push_back({en + delta, cur_en + delta});
                }

                // right overlap
                else if (cur_st >= st && cur_st < en && cur_en > st && cur_en > en) {
                    rem.push_back({en + 1, cur_en});
                    new_vr.push_back({cur_st + delta, en + delta});
                }

                // in between
                else if (cur_st >= st && cur_st <= en && cur_en >= st && cur_en <= en) {
                    new_vr.push_back({cur_st + delta, cur_en + delta});
                }

                // larger
                else if (cur_st < st && cur_st < en && cur_en > st && cur_en > en) {
                    rem.push_back({cur_st, st - 1});
                    rem.push_back({en + 1, cur_en});
                    new_vr.push_back({st + delta, en + delta});
                }

                else {
                    rem.push_back(cur);
                }
            }

            vr = rem;
            rem.clear();
        }
        for (std::pair<long, long> cur : new_vr) {
            vr.push_back(cur);
        }
        new_vr.clear();

        tt = t2h;
        for (std::tuple<long, long, long> t : tt) {
            long st = std::get<0>(t);
            long en = std::get<1>(t);
            long delta = std::get<2>(t);

            for (std::pair<long, long> cur : vr) {
                long cur_st = cur.first;
                long cur_en = cur.second;

                // left overlap
                if (cur_st < st && cur_st < en && cur_en >= st && cur_en <= en) {
                    rem.push_back({cur_st, st - 1});
                    new_vr.push_back({en + delta, cur_en + delta});
                }

                // right overlap
                else if (cur_st >= st && cur_st < en && cur_en > st && cur_en > en) {
                    rem.push_back({en + 1, cur_en});
                    new_vr.push_back({cur_st + delta, en + delta});
                }

                // in between
                else if (cur_st >= st && cur_st <= en && cur_en >= st && cur_en <= en) {
                    new_vr.push_back({cur_st + delta, cur_en + delta});
                }

                // larger
                else if (cur_st < st && cur_st < en && cur_en > st && cur_en > en) {
                    rem.push_back({cur_st, st - 1});
                    rem.push_back({en + 1, cur_en});
                    new_vr.push_back({st + delta, en + delta});
                }

                else {
                    rem.push_back(cur);
                }
            }

            vr = rem;
            rem.clear();
        }
        for (std::pair<long, long> cur : new_vr) {
            vr.push_back(cur);
        }
        new_vr.clear();

        tt = h2l;
        for (std::tuple<long, long, long> t : tt) {
            long st = std::get<0>(t);
            long en = std::get<1>(t);
            long delta = std::get<2>(t);

            for (std::pair<long, long> cur : vr) {
                long cur_st = cur.first;
                long cur_en = cur.second;

                // left overlap
                if (cur_st < st && cur_st < en && cur_en >= st && cur_en <= en) {
                    rem.push_back({cur_st, st - 1});
                    new_vr.push_back({en + delta, cur_en + delta});
                }

                // right overlap
                else if (cur_st >= st && cur_st < en && cur_en > st && cur_en > en) {
                    rem.push_back({en + 1, cur_en});
                    new_vr.push_back({cur_st + delta, en + delta});
                }

                // in between
                else if (cur_st >= st && cur_st <= en && cur_en >= st && cur_en <= en) {
                    new_vr.push_back({cur_st + delta, cur_en + delta});
                }

                // larger
                else if (cur_st < st && cur_st < en && cur_en > st && cur_en > en) {
                    rem.push_back({cur_st, st - 1});
                    rem.push_back({en + 1, cur_en});
                    new_vr.push_back({st + delta, en + delta});
                }

                else {
                    rem.push_back(cur);
                }
            }

            vr = rem;
            rem.clear();
        }
        for (std::pair<long, long> cur : new_vr) {
            vr.push_back(cur);
        }
        new_vr.clear();

        std::cout << "after" << std::endl;
        for (std::pair<long, long> rr : vr) {
            std::cout << "(" << rr.first << "," << rr.second << ")" << std::endl;
        }

        for (int j = 0; j < vr.size(); j++) {
            if (vr[j].first < min) {
                min = vr[j].first;
            }
        }
    }

    std::cout << "min: " << min << std::endl;

    return 0;
}