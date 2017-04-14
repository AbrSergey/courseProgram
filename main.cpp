#include <iostream>

using namespace std;

bool polynomZhegalkina(int numbersVar, int numbersArg){

    bool result = false;

    for (size_t i = 0; i < numbersArg; i++){
        bool value = true;
        for (size_t j = 0; j < numbersVar; j++){
            bool arg;
            cout << "Enter the value of argument" << endl;
            cin >> arg;
            value &= arg;
        }
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

