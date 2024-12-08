#include <iostream>
#include <map>
#include <memory>
#include <cmath>

// Пользовательский аллокатор, ограниченный 10 элементами
template <typename T>
class LimitedAllocator {
public:
    using value_type = T;
    LimitedAllocator(size_t max_elements = 10) : max_elements(max_elements), allocated_elements(0) {}
    T* allocate(std::size_t n) { //метод allocate выделяет память для n обьектов 
        if (allocated_elements + n > max_elements) {
            throw std::bad_alloc();
        }
        T* t = static_cast<T*>(::operator new(n * sizeof(T)));
        allocated_elements += n;
        return t;
    }
    void deallocate(T* t, std::size_t n) {
        ::operator delete(t);
        allocated_elements -= n; //освобождаем паямть для выделенных n элементов
    }
    template <typename U, typename... Args>
    void construct(U* t, Args&&... args) {
        new (t) U(std::forward<Args>(args)...); //создаем обьект типа U на уже выделенной памяти используя конструктор
    }
    template <typename U>
    void destroy(U* t) {
        t->~U();
    }
private:
    size_t max_elements;
    size_t allocated_elements;
};
// Функция для вычисления факториала
int factorial(int i) {
    if (i==0) return 1;
    else return i*factorial(i-1);
}

// Пользовательский контейнер (упрощенная версия для хранения int)
template <typename T, typename Allocator = std::allocator<T>>
class MyContainer {
private:
    T* data;
    size_t capacity;
    size_t count;
    Allocator allocator;
public:
    MyContainer(size_t capacity = 10) : capacity(capacity), count(0) {data = allocator.allocate(capacity); }
    void add(const T& value) { //метод добавляет элемент в контейнер
        if (count >= capacity) 
        throw std::out_of_range("Пустой контейнер");
        allocator.construct(&data[count++], value); // Теперь корректно
    }
~MyContainer() {
    for (size_t i = 0; i < count; i++) {
        allocator.destroy(&data[i]); 
    }
    allocator.deallocate(data, capacity); //освобождаем память 
}
    size_t size() const { return count; } //количество элементов
    bool empty() const { return count == 0; } //пустой ли контейнер
    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }
    void clear() { // читска , вызываем деструктор для всех элементов , обнуляем счетчик
        for (size_t i = 0; i < count; ++i) {
            allocator.destroy(&data[i]); 
        }
        count = 0;
    }
    // Итератор(пс выводим все элементы)
    void iterate() const {
        for (size_t i = 0; i < count; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << "\n";
    }
};
