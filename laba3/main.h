#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <list>

template <typename T>
class lContainer{
private:
    T* data;
    size_t capacity;
    size_t S;

    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];// Выделяем новую память
        for (size_t i = 0; i < S; ++i) {
            newData[i] = data[i];// Копируем существующие элементы
        }
        delete[] data; // Освобождаем старую память
        data = newData;// Указываем на новую память
        capacity = newCapacity; // Обновляем текущий размер
    }

public:
    lContainer(size_t initialCapacity = 10) //начальная емкость контейнера (по умолчанию 10)
        : capacity(initialCapacity), S(0) {
        data = new T[capacity]; //выделяем память для массива data
    }

    ~lContainer() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (S >= capacity) {
            resize(static_cast<size_t>(capacity * 1.5)); //если не хватает памяти увеличиваем память
        }
        data[S++] = value; //добавляем элемент увеличивая 
    }

    void insert(size_t index, const T& value) {
        if (index > S) throw std::out_of_range("ошибка");
        if (S >= capacity) {
            resize(static_cast<size_t>(capacity * 1.5));
        }
        for (size_t i = S; i > index; --i) {
            data[i] = data[i - 1];//сдвигаем элементы вправо, начиная с конца массива до позиции вставки
        }
        data[index] = value;
        S++;
    }

    void erase(size_t index) {
        if (index >= S) throw std::out_of_range("ошибка");
        for (size_t i = index; i < S - 1; ++i) {
            data[i] = data[i + 1];
        }
        S--;
    }

    size_t size() const {
        return S;
    }

    T& operator[](size_t index) {
        if (index >= S) throw std::out_of_range("ошибка");
        return data[index]; //возвращаем элемент по индексу
    }

    void print() const {
        for (size_t i = 0; i < S; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

template <typename T>
class llContainer {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };
    Node* head; //голова
    Node* tail; //хвостик
    size_t S;

public:
    llContainer() : head(nullptr), tail(nullptr), S(0) {}

    ~llContainer() {
        while (head) {
            Node* temp = head;
            head = head->next; //проходит по всем и скипает
            delete temp;
        }
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (!head) { //если пуст!!
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        S++;
    }

    void insert(size_t index, const T& value) {
        if (index > S) std::cout << "ошибка";
        
        Node* newNode = new Node(value);
        
        if (index == 0) { //Если индекс равен 0, вставляет новый узел в начало списка
            newNode->next = head;
            if (head) head->prev = newNode;
            head = newNode;
            if (!tail) tail = newNode; // Если список был пуст
        } else if (index == S) { //Если индекс равен размеру списка, вызывает push_back
            push_back(value);
            return;
        } else {
            Node* current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            newNode->prev = current->prev;
            newNode->next = current;
            if (current->prev) current->prev->next = newNode;
            current->prev = newNode;
            if (index == 0) head = newNode; // Если вставляем в начало
        }
        
        S++;
    }

    void erase(size_t index) {
        if (index >= S) throw std::out_of_range("ошибка");
        
        Node* current = head;
                for (size_t i = 0; i < index; ++i) {
            current = current->next; //Находит узел по индексу
        }
        
        if (current->prev) current->prev->next = current->next; //Обновляет указатели next и prev у соседних узлов, чтобы исключить текущий узел из списка
        if (current->next) current->next->prev = current->prev;

        if (current == head) head = current->next; // Если удаляем голову
        if (current == tail) tail = current->prev; // Если удаляем хвост

        delete current;
        S--;
    }

    size_t size() const {
        return S;
    }

    T& operator[](size_t index) {
        if (index >= S) std::cout <<"ошибка";
        
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        
        return current->data;
    }

    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next; //Проходит по всем узлам, начиная с head, и выводит их данные
        }
        std::cout << std::endl;
    }
};

 //однонапрвленный
template <typename T>
class LIterator {
private:
    typename std::vector<T>::iterator it;
public:
    // Конструктор принимает итератор std::vector<T>
    LIterator(typename std::vector<T>::iterator iterator) : it(iterator) {}
    T& operator*() {
        return *it;
    }
    // Метод для получения значения
    T& get() {
        return *it;
    }
    LIterator& operator++() {
        ++it;
        return *this; //инкремент
    }
    bool operator!=(const LIterator& other) const {
        return it != other.it;
    }//сравнения двух операторов
};

template <typename T>
class LContainer {
private:
    std::vector<T> data;
public:
    LContainer(const std::initializer_list<T>& elements) : data(elements) {}
    LIterator<T> begin() {
        return LIterator<T>(data.begin());
    }
    LIterator<T> end() {
        return LIterator<T>(data.end());
    }
};

//двунаправленный
template <typename T>
class LLIterator {
private:
    typename std::list<T>::iterator it;
public:
    LLIterator(typename std::list<T>::iterator iterator) : it(iterator) {}

    T& operator*() {
        return *it;
    }
    // Метод для получения значения
    T& get() {
        return *it;
    }
    LLIterator& operator++() {
        ++it;
        return *this;
    }
    LLIterator& operator--() {
        --it;
        return *this;//декреМЕНТ
    }
    bool operator!=(const LLIterator& other) const {
        return it != other.it;
    }
};

template <typename T>
class LLContainer {
private:
    std::list<T> data;
public:
    /// @brief 
    /// @param elements 
    LLContainer(const std::initializer_list<T>& elements) : data(elements) {}
    LLIterator<T> begin() {
        return LLIterator<T>(data.begin());
    }
    LLIterator<T> end() {
        return LLIterator<T>(data.end());
    }
};