#include "./headers/commonHeaders.h"
int divide(int A, int B)
{
    unsigned int absA = abs(A);
    unsigned int absB = abs(B);
    unsigned int dividend = absA;
    unsigned int divisor = absB;
    unsigned int quotient = 0;
    unsigned int result = 0;
    while (dividend >= divisor)
    {
        if (quotient == 0)
            quotient = 1;
        divisor <<= 1;
        print("Divisor", divisor);
        //print("Dividend", dividend);
        print("Quotient", quotient);
        if (divisor < dividend)
            quotient <<= 1;
        else
        {
            dividend -= divisor >> 1;
            divisor = absB;
            result = min((result + quotient), (unsigned int)INT_MAX);
            quotient = 0;
        }
    }
    if ((A < 0 && B > 0) || (A > 0 && B < 0))
        result = result * -1;
    return result;
}

void main()
{
    print("Result", divide(2147483647, 1));
}