#include <stdio.h>
void min_max(int arr[], int n, int *min, int *max) {
    int i;
    if (n % 2 == 0) {
        if (arr[0] > arr[1]) {
            *max = arr[0];
            *min = arr[1];
        } else {
            *max = arr[1];
            *min = arr[0];
        }
        i = 2;
    } else {
        *min = arr[0];
        *max = arr[0];
        i = 1;
    }
    while (i < n - 1) {
        if (arr[i] > arr[i + 1]) {
            if (arr[i] > *max) {
                *max = arr[i];
            }
            if (arr[i + 1] < *min) {
                *min = arr[i + 1];
            }
        } else {
            if (arr[i + 1] > *max) {
                *max = arr[i + 1];
            }
            if (arr[i] < *min) {
                *min = arr[i];
            }
        }
        i += 2;
    }
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    int arr[n];
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int min, max;
    min_max(arr, n, &min, &max);
    printf("The minimum element is %d and the maximum element is %d\n", min, max);

    return 0;
}

/*OUTPUT
Enter the number of elements in the array: 6
Enter the elements of the array: 2
80
9
1
-9
27
The minimum element is -9 and the maximum element is 80
*/
