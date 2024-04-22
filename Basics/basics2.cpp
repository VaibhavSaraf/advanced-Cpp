#include <bits/stdc++.h>
using namespace std;

// enum color_t
// {
//     BLACK,
//     BLUE,
//     GREEN
// };
// enum fruit_t
// {
//     APPLE,
//     CHERRY
// };
enum class Color
{
    BLACK,
    GREEN,
    BLUE [[deprecated]]
};
enum class Fruit
{
    APPLE,
    CHERRY
};

int main()
{
    // color_t color = BLACK; // int: 0
    // fruit_t fruit = APPLE; // int: 0

    Color color = Color::BLUE;
    Fruit fruit = Fruit::APPLE;

    return 0;
}