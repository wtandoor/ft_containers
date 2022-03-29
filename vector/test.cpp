// Vector implementation
#include <vector>
#include <iostream>

//переменная size увеличивается на 1 после каждого добавления элемента в вектор. переменная Capacity,
//если она < size и не хватает места для добавления еще одного элемента, то она увеличивается в два раза
// при явном обьявлении вектора(capacity) size == capacity; Так происходит потому что в векторе содержиться мусор

#include "vector.hpp"

int main(){
    std::vector <int> v(10);
    std::cout << v[12] << std::endl;
    ft::vector<int> l(700);
    l.assign(693, 5);
    std::cout << l[695] << std::endl;
    std::cout << l[4] << l[5] << l[6] << std::endl;
}