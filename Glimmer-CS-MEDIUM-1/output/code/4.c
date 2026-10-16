#include <stdio.h>
#include <string.h>
#define MAX 200

int main(){
    char a[MAX], b[MAX], ans[MAX];
    char A[MAX], B[MAX];
    scanf("%s %s",a,b);

    int la = strlen(a);int lb = strlen(b);
    int n = (la > lb) ? la : lb;

    for(int i = 0; i < n; i++){
           A[i] = '0';
    }strcpy(A + (n - la), a);
    for(int i = 0; i < n; i++){
           B[i] = '0';
    }strcpy(B + (n - lb), b);

    for(int i = 0; i < n; i++){
        if(A[i] == B[i]){
            ans[i] = A[i];
        }
        else{
            for(int j = i; j < n; j++){
                ans[j] = '0';
            }
            break;
        }
    }
    ans[n] = '\0';
    printf("%s\n", ans);
}
