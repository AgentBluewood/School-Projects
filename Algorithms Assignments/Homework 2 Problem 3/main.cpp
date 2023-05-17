//
//  main.cpp
//  Homework 2 Problem 3
//
//  Created by Dylan Hilton on 10/16/22.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstring>

void best_path(int matrix[][100], int* output, int m, int n);

int main() {
    int m, n;
    std::cin >> m;
    std::cin >> n;
    int output = 99999999;
    
    int matrix[10][100];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> matrix[i][j];
        }
    }
    
    if (m == 1) {
        output = 0;
        for (int i = 0; i < n; i++) {
            output = output + matrix[0][i];
        }
    } else {
        best_path(matrix, &output, m, n);
    }
    
    std::cout << output << std::endl;
    return 0;
}

void best_path(int matrix[][100], int* output, int m, int n) {
    int dp[m][n];

    memset(dp, 9999, sizeof(dp));
    for (int i = 0; i < m; i++)
        dp[i][0] = matrix[i][0];
    
    
    for (int column = 1; column < n; column++) {
        for (int row = 0; row < m; row++) {
            if (row == 0) {
                dp[row][column] = matrix[row][column] + std::min(dp[row][column-1], std::min(dp[m-1][column-1], dp[row+1][column-1]));
            } else if (row == m-1) {
                dp[row][column] = matrix[row][column] + std::min(dp[row][column-1], std::min(dp[row-1][column-1], dp[0][column-1]));
            } else {
                dp[row][column] = matrix[row][column] + std::min(dp[row][column-1], std::min(dp[row-1][column-1], dp[row+1][column-1]));
            }
        }
    }
    
    for (int i=0; i < m; i++) {
        *output = std::min(*output, dp[i][n-1]);
    }
}
