//
//  main.cpp
//  Homework 5 Problem 1
//
//  Created by Dylan Hilton on 12/9/22.
//

#include <iostream>
#include <climits>
#include <algorithm>
#include <cstring>

int minPalindromes (int n, std::string input) {
    /*int dp[n][n];
    memset(dp, 0, sizeof(dp));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (i == j) {
                dp[i][j] = 1;
            }
            
            std::string temp = std::string(input.c_str() + j, input.c_str() + i + 1);
            if (isPalindrome(temp)){
                dp[j][i] = 1;
            }
            
        }
    }*/
    
    
    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << std::endl;
    }*/
    
    //int numPalindromes[n];
    /*int* numPalindromes = new int[n];
    for (int k = 0; k < n; k++) {
        int min = INT_MAX;
        if (dp[0][k] == 1) {
            numPalindromes[k] = 1;
        } else {
            for (int p = 0; p < k; p++) {
                if ((dp[p+1][k] == 1) && min > numPalindromes[p] + 1) {
                    min = numPalindromes[p] + 1;
                }
            }
            numPalindromes[k] = min;
        }
    }*/
    
    //THIS SHIT WORKS DONT DELETE IT MF
    /*int* dp = new int[n*n];
    memset(dp, 0, sizeof(n*n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j<= i; j++) {
            std::string temp = std::string(input.c_str() + j, input.c_str() + i + 1);
            if (isPalindrome(temp)) {
                *(dp + j*n + i) = 1;
            }
        }
    }
    
    int* numPalindromes = new int[n];
    for (int k = 0; k < n; k++) {
        int min = INT_MAX;
        if (*(dp + 0*n + k) == 1) {
            numPalindromes[k] = 1;
        } else {
            for (int p = 0; p < k; p++) {
                if ((*(dp + (p+1)*n + k)== 1) && min > numPalindromes[p] + 1) {
                    min = numPalindromes[p] + 1;
                }
            }
            numPalindromes[k] = min;
        }
    }
    
    int result = numPalindromes[n-1];
    
    delete [] dp;
    delete[] numPalindromes;
    
    return result;*/
    //THIS SHIT WORKS DONT DELETE IT MF
    
    //OKAY THIS REALLY WORKS BUT I HATE MYSELF SO LETS TRY ONE MORE THING
    /*bool* dp = new bool[n*n];
    memset(dp, false, sizeof(n*n));
    for (int i = 0; i < n; i++) {
        *(dp + i*n + i) = true;
    }
    
    for (int i = 0; i < n - 1; i++) {
        if (input[i] == input[i+1]) {
            *(dp + i*n + (i+1)) = true;
        }
    }
    
    for (int len = 3; len <= n; len++) {
        for (int i = 0; i < n-len+1; i++) {
            int j = i+len-1;
            if ((input[i] == input[j]) && (*(dp + (i+1)*n + (j-1)))) {
                *(dp + i*n + j) = true;
            }
        }
    }
    
    int* numPalindromes = new int[n];
    for (int k = 0; k < n; k++) {
        int min = INT_MAX;
        if (*(dp + 0*n + k)) {
            numPalindromes[k] = 1;
        } else {
            for (int p = 0; p < k; p++) {
                if ((*(dp + (p+1)*n + k)) && min > numPalindromes[p] + 1) {
                    min = numPalindromes[p] + 1;
                }
            }
            numPalindromes[k] = min;
        }
    }
    
    int result = numPalindromes[n-1];
    
    if (result < 3) {
        result++;
    }
    
    delete [] dp;
    delete [] numPalindromes;
    
    return result;*/
    
    bool dp[n][n];
    memset(dp, false, sizeof(dp));
    for (int i = 0; i < n; i++) {
        dp[i][i] = true;
    }
    
    for (int i = 0; i < n - 1; i++) {
        if (input[i] == input[i+1]) {
            dp[i][i+1] = true;
        }
    }
    
    for (int y = 3; y <= n; y++) {
        for (int w = 0; w < n-y+1; w++) {
            int m = w+y-1;
            if ((input[w] == input[m]) && (dp[w+1][m-1])) {
                dp[w][m] = true;
            }
        }
    }
    
    int* numPalindromes = new int[n];
    for (int k = 0; k < n; k++) {
        int min = INT_MAX;
        if (dp[0][k]) {
            numPalindromes[k] = 1;
        } else {
            for (int p = 0; p < k; p++) {
                if ((dp[p+1][k]) && min > numPalindromes[p] + 1) {
                    min = numPalindromes[p] + 1;
                }
            }
            numPalindromes[k] = min;
        }
    }
    
    int result = numPalindromes[n-1];
    
    delete [] numPalindromes;
    
    return result;
}


int main(int argc, const char * argv[]) {
    int n;
    std::string input;
    std::cin >> n;
    std::cin >> input;
    
    std::cout << minPalindromes(n, input);
    return 0;
}

