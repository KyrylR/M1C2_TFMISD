#ifndef LOGICAL_EVAL_H
#define LOGICAL_EVAL_H

#include <stdbool.h>

#include "semantic_table.h"

bool evaluateExpression(const char *expression, int semanticTable[NUM_OPERATIONS][NUM_VALUES][NUM_VALUES]);
bool isOperand(const char ch);
bool isOperator(const char ch);
void buildTruthTable(const char *templateExpr);

#endif // LOGICAL_EVAL_H
