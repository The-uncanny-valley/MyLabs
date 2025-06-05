// Container.cpp
#include "Container.h"
#include <algorithm>

Set::Set() : data(new int[4]), size(0), capacity(4) {}

Set::Set(const Set& other) : data(new int[other.capacity]), size(other.size), capacity(other.capacity) {
    std::copy(other.data, other.data + size, data);
}

Set::~Set() {
    delete[] data;
}

Set& Set::operator=(const Set& other) {
    if (this != &other) {
        delete[] data;
        capacity = other.capacity;
        size = other.size;
        data = new int[capacity];
        std::copy(other.data, other.data + size, data);
    }
    return *this;
}

void Set::resize() {
    capacity *= 2;
    int* newData = new int[capacity];
    std::copy(data, data + size, newData);
    delete[] data;
    data = newData;
}

bool Set::contains(int value) const {
    for (int i = 0; i < size; ++i)
        if (data[i] == value)
            return true;
    return false;
}

void Set::add(int value) {
    if (!contains(value)) {
        if (size == capacity)
            resize();
        data[size++] = value;
    }
}

int& Set::operator[](int index) {
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");
    return data[index];
}

bool Set::operator==(const Set& other) const {
    if (size != other.size)
        return false;
    for (int i = 0; i < size; ++i)
        if (!other.contains(data[i]))
            return false;
    return true;
}

bool Set::operator>(int value) const {
    return contains(value);
}

Set Set::operator-(int n) const {
    Iterator it(*this);
    it.moveLeft(n);
    Set result;
    for (int i = it.current(); i < size; ++i)
        result.add(data[i]);
    return result;
}

void Set::print() const {
    for (int i = 0; i < size; ++i)
        std::cout << data[i] << " ";
    std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Set& set) {
    for (int i = 0; i < set.size; ++i)
        os << set.data[i] << " ";
    return os;
}

std::istream& operator>>(std::istream& is, Set& set) {
    int value;
    is >> value;
    set.add(value);
    return is;
}

Set::Iterator::Iterator(const Set& s) : set(s), pos(s.size - 1) {}

void Set::Iterator::moveLeft(int n) {
    pos -= n;
    if (pos < 0) pos = 0;
}

int Set::Iterator::current() const {
    if (pos < 0 || pos >= set.size)
        throw std::out_of_range("Iterator out of range");
    return pos;
}
