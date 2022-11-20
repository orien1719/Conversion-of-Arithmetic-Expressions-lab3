// реализация пользовательского приложения

#include "arithmetic.h"

int main()
{
    try
   {
        Arithmetic A1;
        cout << "Write your expression:" << endl;
        string str;
        getline(cin, str);
        cout << "Expression is after translting to string: " << endl;
        A1.translateStrToTerm(str);
         A1.PrintVecT();
         cout << "Polish Note: " << endl;
        A1.TermToPolishNote();
        A1.PrintVectP();
        cout << "Result expression: " << endl;
        A1.calculate();
    }
    catch (char* error) 
    {
        cout << error << endl;
    }
}
