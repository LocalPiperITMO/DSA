
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

bool checknum(const string s) {
  if (s == "0") {
    return true;
  }
  long long num = atoll(s.c_str());
  return num != 0;
}
int main() {

  ifstream infile("input.txt");

  string s;
  vector<unordered_map<string, long long>> buffer;

  unordered_map<string, vector<size_t>> appeared;
  unordered_map<size_t, vector<string>> changed;

  size_t layer = 0;
  buffer.emplace_back();

  while (infile >> s) {
    if (s == "{") {
      // going to next layer
      ++layer;
      buffer.emplace_back();
      continue;
    }
    if (s == "}") {
      // going to previous layer, cleaning the last layer based on changed
      // values
      buffer.pop_back();
      for (const auto &i : changed[layer]) {
        appeared[i].pop_back();
      }
      changed[layer].clear();
      --layer;
      continue;
    }

    int eq = s.find("=");
    string s1 = s.substr(0, eq);
    string s2 = s.substr(eq + 1, s.size());

    if (checknum(s2)) {
      // <var1>=number
      buffer[layer][s1] = atoll(s2.c_str());
      // if empty var1 for this layer, adding it to layers
      if (appeared[s1].empty() ||
          appeared[s1][appeared[s1].size() - 1] != layer) {
        appeared[s1].push_back(layer);
        changed[layer].push_back(s1);
      }
    } else {
      // <var1>=<var2>
      // if empty var2 for this layer, adding it to layers
      if (appeared[s2].empty()) {
        appeared[s2].push_back(layer);
        changed[layer].push_back(s2);
      }
      // searching for a value of var2 in this and previous layers
      size_t s2_layer = appeared[s2][appeared[s2].size() - 1];
      buffer[layer][s1] = buffer[s2_layer][s2];

      // if empty var1 for this layer, adding it to layers
      if (appeared[s1].empty() ||
          appeared[s1][appeared[s1].size() - 1] != layer) {
        appeared[s1].push_back(layer);
        changed[layer].push_back(s1);
      }
      cout << buffer[layer][s1] << "\n";
    }
  }
  return 0;
}
