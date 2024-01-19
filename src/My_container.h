#pragma once

#include <iterator>
#include <assert.h>

void print(std::string str){
    std::cout<<str<<std::endl;
}


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
// TODO: Написать реализациб методов итратора
/// @brief Итератор для класса My_container
/// @tparam T
template <typename T>
class iter : public std::iterator<std::input_iterator_tag, T>
{
private:
    T *data;

public:
    iter(T *arg)
    {
        this->data = arg;
    };

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

    bool operator !=(const iter<T> *iter){
        if(!this==iter) return true;
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

    T& operator *(){
        return *(this->data->element);
    }
};
// TODO: Сделать реализацию методов аллокатора
/// @brief Аллокатор для контейнера
/// @tparam T
template <typename T>
class my_allocator
{
private:
    T /* data */;

    void check_assert(){
        auto a = !std::is_same<T,void>();
        print("Аллокатор параметризован типом void ");
        assert(a);
    }
    void create()
    {
    }
    void allocate()
    {
    }
    void deallocate()
    {
    }
    void free()
    {
    }
    void destroy()
    {
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

    iterator begin()
    {
        return iterator(first_element);
    }

    const_iterator cbegin()
    {
        return const_iterator(first_element);
    }

    iterator end()
    {
        return iterator(nullptr);
    }

    const_iterator cend()
    {
        return const_iterator(nullptr);
    }
};
