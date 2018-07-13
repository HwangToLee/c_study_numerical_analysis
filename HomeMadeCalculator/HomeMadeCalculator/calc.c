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