#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

int checkMatrix(vector<vector<int>> &a, int i, int j) {
  bool c1 = (i == a.size() - 1 - i);
  bool c2 = (j == a[0].size() - 1 - j);
  if (c1 && c2)
    return 0;
  if (c1) {
    return (a[i][j] == a[i][a[0].size() - 1 - j]) ? 0 : 1;
  }
  if (c2) {
    return (a[i][j] == a[a.size() - 1 - i][j]) ? 0 : 1;
  }

  unordered_map<int, int> freqs;
  ++freqs[a[i][j]];
  ++freqs[a[i][a[0].size() - 1 - j]];
  ++freqs[a[a.size() - 1 - i][j]];
  ++freqs[a[a.size() - 1 - i][a[0].size() - 1 - j]];

  int mx = 0;
  for (auto kvp : freqs) {
    mx = max(mx, kvp.second);
  }
  return 4 - mx;
}

int main() {
  ifstream infile("input.txt");
  int n, m;
  infile >> n >> m;
  vector<vector<int>> a(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      infile >> a[i][j];
    }
  }
  int res = 0;
  for (int i = 0; i < ceil((double) n / 2.0); ++i) {
    for (int j = 0; j < ceil((double) m / 2.0); ++j) {
      res += checkMatrix(a, i, j);
    }
  }
  cout << res;
  return 0;
}
