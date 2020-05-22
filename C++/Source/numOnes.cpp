#include "./headers/commonHeaders.h"

#include <list>
vector<int> Solution::maxone(vector<int> &A, int B)
{
    //account for B==0
    int numOnes = 0, maxOnes = 0, numZeros = 0;
    int zeroStartIdx = -1;
    int n = A.size();
    vector<int> retVec(2, 0);
    if (B == 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (A[i] == 0)
            {
                if (maxOnes < numOnes)
                {
                    maxOnes = numOnes;
                    retVec[0] = i - numOnes;
                    retVec[1] = i - 1;
                }
                numOnes = 0;
            }
            else
            {
                numOnes++;
            }
        }
        if (numOnes > maxOnes)
        {
            maxOnes = numOnes;
            retVec[0] = n - numOnes;
            retVec[1] = n - 1;
        }
    }
    else
    {
        int length = 0, maxLength = 0, numZeros = 0;
        std::list<int> zeroQ;
        for (int i = 0; i < n; i++)
        {
            if (A[i] == 0)
            {
                if (numZeros == B)
                {
                    int seqStartIdx = zeroQ.front();
                    zeroQ.pop_front();
                    if (length > maxLength)
                    {
                        maxLength = length;
                        retVec[0] = max(i - length, 0);
                        retVec[1] = i - 1;
                    }
                    length = i - 1 - (seqStartIdx);
                    if (A[seqStartIdx] != 0)
                    {
                        length = i - 1 - (zeroQ.front());
                        zeroQ.pop_front();
                    }
                    numZeros--;
                }
                numZeros++;
                zeroQ.push_back(i);
            }
            else if (i == 0)
            {
                zeroQ.push_back(i);
            }
            length++;
        }

        int seqStartIdx = zeroQ.front();
        if (length > maxLength)
        {
            maxLength = length;
            retVec[0] = n - length;
            retVec[1] = n - 1;
        }
    }
    vector<int> maxOneIndices;
    for (int i = retVec[0]; i <= retVec[1]; i++)
        maxOneIndices.push_back(i);
    return maxOneIndices;
}

void main()
{
    vector<int> A{1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0};
    int B = 4;
    print("Result ", maxone(A, B));
}