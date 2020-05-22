#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

#define MOD 1000000007;
long long getPowOfTwo(long long num)
{
    if (num == 1)
        return 2;
    int multiplier = 1;
    if (num % 2)
        multiplier = 2;
    long long halfPower = getPowOfTwo(num / 2);
    return (halfPower * halfPower * multiplier) % MOD;
}
long long getNumOfCombinations(long long num)
{
    return (getPowOfTwo(num) - 1) % MOD;
}

void main()
{
    cout << getPowOfTwo(6) << endl;
}