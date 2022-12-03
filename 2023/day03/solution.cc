#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

void solve_A()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());

  size_t sum = 0;

  std::string line;
  while (input_file >> line)
  {
    size_t half_size = line.size() / 2;
    for (size_t i = 0; i < half_size; i++)
    {
      for (size_t j = 0; j < half_size; j++)
      {
        if (line[i] == line[j + half_size])
        {
          if (line[i] > 0x60)
          {
            sum += line[i] - 0x60;
            std::cout << line[i] << " " << line[i] - 0x60 << std::endl;
          }
          else 
          {
            sum += line[i] - 0x40 + 26;
            std::cout << line[i] << " " << line[i] - 0x40 + 26 << std::endl;
          }
          i = half_size;
          break;
        }
      }
    }
  }

  // Output
  std::cout << sum << std::endl;
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());

  size_t sum = 0;

  std::string line;
  
  for (size_t j = 0; j < 300; j += 3)
  {
    std::vector<size_t> count(53, 0);
    for (size_t l = 0; l < 3; l++)
    {
      // First half 150
      input_file >> line;
      std::vector<bool> occur(53, false);
      for (size_t i = 0; i < line.size(); i++)
      {
        if (line[i] > 0x60)
        {
          occur[line[i] - 0x60] = true;
        }

        else
        {
          occur[line[i] - 0x40 + 26] = true;
        }
      }

      for (size_t i = 0; i < 53; i++)
      {
        count[i] += occur[i];
      }
    }

    for (size_t i = 0; i < 53; i++)
    {
      if (count[i] == 3)
      {
        sum += i;
      }
    }
  }

  std::cout << sum << std::endl;
}

int main()
{
  // solve_A();
  solve_B();
  return 0;
}