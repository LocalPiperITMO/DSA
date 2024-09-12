#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
const long INF = 1e7;

struct Node {
  long g;
  int num;
};
bool operator<(const Node &a, const Node &b) { return a.g > b.g; }

int main() {
  ifstream infile("input.txt");

  int n, m, y_start, x_start, y_end, x_end;
  infile >> n >> m >> y_start >> x_start >> y_end >> x_end;

  vector<string> grid(n);
  for (int i = 0; i < n; ++i) {
    infile >> grid[i];
  }

  vector<Node> visited(n * m);
  for (int i = 0; i < n * m; ++i) {
    visited[i] = {-1, -1};
  }

  unordered_map<char, int> chmp;
  chmp['.'] = 1;
  chmp['W'] = 2;
  chmp['#'] = INF;

  int start = (x_start - 1) + (y_start - 1) * m;
  int end = (x_end - 1) + (y_end - 1) * m;

  visited[start] = {0, start};
  priority_queue<Node> pq;
  pq.push({0, start});

  while (!pq.empty()) {
    auto curr_node = pq.top();
    pq.pop();

    if (curr_node.num == end)
      break;

    int x_cur = curr_node.num % m;
    int y_cur = curr_node.num / m;

    multiset<Node> v;

    if (x_cur - 1 >= 0) {
      v.insert({chmp[grid[y_cur][x_cur - 1]], curr_node.num - 1});
    }
    if (x_cur + 1 < m) {
      v.insert({chmp[grid[y_cur][x_cur + 1]], curr_node.num + 1});
    }
    if (y_cur - 1 >= 0) {
      v.insert({chmp[grid[y_cur - 1][x_cur]], curr_node.num - m});
    }
    if (y_cur + 1 < n) {
      v.insert({chmp[grid[y_cur + 1][x_cur]], curr_node.num + m});
    }

    for (Node next_node : v) {
      long DS =
          curr_node.g + next_node.g >= INF ? INF : curr_node.g + next_node.g;
      if (visited[next_node.num].g == -1 || visited[next_node.num].g > DS) {
        pq.push({DS, next_node.num});
        visited[next_node.num].g = DS;
        visited[next_node.num].num = curr_node.num;
      }
    }
  }
  if (visited[end].num == -1 || visited[end].g >= INF) {
    cout << -1;
    return 0;
  }
  cout << visited[end].g << "\n";
  list<char> res;

  unordered_map<int, char> direct;
  direct[1] = 'E';
  direct[-1] = 'W';
  direct[m] = 'S';
  direct[-m] = 'N';

  int curr = end;
  while (curr != start) {
    res.push_front(direct[curr - visited[curr].num]);
    curr = visited[curr].num;
  }

  for (char i : res) {
    cout << i;
  }
  return 0;
}
