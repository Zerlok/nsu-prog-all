#include "head.h"

int hashfunc(char* string)
{
	unsigned int i,hashvalue=0;
	for (i = 0; i<strlen(string);i++)
	{
		hashvalue += (power(string[i],7)+i);
	}
	hashvalue=hashvalue % HASH;
	return hashvalue;
}

NODE* createNode(char word[])

{
	int counter=1;
	NODE *newnode = (NODE*) malloc(sizeof(NODE));
	newnode->next=NULL;
	newnode->count=1;
	strcpy(newnode->word,word);
	return newnode;

}

NODE* insertNode(NODE* head, char * word)
{
	NODE *newNode = createNode(word);
	NODE *head1 = head;
	 while(1)
		{
			if(strcmp(head->word,word) == 0)
			{
				strcpy(head->word,word);
				head->count++;
				return head1;
			}
			if(head->next != NULL)
			head = head->next;
			else break;
		} 
	
	newNode->next = head1;
	return newNode;
}

int check(NODE *head)
{
	if (head == NULL)
		return 0;
	else
		return 1;
}

int power(int t, int k)
{
  int res = 1;
  while (k) 
      {
        if (k & 1) 
           res *= t;
        t *= t;
        k >>= 1;
      }
  return res;
}

void init(void)
{
	int i; 
	for(i = 0; i < MAX; i++)
	{
		Pmassiv[i] = NULL;
	}
	printf("all systems flow\n");
}

void printNode(void)
{
	int i;
	for (i=0;i<MAX;i++)
	{
		while (Pmassiv[i] != NULL)
		{
			printf("word: %s meet %d times in the text\n",Pmassiv[i]->word,Pmassiv[i]->count);
			Pmassiv[i] = Pmassiv[i]->next;
		}
	}
}
