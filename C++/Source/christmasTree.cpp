#include "../headers/commonHeaders.h"
int solve(vector<int> &A, vector<int> &B)
{
    int minCost = -1;
    int n = A.size();
    for (int j = 1; j < n - 1; j++)
    {
        int minCostLeft = -1, minCostRight = -1;
        for (int i = 0; i < j; i++)
        {
            if (A[i] < A[j])
            {
                print("i", i);
                print("j", j);
                if (minCostLeft == -1 || B[i] < minCostLeft)
                    minCostLeft = B[i];
                print("min cost left ", minCostLeft);
            }
        }

        for (int k = j + 1; k < n; k++)
        {
            if (A[j] < A[k])
            {
                print("k", k);
                if (minCostRight == -1 || B[k] < minCostRight)
                    minCostRight = B[k];
                print("min cost right ", minCostRight);
            }
        }

        int cost = -1;
        if (minCostLeft != -1 && minCostRight != -1)
        {
            cost = minCostLeft + B[j] + minCostRight;
            if (minCost == -1 || minCost > cost)
                minCost = cost;
        }
        print("cost", cost);
        print("minCost", minCost);
        print("-----------------------------");
    }
    return minCost;
}

void main()
{
    vector<int> A =
        {802030518, 598196518, 640274071, 983359971, 71550121, 96204862, 799843967, 446173607, 796619138, 402690754};
    vector<int> B = {23219513, 68171337, 12183499, 5549873, 73542337, 66661387, 79397647, 34495917, 31413076, 50918417};
    print("Result", solve(A, B));
}