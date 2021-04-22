#define _CRT_SECURE_NO_WARNINGS
#include <cmath>
#include <ctype.h>
#include <windows.h>
#include<iomanip>
#include<new.h>
#include<stdio.h>
#include<stdlib.h>
#include <string>
#include <fstream>
#include <iostream>

typedef struct position {
    int data;
    struct position* left;
    struct position* right;
    struct position* parent;
} Pos;

typedef struct tree {
    Pos* root;
} Tree;

int Sum(Pos*);
int bin_search(Tree*, int);
Pos* GetFree(int, Pos*);
void insert(Pos**, int);
Pos* getByValue(Pos*, int);
void remove(Pos*);
Pos* findMax(Pos*);
bool deleteValue(Pos*, int);
void printTree(Pos*, const char*, int);
void deleteAll(Pos*);

void saveToFile(std::ostream& out, const Pos* root);
void loadFromFile(std::istream& in, Pos** root);
int countEvenKeys(const Pos* root);

int main() {
    char a;
    int value, sum = 0;
    Pos* pos = NULL;
    Pos* current;
    system("chcp 1251>null");
    do {
        rewind(stdin);
        printf(
            "Выберите вариант:\n"
            "a. Добавить элемент в дерево.\n"
            "b. Удалить верхний элемент с дерева.\n"
            "c. Удалить элемент дерева по значению.\n"
            "d. Найти элемент.\n"
            "e. Вывести дерево на экран.\n"
            "f. Вывести сумму элементов\n"
            "g. Запись дерева в файл\n"
            "h. Чтение дерева из файла\n"
            "i. Определить количество узлов с четными ключами.\n"
            "x. Завершить программу\n");
        std::cin >> a;
        switch (a) {
        case 'a':printf("Введите число: ");
            while (!scanf("%d", &value)) {
                rewind(stdin);
                printf("Введите число: ");
            }
            insert(&pos, value);
            break;
        case 'b':remove(pos);
            break;
        case 'c':printf("Введите число: ");
            while (!scanf("%d", &value)) {
                rewind(stdin);
                printf("Введите число: ");
            }
            if (!deleteValue(pos, value))
                puts("Такого элемента нет в дереве!");
            break;
        case 'd':printf("Введите число: ");
            while (!scanf("%d", &value)) {
                rewind(stdin);
                printf("Введите число: ");
            }
            if (current = getByValue(pos, value))
                printf("Данное число - %d\n", current->data);
            else
                puts("Такого элемента нет в дереве!");
            break;
        case 'e':printTree(pos, "root", 1);
            break;
        case 'f':sum = Sum(pos);
            printf("Сумма всех элементов равна %d\n", sum);
            break;
        case 'g': {
            std::cout << "Enter filename: ";
            std::string filename;
            std::cin >> filename;
            std::ofstream fout(filename);
            saveToFile(fout, pos);
            std::cout << "Saved successfully!\n";
            break;
        }
        case 'h': {
            std::cout << "Enter filename: ";
            std::string filename;
            std::cin >> filename;
            std::ifstream fin(filename);
            loadFromFile(fin, &pos);
            std::cout << "Loaded successfully!\n";
            break;
        }
        case 'i': {
            std::cout << "There are "
                << countEvenKeys(pos) << " nodes with even keys\n";
            break;
        }
        case 'x': std::cout << "Finishing...";
            break;
        default: puts("Введите правильный символ!");
            break;
        }
    } while (a != 'x');
    deleteAll(pos);
    return 0;
}
int bin_search(Tree* search_tree, int item) {
    Pos* search_node = search_tree->root;
    for (;;) {
        if (search_node == NULL) return 0;
        else if (item == search_node->data) return 1;
        else if (item > search_node->data) search_node = search_node->right;
        else search_node = search_node->left;
    }
}
Pos* GetFree(int value, Pos* parent) {
    Pos* tmp = (Pos*)malloc(sizeof(Pos));
    tmp->left = tmp->right = NULL;
    tmp->parent = parent;
    tmp->data = value;
    return tmp;
}

void insert(Pos** head, int value) {
    Pos* tmp = NULL;
    Pos* ins = NULL;
    if (*head == NULL) {
        *head = GetFree(value, NULL);
        return;
    }
    tmp = *head;
    while (tmp) {
        if (value > tmp->data) {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            }
            else {
                tmp->right = GetFree(value, tmp);
                return;
            }
        }
        else if (value < tmp->data) {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            }
            else {
                tmp->left = GetFree(value, tmp);
                return;
            }
        }
        else {
            return;
        }
    }
}
Pos* getByValue(Pos* root, int value) {
    while (root) {
        if (root->data > value) {
            root = root->left;
            continue;
        }
        else if (root->data < value) {
            root = root->right;
            continue;
        }
        else {
            return root;
        }
    }
    return NULL;
}
void remove(Pos* tmp) {
    if (tmp->left && tmp->right) {
        Pos* buffer = findMax(tmp->left);
        tmp->data = buffer->data;
        remove(buffer);
        return;
    }
    else if (tmp->left) {
        if (tmp == tmp->parent->left)
            tmp->parent->left = tmp->left;
        else
            tmp->parent->right = tmp->left;
    }
    else if (tmp->right) {
        if (tmp == tmp->parent->right)
            tmp->parent->right = tmp->right;
        else
            tmp->parent->left = tmp->right;
    }
    else {
        if (tmp->parent->right == tmp)
            tmp->parent->right = NULL;
        else
            tmp->parent->left = NULL;
    }
    free(tmp);
}
Pos* findMax(Pos* tmp) {
    while (tmp->right)
        tmp = tmp->right;
    return tmp;
}
bool deleteValue(Pos* root, int value) {
    Pos* tmp = getByValue(root, value);
    if (!tmp)
        return false;
    remove(tmp);
    return true;
}
void printTree(Pos* root, const char* dir, int level) {
    if (root) {
        printf("lvl %d %s = %d\n", level, dir, root->data);
        printTree(root->left, "left", level + 1);
        printTree(root->right, "right", level + 1);
    }
}
int Sum(Pos* pos) {
    static int sum = 0;
    if (pos) {
        sum += pos->data;
        Sum(pos->left);
        Sum(pos->right);
    }
    return sum;
}
void deleteAll(Pos* tmp) {
    if (tmp == nullptr) {
        return;
    }

    if (tmp->right)
        deleteAll(tmp->right);
    if (tmp->left)
        deleteAll(tmp->left);
    free(tmp);
}

void saveToFile(std::ostream& out, const Pos* root) {
    if (root != nullptr) {
        out << root->data << " ";
        saveToFile(out, root->left);
        saveToFile(out, root->right);
    }
}

void loadFromFile(std::istream& in, Pos** root) {
    int key;
    while (in >> key) {
        insert(root, key);
    }
}

int countEvenKeys(const Pos* root) {
    if (root == nullptr) {
        return 0;
    }

    return int{ root->data % 2 == 0 }
        +countEvenKeys(root->left)
        + countEvenKeys(root->right);
}