#include<stdio.h>
int final_milk(int x) {

    int y;

    // 请补全代码写在TO DO与END OD TO DO之间：
    //TO DO

    y = (x << 5) - (x << 2) + x;

    //END OF TO DO

    return y;
}
//测试
int main(void) {
    printf("%d\n", final_milk(1));//29
    printf("%d\n", final_milk(3));//87
    printf("%d\n", final_milk(10));//290
    return 0;
}