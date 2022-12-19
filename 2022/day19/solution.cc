#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <deque>
#include <set>
#include <unordered_map>
#include <algorithm>

#define SIZE 3
#define TIME 32

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

std::vector<uint16_t> ore_robot_costs_in_ore(SIZE);
std::vector<uint16_t> clay_robot_costs_in_ore(SIZE);
std::vector<uint16_t> obsidean_robot_costs_in_ore(SIZE);
std::vector<uint16_t> obsidean_robot_costs_in_clay(SIZE);
std::vector<uint16_t> geode_robot_costs_in_ore(SIZE);
std::vector<uint16_t> geode_robot_costs_in_obsidean(SIZE);

std::vector< std::vector< std::unordered_map<uint64_t, uint16_t> > > recursion_table_A(
  SIZE, std::vector< std::unordered_map<uint64_t, uint16_t> >(
    TIME, std::unordered_map<uint64_t, uint16_t>()));

uint64_t hash(uint16_t no, uint16_t nc, uint16_t nb, uint16_t ng, uint8_t nor, uint8_t ncr, uint8_t nbr, uint8_t ngr)
{
  uint64_t h = 
    (no & 0b111111111) | 
    ((nc & 0b111111111) << 9) | 
    ((nb & 0b111111111) << 18) | 
    ((ng & 0b111111111) << 27) | 
    ((nor & 0b11111) << 36) | 
    ((ncr & 0b11111) << 41) | 
    ((nbr & 0b11111) << 46) | 
    ((ngr & 0b11111) << 51) | 
    0b0;

  // std::cout << std::bitset<64>(h) << std::endl;
  
  return h;
}

// std::vector< std::vector<int> > dp(SIZE, std::vector<int>(TIME, 0));

// Return max ng
uint16_t recursion_A(int id, int cur_t, uint16_t no, uint16_t nc, uint16_t nb, uint16_t ng, uint8_t nor, uint8_t ncr, uint8_t nbr, uint8_t ngr)
{
  if (cur_t == TIME)
  {
    return ng;
  }

  int cached = recursion_table_A[id][cur_t][hash(no, nc, nb, ng, nor, ncr, nbr, ngr)];
  if (cached != 0)
  {
    return cached;
  }

  uint8_t num_ore_robot = nor;
  uint8_t num_clay_robot = ncr;
  uint8_t num_obsidean_robot = nbr;
  uint8_t num_geode_robot = ngr;

  uint16_t num_ore = no;
  uint16_t num_clay = nc;
  uint16_t num_obsidean = nb;
  uint16_t num_geode = ng;

  uint16_t max = 0;

  for (size_t t = cur_t; t < TIME; t++)
  {
    // Increment resources
    num_ore       += num_ore_robot;
    num_clay      += num_clay_robot;
    num_obsidean  += num_obsidean_robot;
    num_geode     += num_geode_robot;

    // If can create a geode robot, create it!
    if ((num_obsidean - num_obsidean_robot) >= geode_robot_costs_in_obsidean[id] && 
      (num_ore - num_ore_robot) >= geode_robot_costs_in_ore[id])
    {
      num_ore -= geode_robot_costs_in_ore[id];
      num_obsidean -= geode_robot_costs_in_obsidean[id];
      num_geode_robot++;
    }

    else
    {
      // If we can create all of them, one of them must be created!
      // Otherwise, this is not the maximum one.
      int selected = 0;

      // Try creating an obsidean robot, if possible
      if ((num_clay - num_clay_robot) >= obsidean_robot_costs_in_clay[id] && 
        (num_ore - num_ore_robot) >= obsidean_robot_costs_in_ore[id])
      {
        max = std::max(max, 
          recursion_A(
            id,
            t + 1,
            num_ore - obsidean_robot_costs_in_ore[id], num_clay - obsidean_robot_costs_in_clay[id], num_obsidean, num_geode,
            num_ore_robot, num_clay_robot, num_obsidean_robot + 1, num_geode_robot));

        selected++;
      }

      // Try creating a clay robot, if possible
      if ((num_ore - num_ore_robot) >= clay_robot_costs_in_ore[id])
      {
        max = std::max(max, 
          recursion_A(
            id,
            t + 1, 
            num_ore - clay_robot_costs_in_ore[id], num_clay, num_obsidean, num_geode,
            num_ore_robot, num_clay_robot + 1, num_obsidean_robot, num_geode_robot));
        
        selected++;
      }

      // Try creating a ore robot, if possible
      if ((num_ore - num_ore_robot) >= ore_robot_costs_in_ore[id])
      {
        max = std::max(max,
          recursion_A(
            id,
            t + 1,
            num_ore - ore_robot_costs_in_ore[id], num_clay, num_obsidean, num_geode,
            num_ore_robot + 1, num_clay_robot, num_obsidean_robot, num_geode_robot));

        selected++;
      }

      // Don't continue this recursion since it cannot be the maximum
      if (selected == 3) break;
    }

    recursion_table_A[id][t][hash(num_ore, num_clay, num_obsidean, num_geode, num_ore_robot, num_clay_robot, num_obsidean_robot, num_geode_robot)] = 
      std::max(max, num_geode);
  }

  return std::max(max, num_geode);
}

