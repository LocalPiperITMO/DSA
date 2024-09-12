#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
#define XY pair<int, int>
using namespace std;

int main() {
  int m, n, k;
  int res = 0;
  cin >> m >> n >> k;
  vector<pair<int, int>> blackDays;
  set<pair<int, int>> singularDay;
  for (int i = 0; i < k; ++i) {
    int x, y;
    cin >> x >> y;
    blackDays.push_back({x, y});
  }

  for (int i = 0; i <= m + 1; ++i) {
    blackDays.push_back({i, 0});
    blackDays.push_back({i, n + 1});
  }

  for (int j = 0; j <= n + 1; ++j) {
    blackDays.push_back({0, j});
    blackDays.push_back({m + 1, j});
  }

  sort(blackDays.begin(), blackDays.end(),
       [](const pair<int, int> a, const pair<int, int> b) {
         return (a.second == b.second) ? a.first < b.first
                                       : a.second < b.second;
       });

  for (int i = 1; i < blackDays.size() - 1; ++i) {
    int dif = blackDays[i + 1].first - blackDays[i].first;
    if (blackDays[i + 1].second == blackDays[i].second && dif >= 2) {
      if (dif == 2) {
        singularDay.insert({blackDays[i].first + 1, blackDays[i].second});
      } else {
        ++res;
      }
    }
  }

  sort(blackDays.begin(), blackDays.end(), [](const XY a, const XY b) {
    return (a.first == b.first) ? a.second < b.second : a.first < b.first;
  });

  for (int i = 1; i < blackDays.size() - 1; ++i) {
    int dif = blackDays[i + 1].second - blackDays[i].second;
    if (blackDays[i + 1].first == blackDays[i].first && dif >= 2) {
      if (dif == 2) {
        if (singularDay.find({blackDays[i].first, blackDays[i].second + 1}) !=
            singularDay.end()) {
          ++res;
        }
      } else {
        ++res;
      }
    }
  }
  cout << res;
  return 0;
}
