#ifndef __PARSER_H__
#define __PARSER_H__

#include "dataList.h"

int parser(QueueType *q, char str[], int strMax);
int checkFormula(QueueType *q);
int convertPostfix(QueueType *qout, StackType *s, QueueType *qin);
void removeSpace(char str[], int strMax);
int readNumber(char *pstr, double *num);
#endif
