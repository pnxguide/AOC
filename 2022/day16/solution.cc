#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <deque>
#include <set>
#include <unordered_map>
#include <algorithm>

int BOUND = 30;

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

// Map node with ID
std::unordered_map< std::string, int > V_map;
std::unordered_map< int, std::string > map_V;
std::vector<int> V(50, 0);
std::vector< std::set<int> > adj(50);
std::vector<int> reverse_nonzero_map(50);
std::vector<int> nonzero_map;
int nnz = 0;

std::vector< std::vector<int> > shortest(50, std::vector<int>(50));

std::unordered_map<uint64_t, int> recursion_A_table;

uint64_t hash(int a, int b, std::set<int> c)
{
  // 11 bits
  uint64_t h = (a * nnz + reverse_nonzero_map[b]);

  // c
  // 15 bits
  h <<= nnz;
  for (int cc : c)
  {
    h |= (0b1 << reverse_nonzero_map[cc]);
  }

  return h;
}

int recursion_A(int current_time, int current_node, std::set<int> is_visited)
{
  // Cache
  int h = hash(current_time, current_node, is_visited);
  int cached = recursion_A_table[h];
  if (cached != 0)
  {
    return cached;
  }

  is_visited.insert(current_node);

  if (current_time > BOUND) 
  {
    recursion_A_table[h] = 0;
    return 0;
  }

  else
  {
    // Calculate yields and use the maximum one
    int max_yield = 0;
    for (int k = 0; k < nnz; k++)
    {
      int i = nonzero_map[k];
      if (is_visited.find(i) != is_visited.end()) continue;

      int yield = ((BOUND - current_time) - shortest[current_node][i] - 1) * V[i];
      if (yield > 0)
      {
        max_yield = std::max(
          max_yield, 
          yield + recursion_A(current_time + shortest[current_node][i] + 1, i, is_visited));
      }
    }

    // if (max_yield != 0)
    // {
    //   for (size_t i = 0; i < level * 2; i++) std::cout << " ";
    //   std::cout << "(" << map_V[current_node] << ") " << max_yield << std::endl;
    // }

    recursion_A_table[h] = max_yield;
    return max_yield;
  }
}

uint64_t hashB(int a, int b, int x, int y, std::set<int> c)
{
  // 11 bits
  uint64_t h = ((a * nnz + reverse_nonzero_map[b]) * (BOUND * nnz)) + (x * nnz + reverse_nonzero_map[y]);

  // c
  // 15 bits
  h <<= nnz;
  for (int cc : c)
  {
    h |= (0b1 << reverse_nonzero_map[cc]);
  }

  return h;
}

std::unordered_map<uint64_t, int> recursion_B_table;

