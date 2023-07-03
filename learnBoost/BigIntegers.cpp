// CPP program to demostrate big Integer

#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

#define ll long long

using namespace std;
using namespace boost::multiprecision;
using boost::multiprecision::cpp_dec_float_50;

int128_t boost_product(ll a, ll b)
{
    int128_t ans = (int128_t)a * b;
    return ans;
}

cpp_int boost_factorial(int a)
{
    cpp_int res = 1;
    for (int i = a; i > 1; --i)
        res *= i;
    return res;
}

template <typename T>
inline T area_of_a_circle(T r)
{
    // pi represent predefined constant having value
    // 3.1415926535897932384...
    using boost::math::constants::pi;
    return pi<T>() * r * r;
}

int main()
{

    ll a = 98745636214564698;
    ll b = 7459874565236544789;
    cout << boost_product(a, b) << "\n";
    cout << a * b << endl;
    cout << "factorial of 30 " << boost_factorial(30) << endl;

    float radius_f = 123.0 / 100;
    float area_f = area_of_a_circle(radius_f);

    double radius_d = 123.0 / 100;
    double area_d = area_of_a_circle(radius_d);

    cpp_dec_float_50 r_mp = 123.0 / 100;
    cpp_dec_float_50 area_mp = area_of_a_circle(r_mp);

    // numeric_limits::digits10 represent the number
    // of decimal digits that can be held of particular
    // data type without any loss.

    // Area by using float data type
    cout << "Float: "
         << setprecision(numeric_limits<float>::digits10)
         << area_f << endl;

    // Area by using double data type
    cout << "Double: "
         << setprecision(numeric_limits<double>::digits10)
         << area_d << endl;

    // Area by using Boost Multiprecision
    cout << "Boost Multiprecision: "
         << setprecision(
                numeric_limits<cpp_dec_float_50>::digits10)
         << area_mp << endl;
    return 0;

    return 0;
}