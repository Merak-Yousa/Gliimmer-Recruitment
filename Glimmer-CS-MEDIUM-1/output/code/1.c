#include <stdio.h>

int main() {
    unsigned char a = 251;

    unsigned char res = (a >> 3 - 1) & 1;

    printf("%d\n", res);
    return 0;
}