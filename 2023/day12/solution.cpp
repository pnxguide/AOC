#include <iostream>
#include <fstream>
#include <deque>
#include <set>
#include <unordered_map>

long fff(std::string puzzle, std::vector<int> trace) {
    // Place the largest one first
    std::vector<int> sorted = trace;
    std::sort(sorted.begin(), sorted.end(), std::greater{});
    std::vector<int> orders;
    std::vector<bool> visited(trace.size());
    for (int i = 0; i < sorted.size(); i++) {
        for (int j = 0; j < trace.size(); j++) {
            if (visited[j] == false && trace[j] == sorted[i]) {
                orders.push_back(j);
                visited[j] = true;
                break;
            }
        }
    }

    long combi = 0;
    std::deque<std::tuple<std::string, int>> dfs;
    dfs.push_back({puzzle, 0});

    while (!dfs.empty()) {
        std::tuple<std::string, int> cur = dfs.back();
        dfs.pop_back();

        int cur_index = std::get<1>(cur);
        if (cur_index == orders.size()) {
            std::cout << std::get<0>(cur) << std::endl;
            combi++;
            continue;
        }

        int cur_trace = trace[orders[cur_index]];

        // Check left
        int left_required = 0;
        for (int k = 0; k < orders[cur_index]; k++) {
            left_required += trace[k];
            left_required += 1;
        }

        // Check right
        int right_required = 0;
        for (int k = orders[cur_index] + 1; k < trace.size(); k++) {
            right_required += trace[k];
            right_required += 1;
        }

        // Try placing in different places
        for (int j = left_required; j <= (puzzle.size() - cur_trace - right_required); j++) {
            std::string cur_puzzle = std::get<0>(cur);
            int start = j;

            // Check immediate left
            if (start > 0) {
                if (cur_puzzle[start - 1] == '#') {
                    continue;
                } else {
                    cur_puzzle[start - 1] = '.';
                }
            }

            // Check immediate right
            if (start + cur_trace < puzzle.size()) {
                if (cur_puzzle[start + cur_trace] == '#') {
                    continue;
                } else {
                    cur_puzzle[start + cur_trace] = '.';
                }
            }

            // Try placing here
            bool is_good = true;
            for (int k = 0; k < cur_trace; k++) {
                if (!(cur_puzzle[start + k] == '?' || cur_puzzle[start + k] == '#')) {
                    is_good = false;
                    break;
                } else {
                    cur_puzzle[start + k] = '#';
                }
            }
            if (is_good) {
                dfs.push_back({cur_puzzle, cur_index + 1});
            }
        }
    }

    return combi;
}

int main() {
    long sum = 0;

    std::ifstream infile("day12/input");

    std::string puzzle;
    while (infile >> puzzle) {
        std::vector<int> trace;
        char line[64];
        infile >> line;
        char *token = std::strtok(line, ",");
        while (token) {
            std::string tk(token);
            trace.push_back(std::stoi(tk));
            token = std::strtok(nullptr, ",");
        }

        // Part 2
        puzzle = puzzle + "?" + puzzle + "?" + puzzle + "?" + puzzle + "?" + puzzle;
        int trace_size = trace.size();
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < trace_size; j++) {
                trace.push_back(trace[j]); 
            }
        }

    }

    std::cout << sum << std::endl;
    
    return 0;
}
