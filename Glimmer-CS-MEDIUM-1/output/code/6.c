#include<stdio.h>

long long solve(int row, int n, int cols, int diag1, int diag2) {
    if (row == n) return 1;

    int all = (1 << n ) - 1;
    int forbidden = cols | diag1 | diag2;
    int avail = all & ~forbidden;

    long long count = 0;
    while (avail) {
        int bit = avail & -avail;
        avail = avail & (avail - 1);

        count += solve(row + 1, n,cols | bit, (diag1 | bit) << 1, (diag2 | bit) >> 1);
    }

    return count;
}

int main(void){
   for(int n = 1; n <= 15; n++){
    printf("N = %d  solutions = %lld\n", n , solve(0, n, 0, 0, 0));
   }

    return 0;
}