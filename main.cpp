#include "src/My_container.h"
#include <iostream>
#include <map>
#include <vector>

// TODO: Разобратиься почему именно тут не работает gtest
int main(int, char **) {
  std::cout << "Hello, from Homework3!\n";
  My_container<int, my_allocator<int>> container;
  // Вектор с дефолтным аллокатором
  std::vector<int> first;
  first.push_back(1);
  first.push_back(2);
  first.push_back(3);
  first.push_back(4);
  first.push_back(5);
  first.push_back(6);
  first.push_back(7);
  first.push_back(8);
  first.push_back(9);

  for (const auto &el : first) {
    std::cout << el << std::endl;
  }
  std::cout << "vector with custom allocator" << std::endl;
  // Вектор с кастомным аллокатором
  std::vector<int, my_allocator<int>> vect;
  vect.push_back(1);
  vect.push_back(2);
  vect.push_back(3);
  vect.push_back(4);
  vect.push_back(5);
  vect.push_back(6);
  vect.push_back(7);
  vect.push_back(8);
  vect.push_back(9);
  vect.push_back(10);
  vect.push_back(11);
  vect.push_back(12);
  vect.push_back(13);

  for (const auto &el : vect) {
    std::cout << el << std::endl;
  }

  std::map<int, int> default_map = {{1, 1},  {2, 4},  {3, 9},  {4, 16}, {5, 25},
                                    {6, 36}, {7, 49}, {8, 64}, {9, 81}};
  std::map<int, int, std::less<int>, my_allocator<std::pair<int, int>>> map = {
      {1, 1},  {2, 4},  {3, 9},  {4, 16}, {5, 25},
      {6, 36}, {7, 49}, {8, 64}, {9, 81}};
  std::cout << "map with default allocator" << std::endl;
  for (const auto &el : default_map) {
    std::cout << el.first <<" - "<<el.second << std::endl;
  }
  std::cout << "map with custom allocator" << std::endl;
  for (const auto &el : map) {
    std::cout << el.first <<" - "<<el.second << std::endl;
  }
}
