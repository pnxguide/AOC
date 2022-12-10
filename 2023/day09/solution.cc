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

#define SIZE 99


void solve_A()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());
  std::string line;

  std::set< std::pair<int, int> > visited;
  int xH = 0, yH = 0;
  int xT = 0, yT = 0;
  visited.insert(std::make_pair(0, 0));

  while (std::getline(input_file, line))
  {
    std::vector< std::string > tokens;
    tokenize(line, ' ', tokens);

    for (int i = 0; i < std::stoi(tokens[1]); i++)
    {
      switch (tokens[0][0])
      {
        case 'R':
          xH++;
          break;
        case 'L':
          xH--;
          break;
        case 'U':
          yH--;
          break;
        case 'D':
          yH++;
          break;
      }

      // T . .
      // . . .
      // . H .
      if (yT - yH == -2 && xT - xH == -1)
      {
        yT++;
        xT++;
      }

      // . . T
      // . . .
      // . H .
      else if (yT - yH == -2 && xT - xH == 1)
      {
        yT++;
        xT--;
      }

      // . H .
      // . . .
      // T . .
      else if (yT - yH == 2 && xT - xH == -1)
      {
        yT--;
        xT++;
      }

      // . H .
      // . . .
      // . . T
      else if (yT - yH == 2 && xT - xH == 1)
      {
        yT--;
        xT--;
      }

      // T . .
      // . . H
      // . . .
      else if (yT - yH == -1 && xT - xH == -2)
      {
        yT++;
        xT++;
      }

      // . . .
      // . . H
      // T . .
      else if (yT - yH == 1 && xT - xH == -2)
      {
        yT--;
        xT++;
      }

      // . H .
      // . . .
      // T . .
      else if (yT - yH == -1 && xT - xH == 2)
      {
        yT++;
        xT--;
      }

      // . H .
      // . . .
      // . . T
      else if (yT - yH == 1 && xT - xH == 2)
      {
        yT--;
        xT--;
      }

      // . H .
      // . . .
      // . T .
      else if (yT - yH == 2 && xT - xH == 0)
      {
        yT--;
      }

      // . T .
      // . . .
      // . H .
      else if (yT - yH == -2 && xT - xH == 0)
      {
        yT++;
      }

      // . . .
      // H . T
      // . . .
      else if (xT - xH == 2 && yT - yH == 0)
      {
        xT--;
      }

      // . . .
      // T . H
      // . . .
      else if (xT - xH == -2 && yT - yH == 0)
      {
        xT++;
      }

      std::cout << xH << " " << yH << " :: " << xT << " " << yT << std::endl;
      visited.insert(std::make_pair(xT, yT));
    }
  }

  std::cout << visited.size() << std::endl;
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  assert(input_file.is_open());
  std::string line;

  std::set< std::pair<int, int> > visited;
  std::vector< std::pair<int, int> > tails;
  tails.push_back(std::make_pair(0, 0));
  tails.push_back(std::make_pair(0, 0));
  tails.push_back(std::make_pair(0, 0));
  tails.push_back(std::make_pair(0, 0));
  tails.push_back(std::make_pair(0, 0));
  tails.push_back(std::make_pair(0, 0));
  tails.push_back(std::make_pair(0, 0));
  tails.push_back(std::make_pair(0, 0));
  tails.push_back(std::make_pair(0, 0));
  tails.push_back(std::make_pair(0, 0));
  visited.insert(tails[0]);

  while (std::getline(input_file, line))
  {
    std::vector< std::string > tokens;
    tokenize(line, ' ', tokens);

    for (int i = 0; i < std::stoi(tokens[1]); i++)
    {
      switch (tokens[0][0])
      {
        case 'R':
          tails[0].first++;
          break;
        case 'L':
          tails[0].first--;
          break;
        case 'U':
          tails[0].second--;
          break;
        case 'D':
          tails[0].second++;
          break;
      }

      std::pair<int, int> last = tails.back();

      for (int j = 1; j < tails.size(); j++)
      {
        // T . .
        // . . .
        // . H .
        if (tails[j].second - tails[j-1].second == -2 && tails[j].first - tails[j-1].first == -1)
        {
          tails[j].second++;
          tails[j].first++;
        }

        // . . T
        // . . .
        // . H .
        else if (tails[j].second - tails[j-1].second == -2 && tails[j].first - tails[j-1].first == 1)
        {
          tails[j].second++;
          tails[j].first--;
        }

        // . H .
        // . . .
        // T . .
        else if (tails[j].second - tails[j-1].second == 2 && tails[j].first - tails[j-1].first == -1)
        {
          tails[j].second--;
          tails[j].first++;
        }

        // . H .
        // . . .
        // . . T
        else if (tails[j].second - tails[j-1].second == 2 && tails[j].first - tails[j-1].first == 1)
        {
          tails[j].second--;
          tails[j].first--;
        }

        // T . .
        // . . H
        // . . .
        else if (tails[j].second - tails[j-1].second == -1 && tails[j].first - tails[j-1].first == -2)
        {
          tails[j].second++;
          tails[j].first++;
        }

        // . . .
        // . . H
        // T . .
        else if (tails[j].second - tails[j-1].second == 1 && tails[j].first - tails[j-1].first == -2)
        {
          tails[j].second--;
          tails[j].first++;
        }

        // . H .
        // . . .
        // T . .
        else if (tails[j].second - tails[j-1].second == -1 && tails[j].first - tails[j-1].first == 2)
        {
          tails[j].second++;
          tails[j].first--;
        }

        // . H .
        // . . .
        // . . T
        else if (tails[j].second - tails[j-1].second == 1 && tails[j].first - tails[j-1].first == 2)
        {
          tails[j].second--;
          tails[j].first--;
        }

        // . H .
        // . . .
        // . T .
        else if (tails[j].second - tails[j-1].second == 2 && tails[j].first - tails[j-1].first == 0)
        {
          tails[j].second--;
        }

        // . T .
        // . . .
        // . H .
        else if (tails[j].second - tails[j-1].second == -2 && tails[j].first - tails[j-1].first == 0)
        {
          tails[j].second++;
        }

        // . . .
        // H . T
        // . . .
        else if (tails[j].first - tails[j-1].first == 2 && tails[j].second - tails[j-1].second == 0)
        {
          tails[j].first--;
        }

        // . . .
        // T . H
        // . . .
        else if (tails[j].first - tails[j-1].first == -2 && tails[j].second - tails[j-1].second == 0)
        {
          tails[j].first++;
        }

        // . H .
        // . . .
        // . T .
        else if (tails[j].second - tails[j-1].second == 2 && tails[j].first - tails[j-1].first == 2)
        {
          tails[j].first--;
          tails[j].second--;
        }

        // . T .
        // . . .
        // . H .
        else if (tails[j].second - tails[j-1].second == 2 && tails[j].first - tails[j-1].first == -2)
        {
          tails[j].first++;
          tails[j].second--;
        }

        // . . .
        // H . T
        // . . .
        else if (tails[j].second - tails[j-1].second == -2 && tails[j].first - tails[j-1].first == 2)
        {
          tails[j].first--;
          tails[j].second++;
        }

        // . . .
        // T . H
        // . . .
        else if (tails[j].second - tails[j-1].second == -2 && tails[j].first - tails[j-1].first == -2)
        {
          tails[j].first++;
          tails[j].second++;
        }
      }
      visited.insert(tails.back());
    }
  }

  std::cout << visited.size() << std::endl;
}

int main()
{
  // solve_A();
  solve_B();
  return 0;
}