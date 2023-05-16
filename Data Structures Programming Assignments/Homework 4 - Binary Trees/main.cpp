#include <iostream>
#include <string>
#include <cstdlib>

#include "BSTree.h"
#include "BSTUtils.h"

using namespace std;

int main(int argc, char** argv)
{

    string filename = "test_input.txt";

    BSTree* bst = new BSTree();
    BSTree* bst2 = new BSTree();

    int len;
    string *ifarr = file_to_array(filename, &len);

    array_to_bst(ifarr, len, bst);

    cout << "Representation of BST from file array: \n" << endl;
    cout << bst->getRepresentation() << endl;

    cout << endl << "Nodes: " << bst->getNumNodes() << endl;
    cout << "Height: " << bst->getHeight() << endl;


    string *ifarr2 = presort_array(ifarr, len);
    array_to_bst(ifarr2, len, bst2);

    cout << "\n\nRepresentation of BST from pre-sorted file array: \n" << endl;
    cout << bst2->getRepresentation() << endl;

    cout << endl << "Nodes: " << bst2->getNumNodes() << endl;
    cout << "Height: " << bst2->getHeight() << endl;


    delete bst;
    delete bst2;
    return 0;
}
