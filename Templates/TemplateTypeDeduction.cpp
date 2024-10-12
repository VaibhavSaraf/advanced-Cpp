#include <iostream>

/*
template<typename T>
f(ParamType expr) { }

type deduced for T is dependent not just on type of expr but also on form of ParamType
here T and ParamType is deduce by expr

Example:

template<typename T>
f(const T& expr) { }  // ParamType is const &T

int x = 0;
f(x);       // calls f with int
*/

/*
There are 3 types of ParamType
1. ParamType is pointer or Reference
2. ParamType is universal Reference
3. ParamType is neither a pointer nor a reference
*/

/*
1. ParamType is pointer or Reference


*/

template <typename T>
void foo(const T &name)
{
    std::cout << "Type: " << decltype(T) << std::endl;
    std::cout << name << std::endl;
}

int main()
{
    foo(1);
    foo("vaibhav");
    foo(10.25);
}