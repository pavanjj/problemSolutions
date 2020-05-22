#include "./headers/commonHeaders.h"
unsigned int reverse(unsigned int A)
{
    int size = sizeof(A) * 8;
    unsigned int B = 0;
    cout << B << endl;
    for (int i = 0; i < size; i++)
    {
        if (A & (1 << i))
        {
            print("i", i);
            unsigned int temp = 1 << (size - 1 - i);
            print("temp", temp);
            B = B | temp;
        }
    }
    return B;
}
void main()
{
    print("Result", reverse(3));
}