#include<stdio.h>

void sum(const char* a,const char* b, char out[9]){
    int xa = 0, xb = 0;
    out [8] = '\0';

    for (int i = 0; a[i] != '\0'; i++)
        {xa = (xa << 1) | (a[i] - '0') ; }
    for (int i = 0; b[i] != '\0' ; i++)
        {xb = (xb << 1) | (b[i] - '0') ; }

    int Ea = (xa >> 3) & 0xF; int Ma = xa & 0x7;
    int Eb = (xb >> 3) & 0xF; int Mb = xb & 0x7;

    int siga = 8 | Ma; int sigb = 8 | Mb;

    int E;
    if (Ea >= Eb){
        sigb = sigb >> (Ea - Eb);
        E = Ea;
    }
    else {
        siga = siga >> (Eb - Ea);
        E = Eb;
    }
    
    int sig = siga + sigb;
    while (sig >= 16){
        sig >>= 1;
        E++;
    }

    int result = (E << 3) | (sig & 0x7);

    for (int i = 7 ; i>= 0 ; i--){
        out[i] = '0' + ((result >> (7 - i)) & 1); 
    }
}


int main(void){
    char a[16],b[16],out[9];
    
    while ((scanf("%15s %15s", a, b)) == 2){
        sum(a, b, out);
        printf("%s + %s = %s\n", a, b, out);
    }
    return 0;
}