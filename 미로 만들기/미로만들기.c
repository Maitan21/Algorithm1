//
//  미로만들기.cpp
//  Algorithm
//
//  Created by Jho on 2020/05/15.
//  Copyright © jho All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

#define INT_MAX 9999999

void path(int N, char **touch, FILE *st);
int temp;
int row, col;
int left[100000], right[100000];

int N = 0, i = 0, j = 0, NN = 0;

int main()
{
    char str[200];

    printf("input file name?\n");
    scanf("%s", str)
    ;
    if (!strstr(str, ".txt"))
    {
        strcat(str, ".txt");
    }

    FILE *fp = fopen(str, "r");
    if (fp == NULL)
    {
        printf("file is not exits\n");
        return 0;
    }

    fscanf(fp, "%d ", &N);
    NN = N * N;

    char **room = (char**)malloc(sizeof(char*)*N);
    char **touch = (char**)malloc(sizeof(char*)*N); ///p
    int **length = (int**)malloc(sizeof(int*)*N); //d
    int **list = (int**)malloc(sizeof(int*)*NN);

    for (i = 0; i < N; i++) {
        room[i] = (char*)malloc(sizeof(char)*N);
        touch[i] = (char*)malloc(sizeof(char)*N);
        length[i] = (int*)malloc(sizeof(int)*N);
    }
    for (i = 0; i <= NN; i++) {
        list[i] = (int *)malloc(sizeof(int) * 2);
        list[i][0] = 0;
        list[i][1] = 0;
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
        {
            fscanf(fp, "%c ", &room[i][j]);
            length[i][j] = INT_MAX;
        }
    }
    length[0][0] = 0;

    fclose(fp);

    while (1)
    {
        temp = INT_MAX; //length 초기화
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                if (length[i][j] >= 0 && length[i][j] <= temp)
                {
                    temp = length[i][j];
                    row = i;
                    col = j;
                }
            }
        }

        if (row == N - 1 && col == N - 1) {
            break;
        }

        //touch 각 셀에 방향 표시
        //down
        if ((row - 1 >= 0 && row - 1 < N) && (col >= 0 && col < N) && length[row - 1][col] == INT_MAX)
        {
            if (room[row - 1][col] == '0')
                length[row - 1][col] = length[row][col] + 1;
            else
                length[row - 1][col] = length[row][col];
            touch[row - 1][col] = 'D';
        }
        // Up
        if ((row + 1 >= 0 && row + 1 < N) && (col >= 0 && col < N) && length[row + 1][col] == INT_MAX)
        {
            if (room[row + 1][col] == '0')
                length[row + 1][col] = length[row][col] + 1;
            else
                length[row + 1][col] = length[row][col];
            touch[row + 1][col] = 'U';
        }
        //Right
        if ((row >= 0 && row < N) && (col - 1 >= 0 && col - 1 < N) && length[row][col - 1] == INT_MAX)
        {
            if (room[row][col - 1] == '0')
                length[row][col - 1] = length[row][col] + 1;
            else
                length[row][col - 1] = length[row][col];
            touch[row][col - 1] = 'R';
        }
        //Left
        if ((row >= 0 && row < N) && (col + 1 >= 0 && col + 1 < N) && length[row][col + 1] == INT_MAX)
        {
            if (room[row][col + 1] == '0')
                length[row][col + 1] = length[row][col] + 1;
            else
                length[row][col + 1] = length[row][col];
            touch[row][col + 1] = 'L';
        }

        length[row][col] = -1;
    }

    FILE *st = fopen("output.txt", "w");

    fprintf(st, "%d\n", length[N - 1][N - 1]);
    path(N, touch, st);

    fclose(st);


    return 0;
}
void path(int N, char**touch, FILE *st)
{
    for (i = 0; row <= N - 1 && col <= N - 1; i++)
    {
        if (row == 0 && col == 0)
        {
            break;
        }
        switch (touch[row][col])
        {
        case 'L':
            col=col-1;
            break;
        case 'R':
            col=col+1;
            break;
        case 'U':
            row = row - 1;
            break;
        case 'D':
            row=row+1;
            break;
        }
        left[i] = row;
        right[i] = col;
    }
    //출력은 역순으로 recursion으로 올라감
    for (j = i - 1; j >= 0; j--)
    {
        fprintf(st, "%d %d\n", right[j] + 1,left[j] + 1);
    }
    fprintf(st, "%d %d\n", N, N);
}
