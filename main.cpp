#include <iostream>
#include <string.h>
#include <ctime>
#include <cstdlib>
#include <assert.h>
#include <vector>
#include <algorithm>
#include "functions.h"
#include "tree.h"
#include "const.h"

int MAX_CONTROL_SEQUENCE;

using namespace std;

bool findKeys(std::vector<std::vector<unsigned int> > keys, unsigned int key1, unsigned int key2)
{
    std::vector<unsigned int>::iterator itValue;

    itValue = std::find(keys[key1].begin(), keys[key1].end(), key2);
    if (itValue != keys[key1].end())
        return true;

    return false;
}

int main()
{
    // WELL-KNOWN PARAMETERS

    int lenArg1 = 5; // quantity arguments in function F - polynom Zhegalkina. <= 31
    int lenArg2 = 5; // <= 31

    // input data for 1 part of genertor
    int lenResult = 17; // length in bits of random number <= 31

    assert(lenArg1 < lenResult);

    unsigned int lenF1 = (1 << lenArg1) - 1;  // quantity sums in F as 2**lenArg-1

    unsigned int numberStates1 = 1 << lenArg1;  // quantity states
    unsigned int * setStates1 = new unsigned int [numberStates1];
    for (unsigned int i = 0; i < numberStates1 - 1; i++) setStates1[i] = i + 1; // create transition function g
    setStates1[numberStates1 - 1] = 0;    // create transition function g

    unsigned int * F1 = inputRandom(lenArg1, lenF1);   // generation function F

    // input data for 2 part of generator
    unsigned int  lenF2 = (1 << lenArg2) - 1;
    unsigned int  numberStates2 = 1 << lenArg2;

    unsigned int * setStates2 = new unsigned int [numberStates2];
    for (unsigned int  i = 0; i < numberStates2/2 - 1; i++) setStates2[i] = i + 1;
    setStates2[numberStates2/2 - 1] = 0;

    for (unsigned int  i = numberStates2/2; i < numberStates2 - 1; i++) setStates2[i] = i - numberStates2/2 + 1;
    setStates2[numberStates2 - 1] = 0;

    unsigned int * F2 = inputRandom(lenArg2, lenF2);


    // GENERATOR

    unsigned int  nextState1 = 0; // key 1
    unsigned int  nextState2 = 0; // key 2

    assert((nextState1 < numberStates1) && (nextState2 < (numberStates2 >> 1)));

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
    std::list<unsigned int> *hashTable = new std::list<unsigned int> [1 << lenArg1];
    fillHashTable(lenResult, lenArg1, lenF1, F1, setStates1, hashTable);

    // printing
    std::cout << "lenResult = " << lenResult << std::endl;
    for (unsigned int i = 0; i <  static_cast<unsigned int>(1 << lenArg1); i++){
            std::cout << "H[" << i << "] = ";
            std::list<unsigned int> tmpList = hashTable[i];

            // displaying the result from the list
            for (std::list<unsigned int>::iterator it = tmpList.begin(); it != tmpList.end(); it++)
                std::cout << *it << " ";
            std::cout << std::endl;
    }

    // initialize massiv for saving keys
    std::vector<std::vector<unsigned int> > keys(1 << lenArg1);

    // start stopwatch
    start = std::clock();

    // run a loop in which for each initial state we compute control sequences with DSS
    for (unsigned int  initCondA2 = 0; initCondA2 < (numberStates2 >> 1); initCondA2++)
    {
        // for each state, all possible control sequences of a certain length write in massContSeq
        // and in countMassContrSeq write quantity of control sequences
        // for some states control sequence may not be
        MAX_CONTROL_SEQUENCE = 100;
        unsigned int * massContrSeq = new unsigned int [MAX_CONTROL_SEQUENCE];
        unsigned int  countSeq = DSS(lenResult, result, initCondA2, lenF2, F2, setStates2, massContrSeq); // lenResult <= 31

        for (unsigned int  i = 0; i < countSeq; i++)
        {
            std::list<unsigned int> tmpList = hashTable[hash(massContrSeq[i], lenArg1)];

            for (std::list<unsigned int>::iterator it = tmpList.begin(); it != tmpList.end(); it++)
            {
//                std::cout << "Keys : " << *it << " and " << initCondA2 << std::endl;
                if (!(findKeys(keys, *it, initCondA2)))
                        keys[*it].insert(keys[*it].end(), initCondA2);
            }
        }
    }

    // stop stopwatch
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << std::endl;
    int numberKeys = 0;

    for (unsigned int i = 0; i < keys.size(); i++)
    {
//        if (keys[i].size() > 0) std::cout << "Key1 = " << i << " Key2 = ";

        for (unsigned int j = 0; j < keys[i].size(); j++)
        {
//            std::cout << keys[i][j] << " ";
            numberKeys++;
        }
//        if (keys[i].size() > 0) std::cout << std::endl;
    }
    std::cout << std::endl << "NumberKeys = " << numberKeys << std::endl
              << "Time = " << duration << std::endl;
}
// хороший ли тон в статье добавлять комментарии к коду
