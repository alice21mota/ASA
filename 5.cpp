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

bool cmp(const Edge& a, const Edge& b) {
  return a.weight > b.weight;
}

void makeSet(int x, vector<int>& parent, vector<int>& rank){
    parent[x] = x;
    rank[x] = 0;
}

int findSet(int x, vector<int>& parent){
    if (parent[x] != -1){
        if (parent[x] != x)
            parent[x] = findSet(parent[x], parent);
        return parent[x];
    }
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
    //printf("HI\n");
}

void unionSet(int x, int y, vector<int>& parent, vector<int>& rank){
    //printf("HELLO\n");
    int find_x = findSet(x, parent);
    int find_y = findSet(y, parent);

    link(find_x, find_y, parent, rank);
    //printf("BYE\n");
}

int Kruskal(Graph& graph){
    vector<int> parent(graph.V);
    vector<int> rank(graph.V);
    
    int sum = 0;

    for (int i = 0; i < graph.V; i++)
        makeSet(i, parent, rank);
    
    sort(graph.edges.begin(), graph.edges.end(), cmp);

    for(int i = 0; i < graph.E; i++){
        int u = graph.edges[i].src;
        int v = graph.edges[i].dest;
        printf("set 1 -> %d, set 2 -> %d \n", findSet(u, parent), findSet(v, parent));
        if(findSet(u, parent) != findSet(v, parent)){
            printf("set 3 -> %d, set 4 -> %d \n", findSet(u, parent), findSet(v, parent));
            unionSet(u, v, parent, rank);
            printf("set 5 -> %d, set 6 -> %d \n", findSet(u, parent), findSet(v, parent));
            sum += graph.edges[i].weight;
            printf("find set ->>>>>>> src: %d, dest: %d, weight: %d\n", graph.edges[i].src, graph.edges[i].dest, graph.edges[i].weight);
        }
    }
    return sum;
}

int main(){
    Graph graph = readGraph();
    int sum = Kruskal(graph);
    printf("sum is %d\n", sum);
}