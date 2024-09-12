#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
using namespace std;


int findParent(vector<int>& A, int n) {
  while (A[n] != n) {
    n = A[n]; 
  }
  return n;
}

void uniteParents(vector<int>& A, int u, int v) {
  int v1 = findParent(A, u);
  int v2 = findParent(A, v);
  if (v1 == v2) {
    // already checked
    return;
  }
  A[v1] = v2;
}
int countDistinct(vector<int>& A) {
  int c = 0;
  for (int i = 0; i < A.size(); ++i) {
    if (A[i] == i) {
      ++c;
    }
  }
  return c;
}

int main() {
  int n;
  ifstream infile("input.txt");
  infile >> n; 
  vector<int> parents(n);
  for (int i = 0; i < n; ++i) {
    parents[i] = i;
  }

  for (int i = 0; i < n; ++i) {
    int p;
    infile >> p;
    uniteParents(parents, i, p - 1);
  }
  
  cout << countDistinct(parents);
  return 0;
}
