#include <iostream>
#include <queue>
#include <string>
#define P pair<int, int>

using namespace std;
class Compare {
public:
  bool operator()(P a, P b) {
    if (a.second == b.second) {
      return a.first > b.first;
    }
    return a.second < b.second;
  }
};

int main() {
  int k, n;
  cin >> k;
  priority_queue<P, vector<P>, Compare> pq;
  for (int i = 1; i <= k; ++i) {
    cin >> n;
    pq.push({i, n});
  }
  string res = "";
  while (!pq.empty()) {
    P currentFirstMax = pq.top();
    pq.pop();
    res += to_string(currentFirstMax.first) + " ";
    --currentFirstMax.second;
    if (!pq.empty()) {
      P currentSecondMax = pq.top();
      pq.pop();
      res += to_string(currentSecondMax.first) + " ";
      --currentSecondMax.second;
      if (currentSecondMax.second > 0)
        pq.push(currentSecondMax);
    }
    if (currentFirstMax.second > 0)
      pq.push(currentFirstMax);
  }
  cout << res;
  return 0;
}
