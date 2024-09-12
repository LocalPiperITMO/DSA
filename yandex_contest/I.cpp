#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

class Compare{
  public:
  bool operator()(const pair<int, int> a, const pair<int, int> b) {
    return (a.second == b.second)? a.first > b.first : a.second < b.second;
  }

};
int main() {
  ifstream infile("input.txt");
  int n, k, p;
  infile >> n >> k >> p;

  unordered_map<int, unordered_multimap<int, int>::iterator> requests;
  unordered_multimap<int, int> currentNextPair;
  vector<unordered_multimap<int, int>::iterator> requestVector;

  for (int i = 0; i < p; ++i) {
    int car;
    infile >> car;
    auto findCar = requests.find(car);
    if (findCar == requests.end()) {
      auto carNext = currentNextPair.insert({car, 1e7});
      requests[car] = carNext;
      requestVector.push_back(carNext);
    } else {
      findCar->second->second = i;
      auto carNext = currentNextPair.insert({car, 1e7});
      requests[car] = carNext;
      requestVector.push_back(carNext);
    }

  }

  int numOp = 0, currentK = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
  unordered_set<int> carsOnFloor;
  for (int i = 0; i < requestVector.size(); ++i) {
    auto car = requestVector[i];
    if (carsOnFloor.find(car->first) == carsOnFloor.end()) {
      if (currentK >= k) {
        int carToRemove = pq.top().first;
        carsOnFloor.erase(carToRemove);
        pq.pop();
        --currentK;
      }
      carsOnFloor.insert(car->first);
      pq.push({car->first, car->second});
      ++numOp;
      ++currentK;
    } else {
      auto car = requestVector[i];
      pq.push({car->first, car->second});
    }
  }
  cout << numOp;
  return 0;
}
