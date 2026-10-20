#include<stdio.h>
int main(){
    double foot=0;
    double inch=0;
    
    printf("请输入英尺:");
    scanf("%lf",&foot);

    printf("请输入英寸:");
    scanf("%lf",&inch);

    printf("你的身高为%f米",(foot+inch/12)*0.348);
    return 0;}
