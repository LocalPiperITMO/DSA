#include <ios>
#include <iostream>
#include <queue>
#include <set>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k, x;
  cin >> n >> k;
  multiset<int> ms;
  queue<int> q;
  for (int i = 0; i < k; ++i) {
    cin >> x;
    q.push(x);
    ms.insert(x);
  }
  cout << *ms.begin() << " ";
  for (int i = k; i < n; ++i) {
    cin >> x;
    int toRemove = q.front();
    q.pop();
    ms.erase(ms.find(toRemove));
    q.push(x);
    ms.insert(x);
    cout << *ms.begin() << " ";
  }
  return 0;
}
