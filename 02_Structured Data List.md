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
- 

