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
			tempObject.d.op = str[idx++];
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
					tempObject.d.op = str[idx++];
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
						if (tempObject.d.op == '^')
						{
							err = 0;
							if (queuePush(qout, stackPop(s, &err)))
								return -19; // queue push error
							if (err)
								return -20; // stack pop error
						}
						else if (tempObject.d.op == '*' ||
							tempObject.d.op == '/' ||
							tempObject.d.op == '+' ||
							tempObject.d.op == '-')
							break;
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
						if (tempObject.d.op == '^' ||
							tempObject.d.op == '*' ||
							tempObject.d.op == '/')
						{
							err = 0;
							if (queuePush(qout, stackPop(s, &err)))
								return -19; // queue push error
							if (err)
								return -20; // stack pop error
						}
						else if (tempObject.d.op == '+' ||
								tempObject.d.op == '-')
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
							tempObject.d.op == '-' ||
							tempObject.d.op == '^' ||
							tempObject.d.op == '*' ||
							tempObject.d.op == '/')
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

