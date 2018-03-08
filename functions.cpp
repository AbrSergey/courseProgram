#include "functions.h"
#include "tree.h"
#include <iostream>
#include <string.h>
#include <ctime>
#include <cstdlib>
#include <assert.h>
#include "cmath"
#include <map>
#include <list>

bool polynomZhegalkina(unsigned int arg, unsigned int *summand, int lenSum){

    bool result = 0;

    for (int i = 0; i < lenSum; i++)
        if ((arg & summand[i]) == summand[i]) result ^= 1;

    return result;
}

void inputConsole (){

    //Fill an array of arguments with their values
    bool x;
    int lenArg, lenSum;
    unsigned int arg = 0;

    std::cout << "Enter the number of arguments" << std::endl;
    std::cin >> lenArg;

    for (int i = 0; i < lenArg; i++){
        std::cout << "Value of " << i << " argument" << std::endl;
        std::cin >> x;
        arg |= x;
        arg <<= 1;
    }
    arg >>= 1; //???

    //Fill an array of summand
    std::cout << "Enter the number of summands" << std::endl;
    std::cin >> lenSum;

    unsigned int *sum = new unsigned int[lenSum];
    for (int i = 0; i < lenSum; i++) sum[i] = 0;

    for (int i = 0; i < lenSum; i++){
        for (int j = 0; j < lenArg; j++){
            std::cout << j << " argument in " << i << " summand" << std::endl;
            std::cin >> x;
            sum[i] |= x;
            sum[i] <<= 1;
        }
        sum[i] >>= 1; //???
    }

    x = polynomZhegalkina(arg, sum, lenSum);

    std::cout << "Answer: " << x << std::endl;
}

unsigned int * inputRandom (int lenArg, int lenSum){    // lenArg  unsigned int или int ???

    //Fill an array of summand
    unsigned int *sum = new unsigned int [lenSum];

    for (int i = 0; i < lenSum; i++){
        sum[i] = rand() << (sizeof(unsigned int)*8 - lenArg);
        sum[i] >>= (sizeof(unsigned int)*8 - lenArg);
    }

    return sum;
}

void timeTestForPolynomZhegalkina (){

    std::cout << "Hello World!" << std::endl;

    int lenSum = 3;
    int lenArg = 3;
    unsigned int * sum;

    sum = inputRandom(lenArg, lenSum);

    srand(time(0));
    clock_t start;
    double duration;
    start = std::clock();

    for(int i = 0; i < 10000; i++){
        unsigned int arg = rand();
        polynomZhegalkina(arg, sum, lenSum);
    }

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << "polynomZhegalkina = " << duration << std::endl;
}


unsigned int generator(int lenRezult,
                       int lenF1, unsigned int * F1, unsigned int * setStates1, unsigned int cond1,
                       int lenF2, unsigned int * F2, unsigned int * setStates2, unsigned int cond2)
{
    unsigned int result = 0;

    for (int i = 0; i < lenRezult; i++){

        cond1 = setStates1[cond1];
        cond2 <<= 1;
        cond2 |= polynomZhegalkina(cond1, F1, lenF1);
        cond2 = setStates2[cond2];
        result <<= 1;
        result |= polynomZhegalkina(cond2, F2, lenF2);
    }

    return result;
}


void constructTableForAttack(int lenResult, int lenArg1, int lenF1, unsigned int *F1, unsigned int *setStates1)
{
    // input validation

    assert (lenResult <= 31);
    assert (lenArg1 <= 31);
    assert (lenF1 <= 31);

    // initialization

    unsigned int numberCond = 1 << lenArg1;
    unsigned int  sizeHashTable = 1 << lenResult;
    std::list<unsigned int> *HashTable = new std::list<unsigned int> [sizeHashTable];

    // computation

    for (unsigned int condInit = 0, resPolZheg = 0; condInit <= numberCond; condInit++, resPolZheg = 0){
        int condTmp = condInit;

        // get result from generator A1
        for (int i = 0; i < lenResult; i++){
            resPolZheg |= polynomZhegalkina(condTmp, F1, lenF1);
            condTmp = setStates1[condTmp];
            if (i < lenResult - 1) resPolZheg <<= 1;
        }

        // create list and add element
        if (HashTable[resPolZheg].empty() == true){
            std::list<unsigned int> tmpList;
            tmpList.push_back(condInit);
            HashTable[resPolZheg] = tmpList;
        }
        // add element to the end of list
        else{
            std::list<unsigned int> tmpList;
            tmpList = HashTable[resPolZheg];
            tmpList.push_back(condInit);
            HashTable[resPolZheg] = tmpList;
        }
    }

    // printing

    std::cout << "lenResult = " << lenResult << std::endl;

    for (unsigned int i = 0; i <  sizeHashTable; i++){
            std::cout << "H[" << i << "] = ";
            std::list<unsigned int> tmpList = HashTable[i];

            // displaying the result from the list
            for (std::list<unsigned int>::iterator it = tmpList.begin(); it != tmpList.end(); it++)
                std::cout << *it << " ";

            std::cout << std::endl;
    }

}

void DSS(int lenResult, unsigned int result, unsigned int cond2, int lenF2, unsigned int * F2, unsigned int * setStates2)
{
    Tree tree(cond2);
    TreeNode * root = tree.root();

    if (lenResult == 0) return;

//    bool bitRes;
//    bool flag;
    TreeNode * node = root;
    unsigned int res = result;
    unsigned int state = cond2;

    int t = 1;

    dss_helper (t, state, lenResult, res, lenF2, F2, setStates2, node);
    tree.print();
}

void dss_helper(int t, unsigned int state, int lenRes, unsigned int res,
                int lenF2, unsigned int * F2, unsigned int * setStates2, TreeNode * node)
{
    if (t > lenRes) return;

    bool bitRes, flag = false;

    if ((res & 1) == 1) bitRes = 1;
    else bitRes = 0;

    res >>= 1;
    lenRes--;

    state <<= 1;
    state |= 0;
    bool resF2 = polynomZhegalkina(state, F2, lenF2);
    if (resF2 == bitRes){
        // add left branch
        //_data = setStates(cond2)
        unsigned int cond = setStates2[state];
        node->insert(cond, false);
        flag = true;
        dss_helper(t, cond, lenRes, res, lenF2, F2, setStates2, node->_left);
    }

    state |= 1;
    resF2 = polynomZhegalkina(state, F2, lenF2);
    if (resF2 == bitRes){
        // add right branch
        // _data = setStates(cond2)
        unsigned int cond = setStates2[state];
        node->insert(cond, true);
        flag = true;
        dss_helper(t, cond, lenRes, res, lenF2, F2, setStates2, node->_right);
    }

    if (!flag){
         std::cout << "delete" << std::endl;
         node->delete_branch();
    }
}
