#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
// #include "RandomAccessIterator.hpp"

namespace ft{
    template <class T, class Allocator = std::allocator<T> >
    class vector{
        class RandomAccessIterator;
        public:
            typedef T value_type;
            typedef Allocator allocator_type;
            typedef std::size_t size_type;
            typedef std::ptrdiff_t difference_type;
            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef typename Allocator::pointer pointer;
            typedef typename Allocator::const_pointer const_pointer;
            // typedef RandomAccessIterator<value_type> iterator;
            // typedef RandomAccessIterator<const value_type> const_iterator;
            // typedef reverse_iterator<iterator> reverse_iterator;
            // typedef reverse_iterator<const_iterator> const_reverse_iterator;
        private:
            pointer first;// указатель на первый элемент
            size_type _size, _capacity; //размер и емкость
            allocator_type allocator; //обьект для выделения памяти
        public:
//||-------------------------------------"not copleted, constructors"-------------------------------------||
            //default constructor w/o args
            explicit vector(const allocator_type& alloc = allocator_type()) : first(0), _size(0), _capacity(0), allocator(alloc){
            
            };
// добавить конструктор вектора с помощью двух итераторов которые указывают на начало и конец вектора(любой элемент)
            //fill our vector
            explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _capacity(n), allocator(alloc){
                first = allocator.allocate(n);
                for(size_type i = 0; i < n; i++)
                    allocator.construct(first + i, val); //заполняем каждый элемент вектора дефолтным значением.(0, "")
            };
//copy constructor
            vector(const vector& right):_size(0), _capacity(0) {
                (*this) = right;
            };
// добавить конструктор, который будет принимать на вход ренж итераторов
//||-------------------------------------"end scope, constructors"-------------------------------------||
            
//||-------------------------------------"copleted, destructor"-------------------------------------||
            //сначала мы разрушаем каждый обьект который храниться в выделенной нами памяти
            //Освобождает блок памяти, ранее выделенный с помощью allocate и еще не освобожденный.
            //Элементы в массиве не уничтожаются вызовом функции deallocate, поэтому сначала destroy()
            ~vector(){
                for (size_type i = 0; i < _size; i++){
                    allocator.destroy(first + i);
                }
                if (_capacity != 0)
                    allocator.deallocate(first, _capacity);
            };
//||-------------------------------------"end scope, destructors"-------------------------------------||

//||-------------------------------------"copleted, operator="-------------------------------------||
            //перегрузка оператора присваивания
            vector& operator=(const vector& right){
                if (this == &right)
                    return (*this);
                for (size_t i = 0; i < this->_size; i++)
                    allocator.destroy(first + i);
                this->_size = right._size;
                if (this->_capacity < this->_size){
                    if (this->_capacity != 0)
                        this->allocator.deallocate(first, _capacity);
                    this->_capacity = this->_size;
                    this->first = this->allocator.allocate(this->_capacity);
                }
                for (size_type i = 0; i < this->_size; i++)
                    this->allocator.construct(first + i, right[i]);
                return (*this);
            }
//||-------------------------------------"end scope, operator="-------------------------------------||

//||-------------------------------------"copleted, but iterators didn't added"-------------------------------------||
            // Iterator
            // iterator begin(){ //итератор на первый элемент
            //     return (iterator(first));
            // };

            // iterator end(){ // на последний 
            //     return(iterator(first + _size));
            // };

            // const_iterator begin() const { // конст на первый
            //     return(const_iterator(first));
            // };

            // const_iterator end() const { // конст на последний 
            //     return(const_iterator(first + _size));
            // };

            // reverse_iterator rbegin(){ //итератор в обратную сторону на конец
            //     return (reverse_iterator(end()));
            // };

            // const_reverse_iterator rbegin() const { // конст -"-
            //     return (const_reverse_iterator(end()))
            // };

            // reverse_iterator rend(){ //итератор на начало 
            //     return (reverse_iterator(begin()));
            // };

            // const_reverse_iterator rend(){//конст итератор на начало
            //     return (const_reverse_iterator(begin()));
            // };
//||-------------------------------------"end scope"-------------------------------------||

            // work with capacity, size, resize and etc.
//||------------------------------"completed, work with capacity"-------------------------------||

            size_type size() const{
                return (this->_size);
            };

            size_type max_size() const{ //максимально возможный размер выделенной памяти
                return (this->allocator.max_size());
            };

            size_type capacity() const {
                return (this->_capacity);
            };

            bool empty() const{
                return (this->_size == 0);
            };
            //внутренняя функция резерв, позволяет нам зарезервировать
            //указанное в аргументе количество памяти для нашего вектора.
            //создаем поинтер на новый участок памяти и заполняем его нашими элементами, после наших 0.
            //старую память удаляем.
            void reserve(size_type reserve_size){
                if (reserve_size < _capacity)
                    return ;
                pointer newArr = allocator.allocate(reserve_size);
                try{
                    for(size_type i = 0; i < reserve_size; i++)
                        allocator.construct(newArr + i, *(first + i));
                } catch (std::exception &e){
                    size_type i = 0;
                    while (newArr + i != NULL && i < this->_size) {
                        allocator.destroy(newArr + i);
                        i++;
                    }
                    allocator.deallocate(newArr, reserve_size);
                    throw ;
                }
                for (size_type i = 0; i < _size; i++){
                    allocator.destroy(first + i);
                }
                if (_capacity != 0)
                    allocator.deallocate(first, _capacity);
                _capacity = reserve_size;
                first = newArr;
            };


