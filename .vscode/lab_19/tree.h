#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cstring> // функции для работы с C-строками
#include <vector>
using namespace std;

struct TreeNode { // определяет узел бинарного дерева
    char* data; // C-строка
    TreeNode* left; // указатель на левое поддерево
    TreeNode* right; // указатель на правое поддерево
};

TreeNode* createNode(const char* str) { // функция создания нового узла бинарного дерева
    TreeNode* newNode = new TreeNode; // память под новый узел
    newNode->data = new char[strlen(str) + 1]; // память под копию строки
    strcpy(newNode->data, str); // копирует содержимое str в data
    newNode->left = newNode->right = nullptr;
    return newNode; // указатель на готовый узел
}

void deleteTree(TreeNode* root) { // функция для удаления всего бинарного дерева
    if (!root) return; // если узел пустой, выйти из функции
    deleteTree(root->left); // удаляем левое поддерево (рекурсивно)
    deleteTree(root->right); // удаляем правое поддерево
    delete[] root->data; // освобождаем память, занятую под строку
    delete root; // удаляем сам узел дерева
}

void printTree(TreeNode* root, int level = 0) {
    if (!root) return; // нулевой указатель — ничего не делаем
    printTree(root->right, level + 1); // печатаем правое поддерево, но с увеличенным уровнем
    for (int i = 0; i < level; i++) cout << "    "; // отступы
    cout << root->data << endl; // значение текущего узла
    printTree(root->left, level + 1); // печатаем левое поддерево
}

// строит сбалансированное бинарное дерево поиска (BST) из отсортированного массива строк
TreeNode* buildBalancedTree(vector<const char*>& elements, int start, int end) {
    if (start > end) return nullptr; // базовый случай рекурсии, диапазон пустой
    int mid = (start + end) / 2; // средний элемент
    TreeNode* root = createNode(elements[mid]); // Создаём узел
    root->left = buildBalancedTree(elements, start, mid - 1); // строим дерево из левой половины массива
    root->right = buildBalancedTree(elements, mid + 1, end); //  из правой половины массива
    return root; // указатель на текущий корень
}

int countLeaves(TreeNode* root) { //  считает количество листьев
    if (!root) return 0; // если дерево пустое, то листьев нет
    if (!root->left && !root->right) return 1; // если у текущего узла нет ни левого, ни правого потомка, то это лист
    return countLeaves(root->left) + countLeaves(root->right); // считаем листья в левом и правом поддеревьях
}

void insertBST(TreeNode*& root, const char* value) { // функция вставки в бинарное дерево поиска
    if (!root) { // если поддерево пустое, создаём новый узел
        root = createNode(value);
        return;
    }
    if (strcmp(value, root->data) < 0)
        insertBST(root->left, value);
    else
        insertBST(root->right, value);
}

void toBST(TreeNode* oldRoot, TreeNode*& bstRoot) { // копирует все данные из одного дерева в новое
    if (!oldRoot) return; // если текущий узел пустой
    insertBST(bstRoot, oldRoot->data); // вставляем значение текущего узла в новое дерево
    toBST(oldRoot->left, bstRoot); // обходим левое поддерево
    toBST(oldRoot->right, bstRoot); // обходим правое поддерево
}

#endif
