#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void solve(vector<int> &arr, int k)
{
    int i = 0, j = 0;
}

void printVector(const vector<int> arr)
{
    for (auto &i : arr)
    {
        cout << i << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> arr = {1, 2, 3, 4, 2, 2, 6, 7, 2}; // 1 3 4 6 7 2

    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == 2)
        {
            arr.erase(arr.begin() + i);
            i--;
        }
    }

    for (auto &i : arr)
    {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}