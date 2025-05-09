/*Write a program to implement Knuth-Morris-Pratt (KMP) algorithm for pattern matching. Check your
program for the following Text & Pattern:
T: b a c b a b a b a c a b a b a c a
P: a b a b a c a */

#CODE
#include <stdio.h> 
#include <string.h> 
 
// Function to compute the LPS (Longest Prefix Suffix) array 
void computeLPSArray(char* pattern, int M, int* lps) { 
    int length = 0; 
    lps[0] = 0; // LPS of first character is always 0 
 
    int i = 1; 
    while (i < M) { 
        if (pattern[i] == pattern[length]) { 
            length++; 
            lps[i] = length; 
            i++; 
        } else { 
            if (length != 0) { 
                length = lps[length - 1]; 
            } else { 
                lps[i] = 0; 
                i++; 
            } 
        } 
    } 
} 
 
// KMP search function 
void KMPSearch(char* pattern, char* text) { 
    int M = strlen(pattern); 
    int N = strlen(text); 
 
    int lps[M]; 
    computeLPSArray(pattern, M, lps); 
 
    int i = 0; // index for text[] 
    int j = 0; // index for pattern[] 
    while (i < N) { 
        if (pattern[j] == text[i]) { 
            i++; 
            j++; 
        } 
 
        if (j == M) { 
            printf("Pattern found at index %d\n", i - j); 
            j = lps[j - 1]; // Look for next possible match 
        } else if (i < N && pattern[j] != text[i]) { 
            if (j != 0) { 
                j = lps[j - 1]; 
            } else { 
                i++; 
            } 
        } 
    } 
} 

int main() { 
    char text[] = "BACBABABACABABACA"; 
    char pattern[] = "ABABACA"; 
    KMPSearch(pattern, text); 
    return 0; 
}

/*OUTPUT
Pattern found at index 4
Pattern found at index 10 */
