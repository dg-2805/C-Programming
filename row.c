//Coverts 2D matrix to 1D format and also verifies the row major formula for the address of a matrix element

#include <stdio.h>
#include <stdlib.h>

int main() {
	int m,n,i,j,k,l;
	printf("Enter number of rows and columns:");
	scanf("%d%d",&m,&n);
    int arr[m][n];
    printf("Enter elements of array:");
    for(i=0;i<m;i++){
    	for(j=0;j<n;j++){
    			scanf("%d",&arr[i][j]);
    		}
    }
    int r, c;
    printf("Enter row and column index (0-based): ");
    scanf("%d%d", &r, &c);
    printf("Address without formula: %u\n", (&arr[r][c]-&arr[0][0]));
    printf("Address with formula: %u\n",(r * n+ c));
    printf("In 2D form:\n");
    for(k=0;k<m;k++){
    	for(l=0;l<n;l++){
    		printf("%d\t",arr[k][l]);
    	}
    	printf("\n");
    }
    printf("In 1D form after conversion:\n");
    for(k=0;k<m;k++){
    	for(l=0;l<n;l++){
    		printf("%d\t",arr[k][l]);
    	}
    }
    return 0;
}
/*Sample Output
Enter number of rows and columns:2 3
Enter elements of array:1 4 0 5 6 7
Enter row and column index (0-based): 1 2
Address without formula: 5
Address with formula: 5
In 2D form:
1	4	0	
5	6	7	
In 1D form after conversion:
1	4	0	5	6	7
*/
