#include <iostream>
#include <fstream>
#include <vector> 
#include <string>
#include <utility>
#include <limits>
#include <queue>

using namespace std;


// A pair (vertex, weight) used in the adjacency list
typedef pair<int, int> PII;

const int INF = numeric_limits<int>::min();

// Data structure to represent a weighted graph
struct WeightedGraph{
    int num_vertices;   // Number of vertices in the graph
    int num_edges;  // Number of edges in the graph
    vector<vector<PII>> adjacency_list; // Adjacency list representation of the graph
};


WeightedGraph readGraph() {
    WeightedGraph graph;
    
    cin >> graph.num_vertices;   // Number of vertices
    if (cin.fail() || graph.num_vertices < 1)
        cout << "Invalid input!" << endl;

    cin >> graph.num_edges;   // Number of edges
    if (cin.fail() || graph.num_edges < 0)
        cout << "Invalid input!" << endl;
    
    graph.adjacency_list.resize(graph.num_vertices);
    
    for (int i = 0; i < graph.num_edges; i++){
        int u, v, weight;
        cin >> u >> v >> weight;
        
        if (cin.fail())
            cout << "Invalid input!" << endl;
        u--; 
        v--;
        graph.adjacency_list[u].push_back({v, weight});
        graph.adjacency_list[v].push_back({u, weight}); 

    }
    return graph;
}


// Function to print a weighted graph
void printWeightedGraph(const WeightedGraph& g) {
  cout << "Number of vertices: " << g.num_vertices << endl;
  cout << "Number of edges: " << g.num_edges << endl;
  for (int u = 0; u < g.num_vertices; u++) {
    cout << "Vertex " << u + 1 << " is connected to:" << endl; // Numerate vertices from 1
    for (const PII& p : g.adjacency_list[u]) {
      int v = p.first;
      int weight = p.second;
      cout << "  Vertex " << v + 1 << " with weight " << weight << endl; // Numerate vertices from 1
    }
  }
}

int main(){
    WeightedGraph wgraph = readGraph();
    printWeightedGraph(wgraph);
    int sum = 0;

    cout << "VALUEEEE ->>>>>>>>> " << sum << endl;
    cout << "done" << endl;
    return 0;
}