#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
  int A;
  int B;
  double R;
  double C;
};
const double EPS = 0.00000001;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, S;
  double V;
  cin >> N >> M >> S >> V;
  vector<Edge> graph;
  vector<double> capital(101);
  capital[S] = V;

  for (int i = 0; i < M; ++i) {
    int A, B;
    double RAB, CAB, RBA, CBA;
    cin >> A >> B >> RAB >> CAB >> RBA >> CBA;
    graph.push_back({A, B, RAB, CAB});
    graph.push_back({B, A, RBA, CBA});
  }
  // bellman-ford algorithm
  for (int i = 0; i < N - 1; ++i) {
    for (int j = 0; j < graph.size(); ++j) {
      if (capital[graph[j].B] -
              (capital[graph[j].A] - graph[j].C) * graph[j].R <
          EPS) {
        capital[graph[j].B] = (capital[graph[j].A] - graph[j].C) * graph[j].R;
      }
    }
  }

  for (int i = 0; i < graph.size(); ++i) {
    // if somewhere by exchanging currency you get a better value, means you can get richer
    if ((capital[graph[i].A] - graph[i].C) * graph[i].R - capital[graph[i].B] >
        EPS) {
      cout << "YES";
      return 0;
    }
  }
  cout << "NO";
  return 0;
}
