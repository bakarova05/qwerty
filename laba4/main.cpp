#include <iostream>
#include <map>
#include <memory>
#include <cmath>
#include "main.h"

int main() {
    setlocale(LC_ALL, "");

    std::map<int, int> A;//Создание std::map<int, int>
    for (int i = 0; i < 10; ++i) {//Заполнение факториалами
        A[i] = factorial(i);
    }


    std::map<int, int, std::less<int>, LimitedAllocator<std::pair<const int, int>>> B;//Создание std::map<int, int> с ограниченным аллокатором
    for (int i = 0; i < 10; ++i) {//Заполнение факториалами
        B[i] = factorial(i);
    }


   
    std::cout << "A:\n";
    for (const auto& [key, value] : A) {
        std::cout << key << " " << value << "\n";
    }
    std::cout << "B:\n";
    for (const auto& [key, value] : B) {
        std::cout << key << " " << value << "\n";
    }


    
    MyContainer<int> ContA;//Создание своего контейнера
    for (int i = 0; i < 10; ++i) {
        ContA.add(i);
    }
    MyContainer<int, LimitedAllocator<int>> ContB; //Создание  контейнера с ограниченным аллокатором
    for (int i = 0; i < 10; ++i) {
        ContB.add(i);
    }



    std::cout << "Контейнер :\n";
    ContA.iterate();
    std::cout << "Контейнер с огр аллокатором:\n";
    ContB.iterate();
    return 0;
}
