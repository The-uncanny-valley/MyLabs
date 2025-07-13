#include <iostream>
#include "Money.h" //  директива препроцессора, которая включает заголовочный файл
using namespace std;

int main() {
    Money s1, s2;
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
                cin >> s1;
                break;
            case 2:
                cout << "Введите вторую сумму (формат: рубли,копейки): ";
                cin >> s2;
                break;
            case 3:
                cout << "Введите дробное число для прибавления (например, 10.55): ";
                cin >> val;
                s1 = s1 + val;
                cout << "Результат: " << s1 << endl;
                break;
            case 4:
                cout << "Сравнение: \n";
                cout << "s1 > s2: " << (s1 > s2 ? "Да" : "Нет") << endl;
                cout << "s1 < s2: " << (s1 < s2 ? "Да" : "Нет") << endl;
                cout << "s1 == s2: " << (s1 == s2 ? "Да" : "Нет") << endl;
                break;
            case 5:
                cout << "Первая сумма: " << s1 << endl;
                cout << "Вторая сумма: " << s2 << endl;
                break;
            case 0:
                break;
            default:
                cout << "Неверный выбор.\n";
        }

    } while (choice != 0);

    return 0;
}