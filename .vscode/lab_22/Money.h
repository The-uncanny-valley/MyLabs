#ifndef MONEY_H // Include Guard
#define MONEY_H // создаёт флаг (метку), по которому компилятор узнаёт, что файл уже обрабатывался, и не дублирует его содержимое

#include <iostream>

class Money {
private:
    long rubles;
    int kopecks;
    void normalize(); // для перевода 100 копеек в рубль

public:
    // конструкторы
    Money();
    Money(long r, int k);
    Money(const Money& other); // конструктор копирования

    ~Money(); // деструктор

    long getRubles() const;
    int getKopecks() const;
    void setRubles(long r);
    void setKopecks(int k);

    Money& operator=(const Money& other); // перегрузка оператора присваивания
    Money operator+(double value) const; // перегрузка оператора сложения

    bool operator==(const Money& other) const; // перегрузка оператора "равенство"
    bool operator>(const Money& other) const; // перегрузка оператора "меньше"
    bool operator<(const Money& other) const; //  перегрузка оператора "больше"

    // Дружественные функции ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Money& money); //  перегрузка оператора вывода
    friend std::istream& operator>>(std::istream& is, Money& money); // перегрузка оператора ввода
};

#endif
