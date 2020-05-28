#include "../headers/commonHeaders.h"

int sqrt(int A)
{

    int low = 0, high = A / 2;
    if (A == 1)
        return 1;
    long long result = 0;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        long long square = (long long)mid * (long long)mid;
        if (square == A)
            return mid;
        else if (square > A)
            high = mid - 1;
        else
        {
            print("mid", mid);
            result = mid;
            low = mid + 1;
        }
    }
    return result;
}
void main()
{
    int A = 930675566;
    print("Result", sqrt(A));
}