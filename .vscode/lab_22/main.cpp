#include <iostream>
#include "Money.h"
using namespace std;

int main() {
    Money m1, m2;
    double val;

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Ввести первую сумму\n";
        cout << "2. Ввести вторую сумму\n";
        cout << "3. Прибавить к первой дробное число\n";
        cout << "4. Сравнить суммы\n";
        cout << "5. Вывести суммы\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Введите первую сумму (формат: рубли,копейки): ";
                cin >> m1;
                break;
            case 2:
                cout << "Введите вторую сумму (формат: рубли,копейки): ";
                cin >> m2;
                break;
            case 3:
                cout << "Введите дробное число для прибавления (например, 10.55): ";
                cin >> val;
                m1 = m1 + val;
                cout << "Результат: " << m1 << endl;
                break;
            case 4:
                cout << "Сравнение: \n";
                cout << "m1 > m2: " << (m1 > m2 ? "Да" : "Нет") << endl;
                cout << "m1 < m2: " << (m1 < m2 ? "Да" : "Нет") << endl;
                cout << "m1 == m2: " << (m1 == m2 ? "Да" : "Нет") << endl;
                break;
            case 5:
                cout << "Первая сумма: " << m1 << endl;
                cout << "Вторая сумма: " << m2 << endl;
                break;
            case 0:
                break;
            default:
                cout << "Неверный выбор.\n";
        }

    } while (choice != 0);

    return 0;
}
