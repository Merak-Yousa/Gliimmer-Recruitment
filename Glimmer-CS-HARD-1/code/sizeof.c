#include<stdio.h>
int main(){
	int a[] = {13,23,34,46,67,56};
	
	for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++){
		printf("%d\n",a[i]);
	}
		
	return 0;
}
