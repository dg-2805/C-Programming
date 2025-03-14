#CODE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 10

int comparisons = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void permute(int arr[], int start, int end, FILE *inputFile) {
    if (start == end) {
        for (int i = 0; i < end; i++) {
            fprintf(inputFile, "%d ", arr[i]);
        }
        fprintf(inputFile, "\n");
    } else {
        for (int i = start; i < end; i++) {
            swap(&arr[start], &arr[i]);
            permute(arr, start + 1, end, inputFile);
            swap(&arr[start], &arr[i]);  // Backtrack
        }
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void randomizedQuickSort(int arr[], int low, int high) {
    if (low < high) {
        int randomIndex = low + rand() % (high - low + 1);
        swap(&arr[randomIndex], &arr[high]);  // Random pivot
        int pi = partition(arr, low, high);
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}

int main() {
    srand(time(0));
    int n;
    printf("Enter the number of elements (max %d): ", MAX_N);
    scanf("%d", &n);

    if (n > MAX_N) {
        printf("Limit exceeded! Use n ≤ %d.\n", MAX_N);
        return 1;
    }

    int arr[MAX_N], tempArr[MAX_N];
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }

    FILE *inputFile = fopen("input.txt", "w");
    if (!inputFile) {
        printf("Error opening input file!\n");
        return 1;
    }

    permute(arr, 0, n, inputFile);
    fclose(inputFile);

    inputFile = fopen("input.txt", "r");
    if (!inputFile) {
        printf("Error opening input file!\n");
        return 1;
    }

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        printf("Error opening output file!\n");
        fclose(inputFile);
        return 1;
    }

    int totalComparisons = 0, permutationCount = 0;

    while (1) {
        int validPermutation = 1;
        for (int i = 0; i < n; i++) {
            if (fscanf(inputFile, "%d", &tempArr[i]) != 1) {
                validPermutation = 0;
                break;
            }
        }

        if (!validPermutation) {
            break;
        }

        comparisons = 0;
        randomizedQuickSort(tempArr, 0, n - 1);
        totalComparisons += comparisons;

        for (int i = 0; i < n; i++) {
            fprintf(outputFile, "%d ", tempArr[i]);
        }
        fprintf(outputFile, "\n");

        printf("Comparisons for permutation %d: %d\n", permutationCount + 1, comparisons);
        permutationCount++;
    }

    fclose(inputFile);
    fclose(outputFile);

    if (permutationCount > 0) {
        printf("Average comparisons: %.2f\n", (double)totalComparisons / permutationCount);
    } else {
        printf("No valid permutations found.\n");
    }

    return 0;
}

/*
#OUTPUT
Input File:

0 1 2 3 
0 1 3 2 
0 2 1 3 
0 2 3 1 
0 3 2 1 
0 3 1 2 
1 0 2 3 
1 0 3 2 
1 2 0 3 
1 2 3 0 
1 3 2 0 
1 3 0 2 
2 1 0 3 
2 1 3 0 
2 0 1 3 
2 0 3 1 
2 3 0 1 
2 3 1 0 
3 1 2 0 
3 1 0 2 
3 2 1 0 
3 2 0 1 
3 0 2 1 
3 0 1 2

Enter the number of elements (max 10): 4
Comparisons for permutation 1: 4
Comparisons for permutation 2: 5
Comparisons for permutation 3: 4
Comparisons for permutation 4: 4
Comparisons for permutation 5: 4
Comparisons for permutation 6: 4
Comparisons for permutation 7: 4
Comparisons for permutation 8: 6
Comparisons for permutation 9: 6
Comparisons for permutation 10: 6
Comparisons for permutation 11: 6
Comparisons for permutation 12: 6
Comparisons for permutation 13: 4
Comparisons for permutation 14: 6
Comparisons for permutation 15: 4
Comparisons for permutation 16: 6
Comparisons for permutation 17: 4
Comparisons for permutation 18: 6
Comparisons for permutation 19: 6
Comparisons for permutation 20: 4
Comparisons for permutation 21: 5
Comparisons for permutation 22: 4
Comparisons for permutation 23: 6
Comparisons for permutation 24: 4
Average comparisons: 4.92


Output File:
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3 
0 1 2 3
*/
