#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b,c;
    scanf("%d",&a,&b,&c);
    if(a+b+c!=0 && a>=0 && b>=0 && c>=0)
        printf("DA\n");
        else
        printf("NU\n");

    return 0;
}
