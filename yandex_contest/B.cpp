#include <cstddef>
#include <cstring>
#include <experimental/vector>
#include <ios>
#include <iostream>
#include <utility>
#include <vector>
#define START_UPPER 65
#define END_UPPER 90
using namespace std;

void print_arr(vector<pair<char, size_t>> v) {
  for (pair<char, size_t> p : v) {
    cout << p.first;
  }
  cout << "\n";
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  vector<pair<char, size_t>> vp;
  size_t j = 1, k = 1;
  string s;
  cin >> s;
  for (size_t i = 0; i < s.size(); ++i) {
    char a = s.at(i);
    if ((a >= START_UPPER) && (a <= END_UPPER)) {
      vp.push_back(make_pair(a, j));
      ++j;
    } else {
      vp.push_back(make_pair(a, k));
      ++k;
    }
  }

  bool modified;
  size_t n = vp.size();
  size_t res[n / 2 + 1];

  do {
    long long n = vp.size();
    modified = false;
    long long i = 0;
    while (i < n - 1) {
      if ((vp.at(i).first != vp.at(i + 1).first) &&
          (tolower(vp.at(i).first) == tolower(vp.at(i + 1).first))) {
        if (vp.at(i).first > vp.at(i + 1).first) {
          res[vp.at(i + 1).second] = vp.at(i).second;
        } else {
          res[vp.at(i).second] = vp.at(i + 1).second;
        }
        long long l_b = i - 1;
        long long r_b = i + 2;
        vp.at(i).first = ' ';
        vp.at(i + 1).first = ' ';
        modified = true;

        while ((l_b >= 0) && (r_b <= n - 1)) {
          if ((vp.at(l_b).first != vp.at(r_b).first) &&
              (tolower(vp.at(l_b).first) == tolower(vp.at(r_b).first))) {
            if (vp.at(l_b).first > vp.at(r_b).first) {
              res[vp.at(r_b).second] = vp.at(l_b).second;
            } else {
              res[vp.at(l_b).second] = vp.at(r_b).second;
            }
            vp.at(l_b).first = ' ';
            vp.at(r_b).first = ' ';
          } else {
            break;
          }
          --l_b;
          ++r_b;
        }
        i = r_b;
      } else {
        ++i;
      }
    }
    std::experimental::erase_if(vp,
                                [](const auto &p) { return p.first == ' '; });
  } while (modified && !vp.empty());
  if (vp.empty()) {
    cout << "Possible\n";
    for (long long l = 1; l <= n / 2; ++l) {
      cout << res[l] << " ";
    }
  } else {
    cout << "Impossible";
  }
  return 0;
}
