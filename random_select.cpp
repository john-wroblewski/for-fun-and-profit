#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

//#define _DEBUG_

#define LIST_SIZE  30
#define LIST_MAX   500

using namespace std;

int 		r_select(vector<int> &, unsigned int, unsigned int, unsigned int);
unsigned int 	r_partition(vector<int> &, unsigned int, unsigned int);
void 		list_swap(vector<int> &, unsigned int, unsigned int);
void 		fancy_print(const vector<int> &);
unsigned int 	partition(vector<int> &, unsigned int, unsigned int);

int main(void)
{
  srand(time(NULL));

  vector<int> list;

  for(unsigned int x = 0;x < LIST_SIZE;x++)
    list.push_back(rand() % (LIST_MAX + 1) - 250);

  fancy_print(list);

  for(unsigned int j = 0;j < list.size();j++)
  {
    auto x = r_select(list, 0, list.size() - 1, j);
    cout << j << " order statistic is " << x << endl;
  }

  sort(list.begin(), list.end());
  fancy_print(list);

  return 0;
}

void
list_swap(vector<int> &list, unsigned int a, unsigned int b)
{
  int temp = list[a];
  list[a] = list[b];
  list[b] = temp;

  return;
}

void
fancy_print(const vector<int> &list)
{
  cout << "[ ";

  if(!list.empty())
  {
    for(unsigned int i = 0; i < list.size() - 1;++i)
      cout << list[i] << ", ";

    cout << list.back() << " ]" << endl;
  }
  else
  {
    cout << " ]" << endl;
  }
}

unsigned int
partition(vector<int> &list, unsigned int p, unsigned int r)
{
  if(p == r)
    return r;

  int x = list[r];
  int k = p - 1;

  for(unsigned int j = p;j < r;j++)
  {
    if(list[j] <= x)
    {
      k++;
      list_swap(list, j, k);
    }
  }

  k++;
  list_swap(list, k, r);

  return unsigned(k);  //not dangerous cast, notice that k = p - 1, where p is an unsigned int
}

unsigned int
r_partition(vector<int> &list, unsigned int p, unsigned int r)
{
  unsigned int k = rand() % (r - p + 1) + p;
  list_swap(list, k, r);

#ifdef _DEBUG_

  cout << "\nrandom partitioning around " << list[r] << endl;

#endif

  auto x = partition(list, p, r);

#ifdef _DEBUG_
  fancy_print(list);
#endif

  return x;
}

int
r_select(vector<int> &list, unsigned int p, unsigned int r, unsigned int i)
{
  if(p == r)
    return list[p];

  unsigned int q = r_partition(list, p, r);
  unsigned int k = q - p;

  if(i == k)
    return list[q];
  if(i < k)
  {
#ifdef _DEBUG_
    cout << "\ncalling select(" << p << ", " << q - 1 << ", " << i << ")\n";
#endif
    return r_select(list, p, q - 1, i);
  }
#ifdef _DEBUG_
  cout << "\ncalling select(" << q + 1 << ", " << r << ", " << i - k - 1 << ")\n";
#endif
  return r_select(list, q + 1, r, i - k - 1);
}
