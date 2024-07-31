#include <stdio.h>
#include <stdlib.h>
int **allocate(int r, int c) {
    int **a = (int **)malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++) {
        a[i] = (int *)malloc(c * sizeof(int));
    }
    return a;
}
void accept(int **a, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &a[i][j]);
        }
    }
}
void display(int **a, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
}
int **sparse(int **a, int r, int c) {
    int k = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (a[i][j] != 0) {
                k += 1;
            }
        }
    }
    int **spar = allocate(k + 1, 3);
    int count = 1; 
    spar[0][0] = r;
    spar[0][1] = c;
    spar[0][2] = k;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (a[i][j] != 0) {
                spar[count][0] = i;
                spar[count][1] = j;
                spar[count][2] = a[i][j];
                count++;
            }
        }
    }
    return spar;
}
void freeing(int **a, int r) {
    for (int i = 0; i < r; i++) {
        free(a[i]);
    }
    free(a);
}

int main() {
    int **mat, **spar;
    int m, n;
    scanf("%d%d", &m, &n);
    mat = allocate(m, n);
    accept(mat, m, n);
    display(mat, m, n);
    spar = sparse(mat, m, n);
    display(spar, spar[0][2] + 1, 3);
    freeing(mat, m);
    freeing(spar, spar[0][2] + 1);
    return 0;
}
