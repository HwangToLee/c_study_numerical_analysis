#include "dataList.h"

void stackPrint(StackType* s, char str[])
{
	int idx;

	if (str == NULL)
		printf(">>> Stack Print\n");
	else
		printf(">>> %s Print\n", str);

	for (idx = s->top; idx > 0; idx--)
	{
		switch (s->stack[idx - 1].t)
		{
		case 'n':
			printf("Depth: %d\tType: number\tData: %.6f\n", idx, s->stack[idx-1].d.num);
			break;
		case 'o':
			printf("Depth: %d\tType: operator\tData: %c\n", idx, s->stack[idx - 1].d.op);
			break;
		case 'b':
			printf("Depth: %d\tType: bracket\tData: %c\n", idx, s->stack[idx - 1].d.br);
			break;
		}
	}
	printf(">>> Print End\n");
}

int stackEmpty(StackType* s)
{
	return !s->top;
}

int stackPush(StackType* s, OType item)
{
	// check overflow
	if (s->top == STACK_SIZE)
		return -1; // error
				   // push item
	s->stack[s->top] = item;
	s->top++;

	return 0; // non-error
}

OType stackPeek(StackType* s, int* error)
{
	// check empty
	if (stackEmpty(s))
	{
		*error = -1; // error
		return (OType) { 0 }; // no data
	}
	// return item
	return s->stack[s->top - 1];
}

OType stackPop(StackType* s, int* error)
{
	// check empty
	if (stackEmpty(s))
	{
		*error = -1; // error
		return (OType) { 0 }; // no data
	}
	// pop item
	s->top--;
	return s->stack[s->top];
}

void queuePrint(QueueType* q, char str[])
{
	int idx;
	int order;

	if (str == NULL)
		printf(">>> Queue Print\n");
	else
		printf(">>> %s Print\n", str);

	for (idx = q->head, order = 1; idx != q->tail; idx = (idx + 1) % QUEUE_SIZE, order++)
	{
		switch (q->queue[idx].t)
		{
		case 'n':
			printf("Order: %d\tType: number\tData: %.6f\n", order, q->queue[idx].d.num);
			break;
		case 'o':
			printf("Order: %d\tType: operator\tData: %c\n", order, q->queue[idx].d.op);
			break;
		case 'b':
			printf("Order: %d\tType: bracket\tData: %c\n", order, q->queue[idx].d.br);
			break;
		default:
			printf("Order: %d\tType: ?????\tData: ??????\n", order);
		}
	}
	printf(">>> Print End\n");
}

int queueEmpty(QueueType* q)
{
	if (q->head == q->tail)
		return 1; // queue empty
	else
		return 0;
}

int queueFull(QueueType* q)
{
	if (((q->tail + QUEUE_SIZE - q->head) % QUEUE_SIZE) == QUEUE_SIZE - 1)
		return 1; // queue full
	else
		return 0;
}

int queuePush(QueueType* q, OType item)
{
	// check overflow
	if (queueFull(q))
		return -1; // error
	// push item
	q->queue[q->tail] = item;
	q->tail = (q->tail + 1) % QUEUE_SIZE;

	return 0; // non-error
}

OType queuePeekHead(QueueType* q, int* error)
{
	// check empty
	if (queueEmpty(q))
	{
		*error = -1; // error
		return (OType) { 0 }; // no data
	}
	// return item
	return q->queue[q->head];
}

OType queuePeekTail(QueueType* q, int* error)
{
	// check empty
	if (queueEmpty(q))
	{
		*error = -1; // error
		return (OType) { 0 }; // no data
	}
	// return item
	return q->queue[(q->tail + QUEUE_SIZE - 1) % QUEUE_SIZE];
}

OType queuePop(QueueType* q, int* error)
{
	int tempHead;
	// check empty
	if (queueEmpty(q))
	{
		*error = -1; // error
		return (OType) { 0 }; // no data
	}
	// pop item
	tempHead = q->head;
	q->head = (q->head + 1) % QUEUE_SIZE;
	return q->queue[tempHead];
}