#include<stdio.h>
int main(){
	struct ABC {
		int sb;
		struct ABC *next;
	}a,b,c,*head,*p;
	a.sb = 13;b.sb = 78;c.sb = 91;
	head = &a; a.next = &b; b.next = &c; c.next = NULL;p = head;
	while(p!=NULL){
		printf("sb=%d\n",p->sb);
		p = p->next;
	}
	return 0;
} 
