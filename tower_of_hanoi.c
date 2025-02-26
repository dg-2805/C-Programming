#include <stdio.h>
int c=0;
void tower(int n,char s,char d,char t){
    if (n==1)
    {
        ++c;
        printf("Move disk 1 from %c to %c\n",s,d);
        return;
    }
    tower(n-1,s,t,d);
    ++c;
    printf("Move disk %d from %c to %c\n",n,s,d);
    tower(n-1,t,d,s);
}
int main(){
    int n;
    printf("Enter the number of disks:");
    scanf("%d",&n);
    tower(n,'S','D','T');
    printf("Move count:%d\n",c);
    return 0;
}
/*SAMPLE OUTPUT

Enter the number of disks:4
Move disk 1 from S to T
Move disk 2 from S to D
Move disk 1 from T to D
Move disk 3 from S to T
Move disk 1 from D to S
Move disk 2 from D to T
Move disk 1 from S to T
Move disk 4 from S to D
Move disk 1 from T to D
Move disk 2 from T to S
Move disk 1 from D to S
Move disk 3 from T to D
Move disk 1 from S to T
Move disk 2 from S to D
Move disk 1 from T to D
Move count:15

*/
