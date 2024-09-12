#include <cstddef>
#include <ios>
#include <iostream>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t n, a, start_pos = 1, end_pos = 0, min_start_pos = 1, max_end_pos = 1,
               count = 0, last = 0;
  cin >> n;

  for (size_t i = 0; i < n; ++i) {
    cin >> a;
    if (a == last) {
      ++count;
    } else {
      count = 1;
    }
    last = a;
    ++end_pos;
    if (count > 2) {
      if ((max_end_pos - min_start_pos) < (end_pos - start_pos - 1)) {
        min_start_pos = start_pos;
        max_end_pos = end_pos - 1;
      }
      start_pos = end_pos - 1;
      count = 2;
    }
  }
  if ((max_end_pos - min_start_pos) < (end_pos - start_pos)) {
    min_start_pos = start_pos;
    max_end_pos = end_pos;
  }

  cout << min_start_pos << " " << max_end_pos;
  return 0;
}
