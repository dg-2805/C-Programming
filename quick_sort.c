#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparisons = 0;

int lomutoPartition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = lomutoPartition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int main() {
    int N, n;
    printf("Enter number of arrays (N): ");
    scanf("%d", &N);
    printf("Enter number of elements in each array (n): ");
    scanf("%d", &n);
    srand(time(NULL));
    FILE *infile = fopen("arrays_input.txt", "w");
    FILE *outfile = fopen("arrays_sorted_output.txt", "w");
    int totalComparisons = 0;
    for (int arrayIndex = 0; arrayIndex < N; arrayIndex++) {
        int arr[n];
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 1000;
            fprintf(infile, "%d ", arr[i]);
        }
        fprintf(infile, "\n");
        comparisons = 0;
        quickSort(arr, 0, n - 1);
        for (int i = 0; i < n; i++) {
            fprintf(outfile, "%d ", arr[i]);
        }
        fprintf(outfile, "\n");
        printf("Array %d: Comparisons = %d\n", arrayIndex + 1, comparisons);
        totalComparisons += comparisons;
    }
    double avgComparisons = (double)totalComparisons / N;
    printf("Average Comparisons across %d arrays = %.2lf\n", N, avgComparisons);
    fclose(infile);
    fclose(outfile);
    return 0;
}

/*#OUTPUT
Input File

659 430 181 268 265 726 466 661 311 293 
480 946 967 447 520 269 548 765 972 945 
47 745 674 412 764 177 24 141 292 47 
784 19 228 344 726 887 253 444 744 234 
493 78 893 153 247 133 761 352 78 873 
0 245 72 649 273 919 297 149 997 223 
900 352 575 549 434 360 134 646 956 465 
305 684 931 663 811 423 827 451 656 443 
826 983 54 210 103 925 47 267 825 645 
326 218 350 149 911 890 702 23 125 113

Enter number of arrays (N): 10
Enter number of elements in each array (n): 10
Array 1: Comparisons = 21
Array 2: Comparisons = 25
Array 3: Comparisons = 21
Array 4: Comparisons = 24
Array 5: Comparisons = 27
Array 6: Comparisons = 21
Array 7: Comparisons = 22
Array 8: Comparisons = 25
Array 9: Comparisons = 23
Array 10: Comparisons = 25
Average Comparisons across 10 arrays = 23.40


Output File

181 265 268 293 311 430 466 659 661 726 
269 447 480 520 548 765 945 946 967 972 
24 47 47 141 177 292 412 674 745 764 
19 228 234 253 344 444 726 744 784 887 
78 78 133 153 247 352 493 761 873 893 
0 72 149 223 245 273 297 649 919 997 
134 352 360 434 465 549 575 646 900 956 
305 423 443 451 656 663 684 811 827 931 
47 54 103 210 267 645 825 826 925 983 
23 113 125 149 218 326 350 702 890 911
*/
