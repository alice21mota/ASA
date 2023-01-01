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
    return graph;
}

// Comparator
bool cmp(const Edge& a, const Edge& b) {
  return a.weight > b.weight;
}

void makeSet(int x, vector<int>& parent, vector<int>& rank){
    parent[x] = x;
    rank[x] = 0;
}

int findSet(int x, vector<int>& parent){
    if (parent[x] != x)
        parent[x] = findSet(parent[x], parent);
    return parent[x];
}

void link(int x, int y, vector<int>& parent, vector<int>& rank){
    if (rank[x] > rank[y])
        parent[y] = x;
    else{
        parent[x] = y;
        if (rank[x] == rank[y])
            rank[y]++;
    }
}

void unionSet(int x, int y, vector<int>& parent, vector<int>& rank){
    link(findSet(x, parent), findSet(y, parent), parent, rank);
}

int Kruskal(Graph& graph, vector<int>& parent, vector<int>& rank){
    
    int sum = 0;

    for (int i = 0; i < graph.V + 1; i++)
        makeSet(i, parent, rank);
    
    sort(graph.edges.begin(), graph.edges.end(), cmp);

    for(int i = 0; i < graph.E; i++){
        int u = graph.edges[i].src;
        int v = graph.edges[i].dest;
        
        if(findSet(u, parent) != findSet(v, parent)){
            unionSet(u, v, parent, rank);  
            sum += graph.edges[i].weight;
        }
    }
    return sum;
}

int main(){
    Graph graph = readGraph();
    vector<int> parent(graph.V, -1);
    vector<int> rank(graph.V, 0);
    int sum = Kruskal(graph, parent, rank);
    printf("%d\n", sum);
}