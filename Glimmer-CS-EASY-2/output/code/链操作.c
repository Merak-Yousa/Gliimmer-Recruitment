//在查找观看B站网课后,学习了链表的写法,只是部分记忆不清,使用了自动补全
#include <stdio.h>
#include <stdlib.h>
struct Student{
    int data;
    struct Student *next;
};

//创建节点
struct Student* create(int n){
    struct Student* head = (struct Student*)malloc(sizeof(struct Student));
    
    if (head == NULL) {
        printf("failed\n");
        return NULL;
    }
    
    head->data = n;
    head->next = NULL;
    
    return head;
}

//头插法
struct Student* addhead(struct Student* head, int n){
    struct Student* new = create(n);
    new->next = head;
    return new;
}

//尾插法
struct Student* addtail(struct Student* head, int n){
    struct Student* new = create(n);

    if (head == NULL) {
        return new;
    }
    
    struct Student* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = new;
    return head;
}

//查找元素
int find(struct Student* head, int n){
    struct Student* current = head;
    int index = 1;

    while(current != NULL){

        if(current->data == n){
            return index;
        }
        
        current = current->next;
        index++;
    }
    
    return -1;//not found
}

