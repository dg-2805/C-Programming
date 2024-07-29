#include <stdio.h>
//Convert a matrix to yalematrix form
int main(){
    int arr[3][4]={{0,0,2,1},{0,0,3,0},{1,0,0,0}};
    int A[10];
    int J[10];
    int I[4];
    int k=0,c=0;
    I[0]=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            if (arr[i][j]!=0){
                A[k]=arr[i][j];
                J[k]=j;
                k++;
            }
        }
        I[i+1]=k;
    }
   printf("A array:\n");
    for (int i = 0; i < k; i++) {
        printf("%d\t", A[i]);
    }
    printf("\nI array:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d\t", I[i]);
    }
    printf("\nJ array:\n");
    for (int i = 0; i < k; i++) {
        printf("%d\t", J[i]);
    }

    return 0;
}