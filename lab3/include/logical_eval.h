#ifndef LOGICAL_EVAL_H
#define LOGICAL_EVAL_H

#include <stdbool.h>

bool evaluateExpression(const char *expression);
bool isOperand(const char ch);
bool isOperator(const char ch);
void buildTruthTable(const char *templateExpr);

#endif // LOGICAL_EVAL_H
