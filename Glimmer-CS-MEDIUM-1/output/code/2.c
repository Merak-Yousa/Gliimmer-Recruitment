#include <stdio.h>

int main() {
    unsigned char a = 16;// 二进制: 00010000
//假设将第三位修正为1,第5位修正为0,修正后为4
    unsigned char res = (a & ~(1 << (3 - 1)) | (1 << (3-1)));
    unsigned char res2 = (res & ~(1 << (5 - 1)) | (0 << (5-1)));

    printf("%d\n", res2);
    return 0;
}