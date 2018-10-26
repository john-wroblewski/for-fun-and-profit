/*
 * Print all well ordered numbers of length n, where 1 <= n <= 10.
 */

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > well_ordered(int n)
{
  if(n == 1)
  {
    const vector<int> t = {0};
    vector<vector<int> > v(10,t);
    unsigned int i = 0;

    for(auto &x: v){
      x[0] = i;
      i++;
    }
    return v;
  }

  vector<vector<int> > v = well_ordered(n - 1);
  vector<vector<int> > new_vec;

  for(auto &x: v){
    for(int i = x.back() + 1;i <= 9;i++){
      vector<int> temp(x);
      temp.push_back(i);
      new_vec.push_back(temp);
    }
  }

  return new_vec;
}

int main(int argc, char *argv[]){

  if(argc != 2)
  {
    cout << "oops wrong number of arguments" << endl;
    return 1;
  }

  int n = atoi(argv[1]);

  if(n < 1 || n > 10)
  {
    cout << "oops input out of range" << endl;
    return 2;
  }

  vector<vector<int> > v = well_ordered(n);

  for(auto &x: v){
    for(auto &k: x)
      cout << k;
    cout << endl;
  }

  return 0;
}
