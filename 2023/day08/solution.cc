#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <deque>
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

#define SIZE 99


void solve_A()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());
  std::string line;

  int arr[SIZE][SIZE];
  int point[SIZE][SIZE];
  for (size_t i = 0; i < SIZE; i++)
  {
    input_file >> line;
    for (size_t j = 0; j < SIZE; j++)
    {
      arr[i][j] = line[j] - '0';
      point[i][j] = 0;
    }
  }

  // Horizontal, left to right
  size_t max = 0;
  for (int i = 0; i < SIZE; i++)
  {
    point[i][0]++;
    max = arr[i][0];
    for (int j = 1; j < SIZE; j++)
    {
      if (arr[i][j] > max)
      {
        point[i][j]++;
        max = arr[i][j];
      }
    }
  }

  // Horizontal, right to left
  max = 0;
  for (int i = 0; i < SIZE; i++)
  {
    point[i][SIZE-1]++;
    max = arr[i][SIZE-1];
    for (int j = SIZE-2; j >= 0; j--)
    {
      if (arr[i][j] > max)
      {
        point[i][j]++;
        max = arr[i][j];
      }
    }
  }
  
  // Horizontal, left to right
  max = 0;
  for (int j = 0; j < SIZE; j++)
  {
    point[0][j]++;
    max = arr[0][j];
    for (int i = 1; i < SIZE; i++)
    {
      if (arr[i][j] > max)
      {
        point[i][j]++;
        max = arr[i][j];
      }
    }
  }

  // Horizontal, right to left
  max = 0;
  for (int j = 0; j < SIZE; j++)
  {
    point[SIZE-1][j]++;
    max = arr[SIZE-1][j];
    for (int i = SIZE-2; i >= 0; i--)
    {
      if (arr[i][j] > max)
      {
        point[i][j]++;
        max = arr[i][j];
      }
    }
  }

  size_t sum = 0;
  for (size_t i = 0; i < SIZE; i++)
  {
    for (size_t j = 0; j < SIZE; j++)
    {
      if (point[i][j] > 0)
      {
        sum++;
        std::cout << point[i][j];
      }
      else
      {
        std::cout << point[i][j];
      }
    }
    std::cout << std::endl;
  }

  std::cout << sum << std::endl;
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());
  std::string line;

  int arr[SIZE][SIZE];
  for (size_t i = 0; i < SIZE; i++)
  {
    input_file >> line;
    for (size_t j = 0; j < SIZE; j++)
    {
      arr[i][j] = line[j] - '0';
    }
  }

  size_t max = 0;
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      // Up
      size_t p_up = 0;
      for (int up = i-1; up >= 0; up--)
      {
        if (arr[up][j] < arr[i][j]) p_up++;
        else
        {
          p_up++;
          break;
        }
      }

      size_t p_down = 0;
      for (int down = i+1; down < SIZE; down++)
      {
        if (arr[down][j] < arr[i][j]) p_down++;
        else
        {
          p_down++;
          break;
        }
      }

      size_t p_left = 0;
      for (int left = j-1; left >= 0; left--)
      {
        if (arr[i][left] < arr[i][j]) p_left++;
        else
        {
          p_left++;
          break;
        }
      }

      size_t p_right = 0;
      for (int right = j+1; right < SIZE; right++)
      {
        if (arr[i][right] < arr[i][j]) p_right++;
        else
        {
          p_right++;
          break;
        }
      }

      size_t score = p_up * p_down * p_left * p_right;
      if (score > max)
      {
        max = score;
      }
    }
  }

  std::cout << max << std::endl;
}

int main()
{
  // solve_A();
  solve_B();
  return 0;
}