#include <iostream>

using namespace std;

// using Comparator = bool (*)(int, int);

template <typename T, int size, typename Comparator>
void Sort(T (&arr)[size], Comparator comp)
{
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < size - 1; ++j)
        {
            if (comp(arr[j], arr[j + 1]))
            {
                T temp = std::move(arr[j]);
                arr[j] = std::move(arr[j + 1]);
                arr[j + 1] = std::move(temp);
            }
        }
    }
}

bool Comp(int x, int y)
{
    return x > y;
}

bool Comp1(int x, int y)
{
    return x < y;
}

struct Comp2
{
    bool operator()(int x, int y)
    {
        return x > y;
    }
};

int main()
{
    int arr[]{11, 6, 9, 5, 2};
    for (auto x : arr)
        cout << x << " ";
    cout << endl;

    Comp2 comp;

    Sort(arr, comp);

    for (auto x : arr)
        cout << x << " ";
    cout << endl;

    return 0;
}