#include <stdio.h>
#include <stdlib.h>

int main()
{
    signed x,y;
    scanf("%d",&x,&y);
    if(x==0 || y==0)
    printf("punct pe axe\n");
    if(x>0 && y>0)
    printf("1\n");
    if(x<0 && y>0)
    printf("2\n");
    if(x<0 && y<0)
    printf("3\n");
    if(x>0 && y<0)
    printf("4\n");
    return 0;
}
