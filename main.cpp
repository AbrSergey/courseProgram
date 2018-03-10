#include <iostream>
#include <string.h>
#include <ctime>
#include <cstdlib>
#include "functions.h"
#include"tree.h"

using namespace std;

int main()
{
    int lenArg1 = 3;    // количество аргументов в функции f - полином Жегалкина. <= 31
    int lenArg2 = 5;    // <= 31

    // Задание входных данных для 1 части генератора
    int lenResult = 7; // длина в битах случайного числа <= 31

    int lenF1 = (1 << lenArg1) - 1;  //количество сумм в функции f - полином Жегалкина  2**lenArg-1

    int numberStates1 = 1 << lenArg1;  // количество состояний
    unsigned int * setStates1 = new unsigned int [numberStates1];
    for (int i = 0; i < numberStates1 - 1; i++) setStates1[i] = i + 1;   // формируем функцию переходов g
    setStates1[numberStates1 - 1] = 0;    // формируем функцию переходов g

    unsigned int * F1 = inputRandom(lenArg1, lenF1);   // генерация функции f - полинома Жегалкина

    // Задание входных данных для 2 части генератора
    int lenF2 = (1 << lenArg2) - 1;
    int numberStates2 = 1 << lenArg2;

    unsigned int * setStates2 = new unsigned int [numberStates2];
    for (int i = 0; i < numberStates2/2 - 1; i++) setStates2[i] = i + 1;
    setStates2[numberStates2/2 - 1] = 0;

    for (int i = numberStates2/2; i < numberStates2 - 1; i++) setStates2[i] = i - numberStates2/2 + 1;
    setStates2[numberStates2 - 1] = 0;

    unsigned int * F2 = inputRandom(lenArg2, lenF2);

    // Вызов генератора
//    unsigned int nextState1 = 0; // key 1
//    unsigned int nextState2 = 0; // key 2

//    srand(time(0));
//    clock_t start;
//    double duration;
//    start = std::clock();

//    unsigned int r = generator(lenRezult,
//                               lenF1, F1, setStates1, nextState1,
//                               lenF2, F2, setStates2, nextState2);

//    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

//    cout << "time = " << duration << endl;

//    cout << "generator = " << r << endl;

    // HACK

//    constructTableForAttack(lenResult, lenArg1, lenF1, F1, setStates1);

    int result = 15;

    for (int cond2 = 0; cond2 < numberStates2; cond2++){
        std::cout << "cond2 = " << cond2 << std::endl;
        DSS( lenResult, result, cond2, lenF2, F2, setStates2); // lenResult <= 31
    }

}
