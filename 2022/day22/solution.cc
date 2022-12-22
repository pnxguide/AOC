#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <deque>
#include <set>
#include <unordered_map>
#include <algorithm>

#define XX 150
#define YY 200

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

int mod(int x, int y)
{
  if (x < 0) return (x % y) + y;
  else return x % y;
}

void solve_A()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  std::string line;

  std::vector< std::vector<int> > board(YY, std::vector<int>(XX, 0));
  
  for (size_t j = 0; j < YY; j++)
  {
    std::getline(input_file, line);
    for (size_t i = 0; i < line.size(); i++)
    {
      if (line[i] == ' ') continue;
      else if (line[i] == '.') board[j][i] = 1;
      else if (line[i] == '#') board[j][i] = -1;
    }
  }

  // free
  std::getline(input_file, line);

  // cmd
  std::vector< std::pair< int, char > > cmd;
  std::getline(input_file, line);

  std::string tmp;
  int val = 0;
  for (size_t i = 0; i < line.size(); i++)
  {
    switch (line[i])
    {
      case 'L':
      case 'R':
        val = std::stoi(tmp);
        tmp = "";
        cmd.push_back(std::make_pair(val, line[i]));
        break;
      default:
        tmp = tmp + line[i];
    }
  }

  if (tmp != "")
  {
    cmd.push_back(std::make_pair(std::stoi(tmp), 0));
  }

  int cur_x = 0, cur_y = 0;
  int direction = 0;
  
  for (size_t i = 0; i < cmd.size(); i++)
  {
    std::cout << cmd[i].first << " " << cmd[i].second << std::endl;

    // Walk
    for (size_t j = 0; j < cmd[i].first; j++)
    {
      int prev_x = cur_x, prev_y = cur_y;

      switch (direction)
      {
        // right
        case 0:
          std::cout << cur_x << std::endl;
          while (board[cur_y][mod(cur_x+1, XX)] == 0) cur_x++;
          if (board[cur_y][mod(cur_x+1, XX)] == -1)
          {
            cur_x = prev_x;
            goto turn;
          }
          cur_x++;
          break;
        // up
        case 90:
          while (board[mod(cur_y-1, YY)][cur_x] == 0) cur_y--;
          if (board[mod(cur_y-1, YY)][cur_x] == -1)
          {
            cur_y = prev_y;
            goto turn;
          }
          cur_y--;
          break;
        // left
        case 180:
          while (board[cur_y][mod(cur_x-1, XX)] == 0) cur_x--;
          if (board[cur_y][mod(cur_x-1, XX)] == -1)
          {
            cur_x = prev_x;
            goto turn;
          }
          cur_x--;
          break;
        // down
        case 270:
          while (board[mod(cur_y+1, YY)][cur_x] == 0) cur_y++;
          if (board[mod(cur_y+1, YY)][cur_x] == -1) 
          {
            cur_y = prev_y;
            goto turn;
          }
          cur_y++;
          break;
      }

      cur_x = mod(cur_x, XX);
      cur_y = mod(cur_y, YY);
    }

turn:

    cur_x = mod(cur_x, XX);
    cur_y = mod(cur_y, YY);

    // Turn
    switch (cmd[i].second)
    {
      case 'L':
        direction += 90;
        break;
      case 'R':
        direction -= 90;
        break;
    }

    direction = mod(direction, 360);

    std::cout << cur_x << " " << cur_y << " (" << direction << ")" << std::endl;
  }

  int d = 0;
  if (direction == 0) d = 0;
  else if (direction == 270) d = 1;
  else if (direction == 180) d = 2;
  else if (direction == 90) d = 3;

  std::cout << 1000 * (cur_y+1) + (cur_x+1) * 4 + d << std::endl;
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  std::string line;

  std::vector< std::vector<int> > board(YY, std::vector<int>(XX, 0));
  std::vector< std::vector<int> > type(YY, std::vector<int>(XX, 0));

  for (size_t y = 0; y < YY; y++)
  {
    for (size_t x = 0; x < XX; x++)
    {
      if (y >= 0 && y < 50 && x >= 50 && x < 100)         type[y][x] = 1;
      else if (y >= 0 && y < 50 && x >= 100 && x < 150)   type[y][x] = 2;
      else if (y >= 50 && y < 100 && x >= 50 && x < 100)  type[y][x] = 3;
      else if (y >= 100 && y < 150 && x >= 0 && x < 50)   type[y][x] = 4;
      else if (y >= 100 && y < 150 && x >= 50 && x < 100) type[y][x] = 5;
      else if (y >= 150 && y < 200 && x >= 0 && x < 50)   type[y][x] = 6;

      std::cout << type[y][x];
    }

    std::cout << std::endl;
  }

  for (size_t j = 0; j < YY; j++)
  {
    std::getline(input_file, line);
    for (size_t i = 0; i < line.size(); i++)
    {
      if (line[i] == ' ') continue;
      else if (line[i] == '.') board[j][i] = 1;
      else if (line[i] == '#') board[j][i] = -1;
    }
  }

  // free
  std::getline(input_file, line);

  // cmd
  std::vector< std::pair< int, char > > cmd;
  std::getline(input_file, line);

  std::string tmp;
  int val = 0;
  for (size_t i = 0; i < line.size(); i++)
  {
    switch (line[i])
    {
      case 'L':
      case 'R':
        val = std::stoi(tmp);
        tmp = "";
        cmd.push_back(std::make_pair(val, line[i]));
        break;
      default:
        tmp = tmp + line[i];
    }
  }

  if (tmp != "")
  {
    cmd.push_back(std::make_pair(std::stoi(tmp), 0));
  }

  int cur_x = 50, cur_y = 0;
  int direction = 0;
  
  for (size_t i = 0; i < cmd.size(); i++)
  {
    // Walk
    for (size_t j = 0; j < cmd[i].first; j++)
    {
      int prev_x = cur_x, prev_y = cur_y;

      std::cout << cur_x << " " << cur_y << std::endl;

      switch (direction)
      {
        // right
        case 0:
          // if 2, 3, 5, 6 and out of bound => recompute cur_x
          if (
            (type[cur_y][cur_x] == 2 || 
              type[cur_y][cur_x] == 3 || 
              type[cur_y][cur_x] == 5 || 
              type[cur_y][cur_x] == 6) && 
            (cur_x % 50) == 49)
          {
            // std::cout << cmd[i].first << " " << cmd[i].second << std::endl;
            // std::cout << cur_x << "," << cur_y << std::endl << std::endl;

            switch (type[cur_y][cur_x])
            {
              // 2 -> 5
              case 2:
                assert(type[149-(cur_y%50)][99] == 5);
                if (board[149-(cur_y%50)][99] == -1) goto turn2;
                cur_y = 149-(cur_y%50);
                cur_x = 99;
                direction = 180;
                break;
              // 3 -> 2
              case 3:
                assert(type[49][100+(cur_y%50)] == 2);
                if (board[49][100+(cur_y%50)] == -1) goto turn2;
                cur_x = 100+(cur_y%50);
                cur_y = 49;
                direction = 90;
                break;
              // 5 -> 2
              case 5:
                assert(type[49-(cur_y%50)][149] == 2);
                if (board[49-(cur_y%50)][149] == -1) goto turn2;
                cur_y = 49-(cur_y%50);
                cur_x = 149;
                direction = 180;
                break;
              // 6 -> 5
              case 6:
                assert(type[149][50+(cur_y%50)] == 5);
                if (board[149][50+(cur_y%50)] == -1) goto turn2;
                cur_x = 50+(cur_y%50);
                cur_y = 149;
                direction = 90;
                break;
            }
          }

          else
          {
            while (board[cur_y][mod(cur_x+1, XX)] == 0) cur_x++;
            if (board[cur_y][mod(cur_x+1, XX)] == -1)
            {
              cur_x = prev_x;
              goto turn2;
            }
            cur_x++;
          }

          break;
        // up
        case 90:
          if (
            (type[cur_y][cur_x] == 1 || 
              type[cur_y][cur_x] == 2 || 
              type[cur_y][cur_x] == 4) && 
            cur_y % 50 == 0)
          {
            // std::cout << cmd[i].first << " " << cmd[i].second << std::endl;
            // std::cout << cur_x << "," << cur_y << std::endl << std::endl;

            switch (type[cur_y][cur_x])
            {
              case 1:
                assert(type[150+(cur_x%50)][0] == 6);
                if (board[150+(cur_x%50)][0] == -1) goto turn2;
                cur_y = 150+(cur_x%50);
                cur_x = 0;
                direction = 0;
                break;
              case 2:
                assert(type[199][(cur_x%50)] == 6);
                if (board[199][(cur_x%50)] == -1) goto turn2;
                cur_x = (cur_x%50);
                cur_y = 199;
                direction = 90;
                break;
              case 4:
                assert(type[50+(cur_x%50)][50] == 3);
                if (board[50+(cur_x%50)][50] == -1) goto turn2;
                cur_y = 50+(cur_x%50);
                cur_x = 50;
                direction = 0;
                break;
            }
          }

          else
          {
            while (board[mod(cur_y-1, YY)][cur_x] == 0) cur_y--;
            if (board[mod(cur_y-1, YY)][cur_x] == -1)
            {
              cur_y = prev_y;
              goto turn2;
            }
            cur_y--;
          }

          break;
          
        // left
        case 180:
          if (
            (type[cur_y][cur_x] == 1 || 
              type[cur_y][cur_x] == 3 || 
              type[cur_y][cur_x] == 4 || 
              type[cur_y][cur_x] == 6) && 
            cur_x % 50 == 0)
          {
            std::cout << cmd[i].first << " " << cmd[i].second << std::endl;
            std::cout << cur_x << "," << cur_y << std::endl << std::endl;

            switch (type[cur_y][cur_x])
            {
              case 1:
                assert(type[149-(cur_y%50)][0] == 4);
                if (board[149-(cur_y%50)][0] == -1) goto turn2;
                cur_y = 149-(cur_y%50);
                cur_x = 0;
                direction = 0;
                break;
              case 3:
                assert(type[100][(cur_y%50)] == 4);
                if (board[100][(cur_y%50)] == -1) goto turn2;
                cur_x = (cur_y%50);
                cur_y = 100;
                direction = 270;
                // std::cout << cur_y << " " << cur_x << std::endl;
                break;
              case 4:
                assert(type[49-(cur_y%50)][50] == 1);
                if (board[49-(cur_y%50)][50] == -1) goto turn2;
                cur_y = 49-(cur_y%50);
                cur_x = 50;
                direction = 0;
                break;
              case 6:
                assert(type[0][50+(cur_y%50)] == 1);
                if (board[0][50+(cur_y%50)] == -1) goto turn2;
                cur_x = 50+(cur_y%50);
                cur_y = 0;
                direction = 270;
                break;
            }
          }

          else
          {
            while (board[cur_y][mod(cur_x-1, XX)] == 0) cur_x--;
            if (board[cur_y][mod(cur_x-1, XX)] == -1)
            {
              cur_x = prev_x;
              goto turn2;
            }
            cur_x--;
          }
          
          break;

        // down
        case 270:
          if (
            (type[cur_y][cur_x] == 2 || 
              type[cur_y][cur_x] == 5 || 
              type[cur_y][cur_x] == 6) && 
            cur_y % 50 == 49)
          {
            // std::cout << cmd[i].first << " " << cmd[i].second << std::endl;
            // std::cout << cur_x << "," << cur_y << std::endl << std::endl;

            switch (type[cur_y][cur_x])
            {
              case 2:
                assert(type[50+(cur_x%50)][99] == 3);
                if (board[50+(cur_x%50)][99] == -1) goto turn2;
                cur_y = 50+(cur_x%50);
                cur_x = 99;
                direction = 180;
                break;
              case 5:
                assert(type[150+(cur_x%50)][49] == 6);
                if (board[150+(cur_x%50)][49] == -1) goto turn2;
                cur_y = 150+(cur_x%50);
                cur_x = 49;
                direction = 180;
                break;
              case 6:
                assert(type[0][100+(cur_x%50)] == 2);
                if (board[0][100+(cur_x%50)] == -1) goto turn2;
                cur_x = 100+(cur_x%50);
                cur_y = 0;
                direction = 270;
                break;
            }
          }

          else
          {
            while (board[mod(cur_y+1, YY)][cur_x] == 0) cur_y++;
            if (board[mod(cur_y+1, YY)][cur_x] == -1) 
            {
              cur_y = prev_y;
              goto turn2;
            }
            cur_y++;
          }
          
          break;
      }

      cur_x = mod(cur_x, XX);
      cur_y = mod(cur_y, YY);
    }

turn2:

    cur_x = mod(cur_x, XX);
    cur_y = mod(cur_y, YY);

    // Turn
    switch (cmd[i].second)
    {
      case 'L':
        direction += 90;
        break;
      case 'R':
        direction -= 90;
        break;
    }

    direction = mod(direction, 360);

    std::cout << cur_x << " " << cur_y << " (" << direction << ")" << std::endl;
  }

  int d = 0;
  if (direction == 0) d = 0;
  else if (direction == 270) d = 1;
  else if (direction == 180) d = 2;
  else if (direction == 90) d = 3;

  std::cout << 1000 * (cur_y+1) + (cur_x+1) * 4 + d << std::endl;
}

int main()
{
  // solve_A();
  solve_B();
  return 0;
}