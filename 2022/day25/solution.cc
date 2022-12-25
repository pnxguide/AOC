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

long f(std::string line) {
    long sum = 0;
    long mult = 1;

    for (int i = line.size() - 1; i >= 0; i--) {
        switch (line[i]) {
            case '=':
                sum += mult * -2;
                break;
            case '-':
                sum += mult * -1;
                break;
            case '0':
                sum += mult * 0;
                break;
            case '1':
                sum += mult * 1;
                break;
            case '2':
                sum += mult * 2;
                break;
        }
        mult *= 5;
    }
    return sum;
}

long max_digit_2(int digit) {
    std::string x = "2";
    for (size_t i = 0; i < digit-1; i++) x.push_back('=');
    return f(x);
}

long max_digit_1(int digit) {
    std::string x = "1";
    for (size_t i = 0; i < digit-1; i++) x.push_back('=');
    return f(x);
}

long max_digit_0(int digit) {
    std::string x = "0";
    for (size_t i = 0; i < digit-1; i++) x.push_back('=');
    return f(x);
}

long max_digit_n1(int digit) {
    std::string x = "-";
    for (size_t i = 0; i < digit-1; i++) x.push_back('=');
    return f(x);
}

long max_digit_n2(int digit) {
    std::string x = "=";
    for (size_t i = 0; i < digit-1; i++) x.push_back('=');
    return f(x);
}

void solve_A() {
    // Read an input file
    std::ifstream input_file("day25/input.txt");
    std::string line;

    long accum = 0;

    while (std::getline(input_file, line)) {
        accum += f(line);
    }
    std::cout << accum << std::endl;

    std::string answer;

    // find the first digit
    long pow = 1;
    long a = 0, x = 0;
    long prev_x = 0;
    while (x < accum) {
        long mult = std::pow(5l, pow++);
        prev_x = x;
        x = mult - a + 3;
        a += mult * -2;
    }

    for (long digit = pow-1; digit > 0; digit--) {
        if (accum >= max_digit_2(digit)) {
            answer.push_back('2');
            accum -= 2 * std::pow(5l, digit-1);
        } else if (accum >= max_digit_1(digit)) {
            answer.push_back('1');
            accum -= 1 * std::pow(5l, digit-1);
        } else if (accum >= max_digit_0(digit)) {
            answer.push_back('0');
            accum -= 0 * std::pow(5l, digit-1);
        } else if (accum >= max_digit_n1(digit)) {
            answer.push_back('-');
            accum -= -1 * std::pow(5l, digit-1);
        } else if (accum >= max_digit_n2(digit)) {
            answer.push_back('=');
            accum -= -2 * std::pow(5l, digit-1);
        }
    }

    std::cout << answer << std::endl;
}

void solve_B() {
    // Read an input file
    std::ifstream input_file("day25/input.txt");
    std::string line;
}

int main() {
    solve_A();
    // solve_B();
    return 0;
}