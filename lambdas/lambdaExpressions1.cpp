#include <iostream>
using namespace std;
int main()
{
    auto fn = []()
    {
        cout << "hello, I am vaibhav" << endl;
    };

    fn();

    cout << typeid(fn).name() << endl;

    auto sum = [](int x, int y)
    {
        return x + y;
    };

    cout << sum(5, 2) << endl;
}