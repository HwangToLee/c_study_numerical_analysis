# Structured Data List

## 0. Info

- Last Update: 2018.07.03
- Editor: 이성윤
- E-mail Contact: gomqual@gmail.com
- Source Location: https://github.com/GomPC/c_study_numerical



## 1. 스택 큐

### 1.1. Stack LIFO

- push: put new item in the stack
- pop: take the latest item from the stack
- peek: see the latest item of the stack
- empty: check whether the stack is empty

```c
#include <stdio.h>
#define STACK_SIZE	(10)
typedef struct _StackType_
{
	int stack[STACK_SIZE];
	int top;
} StackType;

StackType Stack = {
	{ 0, }, // int stack[STACK_SIZE];
	0,		// int top;
};

int main()
{
	int i, error = 0;
	for(i = 0; i < 15; i++)
		if(stackPush(i)) printf("Stack Full: %d\n", i);
	i = 0;
	printf("Stack Top: %d\n", Stack.top);
	while (!stackEmpty())
	{
		printf("Stack Pop %d: %d\n", ++i, stackPop(&error));
		if (error)
			printf("!!! Stack Error !!!\n");
	}
	printf("Stack Top: %d\n", Stack.top);
    return 0;
}

int stackEmpty(void)
{
	return !Stack.top;
}

int stackPush(int item)
{
	// check overflow
	if (Stack.top == STACK_SIZE)
		return -1; // error
	// push item
	Stack.stack[Stack.top] = item;
	Stack.top++;

	return 0; // non-error
}

int stackPeek(int* error)
{
	// check empty
	if (stackEmpty())
	{
		*error = -1; // error
		return 0; // no data
	}
	// return item
	return Stack.stack[Stack.top - 1];
}

int stackPop(int* error)
{
	// check empty
	if (stackEmpty())
	{
		*error = -1; // error
		return 0; // no data
	}
	// pop item
	Stack.top--;
	return Stack.stack[Stack.top];
}
```

### 1.2. Postfix Implementation

- Calculate 6 / 2 ( 1 + 3 ) ???
- 두 피연산자 뒤에 연산자를 둠으로써, 수식을 해석할 때 우선순위를 따로 고려할 필요가 없어지고, 괄호도 사라짐
- 6 / 2 * (1 + 3) => 6 2 / 1 3 + *

```c
#define STR_SIZE	(100)
int main()
{
	int i;
	char str[STR_SIZE];
	// input
	printf("Enter the calculation: ");
	scanf_s("%s", str, STR_SIZE);
	
	i = 0;
	while (i < STR_SIZE)
	{
		if (str[i] == '\0')
		{
			// end of string: take out all operators from stack
			int err = 0;
			char tempChar;
			while (1)
			{
				tempChar = stackPop(&err);
				if (err)
					break;
				else
					putchar(tempChar);
			}
			break;
		}
		else if ('0' <= str[i] && str[i] <= '9')
		{
			// number: print
			putchar(str[i]);
		}
		else if (str[i] == '(')
		{
			// bracket (: push
			if (stackPush(str[i]))
			{
				printf("\n!!! Stack full !!!\n");
				break;
			}
		}
		else if (str[i] == ')')
		{
			// bracket ): pop until meet (
			int err = 0;
			char tempChar;
			while(1)
			{
				tempChar = stackPop(&err);
				if (err)
				{
					printf("\n!!! Bracket dismatch !!!\n");
					break;
				}
				else if (tempChar != '(')
				{
					putchar(tempChar);
				}
				else
				{
					break;
				}
			}
			if (err)
				break;
		}
		else if (str[i] == '*' ||
				str[i] == '/')
		{
			// high priority operator
			while (1)
			{
				int err = 0;
				char tempChar;
				tempChar = stackPeek(&err);
				if (err)
				{
					stackPush(str[i]);
					break;
				}
				else if (tempChar == '*' || tempChar == '/')
				{
					putchar(stackPop(&err));
				}
				else
				{
					stackPush(str[i]);
					break;
				}
			}
		}
		else if (str[i] == '+' ||
				str[i] == '-')
		{
			// low priority operator
			while (1)
			{
				int err = 0;
				char tempChar;
				tempChar = stackPeek(&err);
				if (err)
				{
					stackPush(str[i]);
					break;
				}
				else if (tempChar == '*' ||
						tempChar == '/' ||
						tempChar == '+' ||
						tempChar == '-')
				{
					putchar(stackPop(&err));
				}
				else
				{
					stackPush(str[i]);
					break;
				}
			}
		}
		i++;
	}
	printf("\n");
	return 0;
}
```

### 1.3. Queue FIFO

- push: put a new item in the queue
- pop: take the oldest item from the queue
- peek head: see the oldest item
- peek tail: see the latest item
- empty: check whether the queue is empty

