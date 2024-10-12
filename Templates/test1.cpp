#include <iostream>

template <typename T>
void foo(T &&a)
{
    std::cout << __PRETTY_FUNCTION__
              << " Value of a "
              << a
              << std::endl;
}

int main()
{
    foo(1);
    foo(1.5);
    foo('1');
}