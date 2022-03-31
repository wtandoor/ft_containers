// Vector implementation
#include <vector>
#include <iostream>

//переменная size увеличивается на 1 после каждого добавления элемента в вектор. переменная Capacity,
//если она < size и не хватает места для добавления еще одного элемента, то она увеличивается в два раза
// при явном обьявлении вектора(capacity) size == capacity; Так происходит потому что в векторе содержиться мусор

#include "Vector.hpp"

int main(){
    ft::vector<int> z;
    ft::vector<int> o(1);
    z.reserve(22);
    std::cout << z.size() << std::endl;

    // std::cout << v.size() << "  " << d.size() << "   " << a.size();

    // std::cout << z.size() << "  " << z.size() << "   " << o.size();
}