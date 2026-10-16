#include <stdio.h>

int low(int x) {  //有符号
    return x & (-x);
}

int main(){

    printf("%d\n", low(10));   // 预期:2
    printf("%d\n", low(-10));  // 预期:2
    
    return 0;
}