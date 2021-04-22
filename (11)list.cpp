#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <windows.h>
using namespace std;
const int MAX = 10;

struct List {
    int Data;
    List* Next;
    List* Prior;
};

void Make_List(int n, List** Head, List* Prior) {
    if (n > 0) {
        (*Head) = new List();  //выделяем память под новый элемент
        cout << "Введите значение ";
        cin >> (*Head)->Data;  //вводим значение информационного поля
        (*Head)->Prior = Prior;
        (*Head)->Next = NULL;  //обнуление адресного поля
        Make_List(n - 1, &((*Head)->Next), (*Head));
    }
    else
        (*Head) = NULL;
}

void Print_List(List* Head) {
    if (Head != NULL) {
        cout << Head->Data << "\t";
        Print_List(Head->Next);  //переход к следующему элементу
    }
    else
        cout << "\n";
}

List* Insert_List(List* Head, int Number, int DataItem) {
    List* NewItem = new List{ DataItem, nullptr, nullptr };

    if (Head == NULL) {
        return NewItem;
    }

    List* Current = Head;
    for (int i = 1; i < Number && Current->Next != NULL; i++) {
        Current = Current->Next;
    }

    if (Number == 0) {  //вставляем новый элемент на первое место
        NewItem->Next = Head;
        Head->Prior = NewItem;
        Head = NewItem;
    }
    else {  //вставляем новый элемент на непервое место
        if (Current->Next != NULL) Current->Next->Prior = NewItem;
        NewItem->Next = Current->Next;
        Current->Next = NewItem;
        NewItem->Prior = Current;
    }

    return Head;
}

List* Delete_List(List* Head, int Number) {
    List* ptr;  //вспомогательный указатель
    List* Current = Head;
    for (int i = 0; i < Number && Current != NULL; i++) Current = Current->Next;
    if (Current != NULL) {  //проверка на корректность
        if (Current->Prior == NULL) {  //удаляем первый элемент
            Head = Head->Next;
            delete (Current);
            Head->Prior = NULL;
        }
        else {  //удаляем непервый элемент
            if (Current->Next == NULL) {
                //удаляем последний элемент
                Current->Prior->Next = NULL;
                delete (Current);
            }
            else {  //удаляем непервый и непоследний элемент
                ptr = Current->Next;
                Current->Prior->Next = Current->Next;
                Current->Next->Prior = Current->Prior;
                delete (Current);
                Current = ptr;
            }
        }
    }
    return Head;
}

bool Find_List(List* Head, int DataItem) {
    List* ptr;  //вспомогательный указатель
    ptr = Head;
    while (ptr != NULL) {  //пока не конец списка
        if (DataItem == ptr->Data)
            return true;
        else
            ptr = ptr->Next;
    }
    return false;
}

void Delete_All_List(List* Head) {
    if (Head != NULL) {
        Delete_All_List(Head->Next);
        delete Head;
    }
}

int GetMin(List* head) {
    int min_value = head->Data;
    int min_idx = 0;

    int idx = 0;
    while (head != nullptr) {
        if (min_value > head->Data) {
            min_idx = idx;
            min_value = head->Data;
        }
        ++idx;
        head = head->Next;
    }
    return min_idx;
}

int GetMax(List* head) {
    int max_value = head->Data;
    int max_idx = 0;

    int idx = 0;
    while (head != nullptr) {
        if (max_value < head->Data) {
            max_idx = idx;
            max_value = head->Data;
        }
        ++idx;
        head = head->Next;
    }
    return max_idx;
}

void task(List* Head) {
    Delete_All_List(Head);
    for (int i = 0; i < MAX; ++i) {
        Head = Insert_List(Head, i, rand() % 100);
    }

    int min_idx = GetMin(Head);
    int max_idx = GetMax(Head);

    if (min_idx > max_idx) {
        std::swap(min_idx, max_idx);
    }

    List* second = nullptr;
    List* third = nullptr;

    std::cout << "First list: " << std::endl;
    Print_List(Head);

   
    int idx = 0;
    while (Head != nullptr) {
        if (idx < min_idx) {
            third = Insert_List(third, idx, Head->Data);
        }
        else if (idx > max_idx) {
            third = Insert_List(third, idx - max_idx + min_idx - 1, Head->Data);
        }
        else {
            second = Insert_List(second, idx - min_idx, Head->Data);
        }
        Head = Head->Next;
        ++idx;
    }

    std::cout << "Second list: " << std::endl;
    Print_List(second);
    std::cout << "Third list: " << std::endl;
    Print_List(third);
}

int main() {

    setlocale(0, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    List* Head = nullptr;

    int s;
    for (;;) {
        printf(
            "создать список из 10 элементов (1), добавить элемент (2), удалить "
            "элемент (3)\nпросмотреть список (4), выполнить задачу (5), выход "
            "(6): ");

        cin >> (s);

        switch (s) {
        case 1:Make_List(10, &Head, nullptr);
            break;
        case 2: {
            int idx, element;
            std::cout << "Enter index and value: ";
            std::cin >> idx >> element;
            Head = Insert_List(Head, idx, element);
            break;
        }
        case 3: {
            int idx;
            std::cout << "Enter index: ";
            std::cin >> idx;
            Head = Delete_List(Head, idx);
            break;
        }
        case 4: {
            Print_List(Head);
            break;
        }
        case 5:task(Head);
            break;
        case 6:exit(0);
            break;
        default:printf("Incorrect command");
            break;
        }
    }
    return 0;
}
