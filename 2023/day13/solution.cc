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

void parse_string(std::string line1, std::string line2, std::vector< std::string > &l1, std::vector< std::string > &l2)
{
  std::string tmp;
  int open_count = 0;

  for (size_t i = 1; i < line1.size(); i++)
  {
    if (open_count == 0 && (line1[i] == ',' || line1[i] == ']'))
    {
      // std::cout << tmp << std::endl;
      if (tmp != "") l1.push_back(tmp);
      tmp = "";
    }

    else
    {
      tmp.push_back(line1[i]);
      if (line1[i] == '[') open_count++;
      else if (line1[i] == ']') open_count--;
    }
  }

  open_count = 0;

  for (size_t i = 1; i < line2.size(); i++)
  {
    if (open_count == 0 && (line2[i] == ',' || line2[i] == ']'))
    {
      // std::cout << tmp << std::endl;
      if (tmp != "") l2.push_back(tmp);
      tmp = "";
    }

    else
    {
      tmp.push_back(line2[i]);
      if (line2[i] == '[') open_count++;
      else if (line2[i] == ']') open_count--;
    }
  }
}

int recursively_check_order(std::vector< std::string > &l1, std::vector< std::string > &l2)
{
  // Compare
  int is_wrong_order = 0;

  for (size_t i = 0; i < l1.size() && (is_wrong_order == 0); i++)
  {
    // If l2 is running out
    if (!(i < l2.size()))
    {
      // std::cout << "[Debug] " << l1[i] << " vs " << "(Running Out!)" << std::endl;
      is_wrong_order = 1;
      break;
    }

    // std::cout << "[Debug] " << l1[i] << " vs " << l2[i] << std::endl;

    // Empty to ?
    if (l1[i] == "" && l2[i] != "")
    {
      is_wrong_order = -1;
    }

    // ? to Empty
    else if (l1[i] != "" && l2[i] == "")
    {
      is_wrong_order = 1;
    }

    else if (l1[i] == "" && l2[i] == "")
    {}

    // Number to Number
    else if (l1[i][0] != '[' && l2[i][0] != '[')
    {
      if (std::stoi(l1[i]) > std::stoi(l2[i]))
      {
        is_wrong_order = 1;
      }

      else if (std::stoi(l1[i]) < std::stoi(l2[i]))
      {
        is_wrong_order = -1;
      }
    }

    // List to Number
    else if (l1[i][0] == '[' && l2[i][0] != '[')
    {
      // Convert number to list and retry
      l2[i] = "[" + l2[i] + "]";
      // std::cout << "[Debug] " << l1[i] << " vs " << l2[i] << std::endl;
    }

    // Number to List
    else if (l1[i][0] != '[' && l2[i][0] == '[')
    {
      // Convert number to list and retry
      l1[i] = "[" + l1[i] + "]";
      // std::cout << "[Debug] " << l1[i] << " vs " << l2[i] << std::endl;
    }

    // List to List
    if (l1[i][0] == '[' && l2[i][0] == '[')
    {
      // Broke the list and compare
      std::vector< std::string > broken_l1, broken_l2;
      parse_string(l1[i], l2[i], broken_l1, broken_l2);

      is_wrong_order = recursively_check_order(broken_l1, broken_l2);
    }
  }

  if (is_wrong_order == 0 && l1.size() < l2.size())
  {
    is_wrong_order = -1;
  }

  return is_wrong_order;
}

bool sort_handler(std::string l1, std::string l2)
{
  std::vector< std::string > broken_l1, broken_l2;
  parse_string(l1, l2, broken_l1, broken_l2);

  return recursively_check_order(broken_l1, broken_l2) == -1;
}

void solve_A()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());
  std::string line1, line2;

  int cur_index = 1;
  int sum = 0;

  while (std::getline(input_file, line1) && std::getline(input_file, line2))
  {
    std::vector< std::string > l1, l2;
    l1.push_back(line1);
    l2.push_back(line2);

    // std::cout << "Pair " << cur_index << ":" << std::endl;
    if (recursively_check_order(l1, l2) != 1)
    {
      sum += cur_index;
      // std::cout << "Good" << std::endl;
    }
    // std::cout << std::endl;

    cur_index++;

    std::getline(input_file, line1);
  }

  std::cout << sum << std::endl;
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());
  std::string line;
  std::vector< std::string > data;

  while (std::getline(input_file, line))
  {
    if (line != "") data.push_back(line);
  }

  data.push_back("[[2]]");
  data.push_back("[[6]]");

  std::sort (data.begin(), data.end(), sort_handler);

  int product = 1;
  for (size_t i = 0; i < data.size(); i++)
  {
    if (data[i] == "[[2]]" || data[i] == "[[6]]") product *= (i+1);
  }

  std::cout << product << std::endl;
}

int main()
{
  solve_A();
  solve_B();
  return 0;
}