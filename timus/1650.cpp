#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main() {
  int n, m, k;
  cin >> n;
  string man, city;
  long long money;

  unordered_map<string, pair<long long, string>> manInfo;
  map<long long, unordered_set<string>> leaderboard;
  unordered_map<string, long long> cityMoney;

  for (int i = 0; i < n; ++i) {
    cin >> man >> city >> money;
    manInfo[man] = {money, city};
    if (cityMoney.find(city) == cityMoney.end()) {
      cityMoney[city] = money;
      leaderboard[money].insert(city);
    } else {
      leaderboard[cityMoney[city]].erase(city);
      if (leaderboard[cityMoney[city]].empty())
        leaderboard.erase(cityMoney[city]);
      cityMoney[city] += money;
      leaderboard[cityMoney[city]].insert(city);
    }
  }

  cin >> m >> k;
  queue<pair<int, pair<string, string>>> movement;
  int day;
  for (int i = 0; i < k; ++i) {
    cin >> day >> man >> city;
    movement.push({day, {man, city}});
  }
  day = 0;
  int prev = 0, cur = 0;
  map<string, long long> cityLeadCount;
  for (int i = 0; i <= k; ++i) {
    prev = day;
    if (i == k) {
      day = m;
    } else {
      day = movement.front().first;
      man = movement.front().second.first;
      city = movement.front().second.second;
      movement.pop();
    }
    cur = day;

    if (cur != prev && leaderboard.rbegin()->second.size() == 1) {
      string cityToAdd = *(leaderboard.rbegin()->second.begin());
      cityLeadCount[cityToAdd] += cur - prev;
    }
    if (i < k) {
      string oldCity = manInfo[man].second;
      string newCity = city;
      money = manInfo[man].first;

      leaderboard[cityMoney[oldCity]].erase(oldCity);
      if (leaderboard[cityMoney[oldCity]].empty()) {
        leaderboard.erase(cityMoney[oldCity]);
      }
      cityMoney[oldCity] -= money;
      leaderboard[cityMoney[oldCity]].insert(oldCity);

      leaderboard[cityMoney[newCity]].erase(newCity);
      if (leaderboard[cityMoney[newCity]].empty()) {
        leaderboard.erase(cityMoney[newCity]);
      }
      cityMoney[newCity] += money;
      leaderboard[cityMoney[newCity]].insert(newCity);

      manInfo[man].second = newCity;
    }
  }
  for (const auto it : cityLeadCount) {
    cout << it.first << " " << it.second << "\n";
  }
  return 0;
}
