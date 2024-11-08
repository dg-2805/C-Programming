#include <stdio.h>
int main() {
    FILE *file;
    char filename[100];
    int search_key, num;
    int found = 0;
    int index = 0;
    printf("Enter the filename to open: ");
    scanf("%s", filename);
    printf("Enter the integer to search for: ");
    scanf("%d", &search_key);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }
    for (index = 0; fscanf(file, "%d", &num) != EOF; index++) {
        if (num == search_key) {
            printf("Found the key %d in the file at index %d\n", search_key, index);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("%d was not found in the file.\n", search_key);
    }
    fclose(file);
    return 0;
}
/*Sample Output
nter the filename to open: i3.txt
Enter the integer to search for: 5
Found the key 5 in the file at index 404
*/
