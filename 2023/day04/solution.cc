#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

void tokenize(const std::string &s, const char delim,
            std::vector<std::string> &out)
{
    std::string::size_type beg = 0;
    for (auto end = 0; (end = s.find(delim, end)) != std::string::npos; ++end)
    {
        out.push_back(s.substr(beg, end - beg));
        beg = end + 1;
    }
 
    out.push_back(s.substr(beg));
}

void solve_A()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());

  size_t count = 0;

  std::string line;
  while (input_file >> line)
  {
    std::vector<std::string> tokens;
    tokenize(line, ',', tokens);
    assert(tokens.size() == 2);
    
    std::vector<std::string> ranges_str;
    tokenize(tokens[0], '-', ranges_str);
    assert(ranges_str.size() == 2);

    std::vector<int> ranges_x(2);
    ranges_x[0] = std::stoi(ranges_str[0]);
    ranges_x[1] = std::stoi(ranges_str[1]);

    ranges_str.clear();
    tokenize(tokens[1], '-', ranges_str);
    assert(ranges_str.size() == 2);

    std::vector<int> ranges_y(2);
    ranges_y[0] = std::stoi(ranges_str[0]);
    ranges_y[1] = std::stoi(ranges_str[1]);

    if (ranges_x[0] <= ranges_y[0] && ranges_x[1] >= ranges_y[1])
    {
      count++;
    }

    else if (ranges_y[0] <= ranges_x[0] && ranges_y[1] >= ranges_x[1])
    {
      count++;
    }
  }

  // Output
  std::cout << count << std::endl;
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());

  size_t count = 0;

  std::string line;
  while (input_file >> line)
  {
    std::vector<std::string> tokens;
    tokenize(line, ',', tokens);
    assert(tokens.size() == 2);
    
    std::vector<std::string> ranges_str;
    tokenize(tokens[0], '-', ranges_str);
    assert(ranges_str.size() == 2);

    std::vector<int> ranges_x(2);
    ranges_x[0] = std::stoi(ranges_str[0]);
    ranges_x[1] = std::stoi(ranges_str[1]);

    ranges_str.clear();
    tokenize(tokens[1], '-', ranges_str);
    assert(ranges_str.size() == 2);

    std::vector<int> ranges_y(2);
    ranges_y[0] = std::stoi(ranges_str[0]);
    ranges_y[1] = std::stoi(ranges_str[1]);

    if (ranges_x[1] >= ranges_y[0] && ranges_y[1] >= ranges_x[0])
    {
      count++;
    }

    else if (ranges_y[1] >= ranges_x[0] && ranges_x[1] >= ranges_y[0])
    {
      count++;
    }
  }

  // Output
  std::cout << count << std::endl;
}

int main()
{
  // solve_A();
  solve_B();
  return 0;
}