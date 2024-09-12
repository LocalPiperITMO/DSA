#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;
const long INF = 1e7;

struct Node {
  Node() : d(-1), predecessor(-1), visited(false) {}
  int d;
  int predecessor;
  bool visited;
};

int kek(vector<string>& grid, int v, int m) {
  char a = grid[v / m][v % m];
  if (a == '.') {
    return 1;
  } else if (a == 'W') {
    return 2;
  }
  return INF;
}

int main() {
  ifstream infile("input.txt");

  int n, m, y_start, x_start, y_end, x_end;
  infile >> n >> m >> y_start >> x_start >> y_end >> x_end;

  vector<string> grid(n);
  for (int i = 0; i < n; ++i) {
    infile >> grid[i];
  }

  vector<Node> visited(n * m, Node());


  int s = (x_start - 1) + (y_start - 1) * m;
  int e = (x_end - 1) + (y_end - 1) * m;
  visited[s].d = 0;
  visited[s].predecessor = s;
  visited[s].visited = true;

  vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  queue<int> q;
  q.push(s);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    if (kek(grid, u, m) == INF) continue;
    

    for (auto dir : directions) {
      int next_x = u % m + dir.first;
      int next_y = u / m + dir.second;
      
      if (next_x < 0 || next_x >= m || next_y < 0 || next_y >= n)
        continue;
      int v = u + dir.first + dir.second * m;
      
      int new_d = visited[u].d + kek(grid, v, m);

      if (!visited[v].visited || visited[v].d > new_d) {
        visited[v].d = (new_d > INF) ? INF : new_d;
        visited[v].predecessor = u;
        visited[v].visited = true;
        q.push(v);
      }
    }
  }

  if (!visited[e].visited || visited[e].d >= INF) {
    cout << -1;
    return 0;
  }
  cout << visited[e].d << "\n";
  list<char> res;

  int curr = e;
  while (curr != s) {
    int dif = curr - visited[curr].predecessor;
    if (dif == 1) {
      res.push_front('E');
    } else if (dif == -1) {
      res.push_front('W');
    } else if (dif == m) {
      res.push_front('S');
    } else {
      res.push_front('N');
    }
    curr = visited[curr].predecessor;
  }

  for (char i : res) {
    cout << i;
  }
  return 0;
}
