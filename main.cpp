#include <iostream>
#include <string.h>
#include <ctime>
#include <cstdlib>
#include "functions.h"

using namespace std;

unsigned int generator(int lenRezult,
                       int lenF1, unsigned int * F1, unsigned int * setStates1,
                       int lenF2, unsigned int * F2, unsigned int * setStates2);

int main()
{
    // Задание входных данных для 1 части генератора
    int lenRezult = 10; // длина в битах случайного числа
    int lenArg1 = 2;  // количество аргументов в функции f - полином Жегалкина
    int lenF1 = 2; // количество сумм в функции f - полином Жегалкина

    int numberStates1 = 1 << lenArg1;  // количество состояний
    unsigned int * setStates1 = new unsigned int [numberStates1];
    for (int i = 0; i < numberStates1 - 1; i++) setStates1[i] = i + 1;   // формируем функцию переходов g
    setStates1[numberStates1 - 1] = 0;    // формируем функцию переходов g

    unsigned int * F1 = inputRandom(lenArg1, lenF1);   // генерация функции f - полинома Жегалкина

    // Задание входных данных для 2 части генератора
    int lenArg2 = 2;
    int lenF2 = 2;
    int numberStates2 = numberStates1 << 1;

    unsigned int * setStates2 = new unsigned int [numberStates2];
    for (int i = 0; i < numberStates1 - 1; i++) setStates2[i] = i + 1;
    setStates2[numberStates1 - 1] = 0;

    for (int i = numberStates1; i < numberStates2 - 1; i++) setStates2[i] = i - numberStates1 + 1;
    setStates2[numberStates2 - 1] = 0;

    unsigned int * F2 = inputRandom(lenArg2, lenF2);

    // Вызов генератора
    unsigned int r = generator(lenRezult,
                               lenF1, F1, setStates1,
                               lenF2, F2, setStates2);

    cout << "generator = " << r << endl;
}
