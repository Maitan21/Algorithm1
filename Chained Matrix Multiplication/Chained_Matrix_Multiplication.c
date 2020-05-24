//
//  Chained_Matrix_Multiplication.cpp
//  Algorithm
//
//  Created by Jho on 2020/05/15.
//  Copyright © jho All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define INT_MAX 999999;

void order(int a, int s, int *p[], FILE*st)
{
    int d;
    if (a == s) {
        fprintf(st, "%d ", a);
    }
    else {
        d = p[a][s];
        fputs("( ", st);
        order(a, d, p, st);
        order(d + 1, s, p, st);
        fputs(") ", st);
    }
}

void minmult(int n, int d[], int *p[], int *M[])
{
    int i ,j, k, diagonal, temp = 0;
    for (diagonal = 1; diagonal < n; diagonal++)
    {
        for (i = 1; i < n - diagonal; i++)
        {
            j = diagonal + i;
            M[i][j] = INT_MAX;
            for (k = i; k <= j - 1;k++)
            {
                temp = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
                if (temp < M[i][j])
                {
                    M[i][j] = temp;
                    p[i][j] = k;
                }
            }
        }
    }
}
int main()
{
    int N = 0;
    
    int count = 0;
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

    fscanf(fp, "%d", &N);


    int *d = (int *)malloc(sizeof(int)*N - 1);
    int **M;
    M = (int**)malloc(sizeof(int*) * N);
    for (int i = 1; i <= N; i++)
        M[i] = (int*)calloc(N, sizeof(int));
    int **p;
    p = (int**)malloc(sizeof(int*) * N);
    for (int i = 1; i <= N; i++)
        p[i] = (int*)calloc(N, sizeof(int));

    for (int i = 0; i < N; i++)
        fscanf(fp, "%d", &d[i]);

    fclose(fp);

    minmult(N,d,p,M);

    FILE *st = fopen("output.txt", "w");
    order(1, N - 1, p, st);
    fclose(st);

    return 0;
}
