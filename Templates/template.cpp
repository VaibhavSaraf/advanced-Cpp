#include <iostream>
using namespace std;

/***
 * Use of Templates
 * Generalizes software components
 * Such components can be reused in different situations
 * Operate of any kind of data
 * High performance algorithms and classes
 * Compile time; no runtime costs are involved
 * Libraries such as ATL, WTL, Boost, POCO, ACE, etc. use templates for implementation
 *
 */

/***
 * Function Templates
 * Function that acceprts template type arguments
 * Always begins with templalte keyword
 * Template type argument is called type name
 * Type name is a placeholder for the actual type
 * can accept any type
 * the template type can be used as return type
 */

/**
 * Template Argument Deduction
 * Process of deducing the types
 * Each function arguments is examined
 * The corresponding type argument is deduced from the argument
 * The type aargument deduction should lead to same type
 * Type conversions are not performed
 * after deduction, the template is instantiated
 * Override deduction by specifying types in template argument list
      Max<int>(3,2.3);
*/

/**
 * @details Template Intantiation
 * 
 * @brief 
 * A template function or class only acts as blue print
 * The compiler generates code from the blue print at compile time
 * Known as template instantiation
 * Ocuurs implicitly when:
 *  a function template is invoked
 *  taking address of a function template
 *  using explicite instantiation
 *  creating explicit specialization
 * 
 * 
 * 
 * 
 */

template <typename T>
T function(T arg)
{
    // implementation
}

template <typename T>
T add(T a, T b)
{
    return a + b;
}

template <typename T>
T ArraySum(const T *pArr, size_t arrSize)
{
    T sum = 0;
    for (size_t i = 0; i < arrSize; ++i)
    {
        sum += pArr[i];
    }
    return sum;
}

int main()
{
    cout << add(1, 2) << endl;
    cout << add(1.2, 2.3) << endl;

    int *arr = new int[5];
    for (int i = 0; i < 5; i++)
        arr[i] = i;

    double *arr1 = new double[5];
    for (int i = 0; i < 5; i++)
        arr1[i] = i + 0.1;

    cout << ArraySum(arr, 5) << endl;
    cout << ArraySum(arr1, 5) << endl;

    return 0;
}