```c
#include <stdio.h>
#define QUEUE_SIZE	(10)

// circular queue
typedef struct _QueueType_
{
	int queue[QUEUE_SIZE];
	int head;
	int tail;
} QueueType;

QueueType Queue = {
	{ 0, },	// int queue[QUEUE_SIZE];
	0,		// int head;
	0,		// int tail;
};

int main()
{
	int i, error = 0;
    for (i = 0; i < 15; i++)
		if (queuePush(i)) printf("Queue Full: %d\n", i);
	i = 0;
	printf("Queue Head: %d\tTail: %d\n", Queue.head, Queue.tail);
	while (!queueEmpty())
	{
		printf("Queue Pop %d: %d\n", ++i, queuePop(&error));
		if (error)
			printf("!!! Queue Error !!!\n");
	}
	printf("Queue Head: %d\tTail: %d\n", Queue.head, Queue.tail);
    return 0;
}

int queueEmpty(void)
{
	if (Queue.head == Queue.tail)
		return 1; // queue empty
	else
		return 0;
}

int queueFull(void)
{
	if (((Queue.tail + QUEUE_SIZE - Queue.head) % QUEUE_SIZE) == QUEUE_SIZE - 1)
		return 1; // queue full
	else
		return 0;
}

int queuePush(int item)
{
	// check overflow
	if (queueFull())
		return -1; // error
	// push item
	Queue.queue[Queue.tail] = item;
	Queue.tail = (Queue.tail + 1) % QUEUE_SIZE;

	return 0; // non-error
}

int queuePeekHead(int* error)
{
	// check empty
	if (queueEmpty())
	{
		*error = -1; // error
		return 0; // no data
	}
	// return item
	return Queue.queue[Queue.head];
}

int queuePeekTail(int* error)
{
	// check empty
	if (queueEmpty())
	{
		*error = -1; // error
		return 0; // no data
	}
	// return item
	return Queue.queue[(Queue.tail+QUEUE_SIZE-1)%QUEUE_SIZE];
}

int queuePop(int* error)
{
	int tempHead;
	// check empty
	if (queueEmpty())
	{
		*error = -1; // error
		return 0; // no data
	}
	// pop item
	tempHead = Queue.head;
	Queue.head = (Queue.head + 1)%QUEUE_SIZE;
	return Queue.queue[tempHead];
}
```

### 1.4. Postfix Calculator Implementation

- postfix로 표현한 수식을 계산하려면 stack과 queue가 필요함
- string으로 받은 수식을 stack을 이용하여 queue에 postfix로 출력하고, queue의 postfix를 stack을 이용하여 계산함
- string 형태의 수식은 char 단위로 되어 있으므로 10의 자리, 소수점 등을 표현하고 연산자와 구별하려면 parser를 구현하여 숫자, 연산자, 괄호를 구분할 수 있는 데이터로 가공해야 함
- stack과 queue는 새로운 데이터 타입을 기반으로 작동하도록 수정해야 함
- parser는 그 외에도 띄어쓰기를 유연하게 처리하고, 열고 닫는 괄호의 호응을 확인하며, 연산자가 연속으로 두 개 오지 않는지 등 postfix로 변환하기 전에 문법 체크 기능을 수행해야 함
- 주의할 점으로, 문자 '-'는 연산자로 쓰지만 부호로 쓰이기도 하기 때문에, 수식 상 위치에 따라서 숫자의 일부로 볼 것인지, 연산자로 볼 것인지 구분해야 함 -> 수식의 맨 처음이나 여는 괄호 직후에 있으면 음수로 해석
- 문자열에서 숫자를 읽어들일 때는 sscanf를 활용하면 편리함

#### 1.4.1. Main

```c
#include <stdio.h>
#include <Windows.h>
#include "parser.h"
#include "calc.h"

#define STR_SIZE	(256)

int main()
{
	int err;
	char str[STR_SIZE];
	QueueType qInfix = { { 0, }, 0, 0 };
	QueueType qPostfix = { { 0, }, 0, 0 };
	StackType sCalculator = { { 0, }, 0 };
	// input
	printf("Enter the calculation: ");
	gets(str);

	if (err = parser(&qInfix, str, STR_SIZE))
	{
		printf("!!! Error: %d !!!\n", err);
		system("pause");
		return -1;
	}
	queuePrint(&qInfix, "Infix");

	if (err = convertPostfix(&qPostfix, &sCalculator, &qInfix))
	{
		printf("!!! Error: %d !!!\n", err);
		system("pause");
		return -1;
	}

	queuePrint(&qPostfix, "Postfix");

	if (err = postfixCalc(&qPostfix, &sCalculator))
	{
		printf("!!! Error: %d !!!\n", err);
		system("pause");
		return -1;
	}

	printf("Result: %.6lf\n", stackPeek(&sCalculator, &err).d.num);

	system("pause");
	return 0;
}
```



