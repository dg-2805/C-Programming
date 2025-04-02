/*Write a Program to multiply a chain of matrices optimally using iterative version of Dynamic Programming approach. Check your program for the sequence of 4 matrices <M1, M2,
M3, M4>; whose sequence of dimensions is <13, 5, 89, 3, 34> */

#CODE

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void printOptimalParenthesis(int i, int j, int **s, char *name) {
    if (i == j) {
        printf("%c", (*name)++);
        return;
    }
    printf("(");
    printOptimalParenthesis(i, s[i][j], s, name);
    printOptimalParenthesis(s[i][j] + 1, j, s, name);
    printf(")");
}

void matrixChainMultiplication(int p[], int n) {
    int **m = (int **)malloc(n * sizeof(int *));
    int **s = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++) {
        m[i] = (int *)malloc(n * sizeof(int));
        s[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            m[i][j] = 0;
            s[i][j] = 0;
        }
    }

    for (int i = 1; i < n; i++) {
        m[i][i] = 0;
    }

    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];

                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("Minimum number of scalar multiplications: %d\n", m[1][n - 1]);

    printf("Optimal Parenthesization: ");
    char matrixName = 'A';
    printOptimalParenthesis(1, n - 1, s, &matrixName);
    printf("\n");

    printf("Matrix m:\n");
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i <= j) {
                printf("%d\t", m[i][j]);
            } else {
                printf("\t");
            }
        }
        printf("\n");
    }

    printf("Matrix s:\n");
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i <= j) {
                printf("%d\t", s[i][j]);
            } else {
                printf("\t");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(m[i]);
        free(s[i]);
    }
    free(m);
    free(s);
}

int main() {
    int p;
    printf("Enter the number of matrices: ");
    scanf("%d", &p);

    if (p <= 0) {
        printf("Invalid number of matrices. Please enter a positive integer.\n");
        return 1;
    }

    int *arr = (int *)malloc((p + 1) * sizeof(int));
    printf("Enter the dimensions of the matrices: ");

    for (int i = 0; i <= p; i++) {
        scanf("%d", &arr[i]);
    }

    matrixChainMultiplication(arr, p + 1);
    free(arr);

    return 0;
}

/*
#OUTPUT

Enter the number of matrices: 4           
Enter the dimensions of the matrices: 13 5 89 3 34
Minimum number of scalar multiplications: 2856
Optimal Parenthesization: ((A(BC))D)

Matrix m:
0       5785    1530    2856
           0    1335    1845
                0       9078
                           0

Matrix s:
0       1       1       3
        0       2       3
                0       3
                        0


Enter the number of matrices: 3
Enter the dimensions of the matrices: 5 9 4 2
Minimum number of scalar multiplications: 162
Optimal Parenthesization: (A(BC))

Matrix m:
0       180     162
            0    72
                  0

Matrix s:
0       1       1
        0       2
                0

*/
