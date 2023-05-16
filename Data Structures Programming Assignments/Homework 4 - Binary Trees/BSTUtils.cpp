#include <fstream>
#include <cstring>
#include <string.h>
#include "BSTUtils.h"

string* file_to_array(string f_name, int *l)
{
	//implement function
    string* sort = new string[100];
    ifstream input(f_name);
    *l = 0;
    
    if (input.is_open())  {
        while(!input.eof()) {
            getline(input, sort[*l]);
            *l = *l + 1;
        }
    }
    
    input.close();
    return sort;
}

void treeCreator(string arr[], int begin, int end, BSTree* tree) {
    if (end > begin) {
        return;
    }
    
    int mid = begin + (end - begin)/2;
    tree->addNode(arr[mid]);
    treeCreator(arr, begin, mid-1, tree);
    treeCreator(arr, mid+1, end, tree);
}

void array_to_bst(string key_arr[], int len, BSTree* i_bst)
{
	//implement function
    key_arr = presort_array(key_arr, len);
    treeCreator(key_arr, 0, len, i_bst);
}
 
string* arraySorter(string arr[], int low, int high) {
    int mid = (low + high)/2;
    int index = 1;
    int lmid = mid - 1;
    int rmid = mid + 1;
    string* temp = new string[high];
    temp[0] = arr[mid];
    
    while (index < high - 1) {
        lmid = lmid/2;
        temp[index] = arr[lmid];
        rmid = rmid/2;
        temp[index+1] = arr[rmid];
    }
    return temp;
}

string* presort_array(string in_arr[], int len)
{
	//implement function
    string temp;
    for (int i = 0; i < len - 1; ++i) {
        int indexSmallest = i;
        for (int j = i + 1; j < len; ++j) {
            if (strcmp(in_arr[j].c_str(), in_arr[indexSmallest].c_str()) < 0) {
                indexSmallest = j;
            }
        }
        temp = in_arr[i];
        in_arr[i] = in_arr[indexSmallest];
        in_arr[indexSmallest] = temp;
    }
    
    int root = len/2;
    temp = in_arr[0];
    in_arr[0] = in_arr[root];
    in_arr[root] = temp;
    
    return in_arr;
}
