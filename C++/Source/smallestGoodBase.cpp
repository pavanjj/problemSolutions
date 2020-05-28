#include "../headers/commonHeaders.h"
unsigned long long getAllOnesNumber(unsigned long long num, long long power)
{
    unsigned long long allOnesNum = 0;
    while (power >= 0)
    {
        allOnesNum += pow(num, power--);
    }
    return allOnesNum;
}

unsigned long long binSearch(unsigned long long num, unsigned long long min)
{
    long long maxPower = 2;
    unsigned long long low = min, high = pow((double)num, (double)1 / (double)maxPower);
    unsigned long long smallestGoodBase = num - 1;
    while (low <= high)
    {
        unsigned long long mid = low + (high - low) / 2;
        auto allOnesNumber = getAllOnesNumber(mid, maxPower);
        if (allOnesNumber == num)
        {
            smallestGoodBase = mid;
            maxPower++;
            high = pow((double)num, (double)(1 / maxPower));
            low = min;
        }
        else if (allOnesNumber < num)
        {
            low = mid + 1;
        }
        else
            high = mid - 1;

        if (low > high)
        {
            maxPower++;
            low = min;
            high = pow((double)num, (double)(1 / maxPower));
        }
    }
    return smallestGoodBase;
}

string solve(string A)
{
    unsigned long long min = 2;
    auto num = stoull(A);
    return to_string(binSearch(num, min));
}

void main()
{

    string A = "13";
    print("Result", solve(A));
}