#include<stdio.h>
int main(){
    char name[50];
    int age;
    int count=0;
    char choice;

    while(1){
        printf("你的名字和年龄(中间用空格隔开): ");
        scanf("%s %d", name,&age);
        
        getchar();//清除回车符

        printf("第 %d 次输入: 姓名是 %s, 年龄是 %d\n", ++count, name, age);

        printf("是否继续输入？(Y/N): ");
        scanf("%c", &choice);

        if(choice == 'N' || choice == 'n'){
            break;
        }
}
return 0;
}