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

  std::deque<int> accum;
  size_t cycle = 0;

  int X = 0;
  int str = 0;

  accum.push_back(1);

  while (!accum.empty())
  {
    bool eof = !std::getline(input_file, line);

    cycle++;

    if (!accum.empty())
    {
      X += accum.front();
      accum.pop_front();
    }

    std::vector< std::string > tokens;
    tokenize(line, ' ', tokens);

    if (!eof)
    {
      if (tokens[0] == "noop")
      {
        accum.push_back(0);
      }

      else if (tokens[0] == "addx")
      {
        accum.push_back(0);
        accum.push_back(std::stoi(tokens[1]));
      }
    }

    if (cycle == 20 || cycle == 60 || cycle == 100 ||
      cycle == 140 || cycle == 180 || cycle == 220)
    {
      std::cout << cycle << " " << X << std::endl;
      str += (cycle * X);
    }
  }

  std::cout << str << std::endl;
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());
  std::string line;

  std::deque<int> accum;
  size_t cycle = 0;

  int X = 0;
  int str = 0;

  accum.push_back(1);

  std::vector<bool> ctr(240, false);

  while (!accum.empty())
  {
    bool eof = !std::getline(input_file, line);

    cycle++;

    if (!accum.empty())
    {
      X += accum.front();
      accum.pop_front();
    }

    std::vector< std::string > tokens;
    tokenize(line, ' ', tokens);

    if (!eof)
    {
      if (tokens[0] == "noop")
      {
        accum.push_back(0);
      }

      else if (tokens[0] == "addx")
      {
        accum.push_back(0);
        accum.push_back(std::stoi(tokens[1]));
      }
    }

    ctr[cycle] = ((cycle % 40) >= X) && 
      ((cycle % 40) <= X + 2);

    if (cycle == 20 || cycle == 60 || cycle == 100 ||
      cycle == 140 || cycle == 180 || cycle == 220)
    {
      std::cout << cycle << " " << X << std::endl;
      str += (cycle * X);
    }
  }

  for (size_t i = 0; i < 6; i++)
  {
    for (size_t j = 0; j < 40; j++)
    {
      std::cout << (ctr[i*40+j] ? "#" : ".");
    }
    std::cout << std::endl;
  }
}

int main()
{
  // solve_A();
  solve_B();
  return 0;
}