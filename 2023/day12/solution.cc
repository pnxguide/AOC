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

#define M 41
#define N 161

void solve_A()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());
  std::string line;

  char data[M][N];
  int Y = 0;
  int x = 0, y = 0;
  int dx = 0, dy = 0;

  while (std::getline(input_file, line))
  {
    for (size_t i = 0; i < line.size(); i++)
    {
      data[Y][i] = line[i];
      if (data[Y][i] == 'E')
      {
        data[Y][i] = 'z';
        dx = Y;
        dy = i;
      }

      if (data[Y][i] == 'S')
      {
        data[Y][i] = 'a';
        x = Y;
        y = i;
      }
    }

    Y++;
  }

  // BFS
  std::deque< std::pair<int, int> > q;
  std::vector<bool> is_visited(M * N, false);
  std::vector<int> tmp_is_visited;
  std::pair<int, int> cur;
  std::set< std::pair<int, int> > frontier;
  frontier.insert(std::make_pair(x, y));
  int depth = 0;
  bool is_done = false;

  while (!is_done)
  {
    depth++;

    for (std::pair<int, int> x : frontier)
    {
      is_visited[x.first * N + x.second] = true;
      // std::cout << data[x.first][x.second] << std::endl;
      q.push_back(x);
    }
    frontier.clear();

    while (!q.empty())
    {
      cur = q.front();
      q.pop_front();

      // std::cout << cur.first << " " << cur.second << " " << data[cur.first][cur.second] << " " << depth << std::endl;

      if (cur.first == dx && cur.second == dy)
      {
        is_done = true;
        break;
      }

      // neighbors
      if (cur.second+1 < N && 
        data[cur.first][cur.second+1] - data[cur.first][cur.second] <= 1 &&
        !is_visited[(cur.first) * N + (cur.second+1)])
      {
        // std::cout << "push " << data[cur.first][cur.second+1] << std::endl;
        frontier.insert(std::make_pair(cur.first, cur.second+1));
      }

      if (cur.second-1 >= 0 && 
        data[cur.first][cur.second-1] - data[cur.first][cur.second] <= 1 &&
        !is_visited[(cur.first) * N + (cur.second-1)])
      {
        // std::cout << "push " << data[cur.first][cur.second-1] << std::endl;
        frontier.insert(std::make_pair(cur.first, cur.second-1));
      }

      if (cur.first+1 < M && 
        data[cur.first+1][cur.second] - data[cur.first][cur.second] <= 1 &&
        !is_visited[(cur.first+1) * N + (cur.second)])
      {
        // std::cout << "push " << data[cur.first+1][cur.second] << std::endl;
        frontier.insert(std::make_pair(cur.first+1, cur.second));
      }

      if (cur.first-1 >= 0 && 
        data[cur.first-1][cur.second] - data[cur.first][cur.second] <= 1 &&
        !is_visited[(cur.first-1) * N + (cur.second)])
      {
        // std::cout << "push " << data[cur.first-1][cur.second] << std::endl;
        frontier.insert(std::make_pair(cur.first-1, cur.second));
      }
    }
  }

  std::cout << depth - 1 << std::endl;
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());
  std::string line;

  char data[M][N];
  int Y = 0;
  int x = 0, y = 0;
  int dx = 0, dy = 0;

  while (std::getline(input_file, line))
  {
    for (size_t i = 0; i < line.size(); i++)
    {
      data[Y][i] = line[i];
      if (data[Y][i] == 'E')
      {
        data[Y][i] = 'z';
        dx = Y;
        dy = i;
      }

      if (data[Y][i] == 'S')
      {
        data[Y][i] = 'a';
        // x = Y;
        // y = i;
      }
    }

    Y++;
  }

  // BFS
  std::deque< std::pair<int, int> > q;
  std::vector<bool> is_visited(M * N, false);
  std::vector<int> tmp_is_visited;
  std::pair<int, int> cur;
  std::set< std::pair<int, int> > frontier;
  frontier.insert(std::make_pair(dx, dy));
  int depth = 0;
  bool is_done = false;

  while (!is_done)
  {
    depth++;

    for (std::pair<int, int> x : frontier)
    {
      is_visited[x.first * N + x.second] = true;
      // std::cout << data[x.first][x.second] << std::endl;
      q.push_back(x);
    }
    frontier.clear();

    while (!q.empty())
    {
      cur = q.front();
      q.pop_front();

      if (data[cur.first][cur.second] == 'a')
      {
        is_done = true;
        break;
      }

      // neighbors
      if (cur.second+1 < N && 
        data[cur.first][cur.second] - data[cur.first][cur.second+1] <= 1 &&
        !is_visited[(cur.first) * N + (cur.second+1)])
      {
        // std::cout << "push " << data[cur.first][cur.second+1] << std::endl;
        frontier.insert(std::make_pair(cur.first, cur.second+1));
      }

      if (cur.second-1 >= 0 && 
        data[cur.first][cur.second] - data[cur.first][cur.second-1] <= 1 &&
        !is_visited[(cur.first) * N + (cur.second-1)])
      {
        // std::cout << "push " << data[cur.first][cur.second-1] << std::endl;
        frontier.insert(std::make_pair(cur.first, cur.second-1));
      }

      if (cur.first+1 < M && 
        data[cur.first][cur.second] - data[cur.first+1][cur.second] <= 1 &&
        !is_visited[(cur.first+1) * N + (cur.second)])
      {
        // std::cout << "push " << data[cur.first+1][cur.second] << std::endl;
        frontier.insert(std::make_pair(cur.first+1, cur.second));
      }

      if (cur.first-1 >= 0 && 
        data[cur.first][cur.second] - data[cur.first-1][cur.second] <= 1 &&
        !is_visited[(cur.first-1) * N + (cur.second)])
      {
        // std::cout << "push " << data[cur.first-1][cur.second] << std::endl;
        frontier.insert(std::make_pair(cur.first-1, cur.second));
      }
    }
  }

  std::cout << depth - 1 << std::endl;
}

int main()
{
  // solve_A();
  solve_B();
  return 0;
}