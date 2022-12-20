#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <deque>
#include <set>
#include <unordered_map>
#include <algorithm>

#define POW 811589153

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

class Node
{
  public:
    Node *next;
    Node *prev;
    int value;

    Node(int v)
    {
      value = v;
      next = NULL;
      prev = NULL;
    }
};

void solve_A()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  std::string line;

  Node *head = nullptr;
  Node *cur;

  std::vector<int> cmd;
  std::unordered_map<int , Node *> index;
  
  Node *zero;

  int seq = 0;

  while (std::getline(input_file, line))
  {
    cmd.push_back(std::stoi(line));
    int value = std::stoi(line);

    if (head == nullptr)
    {
      head = new Node(value);
      cur = head;
    }

    else
    {
      Node *tmp = new Node(value);
      cur->next = tmp;
      tmp->prev = cur;
      cur = tmp;
    }

    if (cur->value == 0) zero = cur;

    index[seq++] = cur;
  }

  cur->next = head;
  head->prev = cur;

  // Node *t = zero;
  // for (int i = 0; i < cmd.size(); i++)
  // {
  //   std::cout << (long)t->value * POW << " ";
  //   t = t->next;
  // }
  // std::cout << std::endl;

  int size = cmd.size();

  for (size_t round = 0; round < 10; round++)
  {
    for (size_t i = 0; i < size; i++)
    {
      Node *q = index[i];
      int move = ((q->value % (size - 1)) * (POW % (size - 1))) % (size - 1);

      if (index[i]->value == 0) continue;
      else if (move < 0) move--;

      while (move != 0)
      {
        if (move > 0)
        {
          // Forward
          q = q->next;
          move--;
        }

        else if (move < 0)
        {
          // Backward
          q = q->prev;
          move++;
        }
      }

      // Swap
      Node *p = index[i];

      // std::cout << p->value << " " << q->value << std::endl;

      // No Swap
      if (p == q) continue;

      // Before: 
      //  [p-1] -> [p] -> [p+1]
      //  [q-1] -> [q] -> [q+1]
      // After:
      //  [p-1] -> [p+1]
      //  [q] -> [p] -> [q+1]

      p->prev->next = p->next;
      p->next->prev = p->prev;

      p->next = q->next;
      q->next->prev = p;
      q->next = p;
      p->prev = q;
    }

    // t = zero;
    // for (int i = 0; i < cmd.size(); i++)
    // {
    //   std::cout << (long)t->value * POW << " ";
    //   t = t->next;
    // }
    // std::cout << std::endl;
  }

  // t = index[0];
  // for (int i = 0; i < cmd.size(); i++)
  // {
  //   std::cout << t->value << " ";
  //   t = t->next;
  // }
  // std::cout << std::endl;

  Node *x = zero;
  long sum = 0;
  for (int i = 1; i <= 3000; i++)
  {
    x = x->next;
    if (i % 1000 == 0) sum += ((long)x->value * POW);
  }
  // std::cout << std::endl;

  std::cout << sum << std::endl;
}

void solve_B()
{
  // Read an input file
  std::ifstream input_file("input.txt");
  std::string line;

}

int main()
{
  solve_A();
  // solve_B();
  return 0;
}