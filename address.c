#include <stdio.h>
#include <stdlib.h>

int main() {
    int arr[3][4];
    int r, c;

    printf("Enter row and column index (0-based): ");
    scanf("%d%d", &r, &c);

    printf("Address without formula: %ud\n", (void *)(&arr[r][c]-&arr[0][0]));
    printf("Address with formula: %ud\n", (void *)(r * 4 + c));

    return 0;
}