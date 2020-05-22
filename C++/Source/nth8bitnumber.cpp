#include "./headers/commonHeaders.h"
typedef unsigned long long ull;
ull factorial(ull n)
{
    return (n == 1 || n == 0) ? 1 : n * factorial(n - 1);
}

ull genCombo(int a, int b)
{
    int n = a + b;
    int greater = a > b ? a : b;
    int smaller = n - greater;
    ull fact = 1;
    for (int i = greater + 1; i <= n; i++)
    {
        fact *= i;
    }
    print("In gencombo");
    print("a=", a);
    print("b=", b);
    auto num = fact;
    print("Num", num);
    auto den = factorial(smaller);
    print("den", den);
    return num / den;
}

string solve(int A)
{
    int firstNum = 255;
    if (A == 0)
        return "0";
    else if (A == 1)
        return "255";
    A -= 1;
    ull set = 1;
    ull num0s = 1, num1s = 7;
    ull bits = 1;
    while (A > 0)
    {
        auto numCombos = genCombo(num0s - 1, num1s);
        print("Num1s", num1s);
        print("Num0s", num0s);
        print("numCombos after 0", numCombos);
        print("A", A);
        if (A <= numCombos)
        {
            print("In less than for zero combo");
            bits = (bits << 1);
            num0s--;
            if (A == numCombos)
                A -= numCombos;
        }
        else
        {
            print("In greater than for zero combo");
            A -= numCombos;
            numCombos = genCombo(num0s, num1s - 1);
            print("numCombos after 1", numCombos);
            if (A <= numCombos)
            {
                bits = (bits << 1) | 1;
                num1s--;
                if (A == numCombos)
                    A -= numCombos;
            }
            else
            {
                A -= numCombos;
                num0s = ++set;
                num1s = 7;
                bits = 1;
            }
        }
    }

    print("Exited the first loop ------------------", "--------");
    print("Num1s", num1s);
    print("Num0s", num0s);
    while (num1s)
    {
        bits = (bits << 1) | 1;
        num1s--;
    }
    while (num0s)
    {
        bits = (bits << 1);
        num0s--;
    }
    return to_string(bits);
}

void main()
{
    cout << solve(10) << endl;
}
