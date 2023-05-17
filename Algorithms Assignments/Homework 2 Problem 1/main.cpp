//
//  main.cpp
//  Homework 2 Problem 1
//
//  Created by Dylan Hilton on 10/9/22.
//

#include<stdio.h>
#include<stdlib.h>
#include<iostream>

void backtracking(char board[][8], int k, int n, int row, int* count) {
    if (k == 0) {  //check if all pieces are placed
        *count = *count +1;
    } else {
        if (row < n) {
            for(int column = 0; column < n; column++) { //iterate through every column of given row, looking for valid placement spots
                if (board[row][column] == '#') {
                    for (int i = 0; i < n; i++) { //check to make sure no other piece has been placed in this column already
                        if (board[i][column] == 'P') { //'P' means piece is placed here
                            break;
                        }
                        if (i == n-1) {
                            board[row][column] = 'P'; //place piece
                            for (int x = row + 1; x <= n; x++) { //call backtracking algorithm for every row that appears after current row
                                std::cout << "K - 1: " << k-1 << std::endl;
                                backtracking(board, k-1, n, x, count);
                            }
                            board[row][column] = '#'; //undo placement
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int count = 0;
    
    int n,k;
    int i,j;
    char board[8][8];
    fscanf(stdin, "%d %d", &n, &k);
    char tmp;
    fscanf(stdin, "%c", &tmp);
    count = 0;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            fscanf(stdin, "%c", &board[i][j]);
        }
        fscanf(stdin, "%c", &tmp);
    }
    
    backtracking(board, k, n, 0, &count);
    printf("%d\n", count);
    return 0;
}
