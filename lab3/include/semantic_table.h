#ifndef SEMANTIC_TABLE_H
#define SEMANTIC_TABLE_H

// Define constants for the number of logical values and operations
#define NUM_VALUES 2
#define NUM_OPERATIONS 5  // NOT, AND, OR, XOR, IMPLICATION

void fillSemanticTable(int semanticTable[NUM_OPERATIONS][NUM_VALUES][NUM_VALUES]);

#endif // SEMANTIC_TABLE_H
