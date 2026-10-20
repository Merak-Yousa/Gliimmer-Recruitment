#include<stdio.h>
int main(){
	int price=0;
	int amount=100;
	
	printf("请输入票面(元):");
	scanf("%d",&amount);
	

    printf("请输入价格(元):");
	scanf("%d",&price);
	
	int change=amount-price;
	printf("找您%d元",change);
	
	return 0;}