int recursion_B(int current_time1, int current_time2, int current_node1, int current_node2, std::set<int> is_visited)
{
  uint64_t h = hashB(current_time1, current_time2, current_node1, current_node2, is_visited);
  int cached = recursion_B_table[h];
  if (cached != 0)
  {
    return cached;
  }

  is_visited.insert(current_node1);
  is_visited.insert(current_node2);

  if (current_time1 > BOUND && current_time2 > BOUND) 
  {
    recursion_B_table[h] = 0;
    return 0;
  }
  else
  {
    // Calculate yields and use the maximum one
    int max_yield = 0;

    std::vector<int> yields1(50);
    std::vector<int> yields2(50);
    std::vector<int> yields1_list;
    std::vector<int> yields2_list;
    
    for (int k = 0; k < nnz; k++)
    {
      int i = nonzero_map[k];

      if (is_visited.find(i) == is_visited.end())
      {
        yields1[i] = ((BOUND - current_time1) - shortest[current_node1][i] - 1) * V[i];
        yields2[i] = ((BOUND - current_time2) - shortest[current_node2][i] - 1) * V[i];

        if (yields1[i] > 0)
        {
          yields1_list.push_back(i);
        }

        if (yields2[i] > 0) 
        {
          yields2_list.push_back(i);
        }
      }
    }

    // Expand two directions
    for (int i : yields1_list)
    {
      // int i = nonzero_map[x];
      int yield1 = yields1[i];

      for (int j : yields2_list)
      {
        // int j = nonzero_map[y];
        int yield2 = yields2[j];

        if (i != j)
        {
          // std::cout << map_V[i] << " (" << current_time1 << ") / " << map_V[j] << " (" << current_time2 << ")" << std::endl;
          // std::cout << "Yield: " << yield1 + yield2 << " (" << yield1 << " + " << yield2 << ")" << std::endl;

          int two_dir = yield1 + yield2 + recursion_B(
            current_time1 + shortest[current_node1][i] + 1,
            current_time2 + shortest[current_node2][j] + 1,
            i, j, is_visited);

          // std::cout << "Yield Received: " << two_dir << std::endl;
            
          max_yield = std::max(max_yield, two_dir);
        }

        // // Expand only one direction
        // {
        //   // std::cout << "(1st) " << map_V[i] << " (" << current_time1 << ")" << std::endl;
        //   // std::cout << "Yield: " << yield1 << std::endl;

        //   int one_dir = yield1 + recursion_A(
        //     current_time1 + shortest[current_node1][i] + 1,
        //     i, is_visited);
          
        //   // std::cout << "Yield Received: " << one_dir << std::endl;
            
        //   max_yield = std::max(max_yield, one_dir);
        // }

        // {
        //   // std::cout << "(2nd) " << map_V[j] << " (" << current_time2 << ")" << std::endl;
        //   // std::cout << "Yield: " << yield2 << std::endl;

        //   int one_dir = yield2 + recursion_A(
        //     current_time2 + shortest[current_node2][j] + 1,
        //     j, is_visited);

        //   // std::cout << "Yield Received: " << one_dir << std::endl;
          
        //   max_yield = std::max(max_yield, one_dir);
        // }
      }
    }

    // Go for one to the left
    for (int i : yields1_list)
    {
      int yield1 = yields1[i];

      // Expand only one direction
      {
        // std::cout << "(1st) " << map_V[i] << " (" << current_time1 << ")" << std::endl;
        // std::cout << "Yield: " << yield1 << std::endl;

        int one_dir = yield1 + recursion_A(
          current_time1 + shortest[current_node1][i] + 1,
          i, is_visited);
        
        // std::cout << "Yield Received: " << one_dir << std::endl;
          
        max_yield = std::max(max_yield, one_dir);
      }
    }

    // Go for one to the right
    for (int i : yields2_list)
    {
      int yield2 = yields1[i];
      
      // Expand only one direction
      {
        // std::cout << "(1st) " << map_V[i] << " (" << current_time1 << ")" << std::endl;
        // std::cout << "Yield: " << yield1 << std::endl;

        int one_dir = yield2 + recursion_A(
          current_time2 + shortest[current_node2][i] + 1,
          i, is_visited);
        
        // std::cout << "Yield Received: " << one_dir << std::endl;
          
        max_yield = std::max(max_yield, one_dir);
      }
    }

    // if (max_yield != 0)
    // {
    //   for (size_t i = 0; i < level * 2; i++) std::cout << " ";
    //   std::cout << "(" << map_V[current_node1] << "," << map_V[current_node2] << ") " << max_yield << std::endl;
    // }

    recursion_B_table[h] = max_yield;
    return max_yield;
  }
}

