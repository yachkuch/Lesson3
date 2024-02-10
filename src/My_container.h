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
    T element;
    
    single_element(T _val) : element(_val), next_element(nullptr){}
    bool operator != (const  single_element & val ){
        if((this->element == val.element) && (this->next_element == val.next_element)) return true;
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
        if (this->data->element == iter->data)
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
        if (!(this == &iter))
            return true;
        return false;
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
            throw std::exception();
            return this;
        }
    }

    T operator*() {
        auto val = this->data;
         return *val; }
};





/// @brief Аллокатор для контейнера
/// @tparam T
template <class T ,std::size_t size = 1000>
class my_allocator
{
private:
    constexpr static int poolSize = size;
    
    int number_allocate_elements = 0;

    void check_assert()
    {
        auto a = !std::is_same<T, void>();
        print("allocate paromitrase void ");
        assert(a);
    }

public:
    //std::shared_ptr<void> pool;
    void *pool;
    using value_type = T;

    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap =
        std::true_type; // UB if std::false_type and a1 != a2;

    my_allocator() noexcept : pool(::operator new(sizeof(T)*poolSize))
    {
        check_assert();
    };

    template <class U,std::size_t M>
    my_allocator(const my_allocator<U,M> &alloc) noexcept
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
        if((number_allocate_elements+n) > poolSize) std::bad_alloc();     
        if (n <= poolSize)
        {
            auto buff = number_allocate_elements;
            number_allocate_elements+=n;
            return static_cast<T *>(pool + buff*sizeof(T));
            }
        else
        {
            std::bad_alloc();
        }
    }
    void deallocate(T *p, std::size_t n) { number_allocate_elements = 0; }

    // template <class Up, class... Args>
    // void construct(Up* p, Args&&... args) {
    //     ::new ((void*)p) Up(std::forward<Args>(args)...);
    // }

    // void destroy(pointer p) {
    //     p->~T();
    // }

    template<typename U>
    struct rebind {
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
    My_container(int reserved_size) :alloc(allocat()){

    };

    My_container() = default;

    int size_() { return this->size; }

    T at(int a) { return this->this_element->element; }
    // TODO: Доделать реализацию пуш бэка и все готово
    void push_back(const T &element) {
        // WARNING: Не очень понимаю данную строчку
        // typename allocat::template rebind<single_element<T>>::other nodeAlloc;
        //single_element<T> * newNode = nodeAlloc.allocate(1);
         T* newData = std::allocator_traits<T>::allocate(alloc, 1);
        if(first_element == nullptr){
           // first_element = newNode;
        }
       // this_element->next_element = newNode;
       // this_element = newNode;
       // std::allocator_traits<T>::construct(alloc, newNode, element);
    }

    iterator begin() { return iterator(first_element); }

    const_iterator cbegin() { return const_iterator(first_element); }

    iterator end() { return iterator(last_element); }

    const_iterator cend() { return const_iterator(last_element); }
};
