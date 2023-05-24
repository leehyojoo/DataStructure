#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define TEST 10000

int T[MAX][MAX];
int sum[MAX][MAX];
int result[TEST];

int main() {

    int num;
    scanf("%d", &num); // test case number

    int testnum = num;

    while (testnum > 0) {

        int col, row;
        scanf("%d %d", &row, &col); // column & row

        // matrix 
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                scanf("%d", &T[i][j]);
            }
        }

        // sum 배열 초기화
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                sum[i][j] = 0;
            }
        }

        // (0,0)
        sum[0][0] = T[0][0];


        // (i,0)
        for (int i = 1; i < row; i++) {
            sum[i][0] = sum[i - 1][0] + T[i][0];
        }

        // (0,j)
        for (int j = 1; j < col; j++) {
            sum[0][j] = sum[0][j - 1] + T[0][j];
        }

        // (i,j)
        for (int i = 1; i < row; i++) {
            for (int j = 1; j < col; j++) {
                if (sum[i - 1][j] > sum[i][j - 1])
                    sum[i][j] = sum[i - 1][j] + T[i][j];
                else
                    sum[i][j] = sum[i][j - 1] + T[i][j];
            }
        }

        result[num - testnum] = sum[row - 1][col - 1];

        testnum--;
    }

    for (int i = 0; i < num; i++) {
        printf("%d\n", result[i]);
    }

    return 0;
}