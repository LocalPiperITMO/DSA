#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool dfs(vector<vector<int>> &graph, vector<int> &visited, int u, int color) {
  if (visited[u] != 0) {
    if (visited[u] != color) {
      return false;
    } else {
      return true;
    }
  }
  visited[u] = color;
  color = (color == 1) ? 2 : 1;
  for (int v = 0; v < graph.size(); ++v) {
    if (graph[u][v] == 1) {
      if (!dfs(graph, visited, v, color)) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  ifstream infile("input.txt");
  int n, m;
  infile >> n >> m;
  vector<int> visited(n, 0);
  vector<vector<int>> graph(n, vector<int>(n, 0));

  for (int i = 0; i < m; ++i) {
    int u, v;
    infile >> u >> v;
    graph[u - 1][v - 1] = 1;
    graph[v - 1][u - 1] = 1;
  }
  bool res = true;
  for (int u = 0; u < visited.size(); ++u) {
    if (visited[u] == 0) {
      res = res && dfs(graph, visited, u, 1);
    }
  }
  if (res) {
    cout << "YES";
  } else {
    cout << "NO";
  }
  return 0;
}
