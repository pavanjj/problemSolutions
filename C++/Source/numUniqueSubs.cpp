#include "./headers/commonHeaders.h"
#define MOD 1000000007
int solve(vector<int> &A)
{
    int n = A.size();
    if (n == 1)
        return 1;
    long long count = 0;
    long long twoInv = MOD / 2 + 1;
    unordered_set<int> elemsSet;
    int i = 0, j = 1;
    elemsSet.insert(A[0]);
    while (i < n && j < n)
    {
        //look for element's presence
        auto it = elemsSet.find(A[j]);
        if (it != elemsSet.end())
        {
            if (i == j)
                j++;
            else
            {
                long long numElems = elemsSet.size();
                print("i==================================", i);
                print("j==================================", j);
                print("numElems", numElems);
                long long numCombs = (numElems * ((numElems + 1) % MOD)) % MOD;
                numCombs = (numCombs * twoInv) % MOD;
                print("numCOmbs", numCombs);
                count = (count + numCombs) % MOD;
                print("count", count);
                while (i < j)
                {
                    elemsSet.erase(A[i]);
                    i++;
                    if (elemsSet.find(A[j]) == elemsSet.end())
                        break;
                }
            }
        }
        else
        {
            elemsSet.insert(A[j++]);
        }
    }
    if (elemsSet.size())
    {
        long long numElems = elemsSet.size();
        long long numCombs = (numElems * (numElems + 1)) % MOD;
        numCombs = (numCombs * twoInv) % MOD;
        count = (count + numCombs) % MOD;
    }
    return count;
}

void main()
{
    vector<int> A{93, 9, 12, 32, 97, 75, 32, 77, 40, 79, 61, 42, 57, 19, 64, 16, 86, 47, 41, 67, 76, 63, 24, 10, 25, 96, 1, 30, 73, 91, 70, 65, 53, 75, 5, 19, 65, 6, 96, 33, 73, 55, 4, 90, 72, 83, 54, 78, 67, 56, 8, 70, 43, 63};
    print("Size", A.size());
    print("Result ", solve(A));
}