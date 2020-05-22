#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

#define MOD 1000000007

int **create2DArray(int rows, int cols)
{
    int **array2D = 0;
    array2D = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        array2D[i] = new int[cols];
        for (int j = 0; j < cols; j++)
        {
            array2D[i][j] = 0;
        }
    }
    return array2D;
}

int **multiply(int **A, int **B)
{
    int n = 2;
    auto C = create2DArray(n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                C[i][j] = ((long long)(C[i][j] + ((long long)(A[i][k] * B[k][j])) % MOD)) % MOD;
            }
        }
    }
    return C;
}

int **square(int **M)
{
    return multiply(M, M);
}

int **fastPower(int **M, int power)
{
    if (power == 0)
    {
        auto ret = create2DArray(2, 2);
        ret[0][0] = 1;
        ret[1][1] = 1;
        cout << "-------------------------------------------" << endl;
        for (int i = 0; i < 2; i++)
        {

            for (int j = 0; j < 2; j++)
            {
                cout << ret[i][j] << ",";
            }
        }
        cout << endl;

        return ret;
    }
    if (power & 1)
    {
        auto res = square(M);
        return multiply(M, fastPower(res, power / 2));
    }
    else
    {
        auto res = square(M);
        return fastPower(res, power / 2);
    }
}

int fib(int n)
{
    if (n < 1)
        return n;
    auto M = create2DArray(2, 2);
    M[0][0] = 1;
    M[0][1] = 1;
    M[1][0] = 1;
    M[1][1] = 0;
    auto prod = fastPower(M, n - 1);
    return prod[0][0];
}

int solve(int A, int B)
{
    int firstSum = (fib(A + 1) - 1) % MOD;
    int secondSum = (fib(B + 2) - 1) % MOD;
    cout << "A-1 : " << firstSum << endl;
    cout << "B : " << secondSum << endl;
    auto rangeSum = (long long)(secondSum - firstSum);
    if (rangeSum < 0)
        return (rangeSum + MOD) % MOD;
    else
        return rangeSum % MOD;
}

int getSum(int A, int B)
{
    int prev = 0, cur = 0;
    int sum = 0;
    if (A < 2 && B >= 2)
    {
        sum = 1;
        prev = 0;
        cur = 1;
    }
    else if (B < 2)
    {
        sum = B;
    }
    else
    {
        prev = fib(A - 2);
        cur = fib(A - 1);
    }
    int startIndex = A < 2 ? 2 : A;
    for (int i = startIndex; i <= B; i++)
    {
        int temp = cur;
        cur = (cur + prev) % MOD;
        prev = temp;
        sum = (sum + cur) % MOD;
    }
    return sum;
}
int main()
{
    //  cout << calculateSum(774698, 55875608) << endl;
    //   cout << solve(30, 44) << endl;
    //cout << getSum(0, 10) << endl;
    cout << solve(774698, 55875608) << endl;
}