//
//  main.cpp
//  Homework 5 - Graphs
//
//  Created by Dylan Hilton on 12/3/21.
//

#include <iostream>
#include "Graph.h"

using namespace std;

int main(int argc, char* argv[]) {
    //Implement main function
    int teams = 0, node1 = 0, node2 = 0, weight = 0, DFSnode = 0, originalMST = 0, newMST = 0, invalidPaths = 0, positiveMoves = 0;
    bool manager = true;
    cin >> teams;
    
    for (int i = 0; i < teams; i++) {
        manager = true;
        int nodes = 0;
        cin >> nodes;
        
        Graph office(nodes);
        while (cin >> node1 >> node2 >> weight) {
            if (node1 == -1 && node2 == -1 && weight == -1) {
                break;
            }
            
            office.insertEdge(node1, node2, weight);
            
            if (manager == true) {
                DFSnode = node1;
                manager = false;
            }
        }
        
        office.DFS(DFSnode);
        cin >> node1 >> node2 >> weight;
        
        if (office.edgeCheck() == false) {
            cout << "No path is formed from each location to every other" << endl;
            invalidPaths++;
        } else {
            cout << "A path is formed!" << endl;
            originalMST = office.MST();
            cout << "Original MST was: " << originalMST << endl;
            office.insertEdge(node1, node2, weight);
            newMST = office.MST();
            cout << "New MST is: " << newMST << endl;
            if (originalMST > newMST) {
                cout << "Employee’s office should be moved" << endl;
                positiveMoves++;
            } else {
                cout << "Employee’s office should NOT be moved" << endl;
            }
        }
        cout << endl;
    }
    
    cout << "Number of employees’ offices with invalid paths: " << invalidPaths << "/" << teams << endl;
    cout << "Number of employees who would benefit from moving offices: " << positiveMoves << "/" << teams << endl;
    
    return 0;
}
