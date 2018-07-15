#pragma once
#include <iostream>

template <typename T>
void print(T ele){
  std::cout << ele << std::endl;
}

template <typename T, typename... Args>
void print(T ele, Args... args){
  std::cout << ele << ", ";
  print(args...);
}
void output(int);
