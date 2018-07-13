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
