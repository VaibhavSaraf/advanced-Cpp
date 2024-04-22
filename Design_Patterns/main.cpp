#include <iostream>
#include <boost/lexical_cast.hpp>
using namespace std;
using namespace boost;
int main()
{
    cout << "hello world"
         << "\n";

    auto x = boost::lexical_cast<long long>("151651651865186168");
    cout << x << "\n";
    return 0;
}