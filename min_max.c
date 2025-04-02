//Write a C program to find the minimum and maximum elements in an array simultaneously using pairwise comparison. Count the number of comparisons and compare it with the theoretical value. Display the min, max, and total comparisons.

#CODE

#include <stdio.h>

void min_max(int arr[], int n, int *min, int *max, int *comparisons) {
    int i;

    if (n % 2 == 0) {
        (*comparisons)++;
        if (arr[0] > arr[1]) {
            *min = arr[1];
            *max = arr[0];
        } else {
            *min = arr[0];
            *max = arr[1];
        }
        i = 2;
    } else {
        *min = arr[0];
        *max = arr[0];
        i = 1;
    }

    for (; i < n - 1; i += 2) {
        (*comparisons)++;
        if (arr[i] < arr[i + 1]) {
            (*comparisons)++;
            if (arr[i] < *min) {
                *min = arr[i];
            }
            (*comparisons)++;
            if (arr[i + 1] > *max) {
                *max = arr[i + 1];
            }
        } else {
            (*comparisons)++;
            if (arr[i + 1] < *min) {
                *min = arr[i + 1];
            }
            (*comparisons)++;
            if (arr[i] > *max) {
                *max = arr[i];
            }
        }
    }
}

int main() {
    int n;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int min, max, comparisons = 0;
    min_max(arr, n, &min, &max, &comparisons);

    printf("The minimum element is %d\n", min);
    printf("The maximum element is %d\n", max);

    if (n % 2 == 0) {
        printf("The number of elements is even.\n");
        printf("Number of comparisons: %d\n", 1 + 3 * (n - 2) / 2);
    } else {
        printf("The number of elements is odd.\n");
        printf("Number of comparisons: %d\n", 3 * (n - 1) / 2);
    }

    printf("Actual comparisons counted: %d\n", comparisons);

    return 0;
}

/*
#OUTPUT

Enter the number of elements in the array: 5
Enter the elements of the array:
1 -90 2 45 6
The minimum element is -90
The maximum element is 45
The number of elements is odd.
Number of comparisons: 6
Actual comparisons counted: 6


Enter the number of elements in the array: 6
Enter the elements of the array:
-80 2 33 1000 1000 5 5 
The minimum element is -80
The maximum element is 1000
The number of elements is even.
Number of comparisons: 7
Actual comparisons counted: 7
*/

