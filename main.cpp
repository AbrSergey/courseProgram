#include <iostream>
#include <string.h>
#include <ctime>
#include <cstdlib>

using namespace std;

bool polynomZhegalkina(unsigned int arg, unsigned int *summand, int lenSum){

    //Computation of the polynomial

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

void inputRandom (int lenArg, int lenSum){

    //Fill an array of arguments with their values
    bool x;
    unsigned int arg = 0;

    for (int i = 0; i < lenArg; i++){
        x = rand() % 2;
        arg |= x;
        arg <<= 1;
    }
    arg >>= 1; //???

    //Fill an array of summand
    unsigned int *sum = new unsigned int[lenSum];
    for (int i = 0; i < lenSum; i++) sum[i] = 0;

    for (int i = 0; i < lenSum; i++){
        for (int j = 0; j < lenArg; j++){
            x = rand() % 2;
            sum[i] |= x;
            sum[i] <<= 1;
        }
        sum[i] >>= 1; //???
    }

    x = polynomZhegalkina(arg, sum, lenSum);
}

int main()
{
    cout << "Hello World!" << endl;

    srand(time(0));

    for(int i = 0; i < 300000; i++) inputRandom(30,30);

    return 0;
}

