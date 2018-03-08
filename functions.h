#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "tree.h"

bool polynomZhegalkina(unsigned int arg, unsigned int *summand, int lenSum);

void inputConsole ();

unsigned int * inputRandom (int lenArg, int lenSum);

void timeTestForPolynomZhegalkina ();

unsigned int generator(int lenRezult,
                       int lenF1, unsigned int * F1, unsigned int * setStates1, unsigned int cond1,
                       int lenF2, unsigned int * F2, unsigned int * setStates2, unsigned int cond2);

void constructTableForAttack(int lenResult, int lenArg1, int lenF1, unsigned int *F1, unsigned int *setStates1);

void DSS (int lenResult, unsigned int result, unsigned int cond2,
          int lenF2, unsigned int * F2, unsigned int * setStates2);

void dss_helper(int t, unsigned int state, int lenRes, unsigned int res,
                int lenF2, unsigned int * F2, unsigned int * setStates2, TreeNode *node);

#endif // FUNCTIONS_H
