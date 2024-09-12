#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ifstream infile("input.txt");

  vector<long long> v;
  long long n, k, a;
  infile >> n >> k;
  while (infile >> a)
    v.push_back(a);

  long long l = 0, r = v.back() - v.front() + 1;
  while (l + 1 < r) {
    long long m = (l + r) / 2, last = 0, count = 1;
    for (long long i = 0; i < n; ++i) {
      if (v.at(i) - v.at(last) >= m) {
        count += 1;
        last = i;
      }
    }
    if (count < k) {
      r = m;
    } else {
      l = m;
    }
  }
  cout << l;
  return 0;
}
