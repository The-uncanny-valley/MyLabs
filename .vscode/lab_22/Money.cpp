#include "Money.h"
#include <cmath>

//  приватная нормализация
void Money::normalize() {
    if (kopecks >= 100 || kopecks < 0) {
        rubles += kopecks / 100;
        kopecks = kopecks % 100;
    }
    if (kopecks < 0) {
        rubles--;
        kopecks += 100;
    }
}

Money::Money() : rubles(0), kopecks(0) {} // конструктор по умолчанию

Money::Money(long r, int k) : rubles(r), kopecks(k) { // конструктор, который принимает рубли и копейки
    normalize();
}

Money::Money(const Money& other) { // конструктор копирования
    rubles = other.rubles;
    kopecks = other.kopecks;
}

Money::~Money() {}

long Money::getRubles() const { return rubles; }
int Money::getKopecks() const { return kopecks; }

void Money::setRubles(long r) { rubles = r; }
void Money::setKopecks(int k) { kopecks = k; normalize(); }

Money& Money::operator=(const Money& other) {
    if (this != &other) {
        rubles = other.rubles;
        kopecks = other.kopecks;
    }
    return *this;
}

Money Money::operator+(double value) const {
    long r = (long)value;
    int k = round((value - r) * 100);
    Money temp(rubles + r, kopecks + k);
    temp.normalize();
    return temp;
}

bool Money::operator==(const Money& other) const {
    return rubles == other.rubles && kopecks == other.kopecks;
}

bool Money::operator>(const Money& other) const {
    if (rubles > other.rubles) return true;
    if (rubles == other.rubles && kopecks > other.kopecks) return true;
    return false;
}

bool Money::operator<(const Money& other) const {
    return !(*this > other || *this == other);
}

std::ostream& operator<<(std::ostream& os, const Money& money) {
    os << money.rubles << "," << (money.kopecks < 10 ? "0" : "") << money.kopecks;
    return os;
}

std::istream& operator>>(std::istream& is, Money& money) {
    char comma;
    is >> money.rubles >> comma >> money.kopecks;
    money.normalize();
    return is;
}