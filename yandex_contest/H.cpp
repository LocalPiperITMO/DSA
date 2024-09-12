#include <algorithm>
#include <ios>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, k;
  cin >> n >> k;
  vector<int> a;
  int num, s = 0;
  for (int i = 0; i < n; ++i) {
    cin >> num;
    s += num;
    a.push_back(num);
  }

  if (k > n) {
    cout << s;
    return 0;
  }

  sort(a.begin(), a.end(), [](const int a, const int b) { return a > b; });
  int count = 0;
  for (int num : a) {
    ++count;
    if (count >= k) {
      s -= num;
      count = 0;
    }
  }
  cout << s;
  return 0;
}
