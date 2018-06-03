#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "tree.h"
#include <list>

bool polynomZhegalkina(unsigned int arg, unsigned int *summand, int lenSum);

void inputConsole ();

unsigned int * inputRandom (int lenArg, int lenSum);

void timeTestForPolynomZhegalkina ();

unsigned int generator (int lenRezult,
                       int lenF1, unsigned int * F1, unsigned int * setStates1, unsigned int cond1,
                       int lenF2, unsigned int * F2, unsigned int * setStates2, unsigned int cond2);

void fillHashTable(int lenResult, int lenArg1, int lenF1, unsigned int *F1, unsigned int *setStates1,
                             std::list<unsigned int> *hashTable);

void fillHashTableTest(int lenResult, int lenArg1, int lenF1, unsigned int *F1, unsigned int *setStates1,
                             std::list<unsigned int> *hashTable);

unsigned int hash (unsigned int data, unsigned int lenResult);

int DSS (int lenResult, unsigned int result, unsigned int initState,
          int lenF2, unsigned int * F2, unsigned int * setStates2, unsigned int * controlSequence);

void dssHelper(int stage, unsigned int state, int lenRes, unsigned int res,
                int lenF2, unsigned int * F2, unsigned int * setStates2, TreeNode *node);

#endif // FUNCTIONS_H
