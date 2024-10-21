#ifndef TEST_DEQUE_H
#define TEST_DEQUE_H

#include "deque.h"
#include <cassert>
#include <iostream>

void test_constructor_destructor()
{
    Deque<int> d;
    assert(d.empty());
    assert(d.size() == 0);
}

void test_push_back_push_front()
{
    Deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_front(0);
    assert(d.size() == 3);
    assert(d.front() == 0);
    assert(d.back() == 2);
}

void test_pop_back_pop_front()
{
    Deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_front(0);
    d.pop_back();
    assert(d.size() == 2);
    assert(d.back() == 1);
    d.pop_front();
    assert(d.size() == 1);
    assert(d.front() == 1);
}

void test_element_access()
{
    Deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_front(0);
    assert(d.at(0) == 0);
    assert(d.at(1) == 1);
    assert(d.at(2) == 2);
    assert(d[0] == 0);
    assert(d[1] == 1);
    assert(d[2] == 2);
    assert(d.front() == 0);
    assert(d.back() == 2);
}

void test_capacity()
{
    Deque<int> d;
    assert(d.empty());
    assert(d.size() == 0);
    d.push_back(1);
    assert(!d.empty());
    assert(d.size() == 1);
}

void test_modifiers()
{
    Deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_front(0);
    d.clear();
    assert(d.empty());
    assert(d.size() == 0);

    d.push_back(1);
    d.push_back(2);
    d.insert(1, 1);
    assert(d.size() == 3);
    assert(d.at(1) == 1);

    d.erase(1);
    assert(d.size() == 2);
    assert(d.at(1) == 2);

    d.resize(5);
    assert(d.size() == 5);

    Deque<int> d2;
    d2.push_back(10);
    d.swap(d2);
    assert(d.size() == 1);
    assert(d.front() == 10);
    assert(d2.size() == 5);
}

void run_all_tests()
{
    test_constructor_destructor();
    test_push_back_push_front();
    test_pop_back_pop_front();
    test_element_access();
    test_capacity();
    test_modifiers();
    std::cout << "All tests passed!" << std::endl;
}

#endif // TEST_DEQUE_H