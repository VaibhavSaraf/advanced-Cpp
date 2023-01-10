#include <iostream>
#include <thread>
using namespace std;

// 1. Function Pointers

// void fun(int n)
// {
//     while (n--)
//         cout << n << " ";
//     cout << endl;
// }
//
// int main()
// {
//     std::thread t1(fun, 10);
//     t1.join();
//     return 0;
// }

// lambda function

// int main()
// {
//     auto fun = [](int n)
//     {
//         while (n-- > 0)
//         {
//             cout << n << " ";
//         }
//         cout << endl;
//     };

//     std::thread t1(fun, 12);
//     t1.join();

//     std::thread t2([](int n)
//                    {
//         while (n-- > 0)
//         {
//             cout << n << " ";
//         }
//         cout << endl; },
//                    25);
//     t2.join();
//     return 0;
// }

// 3. Functors (function objects)

// class Base
// {
// public:
//     void operator()(int n)
//     {
//         while (n--)
//         {
//             cout << n << " ";
//         }
//         cout << endl;
//     }
// };

// int main()
// {
//     std::thread t1(Base(), 11);
//     t1.join();
// }

// 4. Non static Member funtion
// class Base
// {
// public:
//     void fun(int n)
//     {
//         while (n--)
//             cout << n << " ";
//         cout << endl;
//     }
// };

// int main()
// {
//     Base b;
//     std::thread t1(&Base::fun, b, 10);
//     t1.join();
// }

// 5. Non static Member funtion
class Base
{
public:
    static void fun(int n)
    {
        while (n--)
            cout << n << " ";
        cout << endl;
    }
};

int main()
{
    std::thread t1(Base::fun, 10);
    t1.join();
}