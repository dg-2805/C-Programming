//Representation of a sparse matrix in Triple format, original and transposed form
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float **allocate(int r, int c) {
    float **a = (float **)malloc(r * sizeof(float *));
    for (int i = 0; i < r; i++) {
        a[i] = (float *)malloc(c * sizeof(float));
    }
    return a;
}
void accept(float **mat, int m, int n) {
    int totalElements = m * n;
    int i;
    int minZeroCount = totalElements / 2;
    for (i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = 0.0;
        }
    }
    int nonZeroCount = totalElements - minZeroCount;
    int filledCount = 0;
    while (filledCount < nonZeroCount) {
        int i = rand() % m;
        int j = rand() % n;
        if (mat[i][j] == 0.0) {
            mat[i][j] = (float)rand() / RAND_MAX; 
            filledCount++;
        }
    }
}

void display(float **a, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%.2f\t", a[i][j]);
        }
        printf("\n");
    }
}

void display_triple(float **a, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (i == 0 || j < 2) {
                printf("%.0f\t", a[i][j]);
            } else {
                printf("%.2f\t", a[i][j]);
            }
        }
        printf("\n");
    }
}

float **sparse(float **a, int r, int c) {
    int k = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (a[i][j] != 0.0f) {
                k += 1;
            }
        }
    }
    float **spar = allocate(k + 1, 3);
    int count = 1;
    spar[0][0] = (float)r;
    spar[0][1] = (float)c;
    spar[0][2] = (float)k;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (a[i][j] != 0.0f) {
                spar[count][0] = (float)i;
                spar[count][1] = (float)j;
                spar[count][2] = a[i][j];
                count++;
            }
        }
    }
    return spar;
}
float **transpose(float **spar, int r, int c) {
    float **tr = allocate((int)spar[0][2] + 1, 3);
    tr[0][0] = spar[0][1];
    tr[0][1] = spar[0][0];
    tr[0][2] = spar[0][2];
    int count = 1;
    for (int i = 0; i < (int)spar[0][1]; i++) { 
        for (int j = 1; j <= (int)spar[0][2]; j++) {
            if ((int)spar[j][1] == i) {
                tr[count][0] = spar[j][1];
                tr[count][1] = spar[j][0];
                tr[count][2] = spar[j][2];
                count++;
            }
        }
    }
    return tr;
}

void freeing(float **a, int r) {
    for (int i = 0; i < r; i++) {
        free(a[i]);
    }
    free(a);
}
int main() {
    float **mat, **spar, **tr;
    int m, n;
    printf("Enter the number of rows and columns:\n");
    scanf("%d%d", &m, &n);
    mat = allocate(m, n);
    accept(mat, m, n);
    printf("Original Matrix:\n");
    display(mat, m, n);
    spar = sparse(mat, m, n);
    printf("Triple format (Original Matrix):\n");
    display_triple(spar, (int)spar[0][2] + 1, 3);
    tr = transpose(spar, m, n);
    printf("Triple format (Transpose Matrix):\n");
    display_triple(tr, (int)tr[0][2] + 1, 3);
    freeing(mat, m);
    freeing(spar, (int)spar[0][2] + 1);
    freeing(tr, (int)tr[0][2] + 1);
    return 0;
}

/*Sample Output
└─$ ./sparse
Enter the number of rows and columns:
2 3
Original Matrix:
0.28	0.00	0.00	
0.00	0.78	0.20	
Triple format (Original Matrix):
2	3	3	
0	0	0.28	
1	1	0.78	
1	2	0.20	
Triple format (Transpose Matrix):
3	2	3	
0	0	0.28	
1	1	0.78	
2	1	0.20
*/
