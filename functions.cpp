#include "functions.h"
#include "tree.h"
#include <iostream>
#include <string.h>
#include <ctime>
#include <cstdlib>
#include <assert.h>
#include "cmath"
#include <map>
#include <openssl/sha.h>

unsigned int reverseBits (unsigned int input, int lenInput);

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

        cond2 <<= 1;
        cond2 |= polynomZhegalkina(cond1, F1, lenF1);
        cond1 = setStates1[cond1];
        result <<= 1;
        result |= polynomZhegalkina(cond2, F2, lenF2);
        cond2 = setStates2[cond2];
    }

    return result;
}


void fillHashTable(int lenResult, int lenArg1, int lenF1, unsigned int *F1, unsigned int *setStates1,
                             std::list<unsigned int> *hashTable)
{
    // input validation
    assert (lenResult <= 31);
    assert (lenArg1 <= 31);

    // initialization
    unsigned int numberCond = 1 << lenArg1;

    // computation
    for (unsigned int condInit = 0, resPolZheg = 0; condInit < numberCond; condInit++, resPolZheg = 0){
        int condTmp = condInit;

        // get result from generator A1
        for (int i = 0; i < lenResult; i++){
            resPolZheg |= polynomZhegalkina(condTmp, F1, lenF1);
            condTmp = setStates1[condTmp];
            if (i < lenResult - 1) resPolZheg <<= 1;
        }

        // create list and add element
        if (hashTable[hash(resPolZheg, lenArg1)].empty() == true){
            std::list<unsigned int> tmpList;
            tmpList.push_back(condInit);
            hashTable[hash(resPolZheg, lenArg1)] = tmpList;
        }
        // add element to the end of list
        else{
            std::list<unsigned int> tmpList;
            tmpList = hashTable[hash(resPolZheg, lenArg1)];
            tmpList.push_back(condInit);
            hashTable[hash(resPolZheg, lenArg1)] = tmpList;
        }
    }
}

void fillHashTableTest(int lenResult, int lenArg1, int lenF1, unsigned int *F1, unsigned int *setStates1,
                             std::list<unsigned int> *hashTable)
{
    // input validation
    assert (lenResult <= 31);
    assert (lenArg1 <= 31);

    // initialization
    unsigned int numberCond = 1 << lenArg1;

    // computation
    for (unsigned int condInit = 0, resPolZheg = 0; condInit < numberCond; condInit++, resPolZheg = 0){
        int condTmp = condInit;

        // get result from generator A1
        for (int i = 0; i < lenResult; i++){
            resPolZheg |= polynomZhegalkina(condTmp, F1, lenF1);
            condTmp = setStates1[condTmp];
            if (i < lenResult - 1) resPolZheg <<= 1;
        }

        // create list and add element
        if (hashTable[resPolZheg].empty() == true){
            std::list<unsigned int> tmpList;
            tmpList.push_back(condInit);
            hashTable[resPolZheg] = tmpList;
        }
        // add element to the end of list
        else{
            std::list<unsigned int> tmpList;
            tmpList = hashTable[resPolZheg];
            tmpList.push_back(condInit);
            hashTable[resPolZheg] = tmpList;
        }
    }
}

int DSS(int lenResult, unsigned int result, unsigned int initState, int lenF2, unsigned int * F2, unsigned int * setStates2, unsigned int *controlSequence)
{
    assert (lenResult > 0 && lenResult <= 31);

    // computation

    // create a tree whose root is initState (cond2)
    Tree tree(initState);
    TreeNode * root = tree.root();

    int stage = 1;  // stage of tree
    result = reverseBits (result, lenResult); // reverse bit srquence of result
    dssHelper (stage, initState, lenResult, result, lenF2, F2, setStates2, root); // start of recursion

    // check whether the tree is empty or not
    if (root->_left == NULL && root->_right == NULL)
    {
        root = NULL;
        return 0;
    }

    // if the tree is not empty, then we calculate all possible control sequences
    int countSeq = 0;
    countSeq = root->printBits(controlSequence);

    return countSeq;
}

