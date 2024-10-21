#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>

template <typename T>
class Deque
{
private:
    static constexpr size_t BLOCK_SIZE = 64; // Size of each chunk (can be tweaked)

    using Block = std::vector<T>; // A block is just a vector of fixed size
    std::vector<Block *> map;     // Each element points to a block
    size_t front_index;           // Tracks the front logical index
    size_t back_index;            // Tracks the back logical index
    size_t count;                 // Total number of elements

    // Helper functions to get block and index within a block
    size_t block_index(size_t idx) const { return idx / BLOCK_SIZE; }
    size_t within_block_index(size_t idx) const { return idx % BLOCK_SIZE; }

    // Expands capacity by adding blocks to the front or back
    void expand_capacity(bool front);

public:
    // Constructors and assignment operators
    Deque();
    Deque(const Deque &other);
    Deque &operator=(const Deque &other);
    ~Deque();

    // Element access
    T &at(size_t idx);
    const T &at(size_t idx) const;
    T &operator[](size_t idx);
    const T &operator[](size_t idx) const;
    T &front();
    const T &front() const;
    T &back();
    const T &back() const;

    // Iterators (for simplicity, we won't implement all iterators here)
    T *begin();
    const T *begin() const;
    T *end();
    const T *end() const;

    // Capacity
    bool empty() const;
    size_t size() const;
    size_t max_size() const;

    // Modifiers
    void clear();
    void push_back(const T &value);
    void pop_back();
    void push_front(const T &value);
    void pop_front();
    void insert(size_t pos, const T &value);
    void erase(size_t pos);
    void resize(size_t new_size);
    void swap(Deque &other);
    void print() const;
};

// Implementation of template functions

// Constructor
template <typename T>
Deque<T>::Deque() : front_index(0), back_index(0), count(0)
{
    map.push_back(new Block(BLOCK_SIZE));
}

// Destructor
template <typename T>
Deque<T>::~Deque()
{
    for (auto block : map)
    {
        delete block;
    }
}

// Copy constructor
template <typename T>
Deque<T>::Deque(const Deque &other)
    : front_index(other.front_index), back_index(other.back_index), count(other.count)
{
    map.resize(other.map.size());
    for (size_t i = 0; i < other.map.size(); ++i)
    {
        map[i] = new Block(*other.map[i]);
    }
}

// Copy assignment operator
template <typename T>
Deque<T> &Deque<T>::operator=(const Deque &other)
{
    if (this != &other)
    {
        clear();
        map.resize(other.map.size());
        for (size_t i = 0; i < other.map.size(); ++i)
        {
            map[i] = new Block(*other.map[i]);
        }
        front_index = other.front_index;
        back_index = other.back_index;
        count = other.count;
    }
    return *this;
}

// Element access
template <typename T>
T &Deque<T>::at(size_t idx)
{
    if (idx >= count)
    {
        throw std::out_of_range("Index out of range");
    }
    size_t global_idx = front_index + idx;
    return (*map[block_index(global_idx)])[within_block_index(global_idx)];
}

template <typename T>
const T &Deque<T>::at(size_t idx) const
{
    if (idx >= count)
    {
        throw std::out_of_range("Index out of range");
    }
    size_t global_idx = front_index + idx;
    return (*map[block_index(global_idx)])[within_block_index(global_idx)];
}

template <typename T>
T &Deque<T>::operator[](size_t idx)
{
    return at(idx);
}

template <typename T>
const T &Deque<T>::operator[](size_t idx) const
{
    return at(idx);
}

template <typename T>
T &Deque<T>::front()
{
    return at(0);
}

template <typename T>
const T &Deque<T>::front() const
{
    return at(0);
}

template <typename T>
T &Deque<T>::back()
{
    return at(count - 1);
}

template <typename T>
const T &Deque<T>::back() const
{
    return at(count - 1);
}

// Iterators (basic implementation, for simplicity)
template <typename T>
T *Deque<T>::begin()
{
    return &at(0);
}

template <typename T>
const T *Deque<T>::begin() const
{
    return &at(0);
}

