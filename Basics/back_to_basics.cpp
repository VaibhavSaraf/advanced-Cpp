#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
TYPE                    SUFFIX      EXAMPLE
int                     /           2
unsigned int            u, U        3u
long int                l, L        8L
long unsigned           ul, UL      2ul
long long int           ll, LL      4ll
long long unsigned int  ull, ULL    7ULL
float                   f, F        3.0f only decimal numbers
double                              3.0 only decimal numbers

Binary C++14            0b          0b010101
Octal                   0           0307
Hexadecimal             0x or 0X    0xFFA010

*/

void test()
{
    // cout << sizeof(char) << endl;
    // cout << sizeof(short) << endl;
    // cout << sizeof(int) << endl;
    // cout << sizeof(unsigned int) << endl;
    // cout << sizeof(long int) << endl;
    // cout << sizeof(long long int) << endl;
    // cout << sizeof(long) << endl;
    // cout << sizeof(void) << endl;

    // cout << (1 << 15) << endl;
    cout << (1 << 3) << endl;

    std::cout
        << "hello world\n";
}
void test2()
{
    /*
    Remember: nullptr is not a pointer, but an object of type nullptr_t → safer
    */

    nullptr_t d;
    cout << d << endl;
    cout << nullptr << endl;
    if (d == nullptr)
        cout << "victory\n";
    else
        cout << "loss\n";
}

void test3()
{
    float f = 1.0f;
    unsigned u = 2;
    int i = 3;
    short s = 4;
    uint8_t c = 5; // unsigned char
    f *u;          // float × unsigned → float: 2.0f
    s *c;          // short × unsigned char → int: 20
    u *i;          // unsigned × int → unsigned: 6u
    +c;            // unsigned char → int: 5

    /*Integral data types smaller than 32-bit are implicitly promoted to int , independently
if they are signed or unsigned*/

    int x = (3, 4); // discards 3, then x=4
    cout << x << endl;

    int y = 0;
    int z;
    z = y, x; // z=y (0), then returns x (4)
    cout << z << "\n";
}

/*
size t and ptrdiff t are aliases data types capable of storing the biggest
representable value on the current architecture
*/
/*
Truncation to a smaller type is implemented as a modulo operation with respect to
the number of bits of the smaller type

int x = 65537; // 2ˆ16 + 1
int16_t y = x; // x % 2ˆ16
cout << y; // print 1

int z = 32769; // 2ˆ15 + 1 (does not fit in a int16_t)
int16_t w = z; // (int16_t) (x % 2ˆ16 = 32769)
cout << w; // print -32767
*/

/*
Undefined Behavior
More negative values than positive
int x = std::numeric_limits<int>::max() * -1; // (2ˆ31 -1) * -1
cout << x; // -2ˆ31 +1 ok
int y = std::numeric_limits<int>::min() * -1; // -2ˆ31 * -1
cout << y; // hard to see in complex examples // 2ˆ31 overflow!!
A practical example:*/
void f(int *ptr, int pos)
{
    pos++;
    if (pos < 0)
        return;   // <-- the compiler assumes that
    ptr[pos] = 0; // signed overflow never happen
} // and removes the if statement
void test4()
{                // compiled with optimizations
    int tmp[10]; // leads to segmentation faults
    f(tmp, INT_MAX);
}

// void test5()
// {
//     uint64_t x = 32; // x can be also a pointer
//     x += 2u - 4;
//     cout << x << endl;
//     auto t = -(1 << 31);
//     cout << t << endl;
//     cout << INT64_MAX << endl;
// }

void test6()
{
    float x = 0.0f;
    for (int i = 0; i < 20000000; i++)
        x += 1.0f;
    cout << x << "\n";
}

void test7()
{
    cout << setprecision(20);
    cout << 3.33333333f;                         // print 3.333333254!!
    cout << 3.33333333;                          // print 3.333333333
    cout << (0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1); // print 0.5999999999999999
}

int main()
{

    // test();
    // test2();
    // test3();
    // test4();
    test6();

    return 0;
}