#include <iostream>
#include <string.h>

using namespace std;

bool polynomZhegalkina(unsigned int arg, unsigned int *summand, int lenSum){

    //Computation of the polynomial

    bool result = false, x = false;
    unsigned int valueSum = 0, value = 0;

    for (int i = 0; i < lenSum; i++){
        value = arg & summand[i];
        x = false;
        for (int j = 0; j < sizeof(value)*8; j++){
            x |= value;
            if (x == true) break;
            value <<= 1;
        }
        valueSum |= x;
        valueSum <<= 1;
    }
    valueSum >>= 1; //???

    for (int i = 0; i < lenSum; i++){
        x = valueSum & 1;
        valueSum >>= 1;
        result = (~result | ~x) & (result | x);
    }

    return result;
}

int main()
{
    cout << "Hello World!" << endl;

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
            if (x == true) x = false;
            else x = true;
            sum[i] |= x;
            sum[i] <<= 1;
        }
        sum[i] >>= 1; //???
    }

    x = polynomZhegalkina(arg, sum, lenSum);

    cout << "Answer: " << x << endl;

    return 0;
}

