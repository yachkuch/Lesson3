#pragma once

#include <assert.h>
#include <iterator>
#include <memory>
#include <iostream>

void print(std::string str) { std::cout << str << std::endl; }

struct deleter
{
    void operator()(void *ptr) { ::operator delete(ptr); }
};

// Опробовал перегрузку оператора new
// void * operator new(std::size_t sz){
//     std::cout<<"Мой оператор new"<<std::endl;
// }

struct Exception_go_out_of_memory
{
    std::string ex = "go_out_of_memory";
};

/// @brief Структура для хранения в памяти
template <typename T>
struct single_element
{
    void *next_element = nullptr;
    T *element;
};
/// @brief Итератор для класса My_container
/// @tparam T
template <typename T>
class iter : public std::iterator<std::input_iterator_tag, T>
{
private:
    T *data;

public:
    iter(T *arg) { this->data = arg; };

    bool operator==(const iter<T> *iter)
    {
        if (this->data->element == iter->data)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator!=(const iter<T> *iter)
    {
        if (!this == iter)
            return true;
        return false;
    }

    iter *operator+()
    {
        if (data->next_element != nullptr)
        {
            this->data = (T *)data->next_element;
            return this;
        }
        else
        {
            throw std::exception();
            return this;
        }
    }

    T &operator*() { return *(this->data->element); }
};
/// @brief Аллокатор для контейнера
/// @tparam T
template <class T /*,int size = 1000*/>
class my_allocator
{
private:
    constexpr static int poolSize = 20;
    
    int number_allocate_elements = 0;

    void check_assert()
    {
        auto a = !std::is_same<T, void>();
        print("allocate paromitrase void ");
        assert(a);
    }

public:
    std::shared_ptr<void> pool;
    using value_type = T;

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap =
        std::true_type; // UB if std::false_type and a1 != a2;

    my_allocator() noexcept : pool(new(std::nothrow) T[poolSize])
    {
        check_assert();
    };

    template <class U>
    my_allocator(const my_allocator<U> &alloc) noexcept
    {
        pool = alloc.pool;
    }

    my_allocator<T> select_on_container_copy_construction() const
    {
        std::cout << "select_on_container_copy_construction()" << std::endl;
        return my_allocator<T>();
    }
    T *allocate(std::size_t n)
    {       
        if((number_allocate_elements+n) > poolSize) std::bad_alloc;     
        if (n <= poolSize)
        {
            auto buff = number_allocate_elements;
            number_allocate_elements+=n;
            return (static_cast<T *>(pool.get()) + buff);
            }
        else
        {
            std::bad_alloc();
        }
    }
    void deallocate(T *p, std::size_t n) { ::operator delete(p); }

    template <typename U>
    struct rebind
    {
        typedef class my_allocator<U> other;
    };
};

template <class T, class U>
constexpr bool operator==(const my_allocator<T> &a1,
                          const my_allocator<U> &a2) noexcept
{
    return a1.pool == a2.pool;
}

template <class T, class U>
constexpr bool operator!=(const my_allocator<T> &a1,
                          const my_allocator<U> &a2) noexcept
{
    return a1.pool != a2.pool;
}

/// @brief Класс кастомного контейнера
/// @tparam T параметр класса в котором бубет храниться элемент
template <typename T, typename allocat = std::allocator<T>>
class My_container
{
private:
    single_element<T> *first_element = nullptr;
    single_element<T> *this_element = nullptr;
    single_element<T> *last_element = nullptr;

    using iterator = iter<single_element<T>>;
    using const_iterator = iter<const single_element<T>>;
    using allocator = allocat;

    //! Текущий размер
    std::size_t size = 0;
    std::size_t capcity = 0; // Сколько памяти отсалось зарезервированной

public:
    My_container(int reserved_size){

    };

    My_container() = default;

    int size_() { return this->size; }

    T at(int a) { return this->this_element->element; }
    // TODO: Доделать реализацию пуш бэка и все готово
    void push_back(const T *element) {
        typename allocat::template rebind<single_element<T>>::other nodeAlloc;
        single_element<T>* newNode = nodeAlloc.allocate(1);
    }

    iterator begin() { return iterator(first_element); }

    const_iterator cbegin() { return const_iterator(first_element); }

    iterator end() { return iterator(last_element); }

    const_iterator cend() { return const_iterator(last_element); }
};
