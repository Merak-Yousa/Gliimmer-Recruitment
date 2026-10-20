#define MAXSIZE 100
#include <stdio.h>
typedef int ElemType;

typedef struct {
    ElemType data[MAXSIZE];
    int length;
}SeqList;

void iniList(SeqList *L){
    L->length = 0;
}

int appendElem(SeqList *L, ElemType e){
    if (L->length >= MAXSIZE) {
        return 0; // List is full
    }
}

int main(){
    SeqList list;
    iniList(&list);
    printf("初始化成功,目前长度占用%d\n",list.length);
    printf("目前占用内存%zu字节\n",sizeof(list));
return 0;
}