void solve_A()
{
  BOUND = 30;

  // Read an input file
  std::ifstream input_file("input.txt");
  std::string line;

  int count = 0;
  while (std::getline(input_file, line))
  {
    std::vector< std::string > tokens;
    tokenize(line, ' ', tokens);
    if (V_map.find(tokens[1]) == V_map.end())
    {
      map_V[count] = tokens[1];
      V_map[tokens[1]] = count++;
    }

    std::vector< std::string > subtokens;
    tokenize(tokens[4], '=', subtokens);
    V[V_map[tokens[1]]] = std::stoi(subtokens[1]);

    if (V[V_map[tokens[1]]] != 0 || tokens[1] == "AA")
    {
      nonzero_map.push_back(V_map[tokens[1]]);
      reverse_nonzero_map[V_map[tokens[1]]] = nnz++;
    }

    for (size_t i = 9; i < tokens.size(); i++)
    {
      if (i != tokens.size() - 1) 
      {
        tokens[i].pop_back();
      }
      
      if (V_map.find(tokens[i]) == V_map.end())
      {
        map_V[count] = tokens[i];
        V_map[tokens[i]] = count++;
      }

      adj[V_map[tokens[1]]].insert(V_map[tokens[i]]);
    }
  }

  for (int k = 0; k < count; k++)
  {
    std::set<int> b, m, c;
    std::vector<int> lengths(50, 999);
    b.insert(k);
    m.insert(k);

    for (int i = 0; i < BOUND; i++)
    {
      if (b.size() == 0) break;

      // Update lengths
      for (int s : b)
      {
        // if (shortest[k][s] == 0)
        shortest[k][s] = i;
      }

      // c = Ab - m
      // union all selected rows
      for (int b_i : b)
      {
        // Union
        std::set<int> tmp;
        std::set_union(c.begin(), c.end(), adj[b_i].begin(), adj[b_i].end(),
          std::inserter(tmp, tmp.end()));
        c = tmp;
      }
      // Difference
      b.clear();
      std::set_difference(c.begin(), c.end(), m.begin(), m.end(),
        std::inserter(b, b.end()));
      // Update m
      std::set<int> tmp;
      std::set_union(m.begin(), m.end(), b.begin(), b.end(),
        std::inserter(tmp, tmp.end()));
      m = tmp;
    }
  }

  // Compute SSSP from the current node
  // Using BFS
  int current_node = V_map["AA"];

  std::set<int> is_visited;
  is_visited.insert(current_node);

  std::cout << recursion_A(0, V_map["AA"], is_visited) << std::endl;
}

void solve_B()
{
  BOUND = 26;

  // Read an input file
  std::ifstream input_file("input.txt");
  std::string line;

  int count = 0;
  while (std::getline(input_file, line))
  {
    std::vector< std::string > tokens;
    tokenize(line, ' ', tokens);
    if (V_map.find(tokens[1]) == V_map.end())
    {
      map_V[count] = tokens[1];
      V_map[tokens[1]] = count++;
    }

    std::vector< std::string > subtokens;
    tokenize(tokens[4], '=', subtokens);
    V[V_map[tokens[1]]] = std::stoi(subtokens[1]);

    if (V[V_map[tokens[1]]] != 0 || tokens[1] == "AA")
    {
      nonzero_map.push_back(V_map[tokens[1]]);
      reverse_nonzero_map[V_map[tokens[1]]] = nnz++;
    }

    for (size_t i = 9; i < tokens.size(); i++)
    {
      if (i != tokens.size() - 1) 
      {
        tokens[i].pop_back();
      }
      
      if (V_map.find(tokens[i]) == V_map.end())
      {
        map_V[count] = tokens[i];
        V_map[tokens[i]] = count++;
        
      }

      adj[V_map[tokens[1]]].insert(V_map[tokens[i]]);
    }
  }

  for (int k = 0; k < count; k++)
  {
    std::set<int> b, m, c;
    std::vector<int> lengths(50, 999);
    b.insert(k);
    m.insert(k);

    for (int i = 0; i < BOUND; i++)
    {
      if (b.size() == 0) break;

      // Update lengths
      for (int s : b)
      {
        // if (shortest[k][s] == 0)
        shortest[k][s] = i;
      }

      // c = Ab - m
      // union all selected rows
      for (int b_i : b)
      {
        // Union
        std::set<int> tmp;
        std::set_union(c.begin(), c.end(), adj[b_i].begin(), adj[b_i].end(),
          std::inserter(tmp, tmp.end()));
        c = tmp;
      }
      // Difference
      b.clear();
      std::set_difference(c.begin(), c.end(), m.begin(), m.end(),
        std::inserter(b, b.end()));
      // Update m
      std::set<int> tmp;
      std::set_union(m.begin(), m.end(), b.begin(), b.end(),
        std::inserter(tmp, tmp.end()));
      m = tmp;
    }
  }

  int current_node = V_map["AA"];

  std::set<int> is_visited;
  is_visited.insert(current_node);

  std::cout << recursion_B(0, 0, V_map["AA"], V_map["AA"], is_visited) << std::endl;
}

int main()
{
  // solve_A();
  solve_B();
  return 0;
}
