#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <deque>
#include <set>
#include <unordered_map>
#include <algorithm>

#define BOUND 25

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

  std::vector< std::vector< std::vector<bool> > > map(BOUND, std::vector< std::vector<bool> >(BOUND, std::vector<bool>(BOUND, false)));

  std::vector<int> inputs;
  int total = 0;

  while (std::getline(input_file, line))
  {
    std::vector< std::string > tokens;
    tokenize(line, ',', tokens);
    map[std::stoi(tokens[0])+1][std::stoi(tokens[1])+1][std::stoi(tokens[2])+1] = true;
    inputs.push_back((BOUND * BOUND) * (std::stoi(tokens[0])+1) + BOUND * (std::stoi(tokens[1])+1) + (std::stoi(tokens[2])+1));
    total += 6;
  }

  for (int i = 0; i < inputs.size(); i++)
  {
    int x = inputs[i] / (BOUND * BOUND);
    int y = (inputs[i] % (BOUND * BOUND)) / BOUND;
    int z = inputs[i] % BOUND;

    // Check if contiguous
    total -= map[x+1][y][z] + map[x-1][y][z] + map[x][y+1][z] + map[x][y-1][z] + map[x][y][z+1] + map[x][y][z-1];
  }

  std::cout << total << std::endl;
}

int c(int x, int y, int z)
{
  return (BOUND * BOUND) * (x) + BOUND * y + z;
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  std::string line;

  std::vector<int> inputs;
  int total = 0;

  std::vector< std::vector< std::vector<bool> > > map(BOUND, std::vector< std::vector<bool> >(BOUND, std::vector<bool>(BOUND, false)));

  while (std::getline(input_file, line))
  {
    std::vector< std::string > tokens;
    tokenize(line, ',', tokens);
    map[std::stoi(tokens[0])+1][std::stoi(tokens[1])+1][std::stoi(tokens[2])+1] = true;
    inputs.push_back((BOUND * BOUND) * (std::stoi(tokens[0])+1) + BOUND * (std::stoi(tokens[1])+1) + (std::stoi(tokens[2])+1));
  }

  std::vector< std::vector< std::vector<bool> > > is_air(BOUND, std::vector< std::vector<bool> >(BOUND, std::vector<bool>(BOUND, false)));

  // Generate is_air
  std::deque<int> s;
  s.push_back(0);
  while(!s.empty())
  {
    int cur = s.back();
    s.pop_back();

    int c_x = cur / (BOUND * BOUND);
    int c_y = cur % (BOUND * BOUND) / BOUND;
    int c_z = cur % BOUND;

    if (is_air[c_x][c_y][c_z]) continue;
    is_air[c_x][c_y][c_z] = true;

    if (c_x+1 < BOUND && !map[c_x+1][c_y][c_z]) s.push_back(c(c_x+1, c_y, c_z));
    if (c_x-1 >= 0 && !map[c_x-1][c_y][c_z]) s.push_back(c(c_x-1, c_y, c_z));
    if (c_y+1 < BOUND && !map[c_x][c_y+1][c_z]) s.push_back(c(c_x, c_y+1, c_z));
    if (c_y-1 >= 0 && !map[c_x][c_y-1][c_z]) s.push_back(c(c_x, c_y-1, c_z));
    if (c_z+1 < BOUND && !map[c_x][c_y][c_z+1]) s.push_back(c(c_x, c_y, c_z+1));
    if (c_z-1 >= 0 && !map[c_x][c_y][c_z-1]) s.push_back(c(c_x, c_y, c_z-1));
  }

  for (int i = 0; i < inputs.size(); i++)
  {
    int x = inputs[i] / (BOUND * BOUND);
    int y = (inputs[i] % (BOUND * BOUND)) / BOUND;
    int z = inputs[i] % BOUND;

    // Check if contiguous
    total += is_air[x+1][y][z] + is_air[x-1][y][z] + is_air[x][y+1][z] + is_air[x][y-1][z] + is_air[x][y][z+1] + is_air[x][y][z-1];
  }
  
  std::cout << total << std::endl;
}

int main()
{
  // solve_A();
  solve_B();
  return 0;
}