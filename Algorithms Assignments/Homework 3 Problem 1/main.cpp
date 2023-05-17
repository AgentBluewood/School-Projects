//
//  main.cpp
//  Homework 3 Problem 1
//
//  Created by Dylan Hilton on 10/30/22.
//

#include <iostream>

void dynamicProgramming (int arr[], int n, int* output) {
    int lis[n], lds[n];

    for (int x = 0; x < n; x++) {
        lis[x] = 1;
        lds[x] = 1;
    }
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                lis[i] = std::max(lis[i], lis[j]+1);
            }
        }
    }
    
    for (int i = n-2; i >= 0; i--) {
        for (int j = n-1; j > i; j--) {
            if (arr[i] > arr[j]) {
                lds[i] = std::max(lds[i], lds[j] + 1);
            }
        }
    }
    
    *output = lis[0] + lds[0] - 1;
    for (int i = 1; i < n; i++) {
        *output = std::max(*output, lis[i] + lds[i] - 1);
    }
}

int main(int argc, const char * argv[]) {
    int n;
    std::cin >> n;
    int array[n];
    int output = -1;
    
    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }
    
    dynamicProgramming(array, n, &output);
    std::cout << output;
    
    return 0;
}
