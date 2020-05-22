#include "./headers/commonHeaders.h"
int repeatedNumber(const vector<int> &A)
{
    int n = A.size();
    print("Size", n);
    int count1 = 0, count2 = 0, value1 = 0, value2 = 0;
    for (int i = 0; i < n; i++)
    {
        print("Value=", A[i]);
        if (count1 == 0 && value2 != A[i])
        {
            value1 = A[i];
            count1++;
        }
        else if (value1 == A[i])
            count1++;
        else if (count2 == 0)
        {
            value2 = A[i];
            count2++;
        }
        else if (value2 == A[i])
            count2++;
        else
        {
            count1--;
            count2--;
        }
        print("value1", value1);
        print("value2", value2);
        print("count1", count1);
        print("count2", count2);
        print("-------------------", "----------");
    }

    if (count1 == 0 && count2 == 0)
        return -1;

    bool firstElemValid = (count1 > 0);
    bool secondElemValid = (count2 > 0);
    count1 = 0;
    count2 = 0;
    for (int i = 0; i < n; i++)
    {
        if (firstElemValid && A[i] == value1)
            count1++;
        if (secondElemValid && A[i] == value2)
            count2++;
    }
    if (count1 > n / 3)
        return value1;
    else if (count2 > n / 3)
        return value2;
    else
        return -1;
}

void main()
{
    vector<int> A{1000727, 1000727, 1000641, 1000517, 1000212, 1000532, 1000727, 1001000, 1000254, 1000106, 1000405, 1000100, 1000736, 1000727, 1000727, 1000787, 1000105, 1000713, 1000727, 1000333, 1000069, 1000727, 1000877, 1000222, 1000727, 1000505, 1000641, 1000533, 1000727, 1000727, 1000727, 1000508, 1000475, 1000727, 1000573, 1000727, 1000618, 1000727, 1000309, 1000486, 1000792, 1000727, 1000727, 1000426, 1000547, 1000727, 1000972, 1000575, 1000303, 1000727, 1000533, 1000669, 1000489, 1000727, 1000329, 1000727, 1000050, 1000209, 1000109};
    print("Result ", repeatedNumber(A));
}