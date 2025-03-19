#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to print optimal parenthesization
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

// Function to find the minimum number of multiplications needed
void matrixChainMultiplication(int p[], int n) {
    // Allocating memory for m and s
    int **m = (int **)malloc(n * sizeof(int *));
    int **s = (int **)malloc(n * sizeof(int *)); // Stores the optimal split positions

    for (int i = 0; i < n; i++) {
        m[i] = (int *)malloc(n * sizeof(int));
        s[i] = (int *)malloc(n * sizeof(int));
    }

    // Initializing diagonal values to 0 (cost of single matrix multiplication)
    for (int i = 1; i < n; i++) {
        m[i][i] = 0;
    }

    // L is the chain length (from 2 to n-1)
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX; // Initialize to a large value

            // Try placing parenthesis at different positions between i and j
            for (int k = i; k < j; k++) {
                // Calculate cost
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];

                // Update minimum cost and store split position
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k; // Store split position
                }
            }
        }
    }

    // Output the minimum number of multiplications
    printf("Minimum number of scalar multiplications: %d\n", m[1][n - 1]);

    // Print optimal parenthesization
    printf("Optimal Parenthesization: ");
    char matrixName = 'A'; // To label matrices
    printOptimalParenthesis(1, n - 1, s, &matrixName);
    printf("\n");

    // Free allocated memory
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

    int *arr = (int *)malloc((p + 1) * sizeof(int)); // Allocate (p + 1) to store dimensions correctly
    printf("Enter the dimensions of the matrices: ");
    
    for (int i = 0; i <= p; i++) { // Read p + 1 elements
        scanf("%d", &arr[i]);
    }

    matrixChainMultiplication(arr, p + 1); // Pass p + 1 as n
    free(arr);

    return 0;
}

/*
OUTPUT

$ ./mat
Enter the number of matrices: 4
Enter the dimensions of the matrices: 12

13
15
4
5
Minimum number of scalar multiplications: 1644
Optimal Parenthesization: ((A(BC))D)


Enter the number of matrices: 3
Enter the dimensions of the matrices: 2
3
4
5
Minimum number of scalar multiplications: 64
Optimal Parenthesization: ((AB)C)


Enter the number of matrices: 3
Enter the dimensions of the matrices: 25
23
12
4
Minimum number of scalar multiplications: 3404
Optimal Parenthesization: (A(BC))


Enter the number of matrices: 6
Enter the dimensions of the matrices: 12
13
12
13
12
13
12
Minimum number of scalar multiplications: 9072
Optimal Parenthesization: ((AB)((CD)(EF)))


Enter the number of matrices: 6
Enter the dimensions of the matrices: 100
21
780
62
13
1
7
Minimum number of scalar multiplications: 68346
Optimal Parenthesization: ((A(B(C(DE))))F)

Enter the number of matrices: 4
Enter the dimensions of the matrices: 13
5
89
3
34
Minimum number of scalar multiplications: 2856
Optimal Parenthesization: ((A(BC))D)
*/
