#include <stdio.h>
#include <stdlib.h>
#include <time.h>
float **matrix(int r,int c){
    float **a=(float **)malloc(r*sizeof(float *));
    for(int i=0;i<r;i++){
        a[i]=(float *)malloc(c*sizeof(float));
    }
    return a;
}
void insert(float **a,int r,int c){
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            a[i][j]=rand()%5;
        }
    }
}
void display(float **a,int r,int c){
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            printf("%.0f\t",a[i][j]);
        }
    }
}
void clear(float **a,int r,int c){
    for(int i=0;i<r;i++){
        free(a[i]);
        }
    free(a);
}
int main(){
    double t1=time(NULL);
    int n;
    scanf("%d",&n);
    float **m1,** m2,** r1;
    m1=matrix(n,n);
    m2=matrix(n,n);
    r1=matrix(n,n);
    insert(m1,n,n);
    insert(m2,n,n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            r1[i][j]=0;
            for(int k=0;k<n;k++){
                r1[i][j]+=m1[i][k]*m2[k][j];
            }
        }
    }
    double t2=time(NULL);
    double t3=(t2-t1)/CLOCKS_PER_SEC;
    printf("Time elapsed:%lf",t3);
    display(r1,n,n);
    clear(m1,n,n);
    clear(m2,n,n);
    return 0;
}