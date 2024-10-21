#include "deque.h"

#include "test_deque.h"

int main()
{
    Deque<int> dq;
    dq.push_back(10);
    dq.push_back(20);
    dq.push_back(30);
    dq.push_front(5);
    dq.push_front(3);
    std::cout << "Front: " << dq.front() << "\n";
    std::cout << "Back: " << dq.back() << "\n";
    std::cout << "Element at 2: " << dq[2] << "\n";

    dq.pop_front();
    dq.pop_back();
    std::cout << "After popping, front: " << dq.front() << "\n";
    std::cout << "After popping, back: " << dq.back() << "\n";

    test_constructor_destructor();
    test_push_back_push_front();
    test_pop_back_pop_front();
    test_element_access();
    test_capacity();
    test_modifiers();
    // Add calls to other test functions here
    std::cout << "All tests passed!" << std::endl;
    return 0;
}