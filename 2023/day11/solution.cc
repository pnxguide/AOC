#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <deque>
#include <set>
#include <unordered_map>

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
  std::string line;

  std::vector< std::deque<int> > items(8, std::deque<int>());
  std::vector<int> is_mult(8);
  std::vector<int> values(8);
  std::vector<int> test(8);
  std::vector<int> branch_true(8);
  std::vector<int> branch_false(8);

  while (std::getline(input_file, line))
  {
    std::vector< std::string > tokens;
    tokens.clear();
    tokenize(line, ' ', tokens);

    int cur_index = 0;

    // New entry
    if (tokens[0] == "Monkey")
    {
      cur_index = std::stoi(tokens[1]);

      std::getline(input_file, line);
      tokens.clear();
      tokenize(line, ' ', tokens);

      for (int i = 2; i < tokens.size(); i++)
      {
        items[cur_index].push_back(std::stoi(tokens[i]));
      }

      std::getline(input_file, line);
      tokens.clear();
      tokenize(line, ' ', tokens);

      if (tokens[5] == "old") is_mult[cur_index] = 2;
      else if (tokens[4] == "*") is_mult[cur_index] = 1;
      else is_mult[cur_index] = 0;
      if (tokens[5] != "old") values[cur_index] = (std::stoi(tokens[5]));

      std::getline(input_file, line);
      tokens.clear();
      tokenize(line, ' ', tokens);
      
      test[cur_index] = (std::stoi(tokens[3]));

      std::getline(input_file, line);
      tokens.clear();
      tokenize(line, ' ', tokens);

      branch_true[cur_index] = (std::stoi(tokens[5]));

      std::getline(input_file, line);
      tokens.clear();
      tokenize(line, ' ', tokens);

      branch_false[cur_index] = (std::stoi(tokens[5]));
    }     
  }

  std::vector<int> times(8);

  for (int round= 0; round < 20; round++)
  {
    for (int cur_monkey = 0; cur_monkey < items.size(); cur_monkey++)
    {
      int worry = 0;
      while (!items[cur_monkey].empty())
      {
        worry = items[cur_monkey].front();

        if (is_mult[cur_monkey] == 1) worry *= values[cur_monkey];
        else if (is_mult[cur_monkey] == 2) {
          worry = worry * worry;
        }
        else worry += values[cur_monkey];
        worry /= 3;

        if (worry % test[cur_monkey] == 0)
        {
          items[branch_true[cur_monkey]].push_back(worry);
        }

        else 
        {
          items[branch_false[cur_monkey]].push_back(worry);
        }

        times[cur_monkey]++;
        items[cur_monkey].pop_front();
      }
    }
  }

  for (int i = 0; i < 8; i++)
  {
    std::cout << times[i] << std::endl;
  }
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());
  std::string line;

  std::vector< std::deque<size_t> > items(8, std::deque<size_t>());
  std::vector<size_t> is_mult(8);
  std::vector<size_t> values(8);
  std::vector<size_t> test(8);
  std::vector<size_t> branch_true(8);
  std::vector<size_t> branch_false(8);

  while (std::getline(input_file, line))
  {
    std::vector< std::string > tokens;
    tokens.clear();
    tokenize(line, ' ', tokens);

    size_t cur_index = 0;

    // New entry
    if (tokens[0] == "Monkey")
    {
      cur_index = std::stoi(tokens[1]);

      std::getline(input_file, line);
      tokens.clear();
      tokenize(line, ' ', tokens);

      for (size_t i = 2; i < tokens.size(); i++)
      {
        items[cur_index].push_back(std::stoi(tokens[i]));
      }

      std::getline(input_file, line);
      tokens.clear();
      tokenize(line, ' ', tokens);

      if (tokens[5] == "old") is_mult[cur_index] = 2;
      else if (tokens[4] == "*") is_mult[cur_index] = 1;
      else is_mult[cur_index] = 0;
      if (tokens[5] != "old") values[cur_index] = (std::stoi(tokens[5]));

      std::getline(input_file, line);
      tokens.clear();
      tokenize(line, ' ', tokens);
      
      test[cur_index] = (std::stoi(tokens[3]));

      std::getline(input_file, line);
      tokens.clear();
      tokenize(line, ' ', tokens);

      branch_true[cur_index] = (std::stoi(tokens[5]));

      std::getline(input_file, line);
      tokens.clear();
      tokenize(line, ' ', tokens);

      branch_false[cur_index] = (std::stoi(tokens[5]));
    }     
  }

  std::vector<size_t> times(8);

  for (size_t round= 0; round < 10000; round++)
  {
    for (size_t cur_monkey = 0; cur_monkey < items.size(); cur_monkey++)
    {
      size_t worry = 0;
      while (!items[cur_monkey].empty())
      {
        worry = items[cur_monkey].front();

        if (is_mult[cur_monkey] == 1) worry *= values[cur_monkey];
        else if (is_mult[cur_monkey] == 2) {
          worry = worry * worry;
        }
        else worry += values[cur_monkey];
        worry %= 7*19*13*3*2*11*17*5;

        if (worry % test[cur_monkey] == 0)
        {
          items[branch_true[cur_monkey]].push_back(worry);
        }

        else 
        {
          items[branch_false[cur_monkey]].push_back(worry);
        }

        times[cur_monkey]++;
        items[cur_monkey].pop_front();
      }
    }
  }

  for (size_t i = 0; i < 8; i++)
  {
    std::cout << times[i] << std::endl;
  }
}

int main()
{
  // solve_A();
  solve_B();
  return 0;
}