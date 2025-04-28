#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

//structure to represent edge
struct Edge
{
    int u,v,weight;
};

//Graph class
class Graph{
    int v; //no. of edges 
    vector<Edge>edges; //list all edges

    public:
       Graph(int vertices){
        v=vertices;
       }
       //function to add an edge
       void addEdge(int u,int v,int weight){
          edges.push_back({u,v,weight});
       }
       //find parent of the node
       int findParent(vector<int>& parent,int node){
          if(parent[node]==node){
            return node;
          }
          return parent[node]=findParent(parent,parent[node]);
       }

       //Union of two sets
       void unionSets(vector<int>& parent, vector<int>& rank, int u, int v) {
        int rootU = findParent(parent, u);
        int rootV = findParent(parent, v);
    
        if (rank[rootU] < rank[rootV])
            parent[rootU] = rootV;
        else if (rank[rootU] > rank[rootV])
            parent[rootV] = rootU;
        else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
    //Kruskals Algorithm
    void kruskalMST(){
        vector<Edge>result;
        vector<int>parent(v);
        vector<int>rank(v,0);
        //Initially every node is its own parent
        for(int i=0;i<v;i++){
            parent[i]=i;
        }
        sort(edges.begin(),edges.end(),[](Edge a, Edge b){
            return a.weight<b.weight;
        });
         // Process edges one by one
         for (auto edge : edges) {
            int u = edge.u;
            int v = edge.v;
            int weight = edge.weight;

            // Find parents (root nodes)
            int rootU = findParent(parent, u);
            int rootV = findParent(parent, v);

            // If including this edge doesn't cause a cycle
            if (rootU != rootV) {
                result.push_back(edge); // Include edge in MST
                unionSets(parent, rank, rootU, rootV); // Union the sets
            }
        }
        // Print MST
        cout << "Edges in the Minimum Spanning Tree:\n";
        for (auto edge : result) {
            cout << edge.u << " -- " << edge.v << " == " << edge.weight << endl;
        }
    }
};

int main() {
    Graph g(4); // Create a graph with 4 vertices

    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 10);
    g.addEdge(0, 3, 3);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 4);

    g.kruskalMST(); // Find and print MST

    return 0;
}