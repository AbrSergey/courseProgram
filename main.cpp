#include <iostream>

using namespace std;

bool polynomZhegalkina(int numbersArg, int numbersSummand){

    //You need to change the data structure

    //Fill an array of arguments with their values
    bool *arrayArg = new bool[numbersArg];

    for (size_t i = 0; i < numbersArg; i++){
        cout << "Enter the value of argument" << endl;
        cin >> arrayArg[i];
    }

    //Fill an array of summand
    bool **arraySummand = new bool*[numbersSummand]; //raws

    for (size_t i = 0; i < numbersSummand; i++)
        arraySummand[i] = new bool[numbersArg]; //column

    for (size_t i = 0; i < numbersSummand; i++)
        for (size_t j = 0; j < numbersArg; j++){
            cout << "Print summand" << endl;
            cin >> arraySummand[i][j];
            if (arraySummand[i][j] == true) arraySummand[i][j] = false;
            else arraySummand[i][j] = true;
        }

    //Computation of the polynomial
    bool result = false;
    for (size_t i = 0; i < numbersSummand; i++){
        bool value = true;
        for (size_t j = 0; j < numbersArg; j++)
            value &= (arraySummand[i][j] | arrayArg[j]);
        result = (~result | ~value) & (result | value);
    }

    return result;
}

int main()
{
    cout << "Hello World!" << endl;

    bool x = polynomZhegalkina(3,3);

    cout << "Answer: " << x << endl;

    return 0;
}

