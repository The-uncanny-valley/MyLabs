// main.cpp
#include "Container.h"
#include <iostream>

void showMenu() {
    std::cout << "\nМеню:" << std::endl;
    std::cout << "1. Добавить элемент в множество" << std::endl;
    std::cout << "2. Показать множество" << std::endl;
    std::cout << "3. Проверить принадлежность числа" << std::endl;
    std::cout << "4. Проверить равенство двух множеств" << std::endl;
    std::cout << "5. Сдвинуть итератор влево и показать остаток" << std::endl;
    std::cout << "6. Выход" << std::endl;
    std::cout << "Выберите действие: ";
}

int main() {
    Set set1, set2;
    int choice, value, n;

    while (true) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Введите число для добавления: ";
                std::cin >> value;
                set1.add(value);
                break;
            case 2:
                std::cout << "Множество: ";
                set1.print();
                break;
            case 3:
                std::cout << "Введите число для проверки: ";
                std::cin >> value;
                std::cout << (set1 > value ? "Есть в множестве" : "Нет в множестве") << std::endl;
                break;
            case 4:
                std::cout << "Введите элементы второго множества (введите -1 для завершения): ";
                while (true) {
                    std::cin >> value;
                    if (value == -1) break;
                    set2.add(value);
                }
                std::cout << (set1 == set2 ? "Множества равны" : "Множества разные") << std::endl;
                break;
            case 5:
                std::cout << "Введите количество шагов влево: ";
                std::cin >> n;
                try {
                    Set result = set1 - n;
                    std::cout << "Оставшиеся элементы: ";
                    result.print();
                } catch (std::exception& e) {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            case 6:
                return 0;
            default:
                std::cout << "Неверный выбор!" << std::endl;
        }
    }
}
