#include <stdio.h>
#include <stdlib.h>
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
int read_file(const char *filename, int *arr) {
    FILE *file = fopen(filename, "r");
    int num, index = 0;
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 0;
    }
    while (fscanf(file, "%d", &num) != EOF) {
        arr[index++] = num;
    }
    fclose(file);
    return index;
}
void write_file(const char *filename, int *arr, int count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d\n", arr[i]);
    }
    fclose(file);
}
int main(int argc, char *argv[]) {
    if (argc != 7) {
        printf("Usage: %s <input_file1> <input_file2> <input_file3> <output_file1> <output_file2> <output_file3>\n", argv[0]);
        return 1;
    }
    int arr1[1000], arr2[10000], arr3[100000];
    int count1 = 0, count2 = 0, count3 = 0;
    count1 = read_file(argv[1], arr1);
    count2 = read_file(argv[2], arr2);
    count3 = read_file(argv[3], arr3);
    insertion_sort(arr1, count1);
    insertion_sort(arr2, count2);
    insertion_sort(arr3, count3);
    write_file(argv[4], arr1, count1);
    write_file(argv[5], arr2, count2);
    write_file(argv[6], arr3, count3);
    printf("Sorted numbers have been written to the respective output files.\n");
    return 0;
}
