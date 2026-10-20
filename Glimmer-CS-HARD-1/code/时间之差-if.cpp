#include<stdio.h>
int main(){
	int hour1,hour2=0;
	int min1,min2=0;
	printf("时间1:");
	scanf("%d %d",&hour1,&min1);
	
	printf("时间2:");
	scanf("%d %d",&hour2,&min2);
	
	int ih=hour1-hour2;
	int im=min1-min2;
	
	if (im<0){
		im = im+60;
		ih--;
	}
	
	printf("时间差为%d时%d分",ih,im);
	
	return 0;
	
}
