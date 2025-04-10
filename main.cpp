#include <bits/stdc++.h>
#include "Vector.h"

using namespace std;

int main() {
  double*  kek{new double[4]{0, 2.1, 4.6, 5}};
  Vector v(kek, 0);
  v.pushBack(9.0);

  for (size_t i = 0; i < 5; i++)
  {
    cout << v[i] << endl;
  }
    
  cout << "DONE\n";
  return 0;
}