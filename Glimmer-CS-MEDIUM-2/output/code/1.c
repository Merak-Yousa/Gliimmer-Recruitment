 #include<stdio.h>
 // 若相加不发生溢出返回 1，发生溢出返回 0
int is_safe(int x, int y) {

    int sum = x + y;
    int x_sign = (x >> 31) & 1;
    int y_sign = (y >> 31) & 1;
    int sum_sign = (sum >> 31) & 1;
    int result;

    // 请补全代码写在TO DO与END OD TO DO之间：
    //TO DO

    result = 1;
    if ((x_sign == y_sign & x_sign != sum_sign)){
    result = 0;
    }

    //END OF TO DO

    return  result;
}

int main(void){
    printf("%d\n", is_safe(88, 65));//期望1
    printf("%d\n", is_safe(1, 2));//期望1
    printf("%d\n", is_safe(-2000000000, -2000000000));//期望0
    return 0;
}