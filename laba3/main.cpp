#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "main.h"

int main() {
    setlocale(LC_ALL, "");
    // Тестирование последовательного контейнера
    lContainer<int> A;
    for (int i = 0; i < 10; ++i) {
        A.push_back(i);
    }
    std::cout << "Содержимое последовательного контейнера: ";
    A.print();
    std::cout << "Размер: " << A.size() << std::endl;
    A.erase(2); // Удаление третьего элемента
    A.erase(4); // Удаление пятого элемента
    A.erase(5); // Удаление седьмого элемента
    std::cout << "После удаления: ";
    A.print();
    A.insert(0, 10); // Добавление в начало
    std::cout << "После добавления 10 в начало: ";
    A.print();
    A.insert(3, 20); // Добавление в середину
    std::cout << "После добавления 20 в середину: ";
    A.print();
    A.push_back(30); // Добавление в конец
    std::cout << "После добавления 30 в конец: ";
    A.print();
    std::cout << std::endl;
    // Тестирование двунаправленного списка
    llContainer<int> B;
    for (int i = 0; i < 10; ++i) {
        B.push_back(i);
    }
    std::cout << "Содержимое двунаправленного списка: ";
    B.print();
    std::cout << "Размер: " << B.size() << std::endl;
    B.erase(2); // Удаление третьего элемента
    B.erase(4); // Удаление пятого элемента
    B.erase(5); // Удаление седьмого элемента
    std::cout << "После удаления: ";
    B.print();
    B.insert(0, 10); // Добавление в начало
    std::cout << "После добавления 10 в начало: ";
    B.print();
    B.insert(3, 20); // Добавление в середину
    std::cout << "После добавления 20 в середину: ";
    B.print();
    B.push_back(30); // Добавление в конец
    std::cout << "После добавления 30 в конец: ";
    B.print();  
}
