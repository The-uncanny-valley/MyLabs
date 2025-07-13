#include "tree.h" // пользовательский заголовочный файл, двойные кавычки говорят искать файл в текущей папке проекта, а не в системных директориях
#include <algorithm> // содержит множество стандартных алгоритмов, таких как sort, find, reverse, max, min

int main() {
    TreeNode* balancedRoot = nullptr; // объявляет указатель на структуру TreeNode, это корень сбалансированного дерева
    TreeNode* bstRoot = nullptr; // корень бинарного дерева поиска

    vector<const char*> elements = { // вектор указателей на неизменяемые C-строки 
        "dragon", "griffin", "phoenix", "basilisk", "unicorn", "minotaur", "hydra"
    };

    sort(elements.begin(), elements.end()); // сортирует строки вектора elements по возрастанию (в алфавитном порядке)
    balancedRoot = buildBalancedTree(elements, 0, elements.size() - 1);

    int choice;
    do {
        cout << "\n✦ МЕНЮ ✦\n";
        cout << "1. Печать сбалансированного дерева\n";
        cout << "2. Количество листьев\n";
        cout << "3. Преобразовать в дерево поиска (BST)\n";
        cout << "4. Печать BST\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Сбалансированное дерево:\n";
                printTree(balancedRoot);
                break;
            case 2:
                cout << "Количество листьев: " << countLeaves(balancedRoot) << endl;
                break;
            case 3:
                toBST(balancedRoot, bstRoot);
                cout << "Преобразование завершено.\n";
                break;
            case 4:
                cout << "Дерево поиска (BST):\n";
                printTree(bstRoot);
                break;
        }
    } while (choice != 0);

    deleteTree(balancedRoot);
    deleteTree(bstRoot);
    return 0;
}