#include <iostream>
#include <string.h>
#include <ctime>
#include <cstdlib>
#include "functions.h"

using namespace std;

int main()
{
    int lenRezult = 10; // длина в битах случайного числа
    int numberArg = 2;  // количество аргументов в функции f - полином Жегалкина
    int lenSum = 2; // количество сумм в функции f - полином Жегалкина
    int numberStates = 1 << numberArg;  // количество состояний

    unsigned int *setStates = new unsigned int [numberStates];

    for (int i = 0; i < numberStates - 1; i++)
        setStates[i] = i + 1;   // формируем функцию переходов g

    setStates[numberStates - 1] = 0;    // формируем функцию переходов g

    unsigned int * sum;

    sum = inputRandom(numberArg, lenSum);   // генерация функции f - полинома Жегалкина


    // //////////////////////////////////////////////////
    unsigned int result = 0;

    // Generator A

    for (int i = 0; i < lenRezult - 1; i++){

        result |= polynomZhegalkina(setStates[i], sum, lenSum);

        result <<= 1;
    }

    result |= polynomZhegalkina(setStates[lenRezult - 1], sum, lenSum);
    // ////////////////////////////////////////////////



    cout << "generatorA = " << result << endl;
}