            //функция resize увеличивает или уменьшает аллоцированную память до необходимого нам значения.
            void resize(size_type resize_size, value_type value = value_type()){
                if (resize_size < this->_size){
                    for(size_type i = resize_size; i < this->_size; i++)
                        allocator.destroy(first + i);
                    this->_size = resize_size;
                } else if (resize_size > this->_size){
                    if (this->_capacity < resize_size){
                        if (this->_capacity * 2 > resize_size)
                            this->reserve(_capacity * 2);
                        else
                            this->reserve (resize_size);
                    }
                    for (size_type i = this->_size; i < resize_size; i++){
                        allocator.construct(first + i, value);
                        this->_size++;
                    }
                }
                std::cout << this->_size << " <- new size" << std::endl;
                std::cout << this->_capacity << " <- new capacity" << std::endl;
            };
//||------------------------------"end scope, work with capacity"-------------------------------||

//||------------------------------"completed, elements access"----------------------------------||
            //Элементы доступа без защиты
            reference operator[](size_type i){
                return (*(first + i));
            };
            const_reference operator[](size_type i) const {
                return (*(first + i));
            };
            //Элементы доступа с защитой 
            reference at(size_type i){
                if (i > _capacity){
                    throw std::out_of_range("index out of range");
                }
                return (*(first + i));
            };
            const_reference at(size_type i) const{
                if (i > _capacity){
                    throw std::out_of_range("index out of range");
                }
                return (*(first + i));
            };
            //возвращают ссылку на первый элемент вектора
		    reference front(){
	    		return(*first);
		    };
		    const_reference front() const{
			    return(*first);
		    };
            //возращает ссылку на последний элемент вектора
		    reference back(){
			    return(*(first + _size - 1));
		    };
		    const_reference back() const{
			    return(*(first + _size - 1));
		    };
//nwe
            void swap (vector &x){
                std::swap(first, x.first);
                std::swap(_size, x._size);
                std::swap(_capacity, x._capacity);
                std::swap(allocator, x.allocator);
            };

            void clear(){
                for(size_type i = 0; i < _size; i++){
                    allocator.destroy(first + i);
                }
                _size = 0;
            };

            allocator_type getAllocator() const{
                return (this->allocator);
            };

            void assign (size_type assign_size, const value_type &value){
                clear();
                if (assign_size > _capacity){
                    allocator.deallocate(first, _capacity);
                    first = allocator.allocate(_capacity);
                    _capacity = assign_size;
                }
                for(size_type i = 0; i < assign_size; i++){
                    allocator.construct(first + i, value);
                }
                _size = assign_size;
            };

            void push_back(const value_type& value){
                if (_size == _capacity){
                    if (_capacity == 0)
                        reserve(1);
                    else
                        reserve(_capacity * 2);
                }
                allocator.construct(first + _size, value);
                _size++;
            };

            void pop_back(){
                allocator.destroy(first + _size - 1);
                _size--;
            };

//||-------------------------------------"end scope"-------------------------------------||
    };
}

//||-------------------------------------"completed"-------------------------------------||
/// Non-member function overload
    typedef std::size_t size_type;
    template <typename T, typename Alloc>
    bool operator==(const ft::vector<T, Alloc>&lhs, const ft::vector<T, Alloc>& rhs){
        if (lhs.size() != rhs.size())
            return (false);
        return (equals(lhs.begin(), lhs.end(), rhs.begin()));
    }
    template <typename T, typename Alloc>
    bool operator!=(const ft::vector<T, Alloc>&lhs, const ft::vector<T, Alloc>&rhs){
        return (!(lhs == rhs));
    }
    template <typename T, typename Alloc>
    bool operator<(const ft::vector<T, Alloc>&lhs, const ft::vector<T, Alloc>&rhs){ //realize lexicgraphicCompare
        return (lexicgraphicCompare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template <typename T, typename Alloc>
    bool operator>(const ft::vector<T, Alloc>&lhs, const ft::vector<T, Alloc>&rhs){
        return (rhs < lhs);
    }
    template <typename T, typename Alloc>
    bool operator>=(const ft::vector<T, Alloc>&lhs, const ft::vector<T, Alloc>&rhs){
        return (!(lhs < rhs));
    }
    template <typename T, typename Alloc>
    bool operator<=(const ft::vector<T, Alloc>&lhs, const ft::vector<T, Alloc>&rhs){
        return (!(lhs > rhs));
    }
    template <class T, class Alloc>
    void swap(ft::vector<T, Alloc>&lhs,ft::vector<T, Alloc>&rhs){
        lhs.swap(rhs);
    }
//||-------------------------------------"end scope"-------------------------------------||

#endif