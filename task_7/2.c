#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define List struct list

List {
	int data;
	List *next;
};

void fr(List *head) {
	List *t;

	while(head!=NULL)
	{
		t=head;
		head=head->next;
		free(t);
	}
}

int main () {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int k,s;
	struct list *head , *p, *t;
	head=(struct list*)malloc(sizeof(struct list));
	p=t=head;
	
	scanf("%d",&head->data);
	while(scanf("%d",&k)==1) {
		p=(struct list*) malloc(sizeof(struct list));
		t -> next = p;
		p -> data = k;
		t = p;
	}
	p->next=NULL;
	k=0;
	s=0;
	p=head;
	while(p!=NULL) {
		k++;
		s+=p->data;
		p=p->next;
	}
	if(k!=0) {
		printf("%d",s/k);
	}
	fr(head);
	return 0;
}