#pragma once

#include<iterator>
/// @brief Итератор для класса My_container 
/// @tparam T 
template <typename T>
class iter : public std::iterator<std::input_iterator_tag , T >
{
private:
    T /* data */;

public:
    iter(T /* args */);
};

/// @brief Аллокатор для контейнера 
/// @tparam T 
template <typename T>
class my_allocator
{
private:
    T /* data */;

public:
    my_allocator(T /* args */);
};


/// @brief Класс кастомного контейнера
/// @tparam T параметр класса в котором бубет храниться элемент
template <typename T>
class My_container
{
private:
    /// @brief Структура для хранения в памяти
    struct single_element
    {
        void *next_element = nullptr;
        T element;
    };

    single_element *first_element = nullptr;
    single_element *this_element = nullptr;

public:
    My_container(int reserved_size){

    };

    My_container() = default;

    int size(){
        return size;
    }

    T at(int a){
        return this->this_element->element;
    }

    bool contain(){
        return false;
    }

    void push_back(T *element){

    }

    void push_front(T *element){

    }
};
