#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int row;
    int col;
    float val;
} Triplet;

void initializeMatrix(float **matrix, int m, int n)
{
    int i, j, k;
    for (i = 0; i < (m * n) / 2; i++)
    {
        j = rand() % m;
        k = rand() % n;
        matrix[j][k] = (float)rand() / RAND_MAX;
    }
}

void display(Triplet *t)
{
    int i;
    for (i = 0; i <= t[0].val; i++)
    {
        printf("%d %d %.2f\n", t[i].row, t[i].col, t[i].val);
    }
}

void convertToTriplet(float **matrix, int m, int n, Triplet *t)
{
    int k = 1, i, j;
    t[0].row = m;
    t[0].col = n;
    t[0].val = 0;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            float val = matrix[i][j];
            if (val != 0)
            {
                t[k].row = i;
                t[k].col = j;
                t[k].val = val;
                k++;
            }
        }
    }
    t[0].val = k - 1;
}
void addSparse(Triplet *t1, Triplet *t2, Triplet *t3)
{
    int i = 1, j = 1, k = 1;
    while (i <= t1[0].val && j <= t2[0].val)
    {
        if (t1[i].row < t2[j].row)
        {
            t3[k] = t1[i];
            i++;
            k++;
        }
        else if (t1[i].row > t2[j].row)
        {
            t3[k] = t2[j];
            j++;
            k++;
        }
        else
        {
            if (t1[i].col < t2[j].col)
            {
                t3[k] = t1[i];
                i++;
                k++;
            }
            else if (t1[i].col > t2[j].col)
            {
                t3[k] = t2[j];
                j++;
                k++;
            }
            else
            {
                t3[k].row = t1[i].row;
                t3[k].col = t1[i].col;
                t3[k].val = t1[i].val + t2[j].val;
                i++;
                j++;
                k++;
            }
        }
    }
    while (i <= t1[0].val)
    {
        t3[k] = t1[i];
        i++;
        k++;
    }
    while (j <= t2[0].val)
    {
        t3[k] = t2[j];
        j++;
        k++;
    }
    t3[0].row = t1[0].row;
    t3[0].col = t1[0].col;
    t3[0].val = k - 1;
}

int main()
{
    int m, n, m2, n2, i, j, k, f = 0;
    printf("Enter the number of rows and columns of the matrix: ");
    scanf("%d %d", &m, &n);
    float **matrix1 = (float **)malloc(m * sizeof(float *));
    for (i = 0; i < m; i++)
    {
        matrix1[i] = (float *)malloc(n * sizeof(float));
    }
    initializeMatrix(matrix1, m, n);
    Triplet *t1 = (Triplet *)malloc(((int)((m * n) / 2) + 1) * sizeof(Triplet));
    f += (m * n) / 2;
    convertToTriplet(matrix1, m, n, t1);
    printf("Matrix 1 in Triplet format:\n");
    display(t1);

    printf("Enter the number of rows and columns of the matrix: ");
    scanf("%d %d", &m2, &n2);
    if (m != m2 || n != n2)
    {
        printf("Error: Matrices do not have the same dimensions. Cannot perform addition.\n");
        return 1;
    }
    float **matrix2 = (float **)malloc(m2 * sizeof(float *));
    for (i = 0; i < m2; i++)
    {
        matrix2[i] = (float *)malloc(n2 * sizeof(float));
    }
    initializeMatrix(matrix2, m2, n2);
    Triplet *t2 = (Triplet *)malloc(((int)((m2 * n2) / 2) + 1) * sizeof(Triplet));
    f += (m2 * n2) / 2;
    f++;
    convertToTriplet(matrix2, m2, n2, t2);
    printf("Matrix 2 in Triplet format:\n");
    display(t2);

    Triplet *t3 = (Triplet *)malloc(f * sizeof(Triplet));
    addSparse(t1, t2, t3);
    printf("Resultant matrix in Triplet format:\n");
    display(t3);
    for (i = 0; i < m; i++)
    {
        free(matrix1[i]);
        free(matrix2[i]);
    }
    free(matrix1);
    free(matrix2);
    free(t1);
    free(t2);
    free(t3);
    return 0;
}

/*Sample Output
Enter the number of rows and columns of the matrix: 2
3
Matrix 1 in Triplet format:
2 3 3.00
0 0 0.28
1 1 0.78
1 2 0.20
Enter the number of rows and columns of the matrix: 2
3
Matrix 2 in Triplet format:
2 3 3.00
0 0 0.72
0 1 0.95
1 2 0.63
Resultant matrix in Triplet format:
2 3 4.00
0 0 1.00
0 1 0.95
1 1 0.78
1 2 0.83
*/
