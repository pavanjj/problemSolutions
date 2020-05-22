#include "./headers/commonHeaders.h"
int solve(vector<int> &A)
{
    int n = A.size();
    //generate the size 1 index array and count them
    int count = n;
    vector<int> subArrays(n);
    subArrays[0] = 0;
    std::iota(subArrays.begin() + 1, subArrays.end(), 1);

    for (int subArraySize = 2; subArraySize <= n; subArraySize++)
    {
        vector<int> invalidIndices;
        invalidIndices.reserve(n - (subArraySize - 1));
        for (int i = subArraySize - 1; i < n; i++)
        {
            if (subArrays[i] != -1 && subArrays[i - 1] != -1)
            {
                if (A[i] != A[i - subArraySize + 1])
                {
                    count++;
                }
                else
                {
                    invalidIndices.push_back(i);
                }
            }
            else if (subArrays[i] != -1)
            {
                invalidIndices.push_back(i);
            }
        }
        for (auto &i : invalidIndices)
            subArrays[i] = -1;
        if (invalidIndices.size() == (n - (subArraySize - 1)))
            break;
        // print(" SubArray ", subArrays);
        // print("Subarray size = ", subArraySize);
        // print("num sub arrays = ", (n - (subArraySize - 1)) - invalidIndices.size());
    }
    return count;
}
void main()
{
    vector<int> A{93, 9, 12, 32, 97, 75, 32, 77, 40, 79, 61, 42, 57, 19, 64, 16, 86, 47, 41, 67, 76, 63, 24, 10, 25, 96, 1, 30, 73, 91, 70, 65, 53, 75, 5, 19, 65, 6, 96, 33, 73, 55, 4, 90, 72, 83, 54, 78, 67, 56, 8, 70, 43, 63};
    print("Size", A.size());
    print("Result ", solve(A));
}