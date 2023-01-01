#include <iostream>
#include <fstream>
#include <vector> 
#include <algorithm>

using namespace std;

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

Graph readGraph(){
    //int V, E;
    scanf("%d %d", &V, &E);

    Graph graph(V, E);

      // Read the edges from input
    for (int i = 0; i < E; i++) {
        //int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        graph.edges.push_back({src, dest, weight});
    }

}

// Compare two edges according to their weights.
// Used in std::sort() to sort the edges in ascending order
bool cmp(const Edge& a, const Edge& b) {
  return a.weight > b.weight;
}

