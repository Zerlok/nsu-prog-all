#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define HASH 1024
#define MAX 1024

typedef struct NODE
{
	char *word[40];
	int count;
	struct NODE* next;

} NODE;

NODE * Pmassiv[MAX];

NODE * createNode(char*);
NODE * insertNode(NODE *, char*);
int power(int,int);
int hashfunc(char*);
void init(void);
int check(NODE*);
void printNode(void);