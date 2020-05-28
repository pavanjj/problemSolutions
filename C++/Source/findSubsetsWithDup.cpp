#include "../headers/commonHeaders.h"

void findSubSets(vector<int> &A, vector<vector<int>> &subsets, vector<int> curSet, vector<int> remSet)
{
    int n = remSet.size();
    if (n)
    {
        auto element = remSet[0];
        int repeatCount = 0;
        while (element == remSet[repeatCount])
            repeatCount++;
        remSet.erase(remSet.begin(), remSet.begin() + repeatCount);
        for (int i = 0; i <= repeatCount; i++)
        {
            findSubSets(A, subsets, curSet, remSet);
            curSet.push_back(element);
        }
    }
    else
        subsets.push_back(curSet);
}

vector<vector<int>> subsetsWithDup(vector<int> &A)
{
    sort(A.begin(), A.end());
    vector<vector<int>> subsets, retSet;
    findSubSets(A, subsets, vector<int>(), A);
    sort(subsets.begin(), subsets.end());
    return subsets;
}

void main()
{
    vector<int> A = {1, 2, 2};
    print("Result ", subsetsWithDup(A));
}