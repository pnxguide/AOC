#include <algorithm>
#include <cassert>
#include <deque>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

void tokenize(const std::string &s, const char delim, std::vector<std::string> &out) {
    std::string::size_type beg = 0;
    for (auto end = 0; (end = s.find(delim, end)) != std::string::npos; ++end) {
        out.push_back(s.substr(beg, end - beg));
        beg = end + 1;
    }

    out.push_back(s.substr(beg));
}

void solve_A() {
    // Read an input file
    std::ifstream input_file("day24/input.txt");
    std::string line;

    // constexpr int ROW = 20, COL = 150;
    constexpr int ROW = 4, COL = 6;
    std::vector<std::vector<bool>> u(ROW, std::vector<bool>(COL, false));
    std::vector<std::vector<bool>> d(ROW, std::vector<bool>(COL, false));
    std::vector<std::vector<bool>> l(ROW, std::vector<bool>(COL, false));
    std::vector<std::vector<bool>> r(ROW, std::vector<bool>(COL, false));

    // Skip the first line
    std::getline(input_file, line);
    for (size_t i = 0; i < ROW; i++) {
        std::getline(input_file, line);
        for (size_t j = 0; j < COL; j++) {
            switch (line[j + 1]) {
                case '>':
                    r[i][j] = true;
                    break;
                case '<':
                    l[i][j] = true;
                    break;
                case '^':
                    u[i][j] = true;
                    break;
                case 'v':
                    d[i][j] = true;
                    break;
            }
        }
    }

    constexpr int GOAL_X = COL - 1, GOAL_Y = ROW - 1;

    std::deque<std::pair<int, int>> bfs;
    std::deque<int> bfs_cnt;
    std::vector<std::vector<std::vector<bool>>> cached_u;
    std::vector<std::vector<std::vector<bool>>> cached_d;
    std::vector<std::vector<std::vector<bool>>> cached_l;
    std::vector<std::vector<std::vector<bool>>> cached_r;
    cached_u.push_back(u);
    cached_d.push_back(d);
    cached_l.push_back(l);
    cached_r.push_back(r);
    int max_cached = 1;

    bfs.push_back(std::make_pair(-1, 0));
    bfs_cnt.push_back(0);

    int cur_cnt = 0;

    while (!bfs.empty()) {
        assert(bfs.size() == bfs_cnt.size());

        int cur_X = bfs.front().second;
        int cur_Y = bfs.front().first;
        int cnt = bfs_cnt.front();
        bfs.pop_front();
        bfs_cnt.pop_front();

        if (cur_cnt != cnt) {
            std::cout << cnt << std::endl;
            cur_cnt = cnt;
        }

        // std::cout << cnt << " " << max_cached << "|" << cur_Y << "," << cur_X << std::endl;
        // for (int i = 0; i < ROW; i++) {
        //   for (int j = 0; j < COL; j++) {
        //     if (cur_X == j && cur_Y == i) std::cout << "E";
        //     else if (
        //       !cached_d[cnt][i][j] &&
        //       !cached_u[cnt][i][j] &&
        //       !cached_l[cnt][i][j] &&
        //       !cached_r[cnt][i][j]) std::cout << ".";
        //     else std::cout << "#";
        //   }
        //   std::cout << std::endl;
        // }
        // std::cout << std::endl;

        if (cur_X == GOAL_X && cur_Y == GOAL_Y) {
            std::cout << "Answer: " << cnt + 1 << std::endl;
            break;
        } else {
            // If map is not cached, generate it!
            if (cnt + 1 == max_cached) {
                // Update all blizzards
                std::vector<std::vector<bool>> tmp_u(ROW, std::vector<bool>(COL, false));
                std::vector<std::vector<bool>> tmp_d(ROW, std::vector<bool>(COL, false));
                std::vector<std::vector<bool>> tmp_l(ROW, std::vector<bool>(COL, false));
                std::vector<std::vector<bool>> tmp_r(ROW, std::vector<bool>(COL, false));

                for (int i = 0; i < ROW; i++) {
                    for (int j = 0; j < COL; j++) {
                        if (cached_u[cnt][i][j]) {
                            if (i == 0)
                                tmp_u[ROW - 1][j] = true;
                            else
                                tmp_u[i - 1][j] = true;
                            // std::cout << "u" << std::endl;
                        }

                        if (cached_d[cnt][i][j]) {
                            if (i == ROW - 1)
                                tmp_d[0][j] = true;
                            else
                                tmp_d[i + 1][j] = true;
                            // std::cout << "d" << std::endl;
                        }

                        if (cached_l[cnt][i][j]) {
                            if (j == 0)
                                tmp_l[i][COL - 1] = true;
                            else
                                tmp_l[i][j - 1] = true;
                            // std::cout << "l" << std::endl;
                        }

                        if (cached_r[cnt][i][j]) {
                            if (j == COL - 1)
                                tmp_r[i][0] = true;
                            else
                                tmp_r[i][j + 1] = true;
                            // std::cout << "r" << std::endl;
                        }
                    }
                }

                cached_u.push_back(tmp_u);
                cached_d.push_back(tmp_d);
                cached_l.push_back(tmp_l);
                cached_r.push_back(tmp_r);

                // for (int i = 0; i < ROW; i++) {
                //   for (int j = 0; j < COL; j++) {
                //     if (
                //       !cached_d[cnt+1][i][j] &&
                //       !cached_u[cnt+1][i][j] &&
                //       !cached_l[cnt+1][i][j] &&
                //       !cached_r[cnt+1][i][j]) std::cout << ".";
                //     else std::cout << "#";
                //   }
                //   std::cout << std::endl;
                // }
                // std::cout << std::endl;

                max_cached++;
                assert(cnt + 2 == max_cached && max_cached == cached_u.size());
            }

            // try to move down
            if (cur_Y < ROW - 1 && !cached_d[cnt + 1][cur_Y + 1][cur_X] && !cached_u[cnt + 1][cur_Y + 1][cur_X] &&
                !cached_l[cnt + 1][cur_Y + 1][cur_X] && !cached_r[cnt + 1][cur_Y + 1][cur_X]) {
                bool can_push = true;
                for (size_t k = 0; k < bfs.size(); k++) {
                    if (bfs[k].first == cur_Y + 1 && bfs[k].second == cur_X && bfs_cnt[k] == cnt + 1) {
                        can_push = false;
                        break;
                    }
                }

                if (can_push) {
                    bfs.push_back(std::make_pair(cur_Y + 1, cur_X));
                    bfs_cnt.push_back(cnt + 1);
                }
            }

            if (cur_Y >= 0) {
                // try to move up
                if (cur_Y > 0 && !cached_d[cnt + 1][cur_Y - 1][cur_X] && !cached_u[cnt + 1][cur_Y - 1][cur_X] &&
                    !cached_l[cnt + 1][cur_Y - 1][cur_X] && !cached_r[cnt + 1][cur_Y - 1][cur_X]) {
                    bool can_push = true;
                    for (size_t k = 0; k < bfs.size(); k++) {
                        if (bfs[k].first == cur_Y - 1 && bfs[k].second == cur_X && bfs_cnt[k] == cnt + 1) {
                            can_push = false;
                            break;
                        }
                    }

                    if (can_push) {
                        bfs.push_back(std::make_pair(cur_Y - 1, cur_X));
                        bfs_cnt.push_back(cnt + 1);
                    }
                }

                // try to move left
                if (cur_X > 0 && !cached_d[cnt + 1][cur_Y][cur_X - 1] && !cached_u[cnt + 1][cur_Y][cur_X - 1] &&
                    !cached_l[cnt + 1][cur_Y][cur_X - 1] && !cached_r[cnt + 1][cur_Y][cur_X - 1]) {
                    bool can_push = true;
                    for (size_t k = 0; k < bfs.size(); k++) {
                        if (bfs[k].first == cur_Y && bfs[k].second == cur_X - 1 && bfs_cnt[k] == cnt + 1) {
                            can_push = false;
                            break;
                        }
                    }

                    if (can_push) {
                        bfs.push_back(std::make_pair(cur_Y, cur_X - 1));
                        bfs_cnt.push_back(cnt + 1);
                    }
                }

                // try to move right
                if (cur_X < COL - 1 && !cached_d[cnt + 1][cur_Y][cur_X + 1] && !cached_u[cnt + 1][cur_Y][cur_X + 1] &&
                    !cached_l[cnt + 1][cur_Y][cur_X + 1] && !cached_r[cnt + 1][cur_Y][cur_X + 1]) {
                    bool can_push = true;
                    for (size_t k = 0; k < bfs.size(); k++) {
                        if (bfs[k].first == cur_Y && bfs[k].second == cur_X + 1 && bfs_cnt[k] == cnt + 1) {
                            can_push = false;
                            break;
                        }
                    }

                    if (can_push) {
                        bfs.push_back(std::make_pair(cur_Y, cur_X + 1));
                        bfs_cnt.push_back(cnt + 1);
                    }
                }

                // wait
                if (!cached_d[cnt + 1][cur_Y][cur_X] && !cached_u[cnt + 1][cur_Y][cur_X] &&
                    !cached_l[cnt + 1][cur_Y][cur_X] && !cached_r[cnt + 1][cur_Y][cur_X]) {
                    bool can_push = true;
                    for (size_t k = 0; k < bfs.size(); k++) {
                        if (bfs[k].first == cur_Y && bfs[k].second == cur_X && bfs_cnt[k] == cnt + 1) {
                            can_push = false;
                            break;
                        }
                    }

                    if (can_push) {
                        bfs.push_back(std::make_pair(cur_Y, cur_X));
                        bfs_cnt.push_back(cnt + 1);
                    }
                }
            } else {
                // wait
                bfs.push_back(std::make_pair(cur_Y, cur_X));
                bfs_cnt.push_back(cnt + 1);
            }
        }
    }
}

