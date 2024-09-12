#include <cmath>
#include <iostream>
#include <vector>
#define UP_LEFT 1
#define UP_RIGHT 2
#define DOWN_LEFT 3
#define DOWN_RIGHT 4
using namespace std;

/*
 * angle positions:
 *  X X  XX XX
 * XX XX  X X
 * 1  2  3  4
 */
void print_m(vector<vector<int>> m) {
  for (vector<int> v : m) {
    for (int i : v) {
      cout << i << " ";
    }
    cout << "\n";
  }
}
void angle(int n, int sx, int sy, int *c, vector<vector<int>> *matrix,
           int pos) {
  if (n == 1) {
    switch (pos) {
    case UP_LEFT: {
      matrix->at(sy)[sx] = *c;
      matrix->at(sy - 1)[sx] = *c;
      matrix->at(sy)[sx - 1] = *c;
      break;
    }
    case UP_RIGHT: {
      matrix->at(sy - 1)[sx - 1] = *c;
      matrix->at(sy)[sx - 1] = *c;
      matrix->at(sy)[sx] = *c;
      break;
    }
    case DOWN_LEFT: {
      matrix->at(sy - 1)[sx - 1] = *c;
      matrix->at(sy - 1)[sx] = *c;
      matrix->at(sy)[sx] = *c;
      break;
    }
    case DOWN_RIGHT: {
      matrix->at(sy - 1)[sx - 1] = *c;
      matrix->at(sy)[sx - 1] = *c;
      matrix->at(sy - 1)[sx] = *c;
      break;
    }
    }
    *c += 1;
    return;
  }
  switch (pos) {
  case UP_LEFT: {
    angle(n - 1, sx + pow(2, n - 2), sy + pow(2, n - 2), c, matrix, UP_LEFT);
    angle(n - 1, sx + pow(2, n - 1), sy + pow(2, n - 1), c, matrix, UP_LEFT);
    angle(n - 1, sx, sy + pow(2, n - 1), c, matrix, UP_RIGHT);
    angle(n - 1, sx + pow(2, n - 1), sy, c, matrix, DOWN_LEFT);
    break;
  }
  case UP_RIGHT: {
    angle(n - 1, sx + pow(2, n - 2), sy + pow(2, n - 2), c, matrix, UP_RIGHT);
    angle(n - 1, sx, sy + pow(2, n - 1), c, matrix, UP_RIGHT);
    angle(n - 1, sx, sy, c, matrix, DOWN_RIGHT);
    angle(n - 1, sx + pow(2, n - 1), sy + pow(2, n - 1), c, matrix, UP_LEFT);
    break;
  }
  case DOWN_LEFT: {
    angle(n - 1, sx + pow(2, n - 2), sy + pow(2, n - 2), c, matrix, DOWN_LEFT);
    angle(n - 1, sx + pow(2, n - 1), sy, c, matrix, DOWN_LEFT);
    angle(n - 1, sx, sy, c, matrix, DOWN_RIGHT);
    angle(n - 1, sx + pow(2, n - 1), sy + pow(2, n - 1), c, matrix, UP_LEFT);
    break;
  }
  case DOWN_RIGHT:
    angle(n - 1, sx + pow(2, n - 2), sy + pow(2, n - 2), c, matrix, DOWN_RIGHT);
    angle(n - 1, sx, sy, c, matrix, DOWN_RIGHT);
    angle(n - 1, sx + pow(2, n - 1), sy, c, matrix, DOWN_LEFT);
    angle(n - 1, sx, sy + pow(2, n - 1), c, matrix, UP_RIGHT);
    break;
  }
}

void square(int n, int sx, int sy, int x, int y, int *c,
            vector<vector<int>> *matrix) {
  if (n == 0) {
    *c += 1;
    return;
  }
  // normalize
  if ((sx != 1) || (sy != 1)) {
    x = (x <= pow(2, n)) ? x : x - pow(2, n);
    y = (y <= pow(2, n)) ? y : y - pow(2, n);
  }

  int new_sx = (x <= pow(2, n - 1)) ? sx : sx + pow(2, n - 1);
  int new_sy = (y <= pow(2, n - 1)) ? sy : sy + pow(2, n - 1);
  int pos = 0;
  if ((sx == new_sx) && (sy == new_sy)) {
    pos = UP_LEFT;
  } else if (new_sy == sy) {
    pos = UP_RIGHT;
  } else if (new_sx == sx) {
    pos = DOWN_LEFT;
  } else {
    pos = DOWN_RIGHT;
  }

  square(n - 1, new_sx, new_sy, x, y, c, matrix);
  angle(n, sx, sy, c, matrix, pos);
}

int main() {
  int n, x, y, c = 0;
  cin >> n >> y >> x;
  int buf = 0;

  vector<vector<int>> matrix;
  for (int i = 0; i < pow(2, n); ++i) {
    vector<int> m(pow(2, n), 0);
    matrix.push_back(m);
  }

  square(n, 1, 1, x, y, &c, &matrix);

  print_m(matrix);

  return 0;
}
