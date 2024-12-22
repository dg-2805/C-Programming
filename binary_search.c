#include <stdio.h>
#include <stdlib.h>
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}
int binarySearch(int arr[], int size, int key) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key)
            return mid;
        if (arr[mid] > key)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}
int main() {
    FILE *file;
    char filename[100];
    int search_key;
    int numbers[1000];
    int count = 0;
    printf("Enter the filename to open: ");
    scanf("%s", filename);
    printf("Enter the integer to search for: ");
    scanf("%d", &search_key);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }
    while (fscanf(file, "%d", &numbers[count]) != EOF) {
        count++;
    }
    fclose(file);
    qsort(numbers, count, sizeof(int), compare);
    int result = binarySearch(numbers, count, search_key);
    if (result != -1) {
        printf("Found the key %d in the file at index %d\n", search_key, result);
    } else {
        printf("%d was not found in the file.\n", search_key);
    }
    return 0;
}
/* Sample Output
Enter the filename to open: i3.txt
Enter the integer to search for: 5
Found the key 5 in the file at index 2 */
