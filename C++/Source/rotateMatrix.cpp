#include "./headers/commonHeaders.h"
void solve(vector<vector<int>> &A)
{
    int k = 0;
    int n = A.size();
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = k; j < n - (k + 1); j++)
        {
            int swaps = 0;
            int sNum = A[i][j];
            int sRow = i, sCol = j;
            int dRow = sCol, dCol = n - 1 - sRow;
            while (swaps < 4)
            {
                print("srow", sRow);
                print("scol", sCol);
                print("drow", dRow);
                print("dcol", dCol);
                int dNum = A[dRow][dCol];
                A[dRow][dCol] = sNum;
                sRow = dRow;
                sCol = dCol;
                dRow = sCol;
                dCol = n - 1 - sRow;
                sNum = dNum;
                swaps++;
            }
        }
        k++;
    }
}

void main()
{
    vector<vector<int>> A{
        {1, 2},
        {3, 4}};
    solve(A);
    print("Result ", A);
}