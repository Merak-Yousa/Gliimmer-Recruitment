#include <stdio.h>
// 请补全以下代码
int hasCommonChar(const char *s1, const char *s2) {
    int mask1 = 0;
    int mask2 = 0;
    int m,n;

    for (const char *p = s2; *p; p++){
        n = *p - 'a';
        mask2 |= 1 << n;
    }

    for(const char *p = s1; *p; p++){
        m = *p - 'a';
        if(mask2 & (1 << m)){
            return 1;
        }
    }
 return 0;
}