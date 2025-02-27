/*Write two recursive programs to compute X^n, where both X & n are integers, one
computes it in O(n) time the other in O(log n) time.*/
#include <stdio.h>
int c = 0;
long long power_linear(int X, int n) {
    c++;
    if (n == 1) {
        return X;
    }
    return X * power_linear(X, n - 1);
}
int d = 0;
long long power_logarithmic(int X, int n) {
    d++;
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return X;
    }
    long long temp = power_logarithmic(X, n / 2);
    if (n % 2 == 0) {
        return temp * temp;
    } else {
        return X * temp * temp;
    }
}
int main() {
    int X, n;
    printf("Enter X and n: ");
    scanf("%d %d", &X, &n);
    c = 0;
    d = 0;
    long long result_linear = power_linear(X, n);
    printf("%d^%d = %lld\n", X, n, result_linear);
    printf("Function called %d times (Linear)\n", c);
    long long result_logarithmic = power_logarithmic(X, n);
    printf("%d^%d = %lld\n", X, n, result_logarithmic);
    printf("Function called %d times (Logarithmic)\n", d);
    return 0;
}
/*SAMPLE OUTPUT
daria@DG MINGW64 ~/OneDrive/Documents/New
$ gcc power.c -o power

daria@DG MINGW64 ~/OneDrive/Documents/New
$ ./power
Enter X and n: 2 15
2^15 = 32768
Function called 15 times (Linear)
2^15 = 32768
Function called 4 times (Logarithmic)

daria@DG MINGW64 ~/OneDrive/Documents/New
$ ./power
Enter X and n: 2 32
2^32 = 4294967296
Function called 32 times (Linear)
2^32 = 4294967296
Function called 6 times (Logarithmic)

daria@DG MINGW64 ~/OneDrive/Documents/New
$ ./power
Enter X and n: 2 17
2^17 = 131072
Function called 17 times (Linear)
2^17 = 131072
Function called 5 times (Logarithmic) */
