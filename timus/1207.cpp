#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int findKMin(vector<int> v, int l, int r, int k) {
  // BFPRT
  int p1 = l, p2 = r;
  while (p1 < p2) {
    if (p1 >= p2) {
      break;
    }
    int n = p2 - p1 + 1;
    if (n < 5) {
      sort(v.begin() + p1, v.begin() + p1 + n);
      int m = (p1 * 2 + n) / 2;
      swap(v[p1], v[m]);
      break;
    }
    int p = p1;
    for (int i = p1; i < n / 5; ++i) {
      int p_left = p1 + i * 5;
      int p_right = p1 + i * 5 + 5;
      sort(v.begin() + p_left, v.begin() + p_right);
      int m = (p_left + p_right) / 2;
      swap(v[p], v[m]);
      ++p;
    }
    p2 = p - 1;
  }

  // partition
  int i = r;
  for (int j = r; j >= 1; --j) {
    if (v[j] < v[l]) {
      swap(v[j], v[i]);
      --i;
    }
  }
  swap(v[l], v[i]);
  if (i == k) {
    return v[i];
  } else if (i > k) {
    return findKMin(v, l, i - 1, k);
  }
  return findKMin(v, i + 1, r, k);
}

int main() {
  ifstream infile("input3.txt");
  int n, x;
  infile >> n;
  vector<int> A;
  for (int i = 0; i < n; ++i) {
    infile >> x;
    A.push_back(x);
  }
  cout << findKMin(A, 0, A.size() - 1, n / 2);
  return 0;
}
