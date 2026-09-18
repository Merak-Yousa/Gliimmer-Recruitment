#include <stdio.h>

int square(int num) {
    return num * num;
}//封装平方函数



int Overall(int s1, int s2, int s3) {
    int p = (s1 + s2 + s3) / 3;
    int f = (square(p - s1) + square(p - s2) + square(p - s3)) / 3;
   
    return 3 * p - f / 3;
}//综合成绩的函数



void rank(int zh1, int zh2, int zh3) {
    if (zh1 >= zh2 && zh2 >= zh3) {
        printf("小明 > 小强 > 小林");
    } else if (zh1 >= zh3 && zh3 >= zh2) {
        printf("小明 > 小林 > 小强");
    } else if (zh2 >= zh1 && zh1 >= zh3) {
        printf("小强 > 小明 > 小林");
    } else if (zh2 >= zh3 && zh3 >= zh1) {
        printf("小强 > 小林 > 小明");
    } else if (zh3 >= zh1 && zh1 >= zh2) {
        printf("小林 > 小明 > 小强");
    } else {
        printf("小林 > 小强 > 小明");
    }
}//比较大小



int main() {
    int x1, x2, x3;
    int y1, y2, y3;
    int z1, z2, z3;

    printf("请输入小明的三项成绩（顺序为A B C,以一个空格为间隔）：");
    scanf("%d %d %d", &x1, &x2, &x3);
    printf("请输入小强的三项成绩（顺序为A B C,以一个空格为间隔）：");
    scanf("%d %d %d", &y1, &y2, &y3);
    printf("请输入小林的三项成绩（顺序为A B C,以一个空格为间隔）：");
    scanf("%d %d %d", &z1, &z2, &z3);

    int zh1 = Overall(x1, x2, x3);
    int zh2 = Overall(y1, y2, y3);
    int zh3 = Overall(z1, z2, z3);

    rank(zh1, zh2, zh3);

    return 0;
}