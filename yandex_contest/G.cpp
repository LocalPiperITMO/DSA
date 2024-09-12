#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

int main() {
  ifstream infile("aurora.in");
  unordered_map<char, int> c;
  unordered_map<char, int> k;
  string s;
  infile >> s;
  for (char a : s)
    ++k[a];
  int w;
  for (char a = 'a'; a <= 'z'; ++a) {
    infile >> w;
    c[a] = w;
  }
  vector<pair<char, int>> vp;
  unordered_map<char, int> used;
  string res;
  for (char a : s) {
    if ((k[a] > 1) && (used[a] < 2)) {
      vp.push_back(make_pair(a, c[a]));
      ++used[a];
    } else {
      res += a;
    }
  }
  // stable sort
  sort(vp.begin(), vp.end(),
       [](const pair<char, int> a, const pair<char, int> b) {
         return a.second == b.second ? a.first < b.first : a.second < b.second;
       });
  for (int i = 0; i < vp.size(); i += 2) {
    res = vp[i].first + res;
    res += vp[i + 1].first;
  }
  cout << res;
  return 0;
}
