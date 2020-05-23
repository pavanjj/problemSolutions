#include "../headers/commonHeaders.h"
int binSearch(const vector<int> &A, int B, int start, int end)
{
    int n = A.size();
    int mid = n / 2;
    mid = (start + mid) % n;
    print("mid", mid);
    while (start != mid)
    {
        print("mid", mid);
        if (A[mid] < B)
        {
            start = (mid + 1) % n;
        }
        else if (A[mid] > B)
        {
            end = mid - 1;
            if (end < 0)
                end = (end + n) % n;
        }
        else
        {
            return mid;
        }
        if (end > start)
            mid = (end - start) / 2;
        else
            mid = (end + n - start) / 2;
        mid = (start + mid) % n;
    }
    if (A[mid] == B)
        return mid;
    return -1;
}

int search(const vector<int> &A, int B)
{
    int startIndex = 0;
    int n = A.size();
    for (int i = 0; i < n - 1; i++)
    {
        if (A[i] > A[i + 1])
            startIndex = i + 1;
    }
    int endIndex = (startIndex + n - 1) % n;
    print("startIndex", startIndex);
    print("endIndex", endIndex);
    return binSearch(A, B, startIndex, endIndex);
}
void main()
{
    vector<int> A{101, 103, 106, 109, 158, 164, 182, 187, 202, 205, 2, 3, 32, 57, 69, 74, 81, 99, 100};
    int B = 202;
    print("Result", search(A, B));
}