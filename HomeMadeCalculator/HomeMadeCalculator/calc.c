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
		if (tempObject.t == 'n' || tempObject.t == 'v')
		{
			if (stackPush(s, tempObject))
				return -2;
		}
		else if (tempObject.t == 'o')
		{
			double a, b;
			OType aObj, bObj;
			err = 0;
			bObj = stackPop(s, &err);
			if (err)
				return -3;
			if (bObj.t == 'n')
				b = bObj.d.num;
			else if (bObj.t == 'v')
			{
				// assigned number
				if (bObj.d.var->assign)
					b = bObj.d.var->value;
				// not assigned var cannot be in right-hand side
				else
					return -4; // wrong parameter
			}

			err = 0;
			aObj = stackPop(s, &err);
			if (err)
				return -5;
			if (tempObject.d.op != '=')
			{
				if (aObj.t == 'n')
					a = aObj.d.num;
				else if (aObj.t == 'v')
				{
					if (aObj.d.var->assign)
						a = aObj.d.var->value;
					// not assigned var cannot be used if is not substitution
					else
						return -6; // wrong parameter
				}
			}
			// substitution need left-hand side as variable
			else if (aObj.t != 'v')
				return -7; // wrong parameter

			switch (tempObject.d.op)
			{
			case '^':
				tempObject.d.num = pow(a, b);
				tempObject.t = 'n';
				break;
			case '*':
				tempObject.d.num = a * b;
				tempObject.t = 'n';
				break;
			case '/':
				tempObject.d.num = a / b;
				tempObject.t = 'n';
				break;
			case '+':
				tempObject.d.num = a + b;
				tempObject.t = 'n';
				break;
			case '-':
				tempObject.d.num = a - b;
				tempObject.t = 'n';
				break;
			case '=':
				aObj.d.var->assign = 1;
				aObj.d.var->value = b;
				tempObject = aObj;
				break;
			}
			
			if (stackPush(s, tempObject))
				return -7;
		}
	}

	return 0;
}