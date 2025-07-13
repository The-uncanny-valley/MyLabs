#include <iostream>
#include <vector> // для работы с динамическими массивами
#include <string>
#include <cstdlib> // для генерации случайных чисел
#include <ctime> // для получения текущего времени
#include <iomanip> // для форматированного вывода
#include <list> // для использования связных списков
#include <algorithm>

using namespace std;

struct Record {
    string fio;
    int accountNumber;
    double amount;
};

vector<string> surnames = {"Мизулина", "Кабаева", "Ивлеева", "Собчак", "Кардашьян", "Бузова", "Блиновская"};
vector<string> names = {"Гульназ", "Шавела", "Джемал", "Кекела", "Сесили", "Малхаз"}; // объявление и инициализация вектора строк 
vector<string> patronymics = {"Алексеевна", "Николаевна", "Дмитриевна", "Михайловна", "Евгеньевна"};

string generateFio() {
    return surnames[rand() % surnames.size()] + " " +
           names[rand() % names.size()] + " " +
           patronymics[rand() % patronymics.size()];
}

vector<Record> generateRecords(int count) {
    vector<Record> records;
    for (int i = 0; i < count; ++i) {
        Record r;
        r.fio = generateFio();
        r.accountNumber = rand() % 900000 + 100000;
        r.amount = (rand() % 1000000) / 100.0;
        records.push_back(r);
    }
    return records;
}

int hashString(const string& key, int M) { // полиномиальное хеширование
    unsigned long hash = 0;
    for (char c : key)
        hash = hash * 31 + c;
    return hash % M;
}

int countCollisions(const vector<Record>& records, int M) {
    vector<list<Record>> table(M); // вектор таблиц
    int collisions = 0;
    for (const auto& r : records) {
        int index = hashString(r.fio, M);
        if (!table[index].empty()) collisions++;
        table[index].push_back(r);
    }
    return collisions;
}

void displayRecords(const vector<Record> &records)
{
    for (const auto &r : records)
    {
        cout << setw(70) << left << r.fio
             << " | Счёт: " << r.accountNumber
             << " | Сумма: " << fixed << setprecision(2) << r.amount << endl;
    }
}

void buildHashTable(const vector<Record> &records, vector<list<Record>> &hashTable, int M)
{
    for (const auto &r : records)
    {
        int index = hashString(r.fio, M);
        hashTable[index].push_back(r);
    }
}

void searchByFio(const vector<list<Record>> &hashTable, int M)
{
    string key;
    cout << "Введите ФИО для поиска: ";
    getline(cin >> ws, key);

    int index = hashString(key, M);
    bool found = false;
    for (const auto &r : hashTable[index])
    {
        if (r.fio == key)
        {
            cout << "Найдено: " << r.fio << " | Счёт: " << r.accountNumber << " | Сумма: " << r.amount << endl;
            found = true;
        }
    }
    if (!found)
        cout << "Запись не найдена.\n";
}

void deleteByFio(vector<list<Record>> &hashTable, int M)
{
    string key;
    cout << "Введите ФИО для удаления: ";
    getline(cin >> ws, key);
    int index = hashString(key, M);
    auto &bucket = hashTable[index];
    bucket.remove_if([&](const Record &r)
                     { return r.fio == key; });
    cout << "Удаление завершено.\n";
}

void updateByFio(vector<list<Record>> &hashTable, int M)
{
    string key;
    cout << "Введите ФИО для корректировки: ";
    getline(cin >> ws, key);
    int index = hashString(key, M);
    for (auto &r : hashTable[index])
    {
        if (r.fio == key)
        {
            cout << "Введите новую сумму: ";
            cin >> r.amount;
            cout << "Корректировка выполнена.\n";
            return;
        }
    }
    cout << "Запись не найдена.\n";
}

int main()
{
    srand(time(0));
    const int M = 101; // Размер хеш-таблицы
    vector<Record> records = generateRecords(100);
    vector<list<Record>> hashTable(M);
    buildHashTable(records, hashTable, M);

    int choice;
    do
    {
        cout << "\n1. Показать все записи\n2. Найти по ФИО\n3. Подсчитать коллизии\n4. Удалить по ФИО\n5. Корректировка по ФИО\n6. Выход\nВыбор: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            displayRecords(records);
            break;
        case 2:
            searchByFio(hashTable, M);
            break;
        case 3:
            cout << "Коллизии при M=40: " << countCollisions(records, 40) << endl;
            cout << "Коллизии при M=75: " << countCollisions(records, 75) << endl;
            cout << "Коллизии при M=90: " << countCollisions(records, 90) << endl;
            break;
        case 4:
            deleteByFio(hashTable, M);
            break;
        case 5:
            updateByFio(hashTable, M);
            break;
        }
    } while (choice != 6);

    return 0;
}
