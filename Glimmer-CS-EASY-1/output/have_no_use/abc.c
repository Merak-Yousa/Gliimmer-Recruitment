#include<stdio.h>
int main() {
    int lecture = 1;
    int ticket = 0;
    int homework = 1;

if (lecture&&ticket)
{
    printf("可以参加讲座\n");
}else{
    printf("不可以参加讲座\n");
}

if (ticket||homework){
    printf("今晚有事干\n");
}

if (!ticket){
    printf("需要买票\n");
}

    return 0;
}