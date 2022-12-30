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
  int V = graph.V;
  vector<Edge> result;  // To store the resultant MST
  vector<int> parent(V); // To store the parent of a node
  vector<int> rank(V);   // To store the rank of a node

  // Sort all the edges in non-decreasing order of their weight
  sort(graph.edges.begin(), graph.edges.end(), cmp);

  // Create V disjoint sets with a single element
  for (int i = 0; i < V; i++)
    makeSet(i, parent, rank);

  // Iterate through all sorted edges
  for (int i = 0; i < graph.E; i++) {
    int u = graph.edges[i].src;
    int v = graph.edges[i].dest;

    // Check if the selected edge is creating a cycle
    if (findSet(u, parent) != findSet(v, parent)) {
      // If the selected edge is not creating a cycle, include it
      // in result and merge the two sets
      result.push_back(graph.edges[i]);
      unionSet(u, v, parent, rank);
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




/*
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
*/



/*
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
}*/
/*
int main(){
    WeightedGraph wgraph = readGraph();
    printWeightedGraph(wgraph);
    int sum = 0;

    cout << "VALUEEEE ->>>>>>>>> " << sum << endl;
    cout << "done" << endl;
    return 0;
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

  return 0;
}
