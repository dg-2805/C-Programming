//Transposes a matrix
//Verifies column major formula
//Gives 1D format of the transposed matrix
#include <stdio.h>
#include <stdlib.h>
void display(int m, int n, int a[m][n]) {
    printf("In 2D form:\n");
    for (int k = 0; k < m; k++) {
        for (int l = 0; l < n; l++) {
            printf("%d\t", a[k][l]);
        }
        printf("\n");
    }
}
int main() {
    int m, n;
    printf("Enter number of rows and columns: ");
    scanf("%d%d", &m, &n);
    int arr[m][n];
    int tr[n][m];
    printf("Enter elements of array: ");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    display(m, n, arr);
    printf("Transposed matrix:\n");
    for (int k = 0; k < n; k++) {
        for (int l = 0; l < m; l++) {
            tr[k][l] = arr[l][k];
        }
    }
    display(n, m, tr);
    int r, c;
    printf("Enter row and column index (0-based): ");
    scanf("%d%d", &r, &c);
    printf("Address without formula: %ld\n", &tr[r][c] - &tr[0][0]);
    printf("Address with formula: %d\n", r * m + c);
    printf("In 1D form (Transposed) after conversion:\n");
    for (int k = 0; k < n; k++) {
        for (int l = 0; l < m; l++) {
            printf("%d\t", tr[k][l]);
        }
    }
    printf("\n");  
    return 0;
}

/*
Enter number of rows and columns: 3 4
Enter elements of array: 1 2 3 5 6 1 7 1 0 9 2 1     
In 2D form:
1	2	3	5	
6	1	7	1	
0	9	2	1	
Transposed matrix:
In 2D form:
1	6	0	
2	1	9	
3	7	2	
5	1	1	
Enter row and column index (0-based): 2
1
Address without formula: 7
Address with formula: 7
In 1D form (Transposed) after conversion:
1	6	0	2	1	9	3	7	2	5	11
  */