#### 1.4.2. dataList

- dataList.h

```c
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
```

- dataList.c

```c
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
```

#### 1.4.3. parser

- parser.h

```c
#ifndef __PARSER_H__
#define __PARSER_H__

#include "dataList.h"

int parser(QueueType *q, char str[], int strMax);
int checkFormula(QueueType *q);
int convertPostfix(QueueType *qout, StackType *s, QueueType *qin);
void removeSpace(char str[], int strMax);
int readNumber(char *pstr, double *num);
#endif
```

- parser.c

```c
#include "parser.h"


int parser(QueueType *q, char str[], int strMax)
{
	OType tempObject;
	int err;
	// remove spaces
	removeSpace(str, strMax);

	// convert string to data list
	int idx = 0;
	while (idx < strMax && str[idx] != '\0')
	{
		// number
		if ('0' <= str[idx] && str[idx] <= '9')
		{
			tempObject.t = 'n';
			idx += readNumber(&str[idx], &tempObject.d.num);
			if (queuePush(q, tempObject))
				return -1; // queue push error
		}
		// bracket
		else if (str[idx] == '(' || str[idx] == ')')
		{
			tempObject.t = 'b';
			tempObject.d.br = str[idx++];
			if (queuePush(q, tempObject))
				return -2; // queue push error
		}
		// operator
		else if (str[idx] == '+' || str[idx] == '^' ||
				str[idx] == '*' || str[idx] == '/')
		{
			tempObject.t = 'o';
			tempObject.d.br = str[idx++];
			if (queuePush(q, tempObject))
				return -3; // queue push error
		}
		// minus - special case
		else if(str[idx] == '-')
		{
			if (queueEmpty(q)) // no prior object
			{
				// read as number
				tempObject.t = 'n';
				idx += readNumber(&str[idx], &tempObject.d.num);
				if (queuePush(q, tempObject))
					return -4; // queue push error
			}
			else
			{
				err = 0;
				tempObject = queuePeekTail(q, &err);
				if (err)
					return -5; // queue peek error
				if (tempObject.t == 'b' && tempObject.d.br == '(')
				{
					// read as number
					tempObject.t = 'n';
					idx += readNumber(&str[idx], &tempObject.d.num);
					if (queuePush(q, tempObject))
						return -6; // queue push error
				}
				else
				{
					// read as operator
					tempObject.t = 'o';
					tempObject.d.br = str[idx++];
					if (queuePush(q, tempObject))
						return -7; // queue push error
				}
			}
		}
	}

	if (err = checkFormula(q))
		return err; // formula check wrong

	return 0;
}

int checkFormula(QueueType *q)
{
	int idx, open, close;
	char curr, last;

	open = 0; close = 0; curr = 0; last = 0;
	for (idx = q->head; idx != q->tail; idx = (idx + 1) % QUEUE_SIZE)
	{
		last = curr;
		curr = q->queue[idx].t;
		if (last == 'o' && curr == 'o')
		{
			return -8; // successive operator
		}
		else if (curr == 'b')
		{
			if (q->queue[idx].d.br == '(')
				open++;
			else if (q->queue[idx].d.br == ')')
				close++;
			else
				return -9; // wrong bracket

			if (close > open)
				return -10; // bracket dismatch, ')' is more than '('
		}
	}
	if (close != open)
		return -11; // bracket dismatch, number of '(' and ')' is not equal

	return 0;
}

int convertPostfix(QueueType *qout, StackType *s, QueueType *qin)
{
	int err;
	OType currObject;
	while (!queueEmpty(qin))
	{
		err = 0;
		currObject = queuePop(qin, &err);
		if (err)
			return -12; // queue pop error;
		switch (currObject.t)
		{
		case 'n':
			if (queuePush(qout, currObject))
				return -13; // queue push error
			break;
		case 'b':
			if (currObject.d.br == '(')
			{
				if (stackPush(s, currObject))
					return -14; // stack push error
			}
			else if (currObject.d.br == ')')
			{
				while (!stackEmpty(s))
				{
					err = 0;
					currObject = stackPop(s, &err);
					if (err)
						return -15; // stack pop error
					if (currObject.t != 'b')
					{
						if (queuePush(qout, currObject))
							return -16; // queue push error
					}
					else
					{
						if (currObject.d.br == '(')
							break;
						else
							return -17; // bracket error
					}
				}
			}
			break;
		case 'o':
			switch (currObject.d.op)
			{
			case '^':
				while (!stackEmpty(s))
				{
					err = 0;
					OType tempObject = stackPeek(s, &err);
					if (err)
						return -18; // stack peek error
					if (tempObject.t != 'o')
						break;
					else
					{
						if (tempObject.d.op == '^' ||
							tempObject.d.op == '*' ||
							tempObject.d.op == '/' ||
							tempObject.d.op == '+' ||
							tempObject.d.op == '-')
						{
							err = 0;
							if (queuePush(qout, stackPop(s, &err)))
								return -19; // queue push error
							if (err)
								return -20; // stack pop error
						}
						else
							return -21; // operator error
					}
				}
				break;
			case '*':
			case '/':
				while (!stackEmpty(s))
				{
					err = 0;
					OType tempObject = stackPeek(s, &err);
					if (err)
						return -18; // stack peek error
					if (tempObject.t != 'o')
						break;
					else
					{
						if (tempObject.d.op == '*' ||
							tempObject.d.op == '/' ||
							tempObject.d.op == '+' ||
							tempObject.d.op == '-')
						{
							err = 0;
							if (queuePush(qout, stackPop(s, &err)))
								return -19; // queue push error
							if (err)
								return -20; // stack pop error
						}
						else if (tempObject.d.op == '^')
							break;
						else
							return -21; // operator error
					}
				}
				break;
			case '+':
			case '-':
				while (!stackEmpty(s))
				{
					err = 0;
					OType tempObject = stackPeek(s, &err);
					if (err)
						return -18; // stack peek error
					if (tempObject.t != 'o')
						break;
					else
					{
						if (tempObject.d.op == '+' ||
							tempObject.d.op == '-')
						{
							err = 0;
							if (queuePush(qout, stackPop(s, &err)))
								return -19; // queue push error
							if (err)
								return -20; // stack pop error
						}
						else if (tempObject.d.op == '^' ||
							tempObject.d.op == '*' ||
							tempObject.d.op == '/')
							break;
						else
							return -21; // operator error
					}
				}
				break;
			}
			if (stackPush(s, currObject))
				return -22; // stack push error
			break;
		}
	}
	// take all from stack and put in the queue
	while (!stackEmpty(s))
	{
		err = 0;
		if (queuePush(qout, stackPop(s, &err)))
			return -23; // queue push error
		if (err)
			return -24; // stack pop error
	}

	return 0;
}


void removeSpace(char str[], int strMax)
{
	int convIdx, readIdx;
	
	convIdx = 0; readIdx = 0;
	while (readIdx < strMax)
	{
		if (str[readIdx] == '\0')
		{
			str[convIdx] = str[readIdx];
			break;
		}
		else if (str[readIdx] != ' ')
		{
			str[convIdx++] = str[readIdx++];
		}
		else
			readIdx++;
	}
	if (readIdx == strMax)
		str[strMax - 1] = '\0';
}

#define READ_NUM_MAX	(20)
int readNumber(char *pstr, double *num)
{
	int len = 1;
	char tempStr[READ_NUM_MAX];
	
	// until end of str,
	// while number or point
	tempStr[0] = pstr[0];
	while (pstr[len] != '\0' && (len < READ_NUM_MAX) &&
		(('0' <= pstr[len] && pstr[len] <= '9') ||
			pstr[len] == '.'))
	{
		tempStr[len] = pstr[len];
		len++;
	}
	tempStr[len] = '\0';
	sscanf_s(tempStr, "%lf", num);

	return len;
}
```

