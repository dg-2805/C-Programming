/*a)	Write a Program to read randomly generated numbers from a file, implement MERGE SORT and write the sorted output to another file. Estimate the number of comparisons.
Take number of elements of the array from the user.*/

#CODE

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
int comparisons = 0;
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1 + 1], R[n2 + 1];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    int i = 0, j = 0;
    for (int k = l; k <= r; k++) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i++];
        } else {
            arr[k] = R[j++];
        }
    }
}
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    srand(time(NULL));
    FILE *infile = fopen("input.txt", "w");
    if (infile == NULL) {
        perror("Error opening input file");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        int num = rand() % 1000;  // Range 0-999
        fprintf(infile, "%d\t", num);
    }
    fclose(infile);
    infile = fopen("input.txt", "r");
    if (infile == NULL) {
        perror("Error opening input file for reading");
        return 1;
    }
    int arr[n];
    for (int i = 0; i < n; i++) {
        fscanf(infile, "%d", &arr[i]);
    }
    fclose(infile);
    comparisons = 0;
    mergeSort(arr, 0, n - 1);
    FILE *outfile = fopen("sorted_output.txt", "w");
    if (outfile == NULL) {
        perror("Error opening output file");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        fprintf(outfile, "%d\t", arr[i]);
    }
    fclose(outfile);
    printf("Number of comparisons: %d\n", comparisons);
    return 0;
}

/*

#OUTPUT

Input File

330	238	243	485	890	735	428	42	447	606	748	688	568 421	365	992	301	489	19	519	142	642	911	186	933	751 874	466	406	545	694	608	238	951	977	34	426	115	539 902	66	114	235	710	262	217	340	76	111	54	214	872 481	589	90	1	903	92	806	553	472	377	106	908	49   890	994	537	611	782	949	617	22	594	549	176	70	486 144	626	829	929	150	360	177	330	60	827	919	73	41   448	112	629	519	253	811	568	876	595

Enter number of elements: 100
Number of comparisons: 672

Output File

1	19	22	34	41	42	49	54	60	66	70	73	76    90	92	106	111	112	114	115	142	144	150	176	177	186 214	217	235	238	238	243	253	262	301	330	330	340	360 365	377	406	421	426	428	447	448	466	472	481	485	486 489	519	519	537	539	545	549	553	568	568	589	594	595 606	608	611	617	626	629	642	688	694	710	735	748	751 782	806	811	827	829	872	874	876	890	890	902	903	908 911	919	929	933	949	951	977	992	994		 



b) Take number of array input from the user along with number of elements in each array. Generate random elements for those arrays, write them into a file, implement MERGE SORT and write the sorted output to another file. Estimate the number of comparisons for each array and then calculate average number of comparisons as total comparison count/number of arrays.
*/
#CODE

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int comparisons = 0;

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1 + 1], R[n2 + 1];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    int i = 0, j = 0;
    for (int k = l; k <= r; k++) {
        comparisons++;
        if (L[i] <= R[j]) arr[k] = L[i++];
        else arr[k] = R[j++];
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
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
        mergeSort(arr, 0, n - 1);
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

/*
#OUTPUT

Input File
803 105 56 831 707 218 120 329 838 107 579 553 
961 478 23 687 823 192 474 314 958 961 390 274 
506 525 6 663 16 170 632 791 678 395 851 316 
297 956 291 861 486 814 227 927 157 429 842 954 
147 65 650 344 543 514 877 668 536 327 560 48 
836 209 932 849 700 883 202 55 670 101 959 295 
107 402 745 315 131 590 257 838 509 564 889 816 
212 54 288 233 62 846 803 395 990 341 271 600 
165 339 228 38 580 518 796 880 149 110 140 656 
107 88 234 161 311 593 976 802 709 238 80 487

Enter number of arrays (N): 10
Enter number of elements in each array (n): 12
Array 1: Comparisons = 44
Array 2: Comparisons = 44
Array 3: Comparisons = 44
Array 4: Comparisons = 44
Array 5: Comparisons = 44
Array 6: Comparisons = 44
Array 7: Comparisons = 44
Array 8: Comparisons = 44
Array 9: Comparisons = 44
Array 10: Comparisons = 44
Average Comparisons across 10 arrays = 44.00

Output File
56 105 107 120 218 329 553 579 707 803 831 838 
23 192 274 314 390 474 478 687 823 958 961 961 
6 16 170 316 395 506 525 632 663 678 791 851 
157 227 291 297 429 486 814 842 861 927 954 956 
48 65 147 327 344 514 536 543 560 650 668 877 
55 101 202 209 295 670 700 836 849 883 932 959 
107 131 257 315 402 509 564 590 745 816 838 889 
54 62 212 233 271 288 341 395 600 803 846 990 
38 110 140 149 165 228 339 518 580 656 796 880 
80 88 107 161 234 238 311 487 593 709 802 976
*/
