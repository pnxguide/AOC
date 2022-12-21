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

std::unordered_map< std::string, std::string > var1;
std::unordered_map< std::string, std::string > var2;
std::unordered_map< std::string, char > op;
std::unordered_map< std::string, long > mem;
std::unordered_map< std::string, bool > alloc;

long eval(std::string s)
{
  if (alloc[s]) return mem[s];

  std::cout << s << " = " << var1[s] << " " << op[s] << " " << var2[s] << std::endl;

  long res = 0;
  switch (op[s])
  {
    case '+':
      res = eval(var1[s]) + eval(var2[s]);
      break;
    case '-':
      res = eval(var1[s]) - eval(var2[s]);
      break;
    case '*':
      res = eval(var1[s]) * eval(var2[s]);
      break;
    case '/':
      res = eval(var1[s]) / eval(var2[s]);
      break;
  }

  alloc[s] = 1;
  mem[s] = res;
  return res;
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

    tokens[0].pop_back();
    std::string var = tokens[0];

    // if expr
    if (tokens.size() == 4)
    {
      var1[var] = tokens[1];
      var2[var] = tokens[3];
      op[var] = tokens[2][0];

      alloc[var] = 0;
      mem[var] = 0;

      // std::cout << var << " = " << tokens[1] << " " << tokens[2][0] << " " << tokens[3] << std::endl;
    }

    else
    {
      alloc[var] = 1;
      mem[var] = std::stoi(tokens[1]);

      // std::cout << var << " = " << tokens[1] << std::endl;
    }
  }

  std::cout << eval("root") << std::endl;
}

long eval_2(std::string s, bool *status)
{
  if (s == "humn")
  {
    *status = true;
    return -1;
  }

  if (alloc[s]) return mem[s];

  // std::cout << s << " = " << var1[s] << " " << op[s] << " " << var2[s] << std::endl;

  // try eval left
  bool s1 = false;
  long r1 = eval_2(var1[s], &s1);

  // try eval right
  bool s2 = false;
  long r2 = eval_2(var2[s], &s2);

  if (s1 || s2)
  {
    *status = true;
    return -1;
  }

  long res = 0;
  switch (op[s])
  {
    case '+':
      res = r1 + r2;
      break;
    case '-':
      res = r1 - r2;
      break;
    case '*':
      res = r1 * r2;
      break;
    case '/':
      res = r1 / r2;
      break;
  }

  alloc[s] = 1;
  mem[s] = res;
  return res;
}

long find_match(std::string s, long y)
{
  // try eval left
  bool s1 = false;
  long r1 = eval_2(var1[s], &s1);

  // try eval right
  bool s2 = false;
  long r2 = eval_2(var2[s], &s2);

  std::cout << s << ": " << s1 << " " << s2 << std::endl;

  long res = 0;

  if (var1[s] == "humn")
  {
    switch (op[s])
    {
      // y = r1 + r2
      // r1 = y - r2
      case '+':
        res = y - r2;
        break;
      // y = r1 - r2
      // r1 = y + r2
      case '-':
        res = y + r2;
        break;
      // y = r1 * r2
      // r1 = y / r2
      case '*':
        res = y / r2;
        break;
      // y = r1 / r2
      // r1 = y * r2
      case '/':
        res = y * r2;
        break;
    }
  }

  else if (var2[s] == "humn")
  {
    switch (op[s])
    {
      // y = r1 + r2
      // r2 = y - r1
      case '+':
        res = y - r1;
        break;
      // y = r1 - r2
      // -r2 = y - r1
      // r2 = r1 - y
      case '-':
        res = r1 - y;
        break;
      // y = r1 * r2
      // r1 = y / r2
      case '*':
        res = y / r1;
        break;
      // y = r1 / r2
      // r2 = r1 / y
      case '/':
        res = r1 / y;
        break;
    }
  }

  else
  {
    // if left contains humn
    if (s1)
    {
      switch (op[s])
      {
        // y = r1 + r2
        // r1 = y - r2
        case '+':
          res = find_match(var1[s], y - r2);
          break;
        // y = r1 - r2
        // r1 = y + r2
        case '-':
          res = find_match(var1[s], y + r2);
          break;
        // y = r1 * r2
        // r1 = y / r2
        case '*':
          res = find_match(var1[s], y / r2);
          break;
        // y = r1 / r2
        // r1 = y * r2
        case '/':
          res = find_match(var1[s], y * r2);
          break;
      }
    }

    else if (s2)
    {
      switch (op[s])
      {
        // y = r1 + r2
        // r2 = y - r1
        case '+':
          res = find_match(var2[s], y - r1);
          break;
        // y = r1 - r2
        // -r2 = y - r1
        // r2 = r1 - y
        case '-':
          res = find_match(var2[s], r1 - y);
          break;
        // y = r1 * r2
        // r1 = y / r2
        case '*':
          res = find_match(var2[s], y / r1);
          break;
        // y = r1 / r2
        // r2 = r1 / y
        case '/':
          res = find_match(var2[s], r1 / y);
          break;
      }
    }

    else
    {
      // something wrong!
      return -1;
    }
  }

  return res;
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

    tokens[0].pop_back();
    std::string var = tokens[0];

    // if expr
    if (tokens.size() == 4)
    {
      var1[var] = tokens[1];
      var2[var] = tokens[3];
      op[var] = tokens[2][0];

      alloc[var] = 0;
      mem[var] = 0;

      // std::cout << var << " = " << tokens[1] << " " << tokens[2][0] << " " << tokens[3] << std::endl;
    }

    else
    {
      alloc[var] = 1;
      mem[var] = std::stoi(tokens[1]);

      // std::cout << var << " = " << tokens[1] << std::endl;
    }
  }

  // reverse eval
  std::cout << find_match("lrnp", eval("ptnb")) << std::endl;
}

int main()
{
  // solve_A();
  solve_B();
  return 0;
}