void dssHelper(int stage, unsigned int state, int lenRes, unsigned int res,
                int lenF2, unsigned int * F2, unsigned int * setStates2, TreeNode * node)
{
    if (stage > lenRes) return;
    stage++;

    bool bitRes;    // one result bit of array result bits

    if ((res & 1) == 1) bitRes = 1;
    else bitRes = 0;

    res >>= 1;

    state <<= 1;
    state |= 0;
    bool resF2 = polynomZhegalkina(state, F2, lenF2);
    if (resF2 == bitRes)    // check if output of A1 generator is 0
    {
        unsigned int nextCond = setStates2[state];
        node->insert(nextCond, false);      // add left branch, _data = setStates(cond2)
        dssHelper(stage, nextCond, lenRes, res, lenF2, F2, setStates2, node->_left);
    }

    state |= 1;
    resF2 = polynomZhegalkina(state, F2, lenF2);
    if (resF2 == bitRes)    // check if output of A1 generator is 1
    {
        unsigned int nextCond = setStates2[state];
        node->insert(nextCond, true);       // add right branch, _data = setStates(cond2)
        dssHelper(stage, nextCond, lenRes, res, lenF2, F2, setStates2, node->_right);
    }

    if (node->_left == NULL && node->_right == NULL && (stage - 1) <= lenRes)
        node->deleteBranch();
}

unsigned int reverseBits (unsigned int input, int lenInput)
{
    unsigned int output = input & 1;

    for (int i = 1; i < lenInput; i++)
    {
        output <<= 1;
        output |= (input & (1 << i)) >> i;
    }
    return output;
}

unsigned int hash(unsigned int data, unsigned int lenResult)
{
//    unsigned int r = data >> 16;
//    unsigned int l = data << 16;
//    unsigned int dL = l + (r << 16);
//    unsigned int dR = r + (l >> 16);
//    unsigned int result = dL+dR;

//    l = (result >> 24) << 24;
//    r = ((result >> 16) << 24);
//    dL = l + r;
//    dR = (l >> 8) + (r >> 8);

//    unsigned int r_R = (result << 16) >> 16;
//    result = dL + dR;

//    l = (r_R >> 8) << 8;
//    r = (r_R << 24) >> 24;

//    dL = l + (r << 8);
//    dR = (l >> 8) + r;
//    result += dL+dR;
// ewfrgzzzzzzzzzzzzzzz
    unsigned int l, r, res = data;

    // i - quantity of bases
    for (int i = 1, k = 1; i <= 4; i <<= 1, k++)
    {
        // compute b
        unsigned int b = 0;
        for (int t = 0; t < k; t++)
            b += 16 >> t;

        // compute into bases
        for (int j = 0; j < i; j++)
        {
            l = ((res << ((32 >> k) * j + (32 >> k))) >> b); // << ((32 - (32 >> (k - 1))) - j * (32 >> k) + (32 >> k));
            r = ((res << (32 >> (k - 1)) * j) >> b); // << ((32 - (32 >> (k - 1))) - j * (32 >> k));
            unsigned int sum = l + r;
            unsigned int min = l - r;
            sum <<= (32 >> k);
            sum >>= (32 >> k);
            min <<= (32 >> k);
            min >>= (32 >> k);

            unsigned int tmp = sum + (min << (32 >> k));
            res += tmp << (32 >> (k - 1)) * i;
        }
    }

    res = res % (1 << lenResult);

    return res;


//    unsigned char re[0];
//    unsigned char c[4];
//    c[0] = data & 0xFF;
//    c[1] = (data >> 8) & 0xFF;
//    c[2] = (data >> 16) & 0xFF;
//    c[3] = (data >> 24) & 0xFF;

//    SHA1(c, 4, re);

//    unsigned int y = static_cast<unsigned int>( *re );

//    return y;

}
