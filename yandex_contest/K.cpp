#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <utility>
#include <vector>
#define ll long long
#define PLL pair<ll, ll>
using namespace std;
multimap<ll, ll> memoryMapSizeToPointer;
map<ll, ll> memoryMapPointerToSize;

void insertIntoMaps(const PLL p) {
  memoryMapSizeToPointer.insert({p.second, p.first});
  memoryMapPointerToSize[p.first] = p.second;
}

void removeSize(map<ll, ll>::iterator it) {
  auto itBySize = memoryMapSizeToPointer.find(it->second);
  while (itBySize->second != it->first)
    ++itBySize;
  memoryMapSizeToPointer.erase(itBySize);
  memoryMapPointerToSize.erase(it);
}

ll allocateMemory(ll requestedSize, vector<PLL> *requestVector) {
  auto optimalBlockPointer = memoryMapSizeToPointer.lower_bound(requestedSize);
  if (optimalBlockPointer != memoryMapSizeToPointer.end()) {
    // block found
    requestVector->push_back({optimalBlockPointer->second, requestedSize});
    ll newSize = optimalBlockPointer->first - requestedSize,
       newPointer = optimalBlockPointer->second + requestedSize;

    memoryMapSizeToPointer.erase(optimalBlockPointer);
    memoryMapPointerToSize.erase(requestVector->back().first);

    insertIntoMaps({newPointer, newSize});
    return requestVector->back().first;
  }
  // block not found
  requestVector->push_back({-1, requestedSize});
  return -1;
}

void mergeLeftRight(PLL p, map<ll, ll>::iterator l, map<ll, ll>::iterator r) {
  ll start = l->first;
  ll size = l->second + p.second + r->second;
  removeSize(l);
  removeSize(r);
  insertIntoMaps({start, size});
}

void mergeLeft(PLL p, map<ll, ll>::iterator l) {
  ll start = l->first;
  ll size = l->second + p.second;
  removeSize(l);
  insertIntoMaps({start, size});
}

void mergeRight(PLL p, map<ll, ll>::iterator r) {
  ll start = p.first;
  ll size = p.second + r->second;
  removeSize(r);
  insertIntoMaps({start, size});
}

void freeMemory(ll requestNum, vector<PLL> *requestVector) {
  PLL possibleSatisfiedRequest = requestVector->at(requestNum);
  requestVector->push_back({0, 0});
  if (possibleSatisfiedRequest.first != -1) {
    // need to find both pointed block and his neighbours

    auto rightBlock = memoryMapPointerToSize.lower_bound(
        possibleSatisfiedRequest.second + possibleSatisfiedRequest.first);
    auto leftBlock = (rightBlock == memoryMapPointerToSize.begin())
                         ? memoryMapPointerToSize.end()
                         : prev(rightBlock);

    bool predL =
        leftBlock != memoryMapPointerToSize.end() &&
        leftBlock->first + leftBlock->second == possibleSatisfiedRequest.first;
    bool predR =
        rightBlock != memoryMapPointerToSize.end() &&
        possibleSatisfiedRequest.first + possibleSatisfiedRequest.second ==
            rightBlock->first;

    if (predL && predR) {
      mergeLeftRight(possibleSatisfiedRequest, leftBlock, rightBlock);
      return;
    }
    if (predL) {
      mergeLeft(possibleSatisfiedRequest, leftBlock);
      return;
    }
    if (predR) {
      mergeRight(possibleSatisfiedRequest, rightBlock);
      return;
    }
    insertIntoMaps(
        {possibleSatisfiedRequest.first, possibleSatisfiedRequest.second});
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ifstream infile("input.txt");
  ll N, M, T;
  infile >> N >> M;
  string s;
  vector<PLL> requestVector;
  insertIntoMaps({1, N});
  for (ll i = 1; i <= M; ++i) {
    infile >> T;
    if (T > 0) {
      s += to_string(allocateMemory(T, &requestVector)) + '\n';
    } else {
      freeMemory(-T - 1, &requestVector);
    }
  }
  cout << s;
  return 0;
}