void solve_B() {
    // Read an input file
    std::ifstream input_file("day24/input.txt");
    std::string line;

    constexpr int ROW = 20, COL = 150;
    // constexpr int ROW = 4, COL = 6;
    std::vector<std::vector<bool>> u(ROW, std::vector<bool>(COL, false));
    std::vector<std::vector<bool>> d(ROW, std::vector<bool>(COL, false));
    std::vector<std::vector<bool>> l(ROW, std::vector<bool>(COL, false));
    std::vector<std::vector<bool>> r(ROW, std::vector<bool>(COL, false));

    // Skip the first line
    std::getline(input_file, line);
    for (size_t i = 0; i < ROW; i++) {
        std::getline(input_file, line);
        for (size_t j = 0; j < COL; j++) {
            switch (line[j + 1]) {
                case '>':
                    r[i][j] = true;
                    break;
                case '<':
                    l[i][j] = true;
                    break;
                case '^':
                    u[i][j] = true;
                    break;
                case 'v':
                    d[i][j] = true;
                    break;
            }
        }
    }

    int GOAL_X = COL - 1, GOAL_Y = ROW - 1;

    std::deque<std::pair<int, int>> bfs;
    std::deque<int> bfs_cnt;
    std::vector<std::vector<std::vector<bool>>> cached_u;
    std::vector<std::vector<std::vector<bool>>> cached_d;
    std::vector<std::vector<std::vector<bool>>> cached_l;
    std::vector<std::vector<std::vector<bool>>> cached_r;
    cached_u.push_back(u);
    cached_d.push_back(d);
    cached_l.push_back(l);
    cached_r.push_back(r);
    int max_cached = 1;

    bfs.push_back(std::make_pair(-1, 0));
    bfs_cnt.push_back(0);

    int answer1 = 0;

    while (!bfs.empty()) {
        assert(bfs.size() == bfs_cnt.size());

        int cur_X = bfs.front().second;
        int cur_Y = bfs.front().first;
        int cnt = bfs_cnt.front();
        bfs.pop_front();
        bfs_cnt.pop_front();

        if (cur_X == GOAL_X && cur_Y == GOAL_Y) {
            answer1 = cnt + 1;
            break;
        } else {
            // If map is not cached, generate it!
            if (cnt + 1 == max_cached) {
                // Update all blizzards
                std::vector<std::vector<bool>> tmp_u(ROW, std::vector<bool>(COL, false));
                std::vector<std::vector<bool>> tmp_d(ROW, std::vector<bool>(COL, false));
                std::vector<std::vector<bool>> tmp_l(ROW, std::vector<bool>(COL, false));
                std::vector<std::vector<bool>> tmp_r(ROW, std::vector<bool>(COL, false));

                for (int i = 0; i < ROW; i++) {
                    for (int j = 0; j < COL; j++) {
                        if (cached_u[cnt][i][j]) {
                            if (i == 0)
                                tmp_u[ROW - 1][j] = true;
                            else
                                tmp_u[i - 1][j] = true;
                        }

                        if (cached_d[cnt][i][j]) {
                            if (i == ROW - 1)
                                tmp_d[0][j] = true;
                            else
                                tmp_d[i + 1][j] = true;
                        }

                        if (cached_l[cnt][i][j]) {
                            if (j == 0)
                                tmp_l[i][COL - 1] = true;
                            else
                                tmp_l[i][j - 1] = true;
                        }

                        if (cached_r[cnt][i][j]) {
                            if (j == COL - 1)
                                tmp_r[i][0] = true;
                            else
                                tmp_r[i][j + 1] = true;
                        }
                    }
                }

                cached_u.push_back(tmp_u);
                cached_d.push_back(tmp_d);
                cached_l.push_back(tmp_l);
                cached_r.push_back(tmp_r);

                max_cached++;
                assert(cnt + 2 == max_cached && max_cached == cached_u.size());
            }

            // try to move down
            if (cur_Y < ROW - 1 && !cached_d[cnt + 1][cur_Y + 1][cur_X] && !cached_u[cnt + 1][cur_Y + 1][cur_X] &&
                !cached_l[cnt + 1][cur_Y + 1][cur_X] && !cached_r[cnt + 1][cur_Y + 1][cur_X]) {
                bool can_push = true;
                for (size_t k = 0; k < bfs.size(); k++) {
                    if (bfs[k].first == cur_Y + 1 && bfs[k].second == cur_X && bfs_cnt[k] == cnt + 1) {
                        can_push = false;
                        break;
                    }
                }

                if (can_push) {
                    bfs.push_back(std::make_pair(cur_Y + 1, cur_X));
                    bfs_cnt.push_back(cnt + 1);
                }
            }

            if (cur_Y >= 0) {
                // try to move up
                if (cur_Y > 0 && !cached_d[cnt + 1][cur_Y - 1][cur_X] && !cached_u[cnt + 1][cur_Y - 1][cur_X] &&
                    !cached_l[cnt + 1][cur_Y - 1][cur_X] && !cached_r[cnt + 1][cur_Y - 1][cur_X]) {
                    bool can_push = true;
                    for (size_t k = 0; k < bfs.size(); k++) {
                        if (bfs[k].first == cur_Y - 1 && bfs[k].second == cur_X && bfs_cnt[k] == cnt + 1) {
                            can_push = false;
                            break;
                        }
                    }

                    if (can_push) {
                        bfs.push_back(std::make_pair(cur_Y - 1, cur_X));
                        bfs_cnt.push_back(cnt + 1);
                    }
                }

                // try to move left
                if (cur_X > 0 && !cached_d[cnt + 1][cur_Y][cur_X - 1] && !cached_u[cnt + 1][cur_Y][cur_X - 1] &&
                    !cached_l[cnt + 1][cur_Y][cur_X - 1] && !cached_r[cnt + 1][cur_Y][cur_X - 1]) {
                    bool can_push = true;
                    for (size_t k = 0; k < bfs.size(); k++) {
                        if (bfs[k].first == cur_Y && bfs[k].second == cur_X - 1 && bfs_cnt[k] == cnt + 1) {
                            can_push = false;
                            break;
                        }
                    }

                    if (can_push) {
                        bfs.push_back(std::make_pair(cur_Y, cur_X - 1));
                        bfs_cnt.push_back(cnt + 1);
                    }
                }

                // try to move right
                if (cur_X < COL - 1 && !cached_d[cnt + 1][cur_Y][cur_X + 1] && !cached_u[cnt + 1][cur_Y][cur_X + 1] &&
                    !cached_l[cnt + 1][cur_Y][cur_X + 1] && !cached_r[cnt + 1][cur_Y][cur_X + 1]) {
                    bool can_push = true;
                    for (size_t k = 0; k < bfs.size(); k++) {
                        if (bfs[k].first == cur_Y && bfs[k].second == cur_X + 1 && bfs_cnt[k] == cnt + 1) {
                            can_push = false;
                            break;
                        }
                    }

                    if (can_push) {
                        bfs.push_back(std::make_pair(cur_Y, cur_X + 1));
                        bfs_cnt.push_back(cnt + 1);
                    }
                }

                // wait
                if (!cached_d[cnt + 1][cur_Y][cur_X] && !cached_u[cnt + 1][cur_Y][cur_X] &&
                    !cached_l[cnt + 1][cur_Y][cur_X] && !cached_r[cnt + 1][cur_Y][cur_X]) {
                    bool can_push = true;
                    for (size_t k = 0; k < bfs.size(); k++) {
                        if (bfs[k].first == cur_Y && bfs[k].second == cur_X && bfs_cnt[k] == cnt + 1) {
                            can_push = false;
                            break;
                        }
                    }

                    if (can_push) {
                        bfs.push_back(std::make_pair(cur_Y, cur_X));
                        bfs_cnt.push_back(cnt + 1);
                    }
                }
            } else {
                // wait
                bfs.push_back(std::make_pair(cur_Y, cur_X));
                bfs_cnt.push_back(cnt + 1);
            }
        }
    }

    std::cout << answer1 << std::endl;

    // Head back
    GOAL_X = 0, GOAL_Y = 0;

    bfs.clear();
    bfs_cnt.clear();
    bfs.push_back(std::make_pair(ROW, COL - 1));
    bfs_cnt.push_back(answer1);

    int answer2 = 0;

    while (!bfs.empty()) {
        assert(bfs.size() == bfs_cnt.size());

        int cur_X = bfs.front().second;
        int cur_Y = bfs.front().first;
        int cnt = bfs_cnt.front();
        bfs.pop_front();
        bfs_cnt.pop_front();

        if (cur_X == GOAL_X && cur_Y == GOAL_Y) {
            answer2 = cnt + 1;
            break;
        } else {
            // If map is not cached, generate it!
            if (cnt + 1 == max_cached) {
                // Update all blizzards
                std::vector<std::vector<bool>> tmp_u(ROW, std::vector<bool>(COL, false));
                std::vector<std::vector<bool>> tmp_d(ROW, std::vector<bool>(COL, false));
                std::vector<std::vector<bool>> tmp_l(ROW, std::vector<bool>(COL, false));
                std::vector<std::vector<bool>> tmp_r(ROW, std::vector<bool>(COL, false));

                for (int i = 0; i < ROW; i++) {
                    for (int j = 0; j < COL; j++) {
                        if (cached_u[cnt][i][j]) {
                            if (i == 0)
                                tmp_u[ROW - 1][j] = true;
                            else
                                tmp_u[i - 1][j] = true;
                        }

                        if (cached_d[cnt][i][j]) {
                            if (i == ROW - 1)
                                tmp_d[0][j] = true;
                            else
                                tmp_d[i + 1][j] = true;
                        }

                        if (cached_l[cnt][i][j]) {
                            if (j == 0)
                                tmp_l[i][COL - 1] = true;
                            else
                                tmp_l[i][j - 1] = true;
                        }

                        if (cached_r[cnt][i][j]) {
                            if (j == COL - 1)
                                tmp_r[i][0] = true;
                            else
                                tmp_r[i][j + 1] = true;
                        }
                    }
                }

                cached_u.push_back(tmp_u);
                cached_d.push_back(tmp_d);
                cached_l.push_back(tmp_l);
                cached_r.push_back(tmp_r);

                max_cached++;
                assert(cnt + 2 == max_cached && max_cached == cached_u.size());
            }

            // try to move up
            if (cur_Y > 0 && !cached_d[cnt + 1][cur_Y - 1][cur_X] && !cached_u[cnt + 1][cur_Y - 1][cur_X] &&
                !cached_l[cnt + 1][cur_Y - 1][cur_X] && !cached_r[cnt + 1][cur_Y - 1][cur_X]) {
                bool can_push = true;
                for (size_t k = 0; k < bfs.size(); k++) {
                    if (bfs[k].first == cur_Y - 1 && bfs[k].second == cur_X && bfs_cnt[k] == cnt + 1) {
                        can_push = false;
                        break;
                    }
                }

                if (can_push) {
                    bfs.push_back(std::make_pair(cur_Y - 1, cur_X));
                    bfs_cnt.push_back(cnt + 1);
                }
            }

            if (cur_Y < ROW) {
                // try to move down
                if (cur_Y < ROW - 1 && !cached_d[cnt + 1][cur_Y + 1][cur_X] && !cached_u[cnt + 1][cur_Y + 1][cur_X] &&
                    !cached_l[cnt + 1][cur_Y + 1][cur_X] && !cached_r[cnt + 1][cur_Y + 1][cur_X]) {
                    bool can_push = true;
                    for (size_t k = 0; k < bfs.size(); k++) {
                        if (bfs[k].first == cur_Y + 1 && bfs[k].second == cur_X && bfs_cnt[k] == cnt + 1) {
                            can_push = false;
                            break;
                        }
                    }

                    if (can_push) {
                        bfs.push_back(std::make_pair(cur_Y + 1, cur_X));
                        bfs_cnt.push_back(cnt + 1);
                    }
                }

                // try to move left
                if (cur_X > 0 && !cached_d[cnt + 1][cur_Y][cur_X - 1] && !cached_u[cnt + 1][cur_Y][cur_X - 1] &&
                    !cached_l[cnt + 1][cur_Y][cur_X - 1] && !cached_r[cnt + 1][cur_Y][cur_X - 1]) {
                    bool can_push = true;
                    for (size_t k = 0; k < bfs.size(); k++) {
                        if (bfs[k].first == cur_Y && bfs[k].second == cur_X - 1 && bfs_cnt[k] == cnt + 1) {
                            can_push = false;
                            break;
                        }
                    }

                    if (can_push) {
                        bfs.push_back(std::make_pair(cur_Y, cur_X - 1));
                        bfs_cnt.push_back(cnt + 1);
                    }
                }

                // try to move right
                if (cur_X < COL - 1 && !cached_d[cnt + 1][cur_Y][cur_X + 1] && !cached_u[cnt + 1][cur_Y][cur_X + 1] &&
                    !cached_l[cnt + 1][cur_Y][cur_X + 1] && !cached_r[cnt + 1][cur_Y][cur_X + 1]) {
                    bool can_push = true;
                    for (size_t k = 0; k < bfs.size(); k++) {
                        if (bfs[k].first == cur_Y && bfs[k].second == cur_X + 1 && bfs_cnt[k] == cnt + 1) {
                            can_push = false;
                            break;
                        }
                    }

                    if (can_push) {
                        bfs.push_back(std::make_pair(cur_Y, cur_X + 1));
                        bfs_cnt.push_back(cnt + 1);
                    }
                }

                // wait
                if (!cached_d[cnt + 1][cur_Y][cur_X] && !cached_u[cnt + 1][cur_Y][cur_X] &&
                    !cached_l[cnt + 1][cur_Y][cur_X] && !cached_r[cnt + 1][cur_Y][cur_X]) {
                    bool can_push = true;
                    for (size_t k = 0; k < bfs.size(); k++) {
                        if (bfs[k].first == cur_Y && bfs[k].second == cur_X && bfs_cnt[k] == cnt + 1) {
                            can_push = false;
                            break;
                        }
                    }

                    if (can_push) {
                        bfs.push_back(std::make_pair(cur_Y, cur_X));
                        bfs_cnt.push_back(cnt + 1);
                    }
                }
            } else {
                // wait
                bfs.push_back(std::make_pair(cur_Y, cur_X));
                bfs_cnt.push_back(cnt + 1);
            }
        }
    }

    std::cout << answer2 << std::endl;

    // Move forward again
    GOAL_X = COL - 1, GOAL_Y = ROW - 1;

    bfs.clear();
    bfs_cnt.clear();
    bfs.push_back(std::make_pair(-1, 0));
    bfs_cnt.push_back(answer2);

    int answer3 = 0;

    while (!bfs.empty()) {
        assert(bfs.size() == bfs_cnt.size());

        int cur_X = bfs.front().second;
        int cur_Y = bfs.front().first;
        int cnt = bfs_cnt.front();
        bfs.pop_front();
        bfs_cnt.pop_front();

        if (cur_X == GOAL_X && cur_Y == GOAL_Y) {
            answer3 = cnt + 1;
            break;
        } else {
            // If map is not cached, generate it!
            if (cnt + 1 == max_cached) {
                // Update all blizzards
                std::vector<std::vector<bool>> tmp_u(ROW, std::vector<bool>(COL, false));
                std::vector<std::vector<bool>> tmp_d(ROW, std::vector<bool>(COL, false));
                std::vector<std::vector<bool>> tmp_l(ROW, std::vector<bool>(COL, false));
                std::vector<std::vector<bool>> tmp_r(ROW, std::vector<bool>(COL, false));

                for (int i = 0; i < ROW; i++) {
                    for (int j = 0; j < COL; j++) {
                        if (cached_u[cnt][i][j]) {
                            if (i == 0)
                                tmp_u[ROW - 1][j] = true;
                            else
                                tmp_u[i - 1][j] = true;
                        }

                        if (cached_d[cnt][i][j]) {
                            if (i == ROW - 1)
                                tmp_d[0][j] = true;
                            else
                                tmp_d[i + 1][j] = true;
                        }

                        if (cached_l[cnt][i][j]) {
                            if (j == 0)
                                tmp_l[i][COL - 1] = true;
                            else
                                tmp_l[i][j - 1] = true;
                        }

                        if (cached_r[cnt][i][j]) {
                            if (j == COL - 1)
                                tmp_r[i][0] = true;
                            else
                                tmp_r[i][j + 1] = true;
                        }
                    }
                }

                cached_u.push_back(tmp_u);
                cached_d.push_back(tmp_d);
                cached_l.push_back(tmp_l);
                cached_r.push_back(tmp_r);

                max_cached++;
                assert(cnt + 2 == max_cached && max_cached == cached_u.size());
            }

            // try to move down
            if (cur_Y < ROW - 1 && !cached_d[cnt + 1][cur_Y + 1][cur_X] && !cached_u[cnt + 1][cur_Y + 1][cur_X] &&
                !cached_l[cnt + 1][cur_Y + 1][cur_X] && !cached_r[cnt + 1][cur_Y + 1][cur_X]) {
                bool can_push = true;
                for (size_t k = 0; k < bfs.size(); k++) {
                    if (bfs[k].first == cur_Y + 1 && bfs[k].second == cur_X && bfs_cnt[k] == cnt + 1) {
                        can_push = false;
                        break;
                    }
                }

                if (can_push) {
                    bfs.push_back(std::make_pair(cur_Y + 1, cur_X));
                    bfs_cnt.push_back(cnt + 1);
                }
            }

            if (cur_Y >= 0) {
                // try to move up
                if (cur_Y > 0 && !cached_d[cnt + 1][cur_Y - 1][cur_X] && !cached_u[cnt + 1][cur_Y - 1][cur_X] &&
                    !cached_l[cnt + 1][cur_Y - 1][cur_X] && !cached_r[cnt + 1][cur_Y - 1][cur_X]) {
                    bool can_push = true;
                    for (size_t k = 0; k < bfs.size(); k++) {
                        if (bfs[k].first == cur_Y - 1 && bfs[k].second == cur_X && bfs_cnt[k] == cnt + 1) {
                            can_push = false;
                            break;
                        }
                    }

                    if (can_push) {
                        bfs.push_back(std::make_pair(cur_Y - 1, cur_X));
                        bfs_cnt.push_back(cnt + 1);
                    }
                }

                // try to move left
                if (cur_X > 0 && !cached_d[cnt + 1][cur_Y][cur_X - 1] && !cached_u[cnt + 1][cur_Y][cur_X - 1] &&
                    !cached_l[cnt + 1][cur_Y][cur_X - 1] && !cached_r[cnt + 1][cur_Y][cur_X - 1]) {
                    bool can_push = true;
                    for (size_t k = 0; k < bfs.size(); k++) {
                        if (bfs[k].first == cur_Y && bfs[k].second == cur_X - 1 && bfs_cnt[k] == cnt + 1) {
                            can_push = false;
                            break;
                        }
                    }

                    if (can_push) {
                        bfs.push_back(std::make_pair(cur_Y, cur_X - 1));
                        bfs_cnt.push_back(cnt + 1);
                    }
                }

                // try to move right
                if (cur_X < COL - 1 && !cached_d[cnt + 1][cur_Y][cur_X + 1] && !cached_u[cnt + 1][cur_Y][cur_X + 1] &&
                    !cached_l[cnt + 1][cur_Y][cur_X + 1] && !cached_r[cnt + 1][cur_Y][cur_X + 1]) {
                    bool can_push = true;
                    for (size_t k = 0; k < bfs.size(); k++) {
                        if (bfs[k].first == cur_Y && bfs[k].second == cur_X + 1 && bfs_cnt[k] == cnt + 1) {
                            can_push = false;
                            break;
                        }
                    }

                    if (can_push) {
                        bfs.push_back(std::make_pair(cur_Y, cur_X + 1));
                        bfs_cnt.push_back(cnt + 1);
                    }
                }

                // wait
                if (!cached_d[cnt + 1][cur_Y][cur_X] && !cached_u[cnt + 1][cur_Y][cur_X] &&
                    !cached_l[cnt + 1][cur_Y][cur_X] && !cached_r[cnt + 1][cur_Y][cur_X]) {
                    bool can_push = true;
                    for (size_t k = 0; k < bfs.size(); k++) {
                        if (bfs[k].first == cur_Y && bfs[k].second == cur_X && bfs_cnt[k] == cnt + 1) {
                            can_push = false;
                            break;
                        }
                    }

                    if (can_push) {
                        bfs.push_back(std::make_pair(cur_Y, cur_X));
                        bfs_cnt.push_back(cnt + 1);
                    }
                }
            } else {
                // wait
                bfs.push_back(std::make_pair(cur_Y, cur_X));
                bfs_cnt.push_back(cnt + 1);
            }
        }
    }

    std::cout << answer3 << std::endl;
}

int main() {
    // solve_A();
    solve_B();
    return 0;
}