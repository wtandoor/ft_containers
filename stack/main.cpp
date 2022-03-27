#include <iostream>
#include "Stack.hpp"

int main(){
    ft::stack<std::string> name1;
    name1.push("qq");
    name1.push("qq");
    name1.push("qq");
    name1.push("wer");
    name1.push("ww");

    std::cout << "Count of elements in stack " << name1.size() << std::endl;
    std::cout << "Stack is empty ? - " << name1.empty() << std::endl;

    std::cout << "Last added element in ft::stack " << name1.top() << std::endl;
    std::cout << "Delete this element in ft::stack " << std::endl;

    name1.pop();

    std::cout << "New last added element in ft::stack, after removing " << name1.top() << std::endl;
    return (0);
}