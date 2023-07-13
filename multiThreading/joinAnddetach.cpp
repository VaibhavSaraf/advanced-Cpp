#include <iostream>
#include <chrono>
#include <thread>
#include <bits/stdc++.h>

using namespace std;

void run(int count)
{
    while (count-- > 0)
    {
        cout << count << endl;
    }
    std::this_thread::sleep_for(chrono::seconds(5));
}

void calculate()
{
    int n = 60000000;
    int i = 0;
    while (n--)
    {
        i++;
    }
}

int main()
{
    std::thread t1(run, 10);
    cout << "before t1.join()" << endl;
    // t1.join();
    t1.detach();
    // calculate();
    cout << "after t1.join()" << endl;
    // if (t1.joinable())
    //     t1.join();
    return 0;
}