#include <iostream>
#include <fstream>
#include <vector> 
#include <algorithm>

using namespace std;


// A pair (vertex, weight) used in the adjacency list
typedef pair<int, int> PII;

// Data structure to represent a weighted graph
struct WeightedGraph{
    int num_vertices;   // Number of vertices in the graph
    int num_edges;  // Number of edges in the graph
    vector<vector<PII>> adjacency_list; // Adjacency list representation of the graph
};

// A structure to represent a weighted edge in the graph
struct Edge {
  int src, dest, weight;
};

struct Graph {
  int V, E;
  vector<Edge> edges;

  // Constructor
  Graph(int V, int E) : V(V), E(E) { }
};

// Compare two edges according to their weights.
// Used in std::sort() to sort the edges in ascending order
bool cmp(const Edge& a, const Edge& b) {
  return a.weight > b.weight;
}

// MakeSet function
void makeSet(int x, vector<int>& parent, vector<int>& rank) {
  parent[x] = x;
  rank[x] = 0;
  cout << "here" << endl;
}

// FindSet function
int findSet(int x, vector<int>& parent) {
  // find root and make root as parent of x (path compression)
  if (parent[x] != x)
    parent[x] = findSet(parent[x], parent);
  return parent[x];
}

void link(int x, int y, vector<int>& parent, vector<int>& rank) {
  if (rank[x] > rank[y])
    parent[y] = x;
  else {
    parent[x] = y;
    if (rank[x] == rank[y])
      rank[y] = rank[y] + 1;
  }
}

void unionSet(int x, int y, vector<int>& parent, vector<int>& rank) {
    link(findSet(x, parent), findSet(y, parent), parent, rank);
}

// The main function to construct MST using Kruskal's algorithm
vector<Edge> Kruskal(Graph& graph) {
cout << "ENTERING KRUSKAL " << endl;
  int V = graph.V;
  vector<Edge> result;  // To store the resultant MST
  vector<int> parent(V); // To store the parent of a node
  vector<int> rank(V);   // To store the rank of a node

  // Sort all the edges in non-decreasing order of their weight
  sort(graph.edges.begin(), graph.edges.end(), cmp);

  // Create V disjoint sets with a single element
  for (int i = 0; i < V; i++){
    cout << "I VALUE " << i << endl;
    makeSet(i, parent, rank);
  }

  // Iterate through all sorted edges
  cout << graph.E << endl;
  for (int i = 0; i < graph.E; i++) {
    int u = graph.edges[i].src;
    cout << u << endl;
    int v = graph.edges[i].dest;
    cout << u << "->" << v << ":" << graph.edges[i].weight << endl;

    // Check if the selected edge is creating a cycle
    if (findSet(u, parent) != findSet(v, parent)) {
      // If the selected edge is not creating a cycle, include it
      // in result and merge the two sets
      result.push_back(graph.edges[i]);
      unionSet(u, v, parent, rank);
      cout << u << "->" << v << endl;
    }
  }

  return result;
}


/*
void unionSet(int x, int y, vector<int>& parent, vector<int>& rank) {
  int xroot = findSet(x, parent);
  int yroot = findSet(y, parent);

  // Attach smaller rank tree under root of high rank tree
  // (Union by Rank)
  if (rank[xroot] < rank[yroot])
    parent[xroot] = yroot;
  else if (rank[xroot] > rank[yroot])
    parent[yroot] = xroot;
  // If ranks are same, then make one as root and increment
  // its rank by one
  else {
    parent[yroot] = xroot;
    rank[xroot]++;
  }
}
*/


int main() {
  int V, E;
  cin >> V >> E;

  // Create a graph with V vertices and E edges
  Graph graph(V, E);

  // Read the edges from input
  for (int i = 0; i < E; i++) {
    int src, dest, weight;
    cin >> src >> dest >> weight;
    graph.edges.push_back({src, dest, weight});
  }

  // Call Kruskal's algorithm to compute the minimum spanning tree
  vector<Edge> MST = Kruskal(graph);

  // Print the edges of the minimum spanning tree
  cout << "Edges of the minimum spanning tree:" << endl;
  for (const Edge& edge : MST)
    cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
    cout << "_> here " << endl;

  return 0;
}
