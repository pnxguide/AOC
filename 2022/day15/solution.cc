#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <deque>
#include <set>
#include <unordered_map>
#include <algorithm>

#define TARGET 2000000
#define TARGET2 4000000

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

  std::vector< std::pair<int, int> > ranges;

  while (std::getline(input_file, line))
  {
    std::vector< std::string > tokens;
    tokenize(line, ' ', tokens);

    // Sensor Position
    int s_x = std::stoi(tokens[2].substr(2));
    int s_y = std::stoi(tokens[3].substr(2));

    // Nearest Beacon
    int n_x = std::stoi(tokens[8].substr(2));
    int n_y = std::stoi(tokens[9].substr(2));

    // Distance
    int distance = std::abs(s_x - n_x) + std::abs(s_y - n_y);

    // Check if the distance
    // If s_y - distance (min) < 10 and s_y + distance > 10

    // Target is above
    if (s_y - distance < TARGET && s_y + distance > TARGET)
    {
      int dist_left = distance - std::abs(s_y - TARGET);
      ranges.push_back(std::make_pair(s_x - dist_left, s_x + dist_left));
    }
  }

  // Check ranges overlapping
  // Sort ranges by first
  std::sort(ranges.begin(), ranges.end());

  for (std::pair<int, int> p : ranges)
  {
    std::cout << p.first << " " << p.second << std::endl;
  }
  
  std::vector< std::pair<int, int> > new_ranges;
  int old_range_size = ranges.size();

  bool is_merge = true;

  while (is_merge)
  {
    is_merge = false;
    new_ranges.clear();
    for (int i = 0; i < ranges.size(); i++)
    {
      // Merge ranges
      if (i+1 < ranges.size() && ranges[i].second >= ranges[i+1].first)
      {
        new_ranges.push_back(std::make_pair(ranges[i].first, std::max(ranges[i].second, ranges[i+1].second)));
        is_merge = true;
        i++;
      }

      else
      {
        new_ranges.push_back(ranges[i]);
      }
    }

    ranges = new_ranges;
    std::sort(ranges.begin(), ranges.end());
  }

  int sum_ranges = 0;
  for (std::pair<int, int> p : ranges)
  {
    std::cout << p.first << " " << p.second << std::endl;
    sum_ranges += std::abs(p.first - p.second) + 1;
  }

  std::cout << sum_ranges << std::endl;

  // Need manual set difference
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  std::string line;

  std::vector< std::vector< std::pair<int, int> > > ranges(4000001);

  while (std::getline(input_file, line))
  {
    std::vector< std::string > tokens;
    tokenize(line, ' ', tokens);

    // Sensor Position
    int s_x = std::stoi(tokens[2].substr(2));
    int s_y = std::stoi(tokens[3].substr(2));

    // Nearest Beacon
    int n_x = std::stoi(tokens[8].substr(2));
    int n_y = std::stoi(tokens[9].substr(2));

    // Distance
    int distance = std::abs(s_x - n_x) + std::abs(s_y - n_y);

    std::cout << s_x << " " << s_y << std::endl;

    // Target is above
    for (int i = std::max(s_y - distance, 0); i <= std::min(distance + s_y, TARGET2); i++)
    {
      int dist_left = distance - std::abs(s_y - i);
      ranges[i].push_back(std::make_pair(std::max(s_x - dist_left, 0), std::min(s_x + dist_left, TARGET2)));
      std::sort(ranges[i].begin(), ranges[i].end());

      // Try to merge
      bool is_merge = true;
      while (is_merge)
      {
        is_merge = false;
        std::vector< std::pair<int, int> > new_ranges;
        for (int j = 0; j < ranges[i].size(); j++)
        {
          // Merge ranges
          if (j+1 < ranges[i].size() && ranges[i][j].second >= ranges[i][j+1].first - 1)
          {
            new_ranges.push_back(std::make_pair(ranges[i][j].first, std::max(ranges[i][j].second, ranges[i][j+1].second)));
            j++;
            is_merge = true;
          }

          else
          {
            new_ranges.push_back(ranges[i][j]);
          }
        }
        ranges[i] = new_ranges;
      }
    }
  }

  // Check ranges overlapping
  // Sort ranges by first

  for (int i = 0; i <= TARGET2; i++)
  {
    if (ranges[i].size() == 2)
    {
      std::cout << ranges[i][0].second << " " << ranges[i][1].first << std::endl;
      std::cout << (uint64_t)(ranges[i][1].first - 1) * 4000000 + (uint64_t)(i) << std::endl;
    }
  }
}

int main()
{
  // solve_A();
  solve_B();
  return 0;
}