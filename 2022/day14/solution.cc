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
  std::string line;

  int x_min = 1000, x_max = 0;
  int y_min = 1000, y_max = 0;

  std::vector< std::pair<int, int> > coor;

  while (std::getline(input_file, line))
  {
    std::vector<std::string> tokens;
    tokenize(line, ' ', tokens);

    for (size_t i = 0; i < tokens.size(); i += 2)
    {
      std::vector<std::string> tokens2;
      tokenize(tokens[i], ',', tokens2);
      coor.push_back(std::make_pair(std::stoi(tokens2[0]), std::stoi(tokens2[1])));

      if (std::stoi(tokens2[0]) > x_max) x_max = std::stoi(tokens2[0]);
      if (std::stoi(tokens2[0]) < x_min) x_min = std::stoi(tokens2[0]);
      if (std::stoi(tokens2[1]) > y_max) y_max = std::stoi(tokens2[1]);
      if (std::stoi(tokens2[1]) < y_min) y_min = std::stoi(tokens2[1]);
    }

    coor.push_back(std::make_pair(-1, -1));
  }

  x_min -= 10;
  y_min -= 10;
  std::vector< std::vector<int> > map(y_max - y_min + 11, std::vector<int>(x_max - x_min + 11, 0));

  for (size_t i = 0; i < coor.size() - 1; i++)
  {
    if (coor[i+1].first == -1) continue;
    // std::cout << coor[i].first << "," << coor[i].second << " : " << coor[i+1].first << "," << coor[i+1].second << std::endl;
    
    // Vertical
    if (coor[i].first == coor[i+1].first)
    {
      // Up
      if (coor[i].second > coor[i+1].second)
      {
        for (size_t j = coor[i].second; j >= coor[i+1].second; j--)
        {
          map[j - y_min][coor[i].first - x_min] = 1;
        }
      }

      // Down
      else
      {
        for (size_t j = coor[i].second; j <= coor[i+1].second; j++)
        {
          map[j - y_min][coor[i].first - x_min] = 1;
        }
      }
    }

    // Horizontal
    else
    {
      // Up
      if (coor[i].first > coor[i+1].first)
      {
        for (size_t j = coor[i].first; j >= coor[i+1].first; j--)
        {
          map[coor[i].second - y_min][j - x_min] = 1;
        }
      }

      // Down
      else
      {
        for (size_t j = coor[i].first; j <= coor[i+1].first; j++)
        {
          map[coor[i].second - y_min][j - x_min] = 1;
        }
      }
    }
  }

  for (size_t i = 0; i < y_max - y_min + 11; i++)
  {
    for (size_t j = 0; j < x_max - x_min + 11; j++)
    {
      std::cout << (map[i][j] == 1 ? "#" : map[i][j] == 0 ? "." : "o");
    }
    std::cout << std::endl;
  }

  int count = 0;
  bool is_done = false;

  // Put sand
  while (!is_done)
  {
    int x = 37, y = 0;

    while (true)
    {
      if (map[y+1][x] == 0)
      {
        y++;
      }

      else if (map[y+1][x-1] == 0) 
      { 
        x--; y++;
      }

      else if (map[y+1][x+1] == 0) 
      { 
        x++; y++; 
      }

      else
      {
        if (y > y_max) 
        {
          is_done = true;
          break;
        }

        break;
      }

      if (y > y_max) 
      {
        is_done = true;
        break;
      }
    }
    if (is_done) break;

    map[y][x] = -1;
    count++;

    for (size_t i = 0; i < y_max - y_min + 11; i++)
    {
      for (size_t j = 0; j < x_max - x_min + 11; j++)
      {
        std::cout << (map[i][j] == 1 ? "#" : map[i][j] == 0 ? "." : "o");
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  std::cout << count << std::endl;
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  std::string line;

  int x_min = 1000, x_max = 0;
  int y_min = 1000, y_max = 0;

  std::vector< std::pair<int, int> > coor;

  while (std::getline(input_file, line))
  {
    std::vector<std::string> tokens;
    tokenize(line, ' ', tokens);

    for (size_t i = 0; i < tokens.size(); i += 2)
    {
      std::vector<std::string> tokens2;
      tokenize(tokens[i], ',', tokens2);
      coor.push_back(std::make_pair(std::stoi(tokens2[0]), std::stoi(tokens2[1])));

      if (std::stoi(tokens2[0]) > x_max) x_max = std::stoi(tokens2[0]);
      if (std::stoi(tokens2[0]) < x_min) x_min = std::stoi(tokens2[0]);
      if (std::stoi(tokens2[1]) > y_max) y_max = std::stoi(tokens2[1]);
      if (std::stoi(tokens2[1]) < y_min) y_min = std::stoi(tokens2[1]);
    }

    coor.push_back(std::make_pair(-1, -1));
  }

  x_min = 0;
  y_min = 0;
  x_max = 1000;
  std::vector< std::vector<int> > map(y_max - y_min + 3, std::vector<int>(x_max - x_min + 1, 0));

  for (size_t i = 0; i < coor.size() - 1; i++)
  {
    if (coor[i+1].first == -1) continue;
    // std::cout << coor[i].first << "," << coor[i].second << " : " << coor[i+1].first << "," << coor[i+1].second << std::endl;
    
    // Vertical
    if (coor[i].first == coor[i+1].first)
    {
      // Up
      if (coor[i].second > coor[i+1].second)
      {
        for (size_t j = coor[i].second; j >= coor[i+1].second; j--)
        {
          map[j - y_min][coor[i].first - x_min] = 1;
        }
      }

      // Down
      else
      {
        for (size_t j = coor[i].second; j <= coor[i+1].second; j++)
        {
          map[j - y_min][coor[i].first - x_min] = 1;
        }
      }
    }

    // Horizontal
    else
    {
      // Up
      if (coor[i].first > coor[i+1].first)
      {
        for (size_t j = coor[i].first; j >= coor[i+1].first; j--)
        {
          map[coor[i].second - y_min][j - x_min] = 1;
        }
      }

      // Down
      else
      {
        for (size_t j = coor[i].first; j <= coor[i+1].first; j++)
        {
          map[coor[i].second - y_min][j - x_min] = 1;
        }
      }
    }
  }

  for (size_t i = 0; i < y_max - y_min + 3; i++)
  {
    for (size_t j = 0; j < x_max - x_min + 1; j++)
    {
      std::cout << (map[i][j] == 1 ? "#" : map[i][j] == 0 ? "." : "o");
    }
    std::cout << std::endl;
  }

  int count = 0;
  bool is_done = false;

  // Put sand
  while (!is_done)
  {
    int x = 500, y = 0;

    while (y < y_max + 1)
    {
      // std::cout << x << " " << y << std::endl;
      if (map[y+1][x] == 0)
      {
        y++;
      }

      else if (map[y+1][x-1] == 0) 
      { 
        x--; y++;
      }

      else if (map[y+1][x+1] == 0) 
      { 
        x++; y++; 
      }

      else
      {
        if (y == 0)
        {
          is_done = true;
          break;
        }
        break;
      }

      if (y == 0)
      {
        is_done = true;
        break;
      }
    }

    map[y][x] = -1;
    count++;

    // for (size_t i = 0; i < y_max - y_min + 3; i++)
    // {
    //   for (size_t j = 0; j < x_max - x_min + 1; j++)
    //   {
    //     std::cout << (map[i][j] == 1 ? "#" : map[i][j] == 0 ? "." : "o");
    //   }
    //   std::cout << std::endl;
    // }
    // std::cout << std::endl;

    if (is_done) break;
  }

  for (size_t i = 0; i < y_max - y_min + 3; i++)
  {
    for (size_t j = 0; j < x_max - x_min + 1; j++)
    {
      std::cout << (map[i][j] == 1 ? "#" : map[i][j] == 0 ? "." : "o");
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  std::cout << count << std::endl;
}

int main()
{
  // solve_A();
  solve_B();
  return 0;
}