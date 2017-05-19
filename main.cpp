#include <iostream>
#include <string.h>
#include <ctime>
#include <cstdlib>
#include "functions.h"

using namespace std;

int main()
{
    int lenRezult = 10;
    int numberArg = 2;
    int lenSum = 2;
    int numberStates = 1 << numberArg;

    unsigned int *setStates = new unsigned int [numberStates];

    for (int i = 0; i < numberStates - 1; i++)
        setStates[i] = i + 1;

    setStates[numberStates - 1] = 0;

    unsigned int * sum;

    sum = inputRandom(numberArg, lenSum);

    unsigned int x = generatorA(setStates, numberStates, sum, lenSum, lenRezult);

    cout << "generatorA = " << x << endl;
}
