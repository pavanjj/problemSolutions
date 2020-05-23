#include "../headers/commonHeaders.h"
vector<int> solve(vector<int> &A)
{
    vector<int> result;
    vector<int> retVec(2, -1);
    int i = 0, j = 0;
    int maxLen = 0;
    int n = A.size();
    while (i < n && A[i] < 0)
        i++;
    j = i;
    while (i < n && j < n)
    {
        if (A[j] < 0)
        {
            int len = j - i;
            if (len > maxLen)
            {
                maxLen = len;
                retVec[0] = i;
                retVec[1] = j - 1;
            }
            while (j < n && A[j] < 0)
                j++;
            i = j;
        }
        else
        {
            j++;
        }
    }

    int len = n - i;
    if (len > maxLen)
    {
        maxLen = len;
        retVec[0] = i;
        retVec[1] = n - 1;
    }

    if (retVec[0] != -1)
    {
        for (int i = retVec[0]; i <= retVec[1]; i++)
            result.push_back(A[i]);
    }
    return result;
}

void main()
{
    vector<int> A{8986143, -5026827, 5591744, 4058312, 2210051, 5680315, -5251946, -607433, 1633303, 2186575};
    print("Result", solve(A));
}