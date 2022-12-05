#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <deque>

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
  std::vector< std::deque<char> > stacks(9); 

  // Read initial state
  for (size_t i = 0; i < 8; i++)
  {
    std::getline(input_file, line);
    for (size_t j = 0; j < 9; j++)
    {
      size_t char_index = 1 + (j * 4);
      if (line.size() < char_index) break;
      if (line[char_index] != ' ')
      {
        stacks[j].push_back(line[char_index]);
      }
    }
  }

  // Read two unnecessary lines
  std::getline(input_file, line);
  std::getline(input_file, line);

  // Read commands
  while (std::getline(input_file, line))
  {
    std::vector<std::string> tokens;
    tokenize(line, ' ', tokens);
    assert(tokens.size() == 6);

    int times = std::stoi(tokens[1]);
    int from  = std::stoi(tokens[3]) - 1;
    int to    = std::stoi(tokens[5]) - 1;

    for (int i = 0; i < times; i++)
    {
      stacks[to].push_front(stacks[from].front());
      stacks[from].pop_front();
    }
  }

  // Output
  for (size_t i = 0; i < 9; i++)
  {
    assert(stacks.size() >= 1);
    std::cout << stacks[i].front();
  }
  std::cout << std::endl;
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());

  size_t count = 0;

  std::string line;
  std::vector< std::deque<char> > stacks(9); 

  // Read initial state
  for (size_t i = 0; i < 8; i++)
  {
    std::getline(input_file, line);
    for (size_t j = 0; j < 9; j++)
    {
      size_t char_index = 1 + (j * 4);
      if (line.size() < char_index) break;
      if (line[char_index] != ' ')
      {
        stacks[j].push_back(line[char_index]);
      }
    }
  }

  // Read two unnecessary lines
  std::getline(input_file, line);
  std::getline(input_file, line);

  // Read commands
  while (std::getline(input_file, line))
  {
    std::vector<std::string> tokens;
    tokenize(line, ' ', tokens);
    assert(tokens.size() == 6);

    int times = std::stoi(tokens[1]);
    int from  = std::stoi(tokens[3]) - 1;
    int to    = std::stoi(tokens[5]) - 1;

    std::deque<char> tmp;
    for (int i = 0; i < times; i++)
    {
      tmp.push_front(stacks[from].front());
      stacks[from].pop_front();
    }

    for (int i = 0; i < times; i++)
    {
      stacks[to].push_front(tmp.front());
      tmp.pop_front();
    }
  }

  // Output
  for (size_t i = 0; i < 9; i++)
  {
    assert(stacks.size() >= 1);
    std::cout << stacks[i].front();
  }
  std::cout << std::endl;
}

int main()
{
  // solve_A();
  solve_B();
  return 0;
}