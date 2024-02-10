#include "src/My_container.h"
#include <iostream>
#include <map>
#include <vector>
#include <list>

struct new_srt{
  int a;
  int b;
};
// TODO: Разобратиься почему именно тут не работает gtest
int main(int, char **) {
  std::cout << "Hello, from Homework3!\n";
  
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
  //Вектор с кастомным аллокатором
  std::vector<int, my_allocator<int>> vect;
  vect.push_back(1);
  vect.push_back(2);
  vect.push_back(3);
  vect.push_back(4);
  vect.push_back(5);
  vect.push_back(6);
  vect.push_back(7);


  for (const auto &el : vect) {
    std::cout << el << std::endl;
  }

  std::cout<<"Custom alloc + castom struct"<<std::endl;
  //Вектор с кастомным аллокатором
  std::vector<new_srt, my_allocator<new_srt>> vect3;
  new_srt a = {1,2};
   new_srt a2 = {2,3};
  vect3.push_back(a);
  vect3.push_back(a2);


  for (const auto &el : vect3) {
    std::cout << el.a << std::endl;
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
 std::cout<<"list"<<std::endl;
 std::list<int,my_allocator<int>> list;
 list.push_back(1);
 list.push_back(2);
 list.push_back(3);
 list.push_back(4);
 list.push_back(5);

for (const auto &el : list) {
    std::cout << el << std::endl;
  }

 std::cout<<"My container"<<std::endl;
  My_container<int, my_allocator<int>> container;
  container.push_back(1);
  container.push_back(2);
  container.push_back(3);
  container.push_back(4);
  container.push_back(5);
  container.push_back(6);
  container.push_back(7);
  auto a1 = container.begin();
  auto b1 = container.end();
  while (a1 != b1)
  {
    std::cout<<a1.operator*().element<<std::endl;
  }
  
  for (const auto &el : container) {
    std::cout << el.element <<" - "<<el.element << std::endl;
  }
}
