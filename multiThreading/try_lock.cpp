/*
0. try_lock() Tries to lock the mutex. Returns immediately. On successful lock acquisition returns true otherwise returns false.
1. If try_lock() is not able to lock mutex, then it doesn't get blocked that's why it is called non-blocking.
2. If try_lock is called again by the same thread which owns the mutex, the behaviour is undefined.
   It is a dead lock situation with undefined behaviour. (if you want to be able to lock the same mutex by same thread more than one time the go for recursive_mutex)

   double try_lock is not allowed
*/

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int counter = 0;
std::mutex mtx;

void increaseCounterBy100000()
{
    for (int i = 0; i < 100000; i++)
    {
        /*this is non blocking call*/
        if (mtx.try_lock())
        {
            ++counter;
            mtx.unlock();
            // std::this_thread::sleep_for(chrono::seconds(1));
            cout << counter << " : " << std::this_thread::get_id() << endl;
        }

        /*this is blocking call*/
        // mtx.lock();
        // ++counter;
        // mtx.unlock();
    }
}

int main()
{
    std::thread t1(increaseCounterBy100000);
    std::thread t2(increaseCounterBy100000);

    t1.join();
    t2.join();

    cout << counter << "\n";

    return 0;
}