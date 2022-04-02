// Vector implementation
#include <vector>
#include <iostream>

//переменная size увеличивается на 1 после каждого добавления элемента в вектор. переменная Capacity,
//если она < size и не хватает места для добавления еще одного элемента, то она увеличивается в два раза
// при явном обьявлении вектора(capacity) size == capacity; Так происходит потому что в векторе содержиться мусор

#include "Vector.hpp"

int main(){
    ft::vector<int>  v(19);

    std::cout << v.at(22) << std::endl;
    std::cout << v.size() <<std::endl;
    std::cout << v.capacity() << std::endl;

    // std::cout << v.size() << "  " << d.size() << "   " << a.size();

    // std::cout << z.size() << "  " << z.size() << "   " << o.size();
}