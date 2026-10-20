#include<stdio.h>
struct point{
    int x;
    int y;
};
int main(){
    struct point p;
    p.x = 5;
    p.y = 10;

    struct point *pp;
    pp = &p;

    printf("%d,%d\n",p.x,p.y);

    pp->x = 12;
    pp->y = 232;

    printf("%d,%d\n",pp->x,pp->y);

    printf("%d,%d\n",p.x,p.y);
   return 0;
}
