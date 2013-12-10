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
	
	while(head!=NULL) {
		t=head;
		head=head->next;
		free(t);
	}
}

int main () {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int k,r;
	struct list *head , *p, *t;
	head=(List*)malloc(sizeof(List));

	scanf("%d",&head->data);
	head->next=NULL;
	while(scanf("%d",&k)==1)
	{
		if(k<head->data)
		{
			p=(List*)malloc(sizeof(List));
			p->data=k;
			p->next=head;
			head=p;
		}
		p=head;
		r=1;
		while((r)&&(p->next!=NULL))
		{
			if((k>p->data)&&(k<p->next->data))
			{	
				t=(List*)malloc(sizeof(List));
				t->data=k;
				t->next=p->next;
				p->next=t;
				r=0;
			}
			else
				p=p->next;
		}

		if((k>p->data)&&(p->next==NULL)&&(r))
			{
				t=(List*)malloc(sizeof(List));
				t->data=k;
				p->next=t;
				t->next=NULL;
			}

		
	}
	p=head;
	while(p!=NULL)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	fr(head);
	return 0;
}