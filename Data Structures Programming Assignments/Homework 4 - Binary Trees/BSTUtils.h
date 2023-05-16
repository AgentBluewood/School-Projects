#ifndef BSTUtils_H
#define BSTUtils_H

#include <string>
#include "BSTree.h"
#include "BSTNode.h"

using namespace std;

string* file_to_array(string f_name, int *l);
void array_to_bst(string key_arr[], int len, BSTree *i_bst);
string* presort_array(string in_arr[], int len);


#endif // BSTUtils_H


