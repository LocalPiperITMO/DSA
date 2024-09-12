#include <iostream>
#include <vector>

using namespace std;

int main() {
  size_t t;
  long long n, k;
  vector<long long> nk, v;
  cin >> t;
  for (size_t i = 0; i < t; ++i) {
    cin >> n >> k;
    nk.clear();
    for (size_t j = 0; j < k; ++j) {
      nk.push_back(n / k);
    }
    for (size_t j = 0; j < (n % k); ++j) {
      ++nk.at(j);
    }

    long long s = 0;
    for (long long ni : nk) {
      s += ni * (n - ni);
    }
    v.push_back(s / 2);
  }
  for (long long j : v) {
    cout << j << "\n";
  }

  return 0;
}
