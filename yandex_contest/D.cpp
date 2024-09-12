#include <iostream>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  long long a, b, c, d, k;
  cin >> a >> b >> c >> d >> k;
  long long last = a;

  for (long long i = 1; i <= k; ++i) {
    long long m = a * b;
    if ((a * b) <= c) {
      cout << 0;
      return 0;
    }
    long long n = m - c;
    if (n >= d) {
      cout << d;
      return 0;
    }
    a = min(n, d);
    if (a == last) {
      cout << last;
      return 0;
    }
    last = a;
  }
  cout << a;
  return 0;
}
