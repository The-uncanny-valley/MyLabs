#include <iostream>
#include <fstream> // для работы с файлами
#include <algorithm> // // для std::remove

using namespace std;

class Time {
    int minutes;
    int seconds;

public:
    Time(int m = 0, int s = 0) {
        minutes = m + s / 60;
        seconds = s % 60;
    }

    void input() {
        cout << "Введите минуты и секунды: ";
        cin >> minutes >> seconds;
        normalize(); // приведение к нормальному виду
    }

    // вывод времени в формате MM:SS
    void display() const {
        cout << minutes << ":" << (seconds < 10 ? "0" : "") << seconds << endl;
    }

    // приведение времени к нормальному виду (секунды < 60)
    void normalize() {
        minutes += seconds / 60;
        seconds %= 60;
        if (seconds < 0) {
            seconds += 60;
            minutes--;
        }
    }

    // добавление секунд к текущему времени
    void addSeconds(int s) {
        seconds += s;
        normalize();
    }

    // вычитание секунд
    void subtractSeconds(int s) {
        seconds -= s;
        normalize();
        if (minutes < 0 || (minutes == 0 && seconds < 0)) {
            minutes = 0;
            seconds = 0;
        }
    }

    bool operator==(const Time &t) const { // перегрузка оператора сравнения
        return minutes == t.minutes && seconds == t.seconds;
    }

    friend istream &operator>>(istream &in, Time &t);
    friend ostream &operator<<(ostream &out, const Time &t);
};

istream &operator>>(istream &in, Time &t) {
    char delim;
    in >> t.minutes >> delim >> t.seconds;
    if (delim != ':') {
        in.setstate(ios::failbit); // пометить как ошибка
    }
    t.normalize();
    return in;
}

ostream &operator<<(ostream &out, const Time &t) {
    out << t.minutes << ":" << (t.seconds < 10 ? "0" : "") << t.seconds;
    return out;
}

#include <vector>

const string filename = "times.txt"; // имя файла, где хранятся записи

void saveTimesToFile(const vector<Time> &times) { // сохраняет все объекты Time в файл
    ofstream fout(filename);
    for (const auto &t : times) {
        fout << t << endl;
    }
    fout.close();
}

vector<Time> loadTimesFromFile() {
    ifstream in("times.txt");
    if (!in.is_open()) {
        cerr << "Не удалось открыть файл.\n";
        return {};
    }

    vector<Time> times;
    Time t;
    while (in >> t) {
        times.push_back(t);
    }

    in.close();
    return times;
}

void deleteEqual(const Time &target) { // // удаляет все записи, равные заданному значению
    vector<Time> times = loadTimesFromFile();
    times.erase(remove(times.begin(), times.end(), target), times.end());
    saveTimesToFile(times);
}

void subtractFromMatching(const Time &target) {
    vector<Time> times = loadTimesFromFile();
    for (auto &t : times) {
        if (t == target) {
            t.subtractSeconds(90);
        }
    }
    saveTimesToFile(times);
}

void addKAfter(const Time &target, int K) {
    vector<Time> times = loadTimesFromFile();
    vector<Time> result;
    Time newTime;
    for (size_t i = 0; i < times.size(); ++i) {
        result.push_back(times[i]);
        if (times[i] == target) {
            for (int j = 0; j < K; ++j) {
                cout << "Введите интервал #" << (j + 1) << " для добавления: ";
                newTime.input();
                result.push_back(newTime);
            }
        }
    }
    saveTimesToFile(result);
}

int main() {
    vector<Time> times;
    int choice;
    Time temp;
    int K;

    do {
        cout << "\n1. Ввод и сохранение\n2. Просмотр\n3. Удалить равные\n4. Уменьшить равные\n5. Добавить K после\n0. Выход\nВыбор: ";
        cin >> choice;
        switch (choice) {
            case 1:
                times.clear();
                cout << "Сколько интервалов? ";
                int n;
                cin >> n;
                for (int i = 0; i < n; ++i) {
                    Time t;
                    t.input();
                    times.push_back(t);
                }
                saveTimesToFile(times);
                break;
            case 2:

                times = loadTimesFromFile();

                for (const auto &t : times) t.display();
                break;
            case 3:
                cout << "Введите значение для удаления: ";
                temp.input();
                deleteEqual(temp);
                break;
            case 4:
                cout << "Введите значение для уменьшения: ";
                temp.input();
                subtractFromMatching(temp);
                break;
            case 5:
                cout << "Введите значение после которого добавить: ";
                temp.input();
                cout << "Сколько добавить? ";
                cin >> K;
                addKAfter(temp, K);
                break;
        }
    } while (choice != 0); // пока пользователь не выбрал выход

    return 0;
}