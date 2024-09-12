#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

bool compare(const string &left, const string &right) {
  if (left.length() < right.length()) {
    if (left != right.substr(0, left.length())) {
      return left > right.substr(0, left.length());
    }
    return compare(right.substr(0, left.length()),
                   right.substr(left.length(), right.length()));
  } else if (left.length() > right.length()) {
    return !compare(right, left);
  }
  return left > right;
}
int main() {
  ifstream infile("number.in");
  string s;
  vector<string> v;
  while (infile >> s) {
    v.push_back(s);
  }
  sort(begin(v), end(v), compare);
  for (string s : v) {
    cout << s;
  }
  return 0;
}
