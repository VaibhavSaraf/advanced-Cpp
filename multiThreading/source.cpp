
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;

typedef unsigned long long ull;

ull oddSum;
ull evenSum;

void oddSums(ull start, ull end)
{
    for (ull i = start; i < end; i++)
    {
        if (i & 1 == 1)
        {
            oddSum += i;
        }
    }
}

void evenSums(ull start, ull end)
{
    for (ull i = start; i < end; i++)
    {
        if (i & 1 == 1)
        {
            evenSum += i;
        }
    }
}

int main()
{
    ull start = 0;
    ull end = 1900000000;
    std::thread t1(oddSums, start, end);
    std::thread t2(evenSums, start, end);
    t1.join();
    t2.join();
    auto startTime = high_resolution_clock::now();

    // oddSums(start, end);
    // evenSums(start, end);

    auto stopTime = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stopTime - startTime);

    cout << "odd sum: " << oddSum << endl;
    cout << "even sum: " << evenSum << endl;

    cout << duration.count() / 1000000.0 << endl;

    return 0;
}
