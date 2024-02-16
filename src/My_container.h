#pragma once

#include <assert.h>
#include <iostream>
#include <iterator>
#include <memory>
#include <array>

#define UNUSED(expr) do { (void)(expr); } while (0)

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
    T element;

    single_element(T _val) : element(_val), next_element(nullptr) {}
    bool operator!=(const single_element &val)
    {
        if ((this->element == val.element) &&
            (this->next_element == val.next_element))
            return false;
        return true;
    }
    bool operator==(const single_element &val)
    {
        if (((this->element == val.element) &&
             (this->next_element == val.next_element)))
            return true;
        return false;
    }
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
        if (this->data == iter->data)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator!=(const iter<T> &iter)
    {
        // if(this->data->next_element == nullptr) return true;
        // if(iter.data->next_element == nullptr) return true;
        if (*(this->data) == *(iter.data))
            return false;
        return true;
    }

    iter *operator++()
    {
        if (data->next_element != nullptr)
        {
            this->data = (T *)data->next_element;
            return this;
        }
        else
        {
            // throw std::exception();
            return this;
        }
    }

    T &operator*()
    {
        auto val = this->data;
        return *val;
    }
};

/// @brief Аллокатор для контейнера
/// @tparam T
template <class T, std::size_t size = 1000>
class my_allocator
{
private:
    constexpr static int poolSize = size;
    void *pool_start = nullptr; //! Хранит в себе адрес на анчало пула 

    int number_allocate_elements = 0;

    void check_assert()
    {
        auto a = !std::is_same<T, void>();
        print("allocate paromitrase void ");
        assert(a);
    }

public:
    // std::shared_ptr<void> pool;
    using value_type = T;
    void *pool = nullptr;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap =
        std::true_type; // UB if std::false_type and a1 != a2;

    my_allocator()
        : pool(::operator new(sizeof(T) * poolSize)){
              // check_assert();
              this->pool_start = pool;
          };

    template <class U, std::size_t M>
    my_allocator(const my_allocator<U, M> &alloc) noexcept
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
        if ((number_allocate_elements + n) > poolSize)
            throw std::bad_alloc();
        if (n <= poolSize)
        {
            auto buff = number_allocate_elements;
            number_allocate_elements += n;
            return reinterpret_cast<T *>(reinterpret_cast<char *>(pool) +
                                         buff * sizeof(T));
        }
        else
        {
            throw std::bad_alloc();
        }
    }
    void deallocate(T *p, std::size_t n)
    {
        UNUSED(p);
        if (number_allocate_elements == 0)
            return;
            if(n<number_allocate_elements){
            number_allocate_elements-=n;
            pool = reinterpret_cast<char*>(pool)-sizeof(T)*n;
            } else{
                number_allocate_elements = 0;
                pool = pool_start;
            }
    }

    template <typename U>
    struct rebind
    {
        typedef my_allocator<U, size> other;
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
template <typename T, typename allocat = std::allocator<single_element<T>>>
class My_container
{
private:
    single_element<T> *first_element = nullptr;
    single_element<T> *this_element = nullptr;
    single_element<T> *last_element = nullptr;

    using iterator = iter<single_element<T>>;
    using const_iterator = iter<const single_element<T>>;
    allocat alloc;

    //! Текущий размер
    std::size_t size = 0;
    std::size_t capcity = 0; // Сколько памяти отсалось зарезервированной

public:
    explicit My_container(int reserved_size)
        : alloc(allocat()){

          };

    My_container() = default;
    ~My_container()
    {
        if(first_element == nullptr) return;
        while (first_element->next_element != nullptr)
        {
          auto* single_el = this->first_element;
        this->first_element = reinterpret_cast<single_element<T> *>( single_el->next_element);
        delete single_el;  
        }
        delete first_element;
        return;
    }

    int size_() { return this->size; }

    T at(int a) { return this->this_element->element; }
    void push_back(const T &elemente)
    {
        typename allocat::template rebind<single_element<T>>::other nodeAlloc;
        auto sin_el =
            std::allocator_traits<decltype(nodeAlloc)>::allocate(nodeAlloc, 1);
        reinterpret_cast<single_element<T> *>(sin_el)->next_element = nullptr;
        if (first_element == nullptr)
        {
            first_element = sin_el;
            std::allocator_traits<allocat>::construct(alloc, &first_element->element,
                                                      elemente);
            this_element = first_element;
        }
        else
        {
            auto previos_el = this_element;
            this_element = sin_el;
            previos_el->next_element = sin_el;

            std::allocator_traits<allocat>::construct(alloc, &this_element->element,
                                                      elemente);
        }
        this->size++;
    }

    iterator begin() { return iterator(first_element); }

    const_iterator cbegin() { return const_iterator(first_element); }

    iterator end() { return iterator(this_element); }

    const_iterator cend() { return const_iterator(this_element); }
};
