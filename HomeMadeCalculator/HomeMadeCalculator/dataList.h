#ifndef __DATALIST_H__
#define __DATALIST_H__

#include <stdio.h>
#include <string.h>

#define STACK_SIZE	(100)
#define QUEUE_SIZE	(100)
#define VAR_NAME_SIZE	(25)
#define VAR_LIST_SIZE	(100)

typedef struct _VType_
{
	char name[VAR_NAME_SIZE];
	int assign;
	double value;
} VType;

typedef struct _VListType_
{
	VType var[VAR_LIST_SIZE];
	int size;
} VListType;

typedef union _DType_
{
	double num;
	char op;
	char br;
	VType *var;
} DType;

typedef struct _OType_
{
	char t; // 'n': number, 'o': operator, 'b': bracket, 'v': variable
	DType d;
} OType;

typedef struct _StackType_
{
	OType stack[STACK_SIZE];
	int top;
} StackType;

// circular queue
typedef struct _QueueType_
{
	OType queue[QUEUE_SIZE];
	int head;
	int tail;
} QueueType;

VType* varSearch(VListType *v, char *str, int strMax);
VType* varNew(VListType *v, char *str, int strMax);

void stackClear(StackType *s);
int stackEmpty(StackType* s);
int stackPush(StackType* s, OType item);
OType stackPeek(StackType* s, int* error);
OType stackPop(StackType* s, int* error);
void stackPrint(StackType* s, char str[]);

void queueClear(QueueType *q);
int queueEmpty(QueueType* q);
int queueFull(QueueType* q);
int queuePush(QueueType* q, OType item);
OType queuePeekHead(QueueType* q, int* error);
OType queuePeekTail(QueueType* q, int* error);
OType queuePop(QueueType* q, int* error);
void queuePrint(QueueType* q, char str[]);

#endif

