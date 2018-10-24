/*
 * Takes in a list of numbers and a target difference. Returns the count of pairs of numbers which have a difference of the
 * given target. Runs in linear time.
 */

#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>

using namespace std;

struct capsule{
  vector<pair<int, int> > solution_pairs;
  unsigned int solution_count;
};

struct capsule * diff_pair(vector<int> list, int diff)
{
  struct capsule * ret = new struct capsule;
  ret->solution_count = 0;

  unordered_map<int,bool> table;

  for(auto &x: list)
    table[x] = true;

  for(auto &x: list)
  {
    if(x > diff && table[(x - diff)])
    {
      ret->solution_count++;
      ret->solution_pairs.push_back((make_pair(abs(x - diff), x)));
    }
  }

  return ret;
}

int main(){
  vector<int> in_list = {10, 45, 24, 7, 14, 21};
  int diff = 7;

  struct capsule * cap = diff_pair(in_list,diff);

  cout << cap->solution_count << endl << endl;

  for(auto &x: cap->solution_pairs)
    cout << '<' << x.first << ',' << x.second << '>' << endl;

  return 0;
}
