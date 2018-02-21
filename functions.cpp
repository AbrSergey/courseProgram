#include "functions.h"
#include <iostream>
#include <string.h>
#include <ctime>
#include <cstdlib>
#include <assert.h>
#include "cmath"
#include <map>

using namespace std;

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

    cout << "Enter the number of arguments" << endl;
    cin >> lenArg;

    for (int i = 0; i < lenArg; i++){
        cout << "Value of " << i << " argument" << endl;
        cin >> x;
        arg |= x;
        arg <<= 1;
    }
    arg >>= 1; //???

    //Fill an array of summand
    cout << "Enter the number of summands" << endl;
    cin >> lenSum;

    unsigned int *sum = new unsigned int[lenSum];
    for (int i = 0; i < lenSum; i++) sum[i] = 0;

    for (int i = 0; i < lenSum; i++){
        for (int j = 0; j < lenArg; j++){
            cout << j << " argument in " << i << " summand" << endl;
            cin >> x;
            sum[i] |= x;
            sum[i] <<= 1;
        }
        sum[i] >>= 1; //???
    }

    x = polynomZhegalkina(arg, sum, lenSum);

    cout << "Answer: " << x << endl;
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

    cout << "Hello World!" << endl;

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

    cout << "polynomZhegalkina = " << duration << endl;
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


void attack(int l, int lenF1, unsigned int *F1, unsigned int *setStates1)
{
    int r = 0;
    int tmp = 2 << (l - 1);
    List *H = new List [tmp];

    // computation

    for (int condInit = 0; condInit <= lenF1; condInit++){
        int cond = condInit;
        for (int i = 0; i < l; i++){
            r |= polynomZhegalkina(cond, F1, lenF1);
            cond = setStates1[cond];
            if (i < l - 1) r <<= 1;
        }

        List l;

        if ( H[r].HeadIsNull() == true){
            l.Add(condInit);
            H[r] = l;
        }
        else{
            l = H[r];
            l.Add(condInit);
            H[r] = l;
        }
        r = 0;
    }

    // print to screen

    cout << "lenF1 = " << lenF1 << endl;

    for (int i = 0; i < tmp; i++){
            cout << "H[" << i << "] = ";
            List lp = H[i];
            lp.Show();
            cout << endl;
    }

}

void attack_array(int l, int lenF1, unsigned int *F1, unsigned int *setStates1)
{
        // initialization

        int collision = 10;
        int r = 0;

        int tmp = pow(2,l);

        int ** H = new int *[tmp];
        for (int i = 0; i < tmp; i++)
            H[i] = new int [collision];

        // computation

        for (int condInit = 0; condInit <= lenF1; condInit++){
            int cond = condInit;
            for (int i = 0; i < l; i++){
                r |= polynomZhegalkina(cond, F1, lenF1);
                cond = setStates1[cond];
                if (i < l - 1) r <<= 1;
            }

            int j;
            for (j = 0; H[r][j] != 0; j++)
                assert(j < collision);

            H[r][j] = condInit;
            r = 0;
        }

        // print to screen

        cout << "lenF1 = " << lenF1 << endl;

        for (int i = 0; i < tmp; i++){
            if (H[i][0] != 0){
                cout << "H[" << i << "] = "; //<< H[i] << endl;

                int j = 0;
                while(H[i][j] != 0){
                    cout << H[i][j] << "  ";
                    j++;
                }
                cout << endl;
            }
        }
}
