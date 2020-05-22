#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

#define MOD 1000000007

bool isPrime(int num)
{
    for (int i = 2; i < num; i++)
    {
        int divisor = num / i;
        if (divisor == 1)
            break;
        if (num % divisor == 0)
            return false;
    }
    return true;
}

long long getNumOfPrimesLessThan(int num)
{
    if (num <= 1)
        return 0;
    vector<int> primes(num, 1);
    int count = 1;
    primes[0] = primes[1] = 0;
    for (int i = 2; i * i < num; i++)
    {
        if (primes[i])
        {
            for (int j = i * i; j < num; j += i)
            {
                primes[j] = 0;
                count++;
            }
        }
    }
    return num - count;
}

long long getPowOfTwo(long long num)
{
    if (num == 1)
        return 2;
    int multiplier = (num % 2) ? 2 : 1;
    long long halfPower = getPowOfTwo(num / 2);
    return (halfPower * halfPower * multiplier) % MOD;
}
long long getNumOfCombinations(long long num)
{
    return (getPowOfTwo(num) - 1) % MOD;
}

int solve(vector<int> &A)
{
    long long count = 0;
    std::unordered_map<long long, long long> countMap;
    for (int i = 0; i < A.size(); i++)
    {
        auto numPrimes = getNumOfPrimesLessThan(A[i] + 1);
        auto iter = countMap.find(numPrimes);
        if (iter != countMap.end())
            iter->second = (iter->second + 1) % MOD;
        else
            countMap[numPrimes] = 1;
    }
    for (auto &iter : countMap)
    {
        if (iter.first)
            count = (count + getNumOfCombinations(iter.second)) % MOD;
    }
    return count;
}

// Driver Code
int main()
{
    std::vector<int> arr{251, 923, 561, 230, 100, 399, 542, 198, 548, 892, 721, 781, 174, 809, 9, 232, 165, 861, 36, 837, 377, 313, 475, 269, 210, 530, 940, 570, 24, 434, 764, 275, 709, 325, 505, 161, 724, 47, 359, 625, 291, 81, 406, 465, 242, 767, 698, 408, 629, 86, 597, 358, 399, 72, 979, 962, 603, 919, 884, 627, 353, 1, 254, 414, 678, 111, 575, 755, 511, 287, 380, 802, 720, 138, 620, 314, 905, 670, 74, 886, 756, 671, 244, 508, 744, 224, 822, 347, 495, 706, 326, 201, 707, 580, 615, 386, 43, 543, 141, 554};
    cout << solve(arr) << endl;
}