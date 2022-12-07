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

std::unordered_map< std::string, std::vector<std::string> > path_files;
std::unordered_map< std::string, std::vector<std::string> > path_dirs;
std::unordered_map< std::string, size_t > path_size;

std::vector<size_t> size_rank;

size_t low = 0;

size_t get_size_recursively(std::string path)
{
  size_t total_size = 0;

  if (path_dirs[path].size() != 0)
  {
    for (size_t i = 0; i < path_dirs[path].size(); i++)
    {
      total_size += get_size_recursively(path + path_dirs[path][i]);
    }
  }

  for (size_t i = 0; i < path_files[path].size(); i++)
  {
    total_size += path_size[path + path_files[path][i]];
  }

  if (total_size <= 100000)
  {
    low += total_size;
    // std::cout << total_size << std::endl;
  }

  size_rank.push_back(total_size);

  return total_size;
}

void solve_A()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());
  std::string line;

  size_t total_size = 0;

  std::deque< std::string > current_path;
  std::string current_path_string;

  bool pause = false;
  
  while (true)
  {
    if (!pause) std::getline(input_file, line);
    pause = false;

    std::vector<std::string> tokens;
    tokenize(line, ' ', tokens);

    current_path_string = "";
    for (size_t i = 0; i < current_path.size(); i++)
    {
      current_path_string.append(current_path[i]);
    }

    if (line[0] == '$')
    {
      // cd
      if (tokens[1] == "cd")
      {
        if (tokens[2] == "..")
        {
          current_path.pop_back();
        }

        else
        {
          current_path.push_back(tokens[2]);
        }
      }

      else if (tokens[1] == "ls")
      {
        while (std::getline(input_file, line))
        {
          std::vector<std::string> tokens;
          tokenize(line, ' ', tokens);
          
          if (tokens[0] == "$")
          {
            pause = true;
            break;
          }

          else
          {
            // Directory
            if (tokens[0] == "dir")
            {
              path_dirs[current_path_string].push_back(tokens[1]);
            }

            // File
            else
            {
              path_files[current_path_string].push_back(tokens[1]);
              path_size[current_path_string + tokens[1]] = std::stoul(tokens[0]);
            }
          }
        }
      }
    }

    else
    {
      break;
    }
  }

  std::cout << get_size_recursively("/") << std::endl;
  std::cout << low << std::endl;
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());
  std::string line;

  size_t total_size = 0;

  std::deque< std::string > current_path;
  std::string current_path_string;

  bool pause = false;
  
  while (true)
  {
    if (!pause) std::getline(input_file, line);
    pause = false;

    std::vector<std::string> tokens;
    tokenize(line, ' ', tokens);

    current_path_string = "";
    for (size_t i = 0; i < current_path.size(); i++)
    {
      current_path_string.append(current_path[i]);
    }

    if (line[0] == '$')
    {
      // cd
      if (tokens[1] == "cd")
      {
        if (tokens[2] == "..")
        {
          current_path.pop_back();
        }

        else
        {
          current_path.push_back(tokens[2]);
        }
      }

      else if (tokens[1] == "ls")
      {
        while (std::getline(input_file, line))
        {
          std::vector<std::string> tokens;
          tokenize(line, ' ', tokens);
          
          if (tokens[0] == "$")
          {
            pause = true;
            break;
          }

          else
          {
            // Directory
            if (tokens[0] == "dir")
            {
              path_dirs[current_path_string].push_back(tokens[1]);
            }

            // File
            else
            {
              path_files[current_path_string].push_back(tokens[1]);
              path_size[current_path_string + tokens[1]] = std::stoul(tokens[0]);
            }
          }
        }
      }
    }

    else
    {
      break;
    }
  }

  size_t total = get_size_recursively("/");
  size_t need = 30000000 - (70000000 - total);

  std::sort(size_rank.begin(), size_rank.end());

  for (size_t i = 0; i < size_rank.size(); i++)
  {
    if (size_rank[i] >= need)
    {
      std::cout << size_rank[i] << std::endl;
      break;
    }
  }
}

int main()
{
  // solve_A();
  solve_B();
  return 0;
}