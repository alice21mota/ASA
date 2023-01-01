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
    int V, E;
    scanf("%d %d", &V, &E);

    Graph graph(V, E);

      // Read the edges from input
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        graph.edges.push_back({src, dest, weight});
    }
    /*for (int i = 0; i < E; i++){
        printf("src -> %d  dest-> %d  weight ->  %d\n", graph.edges[i].src, graph.edges[i].dest, graph.edges[i].weight);
    }*/
    return graph;
}

// Compare two edges according to their weights.
// Used in std::sort() to sort the edges in ascending order
bool cmp(const Edge& a, const Edge& b) {
  return a.weight > b.weight;
}

//MakeSet function
void makeSet(int x, vector<int>& parent, vector<int>& rank) {
  parent[x] = x;
  rank[x] = 0;
  cout << "in makeset parent is " << parent[x] << "rank is " << rank[x] << ":" << x << endl;
}

// FindSet function
int findSet(int x, vector<int>& parent) {
  // find root and make root as parent of x (path compression)
  if (parent[x] == x)
    return x;
  return parent[x] = findSet(parent[x], parent);
}

void link(int x, int y, vector<int>& parent, vector<int>& rank) {
   cout << "Y  " << y << "  X " << x << endl; 
  if (rank[x] > rank[y])
    parent[y] = x;
  else {
    //cout << "!!!!!! x  " << x << "  parent " << parent[x] << endl;
    parent[x] = y;
    //cout << "x  " << x << "  parent " << parent[x] << endl;
    if (rank[x] == rank[y])
      rank[y] ++;
  }
}

void unionSet(int x, int y, vector<int>& parent, vector<int>& rank) {
    cout << "got here" << endl;
    link(findSet(x, parent), findSet(y, parent), parent, rank);
}

int Kruskal(Graph& graph) {
  int V = graph.V;
  int sum = 0;
  //vector<Edge> result;  // To store the resultant MST
  vector<int> parent(V); // To store the parent of a node
  vector<int> rank(V);   // To store the rank of a node

  // Create V disjoint sets with a single element
  for (int i = 0; i < graph.V; i++){
    makeSet(i, parent, rank);
  }


  // Sort all the edges in non-increasing order of their weight
  sort(graph.edges.begin(), graph.edges.end(), cmp);

  // Iterate through all sorted edges
  for (int i = 0; i < graph.E; i++) {
    int u = graph.edges[i].src;
    int v = graph.edges[i].dest;

    // Check if the selected edge is creating a cycle
    if (findSet(u, parent) != findSet(v, parent)) {
      // If the selected edge is not creating a cycle, include it
      // in result and merge the two sets
      //result.push_back(graph.edges[i]);
      
      sum += graph.edges[i].weight;
      unionSet(u, v, parent, rank);
      cout << "got in here " << endl;
    }

    /*else{
        cout << u << "-" << v << ":" << graph.edges[i].weight << endl;
    }*/
  }
  return sum;
}

int main(){
    Graph graph = readGraph();
    for (int i = 0; i < graph.E; i++){
        cout << graph.edges[i].src << "-" << graph.edges[i].dest << ":" << graph.edges[i].weight << endl;
    }
    int sum = Kruskal(graph);
    printf("%d\n", sum);
}
