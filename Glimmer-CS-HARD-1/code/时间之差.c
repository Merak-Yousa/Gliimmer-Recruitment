#include<stdio.h>
int main(){
	double hours1,hours2=0.0;
	double minutes1,minutes2=0.0;
	
	printf("请输入第一个时间:");
	scanf("%lfh%lfmin",&hours1,&minutes1);
	printf("请输入第二个时间:");
	scanf("%lfh%lfmin",&hours2,&minutes2);
	
	double maa=hours1*60+minutes1;
	double mbb=hours2*60+minutes2;
	double change=maa-mbb;
	
	int hours3=change/60;
	double minutes3=change-hours3*60;
	
	printf("两时间之差为%d时%lf分",hours3,minutes3);
	
	return 0;}
