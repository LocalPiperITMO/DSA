#include <cmath>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

struct Vertex {
  long long cost;
  int id;
};
bool operator<(const Vertex &a, const Vertex &b) { return a.cost > b.cost; }

int getDif(long long a, long long b) {
  int c = 0;
  while (a != b) {
    a /= 10;
    b /= 10;
    ++c;
  }
  return 10 - c;
}

int main() {
  //ifstream infile("input.txt");
  int n;
  cin >> n;
  vector<long long> difcount(10);
  for (int i = 0; i < 10; ++i) {
    cin >> difcount[i];
  }

  vector<long long> telegraphs(n);
  unordered_map<long long, int> telegraphToIndex;
  for (int i = 0; i < n; ++i) {
    long long t;
    cin >> t;
    telegraphs[i] = t;
    telegraphToIndex[t] = i;
  }

  priority_queue<Vertex> pq;
  pq.push({0, 0});

  vector<Vertex> visited(n, {-1, -1});
  for (int i = 0; i < n; ++i) {
    visited[i] = {-1, -1};
  }
  visited[0] = {0 , 0};
  while (!pq.empty()) {
    auto curr = pq.top();
    pq.pop();
    if (curr.id == n - 1)
      break;
    long long old_val = telegraphs[curr.id];
    // find linked telegraphs by iterating
    multiset<Vertex> linkedTelegraphs;
    for (int i = 0; i < 10; ++i) {
      long long p1 = pow(10, i);
      long long r1 = (old_val / p1) % 10;
      for (int j = 0; j < 10; ++j) {
        long long new_val = old_val - r1 * p1 + j * p1;
        if (old_val == new_val)
          continue;
        auto next = telegraphToIndex.find(new_val);
        if (next != telegraphToIndex.end()) {
          linkedTelegraphs.insert(
              {difcount[getDif(old_val, new_val)], next->second});
        }
      }
      for (int j = i + 1; j < 10; ++j) {
        long long p2 = pow(10, j);
        long long r2 = (old_val / p2) % 10;
        long long new_val = old_val - r1 * p1 + r2 * p1 - r2 * p2 + r1 * p2;
        if (old_val == new_val)
          continue;
        auto next = telegraphToIndex.find(new_val);
        if (next != telegraphToIndex.end()) {
          linkedTelegraphs.insert(
              {difcount[getDif(old_val, new_val)], next->second});
        }
      }
    }
    // iterate through linked telegraphs
    for (auto next : linkedTelegraphs) {
      long long new_cost = curr.cost + next.cost;
      if (visited[next.id].cost == -1 || visited[next.id].cost > new_cost) {
        visited[next.id].cost = new_cost;
        visited[next.id].id = curr.id;
        pq.push({new_cost, next.id});
      }
    }
  }


  if (visited[n - 1].cost == -1) {
    cout << -1 << endl;
  } else {
    cout << visited[n - 1].cost << endl;
    int c = 1;
    for (int i = n - 1; i != 0; i = visited[i].id) {
      c++;
    }
    cout << c << endl;

    vector<int> res;
    for (int i = n - 1; i != 0; i = visited[i].id) {
      res.push_back(i + 1);
    }
    res.push_back(1);
    
    for (int i = c - 1; i >= 0; --i) {
      cout << res[i] << " ";
    }
    cout << endl;
  }

  return 0; 
}