#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b,c;
    scanf("%d",&a,&b,&c);
        if((a==b && a!=c) || (a==c && a!=b) || (b==c && a!=b))
            printf("isoscel\n");
        if(a*a+b*b==c*c || a*a+c*c==b*b || b*b+c*c==a*a)
            printf("dreptunghic\n");
        if((a*a+b*b==c*c && a==b) || (a*a+c*c==b*b && a==c)|| (b*b+c*c==a*a && b==c))
            printf("dreptunghic isoscel\n");
        if(a==b && b==c && a==c)
            printf("echilateral\n");
        if(a!=b && a!=c && b!=c)
            printf("oarecare\n");

    return 0;
}