template <typename T>
T *Deque<T>::end()
{
    return &at(count);
}

template <typename T>
const T *Deque<T>::end() const
{
    return &at(count);
}

// Capacity functions
template <typename T>
bool Deque<T>::empty() const
{
    return count == 0;
}

template <typename T>
size_t Deque<T>::size() const
{
    return count;
}

template <typename T>
size_t Deque<T>::max_size() const
{
    return std::numeric_limits<size_t>::max() / sizeof(T);
}

// Modifiers
template <typename T>
void Deque<T>::clear()
{
    for (auto block : map)
    {
        delete block;
    }
    map.clear();
    front_index = back_index = count = 0;
    map.push_back(new Block(BLOCK_SIZE));
}

template <typename T>
void Deque<T>::push_back(const T &value)
{
    if (back_index == BLOCK_SIZE * map.size())
    {
        expand_capacity(false);
    }
    (*map[block_index(back_index)])[within_block_index(back_index)] = value;
    ++back_index;
    ++count;
}

template <typename T>
void Deque<T>::pop_back()
{
    if (count == 0)
        throw std::out_of_range("Deque is empty");
    --back_index;
    --count;
}

template <typename T>
void Deque<T>::push_front(const T &value)
{
    if (front_index == 0)
    {
        expand_capacity(true);
    }
    --front_index;
    (*map[block_index(front_index)])[within_block_index(front_index)] = value;
    ++count;
}

template <typename T>
void Deque<T>::pop_front()
{
    if (count == 0)
        throw std::out_of_range("Deque is empty");
    ++front_index;
    --count;
}

template <typename T>
void Deque<T>::insert(size_t pos, const T &value)
{
    if (pos > count)
        throw std::out_of_range("Index out of range");

    if (pos == 0)
    {
        push_front(value);
    }
    else if (pos == count)
    {
        push_back(value);
    }
    else
    {
        if (back_index == BLOCK_SIZE * map.size())
        {
            expand_capacity(false);
        }

        size_t global_idx = front_index + pos;
        size_t block_idx = block_index(global_idx);
        size_t within_block_idx = within_block_index(global_idx);

        // Shift elements to the right to make space for the new element
        for (size_t i = count; i > pos; --i)
        {
            size_t src_global_idx = front_index + i - 1;
            size_t dest_global_idx = src_global_idx + 1;
            (*map[block_index(dest_global_idx)])[within_block_index(dest_global_idx)] =
                (*map[block_index(src_global_idx)])[within_block_index(src_global_idx)];
        }

        // Insert the new element
        (*map[block_idx])[within_block_idx] = value;
        ++back_index;
        ++count;
    }
}

template <typename T>
void Deque<T>::erase(size_t pos)
{
    if (pos >= count)
        throw std::out_of_range("Index out of range");
    // Simple erase logic (for simplicity)
    for (size_t i = pos; i < count - 1; ++i)
    {
        at(i) = at(i + 1);
    }
    pop_back();
}

template <typename T>
void Deque<T>::resize(size_t new_size)
{
    while (count > new_size)
    {
        pop_back();
    }
    while (count < new_size)
    {
        push_back(T());
    }
}

template <typename T>
void Deque<T>::swap(Deque &other)
{
    std::swap(map, other.map);
    std::swap(front_index, other.front_index);
    std::swap(back_index, other.back_index);
    std::swap(count, other.count);
}

// Private: Expands capacity
template <typename T>
void Deque<T>::expand_capacity(bool front)
{
    if (front)
    {
        map.insert(map.begin(), new Block(BLOCK_SIZE));
        front_index += BLOCK_SIZE;
        back_index += BLOCK_SIZE;
    }
    else
    {
        map.push_back(new Block(BLOCK_SIZE));
    }
}

// Print function
template <typename T>
void Deque<T>::print() const
{
    for (size_t i = 0; i < count; ++i)
    {
        size_t global_idx = front_index + i;
        std::cout << (*map[block_index(global_idx)])[within_block_index(global_idx)] << " ";
    }
    std::cout << std::endl;
}

#endif // DEQUE_H