#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
  int val;
  Node *prev;
  Node *next;
  Node(int v, Node *n, Node *p) {
    val = v;
    next = n;
    prev = p;
  }
};
class GoblinQueue {
  Node *queueBegin;
  Node *queueEnd;
  Node *queueMid;
  int size;

public:
  void enterQueue(int val) {
    Node *newNode = new Node(val, nullptr, queueEnd);
    if (queueEnd) {
      queueEnd->next = newNode;
    } else {
      queueBegin = newNode;
      queueMid = queueBegin;
    }
    if (size % 2 == 0 && queueMid->next)
      queueMid = queueMid->next;
    queueEnd = newNode;
    ++size;
  }
  GoblinQueue() {
    queueBegin = nullptr;
    queueEnd = nullptr;
    queueMid = nullptr;
    size = 0;
  }
};

int main() {
  ifstream infile("input.txt");
  int n;
  char a;
  int g;
  infile >> n;
  vector<int> q;
  for (int i = 0; i < n; ++i) {
    infile >> a;
    if (a == '-') {
      cout << q.front() << "\n";
      q.erase(q.begin());
    } else if (a == '+') {
      infile >> g;
      q.push_back(g);
    } else if (a == '*') {
      infile >> g;
      q.insert(q.begin() + (1 + q.size()) / 2, g);
    }
  }
  return 0;
}
