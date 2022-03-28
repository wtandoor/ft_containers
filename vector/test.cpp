// Vector implementation
#include <vector>
#include <iostream>

//переменная size увеличивается на 1 после каждого добавления элемента в вектор. переменная Capacity,
//если она < size и не хватает места для добавления еще одного элемента, то она увеличивается в два раза
// при явном обьявлении вектора(capacity) size == capacity; Так происходит потому что в векторе содержиться мусор

#include "vector.hpp"

int main(){
    std::vector <float> v(10);
    std::cout << v[12] << std::endl;
    ft::vector<int> l(1);
    std::cout << l[3] << std::endl;
}