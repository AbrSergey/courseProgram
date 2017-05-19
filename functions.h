#ifndef FUNCTIONS_H
#define FUNCTIONS_H

bool polynomZhegalkina(unsigned int arg, unsigned int *summand, int lenSum);

void inputConsole ();

unsigned int * inputRandom (int lenArg, int lenSum);

void timeTestForPolynomZhegalkina ();

unsigned int generatorA(unsigned int * setStates, int numberStates, unsigned int * sum, int lenSum, int lenRezult);

#endif // FUNCTIONS_H
