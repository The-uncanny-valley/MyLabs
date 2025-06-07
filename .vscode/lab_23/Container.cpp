// Container.cpp
#include "Container.h"
#include <algorithm> // готовые шаблонные функции

Set::Set() : data(new int[4]), size(0), capacity(4) {} // реализация конструктора по умолчанию 

Set::Set(const Set& other) : data(new int[other.capacity]), size(other.size), capacity(other.capacity) {
    std::copy(other.data, other.data + size, data); // вызов функции из библиотеки <algorithm>, которая используется для копирования элементов
} // конструктор копирования

Set::~Set() { //  метод, который вызывается автоматически, когда объект класса уничтожается
    delete[] data; //  оператор удаления массива
}

Set& Set::operator=(const Set& other) { // определение оператора присваивания (=) для класса Set
    if (this != &other) { // проверка самоприсваивания
        delete[] data; // освобождаем старую память, которую текущий объект уже держал.
        capacity = other.capacity;
        size = other.size; // копируем информацию о размере
        data = new int[capacity]; // новый массив под элементы
        std::copy(other.data, other.data + size, data); // копируем реальные элементы
    }
    return *this; // возвращает ссылку на текущий объект
}

void Set::resize() { // метод для выделения нового, большего массива
    capacity *= 2;
    int* newData = new int[capacity]; // оздаём новый массив на новом участке памяти
    std::copy(data, data + size, newData); // копируем все существующие элементы в новый массив
    delete[] data; // удаляем старый массив
    data = newData; // назначаем новый массив в качестве рабочего
}

bool Set::contains(int value) const { // реализация метода, который проверяет, есть ли значение в множестве
    for (int i = 0; i < size; ++i)
        if (data[i] == value)
            return true;
    return false;
}

void Set::add(int value) { // реализация метода Set::add, который добавляет элемент в множество.
    if (!contains(value)) {
        if (size == capacity) // если массив уже заполнен
            resize(); // resize() удваивает capacity
        data[size++] = value; // добавляем новый элемент в конец массива
    }
}

int& Set::operator[](int index) { //  перегрузка оператора индексирования [] для класса Set
    if (index < 0 || index >= size) // проверка границ
        throw std::out_of_range("Index out of range"); //  выбрасываем исключение
    return data[index]; // возвращается реальная ячейка массива, а не её копия
}

bool Set::operator==(const Set& other) const { // перегрузку оператора == для сравнения двух множеств Set
    if (size != other.size) // если количество элементов разное, множества точно не равны
        return false;
    for (int i = 0; i < size; ++i) // проверим, что все элементы текущего множества есть в other
        if (!other.contains(data[i]))
            return false;
    return true;
}

bool Set::operator>(int value) const { // проверяет, содержит ли множество Set элемент value
    return contains(value);
}

Set Set::operator-(int n) const { // новое множество из элементов текущего, начиная с позиции n (левый "срез")
    Iterator it(*this); // итератор, привязанный к текущему множеству
    it.moveLeft(n); // cдвигает итератор влево на n
    Set result;
    for (int i = it.current(); i < size; ++i)
        result.add(data[i]); // добавляет все элементы с этой позиции до конца в новое множество
    return result;
}

void Set::print() const { // метод print, который выводит содержимое множества в консоль
    for (int i = 0; i < size; ++i)
        std::cout << data[i] << " ";
    std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Set& set) { // перегрузка оператора <<
    for (int i = 0; i < set.size; ++i)
        os << set.data[i] << " ";
    return os; // возвращает поток os, чтобы поддерживать цепочку операций
}

std::istream& operator>>(std::istream& is, Set& set) {
    int value;
    is >> value; // считывает один элемент из потока
    set.add(value); // добавляет его в множество
    return is; // возвращает ссылку на поток
}

Set::Iterator::Iterator(const Set& s) : set(s), pos(s.size - 1) {} // конструктор итератора. Позволяет обходить множество с конца

void Set::Iterator::moveLeft(int n) { // сдвигает итератор влево на n позиций
    pos -= n;
    if (pos < 0) pos = 0;
}

int Set::Iterator::current() const { // возвращает текущую позицию, на которую указывает итератор
    if (pos < 0 || pos >= set.size) // проверка, указывает ли итератор на допустимый элемент множества
        throw std::out_of_range("Iterator out of range");
    return pos;
}