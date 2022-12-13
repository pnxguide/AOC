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
  std::string line;
  input_file >> line;

  for (size_t i = 0; i < line.size() - 4; i++)
  {
    if (line[i] != line[i+1] && line[i] != line[i+2] && line[i] != line[i+3]
      && line[i+1] != line[i+2] && line[i+1] != line[i+3]
      && line[i+2] != line[i+3])
    {
      std::cout << (i + 4) << std::endl;
      break;
    }
  }
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());
  std::string line;
  input_file >> line;

  for (size_t i = 0; i < line.size() - 14; i++)
  {
    bool bad = false;

    for (size_t j = 0; (j < 14) && !bad; j++)
    {
      for (size_t k = j+1; (k < 14) && !bad; k++)
      {
        if (line[i+j] == line[i+k])
        {
          bad = true;
          break;
        }
      }
    }

    if (!bad)
    {
      std::cout << (i + 14) << std::endl;
      break;
    }
  }
}

int main()
{
  // solve_A();
  solve_B();
  return 0;
}