void solve_A()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  std::string line;

  while (std::getline(input_file, line))
  {
    std::vector< std::string > tokens;
    tokenize(line, ' ', tokens);

    int id = std::stoi(tokens[1])-1;
    ore_robot_costs_in_ore[id]        = std::stoi(tokens[6]);
    clay_robot_costs_in_ore[id]       = std::stoi(tokens[12]);
    obsidean_robot_costs_in_ore[id]   = std::stoi(tokens[18]);
    obsidean_robot_costs_in_clay[id]  = std::stoi(tokens[21]);
    geode_robot_costs_in_ore[id]      = std::stoi(tokens[27]);
    geode_robot_costs_in_obsidean[id] = std::stoi(tokens[30]);
  }

  std::vector<int> maxs(SIZE);

  #pragma omp parallel for
  for (size_t id = 0; id < SIZE; id++)
  {
    uint16_t max = recursion_A(id, 0, 0, 0, 0, 0, 1, 0, 0, 0);
    std::cout << (id+1) << ": " << max << std::endl;
    maxs[id] = ((id+1) * max);
  }

  int sum = 0;
  for (size_t id = 0; id < SIZE; id++)
  {
    sum += maxs[id];
  }

  std::cout << sum << std::endl;
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  std::string line;

  while (std::getline(input_file, line))
  {
    std::vector< std::string > tokens;
    tokenize(line, ' ', tokens);

    int id = std::stoi(tokens[1])-1;

    if (id >= 3) break;

    ore_robot_costs_in_ore[id]        = std::stoi(tokens[6]);
    clay_robot_costs_in_ore[id]       = std::stoi(tokens[12]);
    obsidean_robot_costs_in_ore[id]   = std::stoi(tokens[18]);
    obsidean_robot_costs_in_clay[id]  = std::stoi(tokens[21]);
    geode_robot_costs_in_ore[id]      = std::stoi(tokens[27]);
    geode_robot_costs_in_obsidean[id] = std::stoi(tokens[30]);
  }

  std::vector<int> maxs(SIZE);

  #pragma omp parallel for
  for (size_t id = 0; id < SIZE; id++)
  {
    uint16_t max = recursion_A(id, 0, 0, 0, 0, 0, 1, 0, 0, 0);
    std::cout << (id+1) << ": " << max << std::endl;
    maxs[id] = max;
  }

  int product = 1;
  for (size_t id = 0; id < SIZE; id++)
  {
    product *= maxs[id];
  }

  std::cout << product << std::endl;
}

int main()
{
  // solve_A();
  solve_B();
  return 0;
}