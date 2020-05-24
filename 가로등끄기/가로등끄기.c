//
//  가로등끄기.cpp
//  Algorithm
//
//  Created by Jho on 2020/05/15.
//  Copyright © jho All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *D;
int *W;
int *path;
int ***EE;
int ***DD;
int ***PP;

int light(int L, int R, int dir)
{
    int q,w;

    if (dir == 1)
    {
        q = EE[L + 1][R][1] + (DD[L + 1][R][1] + D[L + 1] - D[L])*W[L];
        w = EE[L + 1][R][2] + (DD[L + 1][R][2] + D[R] - D[L])*W[L];

        if ((q > w && w > 0) || q < 0) {
            DD[L][R][1] = DD[L + 1][R][2] + D[R] - D[L];
            EE[L][R][1] = w;
            PP[L][R][1] = R;
            return w;
        }
        else {
            DD[L][R][1] = DD[L + 1][R][1] + D[L + 1] - D[L];
            EE[L][R][1] = q;
            PP[L][R][1] = L + 1;
            return q;
        }
    }
    else
    {
        q = EE[L][R - 1][1] + W[R] * (DD[L][R - 1][1] + D[R] - D[L]);
        w = EE[L][R - 1][2] + W[R] * (DD[L][R - 1][2] + D[R] - D[R - 1]);

        if ((q > w && w > 0) || (q < 0)) {
            DD[L][R][2] = DD[L][R - 1][2] + D[R] - D[R - 1];
            EE[L][R][2] = w;
            PP[L][R][2] = R - 1;
            return w;
        }
        else {
            DD[L][R][2] = DD[L][R - 1][1] + D[R] - D[L];
            EE[L][R][2] = q;
            PP[L][R][2] = L;
            return q;
        }
    }
}

int main()
{
    char str;
    int N = 0, i, j, L = 0, R = 0, initpoint = 0;

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

    fscanf(fp, "%d %d", &N, &initpoint);
    
    path = (int*)malloc(sizeof(int)*(N + 1));
    D = (int*)malloc(sizeof(int)*(N + 1));
    W = (int*)malloc(sizeof(int)*(N + 1));
    EE = (int***)malloc(sizeof(int**)*(N + 1));
    DD = (int***)malloc(sizeof(int**)*(N + 1));
    PP = (int***)malloc(sizeof(int**)*(N + 1));
    
    for (i = 0; i <= N; i++)
    {
        EE[i] = (int**)malloc(sizeof(int*)*(N + 1));
        DD[i] = (int**)malloc(sizeof(int*)*(N + 1));
        PP[i] = (int**)malloc(sizeof(int*)*(N + 1));

        for (j = 0; j <= N; j++)
        {
            EE[i][j] = (int*)malloc(sizeof(int)*(3));
            DD[i][j] = (int*)malloc(sizeof(int)*(3));
            PP[i][j] = (int*)malloc(sizeof(int)*(3));
        }
    }

    for (i = 1; i <= N; i++){
        fscanf(fp, "%d %d", &D[i], &W[i]);
        }
    for (i = 1; i <= N; i++)
    {
        fscanf(fp, "%d %d ", &D[i], &W[i]);
    }
    fclose(fp);

    
    for (i = 1; i <= N; i++)
    {
        for (j = 0; j <= 0; j++)
        {
            DD[i][j][1] = 1000000000;
            DD[i][j][2] = 1000000000;
        }

        if (i != initpoint) {
            EE[i][i][1] = 1000000000;
            EE[i][i][2] = 1000000000;
        }
        DD[i][i][1] = 0;
        DD[i][i][2] = 0;
        PP[i][i][1] = 0;
        PP[i][i][2] = 0;
    }
    EE[initpoint][initpoint][1] = 0;
    EE[initpoint][initpoint][2] = 0;

    //light minimum
    for (i = 1; j <= N && i < N; i++)
    {
        EE[i][i + j][1] = light(i, i + j, 1);
        EE[i][i + j][2] = light(i, i + j, 2);

        if (i + j == N)
        {
            j++;
            i = 0;
        }
        if (j == N - 1)
            break;
    }
    light(1, N, 1);
    light(1, N, 2);

    //path

    FILE *st = fopen("output.txt", "w");

    if (((EE[1][N][1] > EE[1][N][2]) && (EE[1][N][2] > 0)) || (EE[1][N][1] < 0)) {
        fprintf(st, "%d\n", EE[1][N][2]);
        path[0] = N;
    }
    else {
        fprintf(st, "%d\n", EE[1][N][1]);
        path[0] = 1;
    }

    L = 1;
    R = N;
    j = 0;

    for (i = 1; i <= N; i++)
    {
        if (path[i] == initpoint)
            break;

        if (EE[L][R][1] > EE[L][R][2])
        {
            path[i] = PP[L][R][2];
            R--;
        }
        else
        {
            path[i] = PP[L][R][1];
            L++;
        }
    }
    for (i = N - 1; i >= 0; i--)
        fprintf(fp, "%d\n", path[i]);

    return 0;
}
