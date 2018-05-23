#include <iostream>
#include <string.h>
#include <ctime>
#include <cstdlib>
#include <assert.h>
#include "functions.h"
#include "tree.h"

using namespace std;
const int MAX_CONTROL_SEQUENCE = 10;

int main()
{
    // WELL-KNOWN PARAMETERS

    int lenArg1 = 2;    // количество аргументов в функции f - полином Жегалкина. <= 31
    int lenArg2 = 3;    // <= 31

    // Задание входных данных для 1 части генератора
    int lenResult = 5; // длина в битах случайного числа <= 31

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


    // GENERATOR

    int nextState1 = 0; // key 1
    int nextState2 = 1; // key 2

    assert((nextState1 < numberStates1) && (nextState2 < (numberStates2 << 1)));

    // start stopwatch
    srand(time(0));
    clock_t start;
    double duration;
    start = std::clock();

    // start generator of pseudo-random number
    unsigned int result = generator(lenResult,
                               lenF1, F1, setStates1, nextState1,
                               lenF2, F2, setStates2, nextState2);

    // stop stopwatch
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    // print time and number from generator
    cout << "time = " << duration << endl;
    cout << "generator = " << result << endl;


    // HACK

    // calculate the sequence of bits as a result of the work of the first part of the generator
    // and fill in the form of a hash table H[sequence_bits]=condition
    constructTableForAttack(lenResult, lenArg1, lenF1, F1, setStates1);

    // run a loop in which for each state we compute control sequences with DSS
    for (int cond2 = 0; cond2 <  numberStates2; cond2++){

        std::cout << "cond2 = " << cond2 << std::endl;

        // for each state, all possible control sequences of a certain length write in massContSeq
        // and in countMassContrSeq write quantity of control sequences
        // for some states control sequence may not be
        unsigned int * massContrSeq = new unsigned int [MAX_CONTROL_SEQUENCE];
        int countMassContrSeq = DSS(lenResult, result, cond2, lenF2, F2, setStates2, massContrSeq); // lenResult <= 31

        for (int i = 0;i < countMassContrSeq; i++){
            std::cout << i << " control sequence " << " = " << massContrSeq[i] << std::endl;
        }
    }
}
