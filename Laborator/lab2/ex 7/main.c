#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b,c,d,min1=1;
    scanf("%d",&a,&b,&c,&d);
    min1=a;
    if(b<min1) min1=b;
    if(c<min1) min1=c;
    if(d<min1) min1=d;

    printf("%d",min1);

    return 0;
}
