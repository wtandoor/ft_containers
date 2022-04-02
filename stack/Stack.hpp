#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <vector>

namespace ft{
    template<class T, class Container = std::vector<T> > // T - тип данных для сохранения в стеке, 
                                                        //Container - тип базового контейнера 
                                                        //используемого для реализации стека, по умолчанию deque<T> 
        class stack{
            public:
                typedef T value_type; //Тип, представляющий тип объекта, который хранится в виде элемента в stack.
                typedef Container container_type; // Тип, предоставляющий базовый контейнер для принятия stack
                typedef typename Container::size_type size_type; //Целочисленный Typedef без знака, который может представлять число элементов в stack.
                typedef value_type & reference;// Ссылка на T value_type
                typedef const value_type& const_reference; // const Ссылка на T value_type
            protected:
                container_type _container; //container на основе которого мы реализуем метод стек, в следствие чего выполняем все операции с ним.
            public:
                explicit stack(const container_type& cont = container_type()):_container(cont){

                };

                stack(const stack & other) : _container(other._container){ // Создание обьекта с помощью другого стека

                };

                stack & operator=(const stack & other){ //перегрузка оператора = возвращает текущий обьекта
                    _container = other._container;
                    return (*this);
                };

                bool empty() const{ //Проверяет, является ли stack пустым.
                    return (_container.empty());
                };

                size_type size() const{ //Возвращает количество элементов в контейнере stack.
                    return (_container.size());
                };

                value_type & top(){ //Возвращает ссылку на элемент в верхней части stack.
                    return (_container.back());
                };

                const value_type& top() const { //Возвращает ссылку на элемент в верхней части stack.
                    return (_container.back());
                };
                
                void push(const value_type& val){ //Добавляет элемент в верхнюю часть stack.
                    _container.push_back(val);
                };

                void pop(){ //Удаляет элемент из верхней части stack.
                    _container.pop_back();
                };
                // перегрузка операторов сравнения
                template <class A, class B>
                    friend bool operator==(const stack<A,B> &lhs, const stack<A,B> &rhs){
                        return (lhs._container == rhs._container);
                    }
                
                template <class A, class B>
                    friend bool operator!=(const stack<A,B> &lhs, const stack<A,B>&rhs){
                        return (lhs._container != rhs._container);
                    }
                
                template <class A, class B>
                    friend bool operator>(const stack<A,B> &lhs, const stack<A, B> &rhs){
                        return (lhs._container > rhs._container);
                    }

                template <class A, class B>
                    friend bool operator<(const stack<A,B> &lhs, const stack<A, B> &rhs){
                        return (lhs._container < rhs._container);
                    }

                template <class A, class B>
                    friend bool operator<=(const stack<A,B> &lhs, const stack<A, B> &rhs){
                        return (lhs._container <= rhs._container);
                    }

                template <class A, class B>
                    friend bool operator>=(const stack<A,B> &lhs, const stack<A, B> &rhs){
                        return (lhs._container >= rhs._container);
                    }   
        };
}

#endif