#include <iostream>
#include"src/My_container.h"
#include <vector>
// TODO: Разобратиься почему именно тут не работает gtest
int main(int, char**){
    std::cout << "Hello, from Homework3!\n";
    My_container<int> container;
    std::vector <int> first;
    auto a = first.begin();
}
