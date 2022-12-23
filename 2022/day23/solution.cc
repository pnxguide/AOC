#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <deque>
#include <set>
#include <unordered_map>
#include <algorithm>

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

std::vector< std::pair<int, int> > map;
std::unordered_map< int, std::unordered_map<int, bool> > hash;

bool find_map(int i, int j)
{
  return hash[i][j];
}

std::vector<bool> check_adjacent(int i, int j)
{
  return {find_map(i-1, j-1), find_map(i-1, j), find_map(i-1, j+1),
    find_map(i, j-1), find_map(i, j+1),
    find_map(i+1, j-1), find_map(i+1, j), find_map(i+1, j+1)};
}

void solve_A()
{
  // Read an input file
  std::ifstream input_file("day23/input.txt");
  std::string line;

  for (size_t i = 0; i < 72; i++)
  {
    std::getline(input_file, line);
    for (size_t j = 0; j < 72; j++)
    {
      if (line[j] == '#') {
        map.push_back(std::make_pair(i, j));
        hash[i][j] = true;
      }
    }
  }

  // prepare for the move
  for (size_t r = 0; ; r++)
  {    
    std::vector< std::pair<int, int> > move_pos;
    std::vector< std::pair<int, int> > move_cmd;
    std::unordered_map< int, std::unordered_map<int, int> > num_cmd;

    std::vector< std::pair<int, int> > new_map;
    std::unordered_map< int, std::unordered_map<int, bool> > new_hash;

    for (auto p : map)
    {
      int i = p.first, j = p.second;
      // std::cout << i << " " << j << std::endl;

      std::vector<bool> adj = check_adjacent(i, j);

      if (!(adj[0] || adj[1] || adj[2] || adj[3] || adj[4] || adj[5] || adj[6] || adj[7]))
      {
        move_pos.push_back(std::make_pair(i, j));
        move_cmd.push_back(std::make_pair(i, j));
        continue;
      }

      switch (r % 4)
      {
        case 0:
        {
          // north
          if (!adj[0] && !adj[1] && !adj[2])
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i-1, j));
            num_cmd[i-1][j]++;
          }

          // south
          else if (!adj[5] && !adj[6] && !adj[7])
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i+1, j));
            num_cmd[i+1][j]++;
          }

          // west
          else if (!adj[0] && !adj[3] && !adj[5])
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i, j-1));
            num_cmd[i][j-1]++;
          }

          // east
          else if (!adj[2] && !adj[4] && !adj[7])
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i, j+1));
            num_cmd[i][j+1]++;
          }

          else
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i, j));
          }
        }
        break;
        
        case 1:
        {
          // south
          if (!adj[5] && !adj[6] && !adj[7])
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i+1, j));
            num_cmd[i+1][j]++;
          }

          // west
          else if (!adj[0] && !adj[3] && !adj[5])
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i, j-1));
            num_cmd[i][j-1]++;
          }

          // east
          else if (!adj[2] && !adj[4] && !adj[7])
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i, j+1));
            num_cmd[i][j+1]++;
          }

          // north
          else if (!adj[0] && !adj[1] && !adj[2])
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i-1, j));
            num_cmd[i-1][j]++;
          }

          else
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i, j));
          }
        }
        break;

        case 2:
        {
          // west
          if (!adj[0] && !adj[3] && !adj[5])
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i, j-1));
            num_cmd[i][j-1]++;
          }

          // east
          else if (!adj[2] && !adj[4] && !adj[7])
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i, j+1));
            num_cmd[i][j+1]++;
          }

          // north
          else if (!adj[0] && !adj[1] && !adj[2])
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i-1, j));
            num_cmd[i-1][j]++;
          }

          // south
          else if (!adj[5] && !adj[6] && !adj[7])
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i+1, j));
            num_cmd[i+1][j]++;
          }

          else
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i, j));
          }
        }
        break;

        case 3:
        {
          // east
          if (!adj[2] && !adj[4] && !adj[7])
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i, j+1));
            num_cmd[i][j+1]++;
          }

          // north
          else if (!adj[0] && !adj[1] && !adj[2])
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i-1, j));
            num_cmd[i-1][j]++;
          }

          // south
          else if (!adj[5] && !adj[6] && !adj[7])
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i+1, j));
            num_cmd[i+1][j]++;
          }

          // west
          else if (!adj[0] && !adj[3] && !adj[5])
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i, j-1));
            num_cmd[i][j-1]++;
          }

          else
          {
            move_pos.push_back(std::make_pair(i, j));
            move_cmd.push_back(std::make_pair(i, j));
          }
        }
        break;
      }
    }

    // Update
    int c = 0;
    for (size_t k = 0; k < move_pos.size(); k++)
    {
      if (
        num_cmd[move_cmd[k].first][move_cmd[k].second] == 1
        && !(move_pos[k].first == move_cmd[k].first && move_pos[k].second == move_cmd[k].second)
      )
      {
        c++;
        new_map.push_back(move_cmd[k]);
        new_hash[move_cmd[k].first][move_cmd[k].second] = true;
      }

      else
      {
        new_map.push_back(move_pos[k]);
        new_hash[move_pos[k].first][move_pos[k].second] = true;
      }
    }

    map = new_map;
    hash = new_hash;

    if (c == 0) 
    {
      std::cout << r+1 << std::endl;
      break;
    }
  }

  int x1 = map[0].second, x2 = map[0].second, y1 = map[0].first, y2 = map[0].first;

  for (auto p : map)
  {
    if (p.first < y1) y1 = p.first;
    if (p.first > y2) y2 = p.first;
    if (p.second < x1) x1 = p.second;
    if (p.second > x2) x2 = p.second;
  }

  std::cout << (x2 - x1 + 1) * (y2 - y1 + 1) - map.size() << std::endl;
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("day23/input.txt");
  std::string line;

}

int main()
{
  solve_A();
  // solve_B();
  return 0;
}