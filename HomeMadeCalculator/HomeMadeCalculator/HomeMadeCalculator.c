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
	VListType VList = {
		{ { 0 }, },
		0,
	};
	while (1)
	{
		OType result;
		// input
		printf(">> ");
		gets(str);

		if (err = parser(&qInfix, &VList, str, STR_SIZE))
		{
			printf("!!! Parser Error: %d !!!\n", err);
			system("pause");
			return -1;
		}
		queuePrint(&qInfix, "Infix");
		if (err = convertPostfix(&qPostfix, &sCalculator, &qInfix))
		{
			printf("!!! Postfix Error: %d !!!\n", err);
			system("pause");
			return -1;
		}
		queuePrint(&qPostfix, "Postfix");
		if (err = postfixCalc(&qPostfix, &sCalculator))
		{
			printf("!!! Calc Error: %d !!!\n", err);
			system("pause");
			return -1;
		}
		result = stackPop(&sCalculator, &err);
		if (result.t == 'n')
			printf("\tans = %.6lf\n", result.d.num);
		else if (result.t == 'v')
			printf("\t%s = %.6lf\n", result.d.var->name, result.d.var->value);

		stackClear(&sCalculator);
		queueClear(&qInfix);
		queueClear(&qPostfix);
	}
	system("pause");
	return 0;
}
