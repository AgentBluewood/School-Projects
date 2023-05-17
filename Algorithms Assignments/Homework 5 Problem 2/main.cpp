//
//  main.cpp
//  Homework 5 Problem 2
//
//  Created by Dylan Hilton on 12/11/22.
//

#include <iostream>
#include <list>
#include <stack>
#include <climits>
#include <vector>

class AdjListNode {
    int v;
    int weight;
   
public:
    AdjListNode(int _v, int _w)
    {
        v = _v;
        weight = _w;
    }
    int getV() { return v; }
    int getWeight() { return weight; }
};

class Graph {
    int V;
   
    std::list<AdjListNode>* adj;
   
    void topsort(int v, bool visited[],
                             std::stack<int>& Stack);
   
public:
    Graph(int V);
    ~Graph();
 

    void addEdge(int u, int v, int weight);
    void longestDAGPath(int source, int destination);
};
   
Graph::Graph(int V) {
    this->V = V;
    adj = new std::list<AdjListNode>[V];
}
 
Graph::~Graph() {
    delete [] adj;
}
 
 
void Graph::addEdge(int u, int v, int weight) {
    AdjListNode node(v, weight);
    adj[u].push_back(node);
}

void Graph::topsort(int v, bool discovered[],
                    std::stack<int>& topOrder) {
    discovered[v] = true;
   
    for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
        AdjListNode node = *i;
        if (!discovered[node.getV()])
            topsort(node.getV(), discovered, topOrder);
    }
    topOrder.push(v);
}

void Graph::longestDAGPath(int source, int destination) {
    std::stack<int> topOrder;
    int distance[V];

    bool discovered[V];
    for (int i = 0; i < V; i++)
        discovered[i] = false;

    for (int i = 0; i < V; i++)
        if (discovered[i] == false)
            topsort(i, discovered, topOrder);
   
    for (int i = 0; i < V; i++) {
        distance[i] = INT_MIN;
    }
    
    distance[source] = 0;

    while (!topOrder.empty()) {
        int current = topOrder.top();
        topOrder.pop();
        
        if (distance[current] != INT_MIN) {
            for (auto i = adj[current].begin(); i != adj[current].end(); ++i){
                if (distance[i->getV()] < distance[current] + i->getWeight()) {
                    distance[i->getV()] = distance[current] + i->getWeight();
                }
            }
        }
    }
   
    std::cout << distance[destination];
}

int main(int argc, const char * argv[]) {
    int numNodes, numEdges;
    int source, destination;
    
    std::cin >> numNodes >> numEdges;
    std::cin >> source >> destination;
    
    Graph DAG(numNodes);
    
    int node1, node2, weight;
    for (int k = 0; k < numEdges; k++) {
        std::cin >> node1 >> node2 >> weight;
        DAG.addEdge(node1, node2, weight);
    }
    
    DAG.longestDAGPath(source, destination);
    
    return 0;
}
