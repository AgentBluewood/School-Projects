//
//  main.cpp
//  Homework 2 Problem 2
//
//  Created by Dylan Hilton on 10/15/22.
//

#include<stdio.h>
#include<stdlib.h>
#include <climits>
#include <algorithm>
#include <iostream>

void maxDifference(int arr[], int n, int *output)
{
    int maxFromEnd[n+1];
    for (int i = 0; i < n+1; i++) {
        maxFromEnd[i] = INT_MIN;
    }
    
    for (int i = n - 1; i >= 0; i--) {
        maxFromEnd[i] = std::max(maxFromEnd[i + 1], arr[i]);
    }
    
    if (maxFromEnd[0] < maxFromEnd[n-1]) {
        *output = 0;
    } else {
        *output = arr[1] - arr[0];
        for (int i = 0; i < n; i++) {
            int temp = maxFromEnd[i] - arr[i];
            *output = std::max(*output, temp);
        }
    }
}

int main(int argc, char* argv[])
{
    int n;
    int *arr;
    fscanf(stdin, "%d", &n);
    arr = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++)
    {
        fscanf(stdin, "%d", &arr[i]);
    }
    int output = 0;

    maxDifference(arr, n, &output);
    printf("%d\n", output);

    return 0;
}
