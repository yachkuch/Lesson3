#pragma once

#include <iterator>

/// @brief Структура для хранения в памяти
template<typename T>
struct single_element
{
    void *next_element = nullptr;
    T *element;
};
// TODO: Написать реализациб методов итратора
/// @brief Итератор для класса My_container
/// @tparam T
template <typename T>
class iter : public std::iterator<std::input_iterator_tag, T>
{
private:
    //friend class My_container;

        T /* data */;

public:
    iter(T /* args */);
};
// TODO: Сделать реализацию методов аллокатора
/// @brief Аллокатор для контейнера
/// @tparam T
template <typename T>
class my_allocator
{
private:
    T /* data */;

    // void check_assert(){
    //     static_assert(!std::is_same<T,void>,"Type allocator cant be void \n");
    // }
    void create(){

    }
    void allocate(){

    }
    void deallocate(){

    }
    void free(){

    }
    void destroy(){

    }

public:
    my_allocator(T /* args */);
};

/// @brief Класс кастомного контейнера
/// @tparam T параметр класса в котором бубет храниться элемент
template <typename T>
class My_container
{
private:
    single_element<T> *first_element = nullptr;
    single_element<T> *this_element = nullptr;

    using iterator = iter<single_element<T>>;
    using const_iterator = iter<const single_element<T>>;
    using allocator = my_allocator<single_element<T>>;

public:
    My_container(int reserved_size){

    };

    My_container() = default;

    int size()
    {
        return size;
    }

    T at(int a)
    {
        return this->this_element->element;
    }

    bool contain()
    {
        return false;
    }

    void push_back(T *element)
    {
    }

    void push_front(T *element)
    {
    }
};
