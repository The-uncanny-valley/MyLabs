// Container.h
#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>

class Set {
private:
    int* data;
    int size;
    int capacity;

    void resize();
    bool contains(int value) const;

public:
    Set();
    Set(const Set& other);
    ~Set();
    Set& operator=(const Set& other);

    int& operator[](int index);
    bool operator==(const Set& other) const;
    bool operator>(int value) const;
    Set operator-(int n) const;

    void add(int value);
    void print() const;

    friend std::ostream& operator<<(std::ostream& os, const Set& set);
    friend std::istream& operator>>(std::istream& is, Set& set);

    class Iterator {
    private:
        const Set& set;
        int pos;
    public:
        Iterator(const Set& s);
        void moveLeft(int n);
        int current() const;
    };
};

#endif // CONTAINER_H
