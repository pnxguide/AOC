#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

void solve_A()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());

  // Read each line until reach EoF
  std::string line;
  uint64_t sum = 0, max = 0;
  while (std::getline(input_file, line))
  {
    // Proceed to the next elf
    if (line == "")
    {
      if (sum > max)
      {
        max = sum;
      }

      sum = 0;
    }

    // Accumulate the sum
    else
    {
      sum += stoul(line);
    }
  }

  // Check the last elf
  if (sum > max)
  {
    max = sum;
  }

  std::cout << max << std::endl;
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());

  // Read each line until reach EoF
  std::string line;
  uint64_t sum = 0, max1 = 0, max2 = 0, max3 = 0;
  while (std::getline(input_file, line))
  {
    // Proceed to the next elf
    if (line == "")
    {
      if (sum >= max1)
      {
        max3 = max2;
        max2 = max1;
        max1 = sum;
      }

      else if (sum >= max2)
      {
        max3 = max2;
        max2 = sum;
      }

      else if (sum >= max3)
      {
        max3 = sum;
      }

      sum = 0;
    }

    // Accumulate the sum
    else
    {
      sum += stoul(line);
    }
  }

  // Check the last elf
  if (sum >= max1)
  {
    max3 = max2;
    max2 = max1;
    max1 = sum;
  }

  else if (sum >= max2)
  {
    max3 = max2;
    max2 = sum;
  }

  else if (sum >= max3)
  {
    max3 = sum;
  }

  std::cout << (max1 + max2 + max3) << std::endl;
}

int main()
{
  solve_A();
  solve_B();
  return 0;
}