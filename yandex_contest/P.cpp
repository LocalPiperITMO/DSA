#include <algorithm>
#include <ios>
#include <iostream>
#include <vector>

using namespace std;
void DFS_horizontal(vector<vector<int>> &grid, vector<bool> &visited, int v,
                    int target) {
  visited[v] = true;
  for (int i = 0; i < grid.size(); ++i) {
    if (!visited[i] && grid[v][i] <= target) {
      DFS_horizontal(grid, visited, i, target);
    }
  }
}

void DFS_vertical(vector<vector<int>> &grid, vector<bool> &visited, int v,
                  int target) {
  visited[v] = true;
  for (int i = 0; i < grid.size(); ++i) {
    if (!visited[i] && grid[i][v] <= target) {
      DFS_vertical(grid, visited, i, target);
    }
  }
}

bool tryToPass(vector<vector<int>> &matrix, int fuelCapacity) {
  int n = matrix.size();
  vector<bool> visited(n, false);

  DFS_horizontal(matrix, visited, 0, fuelCapacity);

  for (int i = 0; i < n; ++i) {
    if (!visited[i])
      return false;
  }

  vector<bool> visited2(n, false);

  DFS_vertical(matrix, visited2, 0, fuelCapacity);

  for (int i = 0; i < n; ++i) {
    if (!visited2[i])
      return false;
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  int r = 0;
  vector<vector<int>> matrix(n, vector<int>(n, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> matrix[i][j];
      r = max(r, matrix[i][j]);
    }
  }

  int l = -1;
  ++r;
  while (r - l > 1) {
    int mid = (l + r) / 2;
    if (tryToPass(matrix, mid)) {
      r = mid;
    } else {
      l = mid;
    }
  }
  cout << r;
  return 0;
}
