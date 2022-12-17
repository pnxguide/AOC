#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <deque>
#include <set>
#include <unordered_map>
#include <algorithm>

#define LIMIT (1709 + 1581)

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
  std::string commands;
  input_file >> commands;

  // Coordinate (x, -y)

  std::vector< std::vector< std::pair<long, long> > > patterns(5);

  // Pattern 1
  patterns[0].push_back(std::make_pair(0, 0));
  patterns[0].push_back(std::make_pair(1, 0));
  patterns[0].push_back(std::make_pair(2, 0));
  patterns[0].push_back(std::make_pair(3, 0));

  // Pattern 2
  patterns[1].push_back(std::make_pair(1, 0));
  patterns[1].push_back(std::make_pair(0, 1));
  patterns[1].push_back(std::make_pair(1, 1));
  patterns[1].push_back(std::make_pair(2, 1));
  patterns[1].push_back(std::make_pair(1, 2));

  // Pattern 3
  patterns[2].push_back(std::make_pair(0, 0));
  patterns[2].push_back(std::make_pair(1, 0));
  patterns[2].push_back(std::make_pair(2, 0));
  patterns[2].push_back(std::make_pair(2, 1));
  patterns[2].push_back(std::make_pair(2, 2));

  // Pattern 4
  patterns[3].push_back(std::make_pair(0, 0));
  patterns[3].push_back(std::make_pair(0, 1));
  patterns[3].push_back(std::make_pair(0, 2));
  patterns[3].push_back(std::make_pair(0, 3));

  // Pattern 5
  patterns[4].push_back(std::make_pair(0, 0));
  patterns[4].push_back(std::make_pair(1, 0));
  patterns[4].push_back(std::make_pair(0, 1));
  patterns[4].push_back(std::make_pair(1, 1));

  long max_height = 0;
  long count = 0;

  long current_pattern = 0;
  std::vector< std::pair<long, long> > current_position;
  for (size_t i = 0; i < patterns[current_pattern].size(); i++)
  {
    current_position.push_back(
      std::make_pair(
        patterns[current_pattern][i].first + 2,
        patterns[current_pattern][i].second + 3 + max_height));
  }

  std::vector< std::unordered_map<long, bool> > board(7, std::unordered_map<long, bool>());

  while (count < LIMIT)
  {
    bool just_started = false;

    for (size_t i = 0; i < commands.size(); i++)
    {
      just_started = false;

      switch (commands[i])
      {
        case '>':
        {
          bool can_move_right = true;
          for (size_t j = 0; j < current_position.size(); j++)
          {
            if (current_position[j].first >= 6 || board[current_position[j].first + 1][current_position[j].second])
            {
              can_move_right = false;
              break;
            }
          }

          if (can_move_right)
          {
            for (size_t j = 0; j < current_position.size(); j++)
              current_position[j].first++;
          }
        }
        break;
        case '<':
        {
          bool can_move_left = true;
          for (size_t j = 0; j < current_position.size(); j++)
          {
            if (current_position[j].first <= 0 || board[current_position[j].first - 1][current_position[j].second])
            {
              can_move_left = false;
              break;
            }
          }

          if (can_move_left)
          {
            for (size_t j = 0; j < current_position.size(); j++)
              current_position[j].first--;
          }
        }
        break;
      }

      bool can_move_down = true;
      for (size_t j = 0; j < current_position.size(); j++)
      {
        // Check bottom
        if (current_position[j].second <= 0 || board[current_position[j].first][current_position[j].second - 1])
        {
          can_move_down = false;
          break;
        }
      }

      if (can_move_down)
      {
        for (size_t j = 0; j < current_position.size(); j++)
          current_position[j].second--;
      }

      // Change shape
      else
      {
        // 1) Put shape in the board
        for (size_t j = 0; j < current_position.size(); j++)
        {
          board[current_position[j].first][current_position[j].second] = true;
          if (current_position[j].second > max_height)
          {
            max_height = current_position[j].second;
          }
        }

        // 2) Change the shape
        count += 1;
        current_pattern = count % 5;
        // if (count % 100000 == 0) std::cout << count << std::endl;

        // 3) Generate new current_position
        current_position.clear();
        for (size_t j = 0; j < patterns[current_pattern].size(); j++)
        {
          current_position.push_back(
            std::make_pair(
              patterns[current_pattern][j].first + 2, 
              patterns[current_pattern][j].second + 3 + max_height + 1));
        }

        just_started = true;
      }

      if (count >= LIMIT)
      {
        break;
      }
    }

    for (size_t i = 0; i < current_position.size(); i++)
    {
      std::cout << current_position[i].first << " " << current_position[i].second << std::endl;
    }

    for (size_t j = 0; j < 4; j++)
    {
      for (size_t i = 0; i < 7; i++)
      {
        std::cout << board[i][max_height-j];
      }
      std::cout << std::endl;
    }

    std::cout << count << " " << (max_height + 1) << std::endl;
  }

  // 1st Loop         = 2591          / #shape = 1709
  // 2nd Loop         = 5173 (+2582)  / 3414 (+1705)
  // 3rd Loop         = 7755 (+2582)  / 5119 (+1705)
  // ...
  // 586510262nd Loop = 1514369499075 (+2582) / 999999998419 (+1705)

  // 1514369499075 + 2412
  
  // 1514369501487
  // 1514369502363

  // 100000th Shape = 151452

  // 1st Loop         = 2591          / #shape = 1709
  // 2nd Loop         = 5173 (+2582)  / 3414 (+1705)
  // 3rd Loop         = 7755 (+2582)  / 5119 (+1705)
  // ...
  // 586510262nd Loop = 1514369499075 (+2582) / 999999998419 (+1705)

  // 1709 + (1705 * 586510262)
  // 586510262nd Loop makes 999999998419 shapes
  // 2591 + (2582 * 586510262)
  // 586510262nd Loop makes 1514369499075
  // 1581 shapes left
  // 1514369499075 + 2411 - 2

  // 1709 + (1705 * n) = 100000
  // n = 57

  // 57th Loop makes 98894 shapes
  // 57th Loop makes 2591 + (2582 * 57) = 149765
  // 1106 shapes left
  // 151454 - 2

  // 150871

  std::cout << (max_height + 1) << std::endl;
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  std::string line;

}

int main()
{
  solve_A();
  // solve_B();
  return 0;
}