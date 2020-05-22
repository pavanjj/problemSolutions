#include "./headers/commonHeaders.h"
#define MOD 1000000007
typedef unsigned long long ull;

ull getCombos(ull n, ull positions)
{
    if (positions == 2)
    {
        return (n + 1) % MOD;
    }

    if (positions == 1)
        return 1;
    if (positions == 0)
        return 0;

    ull numCombs = 0;
    for (int i = 0; i <= n; i++)
    {
        numCombs = (numCombs + getCombos(n - i, positions - 1)) % MOD;
    }
    return numCombs % MOD;
}

int solve(int A, int B, int C, int D)
{
    int n = B + C + D;
    ull numsToDistribute = A - n;
    numsToDistribute++;
    auto nums = (numsToDistribute * ((numsToDistribute + 1) % MOD)) % MOD;
    print("nums", nums);
    ull twoInv = (MOD / 2) + 1;
    return (nums * twoInv) % MOD;
}

void main()
{
    print("Result", solve(120269, 56254, 5599, 11585));
}