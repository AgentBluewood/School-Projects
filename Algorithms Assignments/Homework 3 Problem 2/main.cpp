//
//  main.cpp
//  Homework 3 Problem 2
//
//  Created by Dylan Hilton on 10/30/22.
//

#include <iostream>

void postOrderTraversal(int inorder[], int preorder[], int n)
{
    int root = -1;
    for (int i = 0; i < n; i++) {
        if (inorder[i] == preorder[0])
            root = i;
    }
           
    if (root != 0)
        postOrderTraversal(inorder, preorder + 1, root);

    if (root != n - 1)
        postOrderTraversal(inorder + root + 1, preorder + root + 1, n - root - 1);

    std::cout << preorder[0] << " ";
}

int main(int argc, const char * argv[]) {
    int n;
    std::cin >> n;
    
    int preorder[n], inorder[n];
    
    for (int i = 0; i < n; i++) {
        std::cin >> preorder[i];
    }
    
    for (int j = 0; j < n; j++) {
        std::cin >> inorder[j];
    }
    
    postOrderTraversal(inorder, preorder, n);
    
    return 0;
}
