int findAbsDiff(int a, int b)
{
    return abs(a - b);
}

int Solution::threeSumClosest(vector<int> &A, int B)
{
    int i = 0, j = 1, k = 2;
    int n = A.size();
    if (n < 3)
        return 0;
    int minAbsDiff = -1, closestSum = -1;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                int sum = A[i] + A[j] + A[k];
                int absDiff = findAbsDiff(B, sum);
                if (absDiff < minAbsDiff || minAbsDiff == -1)
                {
                    minAbsDiff = absDiff;
                    if (minAbsDiff == 0)
                        return sum;
                    closestSum = sum;
                }
            }
        }
    }
    return closestSum;
}
