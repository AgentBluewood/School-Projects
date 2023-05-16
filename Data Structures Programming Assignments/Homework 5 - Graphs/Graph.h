//
//  Graph.h
//  Homework 5 - Graphs
//
//  Created by Dylan Hilton on 12/3/21.
//

#ifndef Graph_h
#define Graph_h

#pragma once
#include <iostream>
#include <climits>
#include <vector>

using namespace std;

class Graph {
private:
    vector<vector<int>> matrix;
    int size;
    vector<bool> visited;

public:
    Graph(int mySize) {
        //Implement function
        size = mySize;
        matrix = vector<vector<int>>(mySize, vector<int>(mySize, 0));
        visited = vector<bool>(mySize, false);
    }

    void resetVisited() {
        //Implement function
        visited = vector<bool>(size, false);
    }

    void insertEdge(int v1, int v2, int weight) {
        //Implement function
        matrix[v1][v2] = weight;
        matrix[v2][v1] = weight;
    }

    void DFS(int vertex) {
        //Implement function
        if (visited[vertex] == false) {
            visited[vertex] = true;
            for (int i = 0; i < size; i++) {
                if(matrix[vertex][i] != 0) {
                    DFS(i);
                }
            }
        }
    }

    bool edgeCheck() {
        //Implement function
        int nodesVisited = 0;
        for (int i = 0; i < size; i++) {
            if(visited[i] == true) {
                nodesVisited++;
            }
        }
        if (nodesVisited == size) {
            return true;
        }
        return false;
    }
    
    int minKey(int key[], bool mstSet[]) {
        int min = INT_MAX, min_index;
        for (int i = 0; i < size; i++) {
            if(mstSet[i] == false && key[i] < min) {
                min = key[i];
                min_index = i;
            }
        }
        return min_index;
    }
    
    int MST() {
        //Implement function
        int parent[size];
        int key[size];
        bool mstSet[size];
        
        for (int i = 0; i < size; i++) {
            key[i] = INT_MAX;
            mstSet[i] = false;
        }
        
        key[0] = 0;
        parent[0] = -1;
        
        for (int count = 0; count < size - 1; count++) {
            int vertex = minKey(key, mstSet);
            mstSet[vertex] = true;
            
            for (int i = 0; i < size; i++) {
                if (matrix[vertex][i] && mstSet[i] == false && matrix[vertex][i] < key[i]) {
                    parent[i] = vertex;
                    key[i] = matrix[vertex][i];
                }
            }
        }
        
        int sum = 0;
        for (int x = 1; x < size; x++) {
            sum = sum + matrix[x][parent[x]];
        }
    
        return sum;
    }
};

#endif /* Graph_h */
