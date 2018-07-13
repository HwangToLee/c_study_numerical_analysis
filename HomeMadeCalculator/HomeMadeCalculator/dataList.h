#ifndef __DATALIST_H__
#define __DATALIST_H__

#include <stdio.h>

#define STACK_SIZE	(100)
#define QUEUE_SIZE	(100)

typedef union _DType_
{
	double num;
	char op;
	char br;
} DType;

typedef struct _OType_
{
	char t; // 'n': number, 'o': operator, 'b': bracket
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

int stackEmpty(StackType* s);
int stackPush(StackType* s, OType item);
OType stackPeek(StackType* s, int* error);
OType stackPop(StackType* s, int* error);
void stackPrint(StackType* s, char str[]);

int queueEmpty(QueueType* q);
int queueFull(QueueType* q);
int queuePush(QueueType* q, OType item);
OType queuePeekHead(QueueType* q, int* error);
OType queuePeekTail(QueueType* q, int* error);
OType queuePop(QueueType* q, int* error);
void queuePrint(QueueType* q, char str[]);

#endif