#### 1.4.4. calc

- calc.h

```c
#ifndef __CALC_H__
#define __CALC_H__

#include <math.h>
#include "dataList.h"

int postfixCalc(QueueType *qin, StackType *s);

#endif
```

- calc.c

```c
#include "calc.h"

int postfixCalc(QueueType *qin, StackType *s)
{
	int err;
	OType tempObject;
	while (!queueEmpty(qin))
	{
		err = 0;
		tempObject = queuePop(qin, &err);
		if (err)
			return -1;
		if (tempObject.t == 'n')
		{
			if (stackPush(s, tempObject))
				return -2;
		}
		else if (tempObject.t == 'o')
		{
			double a, b;
			err = 0;
			b = stackPop(s, &err).d.num;
			if (err)
				return -3;
			err = 0;
			a = stackPop(s, &err).d.num;
			if (err)
				return -4;
			switch (tempObject.d.op)
			{
			case '^':
				a = pow(a, b);
				break;
			case '*':
				a = a * b;
				break;
			case '/':
				a = a / b;
				break;
			case '+':
				a = a + b;
				break;
			case '-':
				a = a - b;
				break;
			}
			tempObject.t = 'n';
			tempObject.d.num = a;
			if (stackPush(s, tempObject))
				return -5;
		}
	}

	return 0;
}
```

