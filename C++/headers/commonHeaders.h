#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cmath>
#include <algorithm>
#include <numeric>
using namespace std;

void print(string A, long long B)
{
    cout << A << "=" << B << endl;
}

void print(string A, string B = "")
{
    if (B.size())
        cout << A << "=" << B << endl;
    else
        cout << A << endl;
}
void print(string A, vector<int> &B)
{
    cout << A << endl;
    for (int i = 0; i < B.size(); i++)
    {
        cout << B[i] << " ";
    }
    cout << endl;
}
void print(string A, vector<vector<int>> &B)
{
    cout << A << endl;
    for (int i = 0; i < B.size(); i++)
    {
        for (int j = 0; j < B[i].size(); j++)
            cout << B[i][j] << " ";
        cout << endl;
    }
}