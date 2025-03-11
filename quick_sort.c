//File with randomly generated integers and implementing quick sort on them,storing in an output file
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
/*SAMPLE OUTPUT

$ gcc quick.c -o quick
$ ./quick
Enter number of arrays (N): 10
Enter number of elements in each array (n): 10
Array 1: Comparisons = 20
Array 2: Comparisons = 20
Array 3: Comparisons = 24
Array 4: Comparisons = 19
Array 5: Comparisons = 26
Array 6: Comparisons = 27
Array 7: Comparisons = 26
Array 8: Comparisons = 22
Array 9: Comparisons = 24
Array 10: Comparisons = 25
Average Comparisons across 10 arrays = 23.30


arrays_input.txt
338 249 759 465 271 421 326 666 797 638 
916 407 709 9 946 631 166 858 990 600 
224 197 992 639 829 176 383 27 111 61 
796 891 14 967 874 852 64 899 571 863 
358 9 679 715 285 339 721 199 426 862 
682 354 858 158 66 135 465 886 755 939 
521 960 185 193 733 602 111 648 606 43 
692 123 758 884 582 585 163 105 533 158 
926 898 235 162 253 773 298 313 862 655 
8 130 941 499 175 363 440 818 511 158 

arrays_sorted_output.txt
249 271 326 338 421 465 638 666 759 797 
9 166 407 600 631 709 858 916 946 990 
27 61 111 176 197 224 383 639 829 992 
14 64 571 796 852 863 874 891 899 967 
9 199 285 339 358 426 679 715 721 862 
66 135 158 354 465 682 755 858 886 939 
43 111 185 193 521 602 606 648 733 960 
105 123 158 163 533 582 585 692 758 884 
162 235 253 298 313 655 773 862 898 926 
8 130 158 175 363 440 499 511 818 941 
*/
