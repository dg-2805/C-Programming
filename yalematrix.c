/*Yale format represents a matrix M by three (one-dimensional) arrays, that respectively contain nonzero values, the extents of rows, and column indices*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows, cols;
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);

    // Dynamic memory allocation for the matrix
    int **arr = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        arr[i] = (int *)malloc(cols * sizeof(int));
    }

    printf("Enter elements of the matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    // Counting non-zero elements
    int nonZeroCount = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] != 0) {
                nonZeroCount++;
            }
        }
    }

    int *A = (int *)malloc(nonZeroCount * sizeof(int));
    int *J = (int *)malloc(nonZeroCount * sizeof(int));
    int *I = (int *)malloc((rows + 1) * sizeof(int));

    int k = 0;
    I[0] = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] != 0) {
                A[k] = arr[i][j];
                J[k] = j;
                k++;
            }
        }
        I[i + 1] = k;
    }
    
    printf("A array:\n");
    for (int i = 0; i < k; i++) {
        printf("%d\t", A[i]);
    }
    printf("\nI array:\n");
    for (int i = 0; i <= rows; i++) {
        printf("%d\t", I[i]);
    }
    printf("\nJ array:\n");
    for (int i = 0; i < k; i++) {
        printf("%d\t", J[i]);
    }

    
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);
    free(A);
    free(J);
    free(I);

    return 0;
}


/* Sample Output
Enter number of rows: 3
Enter number of columns: 3
Enter elements of the matrix:
0 1 0 1 2 0 0 0 4
A array:
1       1       2       4
I array:
0       1       3       4
J array:
1       0       1       2
*/
