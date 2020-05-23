#include "../headers/commonHeaders.h"
int findMedian(vector<vector<int>> &A)
{
    int n = A.size();
    int m = A[0].size();
    int numElems = n * m;
    int numLessElems = numElems / 2;
    int curMedian = A[0][m / 2];
    vector<vector<int>> boundaries(n, vector<int>(2, 0));
    for (int i = 0; i < n; i++)
        boundaries[i][1] = m;
    bool done = false;
    while (!done)
    {
        int less = 0, equal = 0;
        print("curMedian", curMedian);
        vector<int> count(n, 0);
        vector<int> countLess(n, 0);
        for (int i = 0; i < n; i++)
        {
            int rowLess = 0, rowEqual = 0;
            for (int j = boundaries[i][0]; j < boundaries[i][1]; j++)
            {
                if (A[i][j] < curMedian)
                    rowLess++;
                else if (A[i][j] == curMedian)
                    rowEqual++;
                else
                    break;
            }
            countLess[i] = rowLess;
            count[i] = rowLess + rowEqual;
            less += rowLess;
            equal += rowEqual;
        }
        print("Less", less);
        print("Equal", equal);
        print("count", count);
        if (less == numLessElems || ((less < numLessElems) && (less + equal > numLessElems)))
            return curMedian;
        else
        {
            curMedian = -1;
            if (less > numLessElems)
            {
                //set the proper boundaries
                for (int i = 0; i < n; i++)
                {
                    //here onl equals need to go
                    boundaries[i][1] = boundaries[i][0] + countLess[i];
                    if (boundaries[i][0] < boundaries[i][1] && curMedian == -1)
                        curMedian = A[i][boundaries[i][0]];
                }
            }
            else
            {
                //herer both equals and lesses are to be retained
                for (int i = 0; i < n; i++)
                {
                    boundaries[i][0] = boundaries[i][0] + count[i];
                    if (boundaries[i][0] < boundaries[i][1] && curMedian == -1)
                        curMedian = A[i][boundaries[i][0]];
                }
                numLessElems -= less + equal;
            }
        }
    }
}

void main()
{
    // vector<vector<int>>
    //     A{{5},
    //       {4},
    //       {3},
    //       {1},
    //       {3},
    //       {1},
    //       {4},
    //       {2},
    //       {5},
    //       {3},
    //       {3}};
    vector<vector<int>> A{
        {2, 3, 11, 12, 29},
        {12, 16, 20, 21, 29},
        {6, 9, 21, 27, 30}};
    print("Result", findMedian(A));
}
