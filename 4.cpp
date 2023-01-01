#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
  int u, v, w;  // u and v are the two endpoints of the edge, w is the weight
  bool operator<(const Edge& e) const {  // operator overload for sorting
    return w > e.w;
  }
};

struct Node {
  int parent;
  int rank;
};

vector<Node> nodes;

void makeSet(int x) {
  nodes[x].parent = x;
  nodes[x].rank = 0;
}

int findSet(int x) {
  if (nodes[x].parent != x) {
    nodes[x].parent = findSet(nodes[x].parent);
  }
  return nodes[x].parent;
}

void link(int x, int y) {
  if (nodes[x].rank > nodes[y].rank) {
    nodes[y].parent = x;
  } else {
    nodes[x].parent = y;
    if (nodes[x].rank == nodes[y].rank) {
      nodes[y].rank++;
    }
  }
}

void unionSet(int x, int y) {
  link(findSet(x), findSet(y));
}

int main() {
  int n, m;
  cin >> n >> m;

  nodes.resize(n);
  for (int i = 0; i < n; i++) {
    makeSet(i);
  }

  vector<Edge> edges;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    edges.push_back({u, v, w});
  }

  // Sort the edges in ascending order of weight
  sort(edges.begin(), edges.end());

  int ans = 0;  // Initialize the total weight of the minimum spanning tree to 0
  for (const Edge& e : edges) {
    int u = e.u, v = e.v, w = e.w;
    if (findSet(u) != findSet(v)) {  // If u and v are not in the same set
      unionSet(u, v);  // Union the two sets
      ans += w;  // Add the weight of the edge to the total weight
    }
  }

  cout << ans << endl;  // Print the total weight of the minimum spanning tree

  return 0;
}
