#ifndef FUNCTIONS_H
#define FUNCTIONS_H

bool polynomZhegalkina(unsigned int arg, unsigned int *summand, int lenSum);

void inputConsole ();

unsigned int * inputRandom (int lenArg, int lenSum);

void timeTestForPolynomZhegalkina ();

unsigned int generator(int lenRezult,
                       int lenF1, unsigned int * F1, unsigned int * setStates1, unsigned int cond1,
                       int lenF2, unsigned int * F2, unsigned int * setStates2, unsigned int cond2);

void attack(int l, int lenF1, unsigned int *F1, unsigned int *setStates1);



#endif // FUNCTIONS_H
