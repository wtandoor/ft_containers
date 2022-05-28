#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include "../utility/utility.hpp"
#include "reverse_iterator.hpp"

namespace ft{
    template <class T, class Allocator = std::allocator<T> >
    class vector{
        template<typename L>class RandomAccessIterator{
            public:
                typedef typename iterator_traits<L*>::value_type value_type;
                typedef typename iterator_traits<L*>::pointer    pointer;
                typedef typename iterator_traits<L*>::reference  reference;
                typedef typename iterator_traits<L*>::difference_type difference_type;
                typedef pointer iterator_type;
                typedef std::random_access_iterator_tag iterator_category;
            private:
                pointer _pointer;
            
            public:
                RandomAccessIterator(): _pointer(){

                };

                RandomAccessIterator(pointer other) : _pointer(other){

                };

                virtual ~RandomAccessIterator(){

                };

                RandomAccessIterator(const RandomAccessIterator<typename remove_const<value_type>::type> & other): _pointer(&(*other)){

                };

                RandomAccessIterator<value_type> & operator=(const RandomAccessIterator<typename remove_const<value_type>::type> & other){
                    _pointer = &(*other);
                    return (*this);
                }

                RandomAccessIterator & operator++(){
                    _pointer++;
                    return (*this);
                }

                RandomAccessIterator  operator++(int){
                    RandomAccessIterator tmp = *this;
                    ++_pointer;
                    return tmp;
                }
                

                RandomAccessIterator & operator--(){
                    _pointer--;
                    return (*this);
                }

                RandomAccessIterator  operator--(int){
                    RandomAccessIterator tmp = *this;
                    _pointer--;
                    return tmp;
                }

                RandomAccessIterator  operator+(const difference_type & other) const{
                    return _pointer + other;
                }

                RandomAccessIterator  operator-(const difference_type & other) const{
                    return _pointer - other;
                }

                RandomAccessIterator & operator+=(const difference_type & other){
                    _pointer = _pointer + other;
                    return (*this);
                }

                RandomAccessIterator & operator-=(const difference_type & other){
                    _pointer = _pointer - other;
                    return *this;
                }

                pointer operator->() const{
                    return _pointer;
                }

                reference operator*()const{
                    return *_pointer;
                }

                reference operator[](difference_type i) const{
                    return *(_pointer + i);
                }
        };
        public:
            template<typename First, typename Second>
            friend bool operator==(const vector::template RandomAccessIterator<First>& lhs, const vector::template RandomAccessIterator<Second>& rhs){
                return &(*lhs) == &(*rhs);
            }
            template<typename First, typename Second>
            friend bool operator!=(const vector::template RandomAccessIterator<First>& lhs, const vector::template RandomAccessIterator<Second>&rhs){
                return &(*lhs) != &(*rhs);
            }
            template<typename First, typename Second>
            friend bool operator<(const vector::template RandomAccessIterator<First>& lhs, const vector::template RandomAccessIterator<Second>&rhs){
                return &(*lhs) < &(*rhs);
            }
            template<typename First, typename Second>
            friend bool operator>(const vector::template RandomAccessIterator<First>& lhs, const vector::template RandomAccessIterator<Second>&rhs){
                return &(*lhs) > &(*rhs);
            }
            template<typename First, typename Second>
            friend bool operator<=(const vector::template RandomAccessIterator<First>& lhs, const vector::template RandomAccessIterator<Second>&rhs){
                return &(*lhs) <= &(*rhs);
            }
            template<typename First, typename Second>
            friend bool operator>=(const vector::template RandomAccessIterator<First>& lhs, const vector::template RandomAccessIterator<Second>&rhs){
                return &(*lhs) >= &(*rhs);
            }
            template<typename First, typename Second>
            friend typename vector::template RandomAccessIterator<First>::difference_type operator-(const vector::template RandomAccessIterator<First> &lhs, const vector::template RandomAccessIterator<Second>&rhs){
                return &(*lhs) - &(*rhs);
            }
            template<typename First, typename Second>
            friend typename vector::template RandomAccessIterator<First>::difference_type operator+(const vector::template RandomAccessIterator<First> &lhs, const vector::template RandomAccessIterator<Second>&rhs){
                return &(*lhs) + &(*rhs);
            }
            template<typename G>
            friend vector::template RandomAccessIterator<G> operator+(const typename vector::template RandomAccessIterator<G>::difference_type & lhs, const typename vector::template RandomAccessIterator<G> & rhs){
                return lhs+rhs;
            }
            template<typename G>
            friend vector::template RandomAccessIterator<G> operator-(const typename vector::template RandomAccessIterator<T>::difference_type & lhs, const typename vector::template RandomAccessIterator<G> & rhs){
                return lhs-rhs;
            }
        public:
            typedef T value_type;
            typedef Allocator allocator_type;
            typedef std::size_t size_type;
            typedef std::ptrdiff_t difference_type;
            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef typename Allocator::pointer pointer;
            typedef typename Allocator::const_pointer const_pointer;
            typedef RandomAccessIterator<value_type> iterator;
            typedef RandomAccessIterator<const value_type> const_iterator;
            typedef reverse_iterator<const_iterator> const_reverse_iterator;
            typedef reverse_iterator<iterator> reverse_iterator;
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
            explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _capacity(n), allocator(alloc) {
                first = allocator.allocate(n);
                for(size_type i = 0; i < n; i++)
                    allocator.construct(first + i, val); //заполняем каждый элемент вектора дефолтным значением.(0, "")
            };
//copy constructor
            vector(const vector& right):_size(0), _capacity(0) {
                *this = right;
            };
// добавить конструктор, который будет принимать на вход ренж итераторов
            template<class InputIter>
            vector(InputIter input1, InputIter second, const allocator_type & alloc = allocator_type(), typename enable_if<!is_integral<InputIter>::value>::type* = 0): allocator(alloc){
                if (input1 > second)
                    throw std::length_error("vector");
                _size = second - input1;
                _capacity = _size;
                first = allocator.allocate(_capacity);
                for(difference_type i = 0; i < static_cast<difference_type>(_size); i++){
                    allocator.construct(first + i, *(input1 + i));
                }
            }
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
            iterator begin(){ //итератор на первый элемент
                return (iterator(first));
            };
            const_iterator begin() const { // конст на первый
                return(const_iterator(first));
            };
            iterator end(){ // на последний 
                return(iterator(first + _size));
            };

            const_iterator end() const { // конст на последний 
                return(const_iterator(first + _size));
            };

            reverse_iterator rbegin(){ //итератор в обратную сторону на конец
                return (reverse_iterator(end()));
            };

            const_reverse_iterator rbegin() const { // конст -"-
                return (const_reverse_iterator(end()));
            };

            reverse_iterator rend(){ //итератор на начало 
                return (reverse_iterator(begin()));
            };

            const_reverse_iterator rend() const {//конст итератор на начало
                return (const_reverse_iterator(begin()));
            };
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
                return (_capacity);
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
                    for(size_type i = 0; i < _size; i++)
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
                            this->reserve(resize_size);
                    }
                    for (size_type i = this->_size; i < resize_size; i++){
                        allocator.construct(first + i, value);
                        this->_size++;
                    }
                }
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

            void swap (vector &x){
                if (this != &x){
                    std::swap(first, x.first);
                    std::swap(_size, x._size);
                    std::swap(_capacity, x._capacity);
                    std::swap(allocator, x.allocator);
                }
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

            template<class inputIter>
            void assign(inputIter first1, inputIter second, typename enable_if<!is_integral<inputIter>::value>::type* = 0){
                if (first1 > second)
                    throw std::logic_error("vector");
                difference_type count = second - first1;
                clear();
                if (count > static_cast<difference_type>(capacity())){
                    allocator.deallocate(first, _capacity);
                    first = allocator.allocate(count);
                    _capacity = count;
                }
                iterator pos = begin();
                while (first1 < second){
                    allocator.construct(&(*pos), *first1);
                    pos++;
                    first1++;
                }
                _size = count;
            }


            void assign (size_type assign_size, const value_type &value){
                clear();
                if (assign_size > _capacity){
                    allocator.deallocate(first, _capacity);
                    first = allocator.allocate(assign_size);
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

            iterator data(){
                if (_size != 0)
                    return begin();
                return (begin());
            }

            template<class Input>
            void insert(iterator position, Input start, Input last, typename enable_if<!is_integral<Input>::value>::type* = 0){
                if (position < begin() || position > end() || start > last)
                    throw std::logic_error("vector");
                size_t distance = static_cast<size_t>(position - begin());
                size_t countElements = static_cast<size_t>(last - start);
                if (_size + countElements > _capacity){
                    size_t capacity1 = _capacity * 2 >= _size + countElements ? _capacity * 2 : _size + countElements;
                    pointer newArr = allocator.allocate(capacity1);
                    std::uninitialized_copy(begin(), position, iterator(newArr));
                    try{
                        for (size_t i = 0; i < countElements; start++, i++)
                            allocator.construct(newArr + distance + i, *start);
                    } catch (...){
                        for (size_t i = 0; i < countElements + distance; ++i)
                            allocator.destroy(newArr + i);
                        allocator.deallocate(newArr, capacity1);
                        throw;
                    }
                    std::uninitialized_copy(position, end(), iterator(newArr + distance + countElements));
                    for (size_t i = 0; i < _size; i++)
                        allocator.destroy(first + i);
                    allocator.deallocate(first, _capacity);
                    _size += countElements;
                    _capacity = capacity1;
                    first = newArr;
                } else {
                    for (size_t i = _size; i > static_cast<size_t>(distance); i--){
                        allocator.destroy(first + i + countElements - 1);
                        allocator.construct(first + i + countElements - 1, *(first + i - 1));
                    }
                    for (size_t i = 0; i <static_cast<size_t>(countElements); i++, start++){
                        allocator.destroy(first + i + countElements);
                        allocator.construct(first + distance + i, *start);
                    }
                    _size += countElements;
                }
            };

            //добавление одного элемента на определенное место
            iterator insert(iterator position, const value_type& val){
                if (position < begin() || position > end())
                    throw std::logic_error("vector");
                difference_type distance = position - begin();
                if (_size == _capacity){
                    if (_capacity == 0){
                        _capacity = 1;
                    } else {
                        _capacity = _capacity * 2;
                    }
                    pointer newArr = allocator.allocate(_capacity);
                    std::uninitialized_copy(begin(), position, iterator(newArr));
                    allocator.construct(newArr + distance, val);
                    std::uninitialized_copy(position, end(), iterator(newArr + distance + 1));
                    for (size_t i = 0; i < _size; i++){
                        allocator.destroy(first + i);
                    }
                    allocator.deallocate(first, _size);
                    _size++;
                    first = newArr;
                } else {
                    for(size_type i = _size - 1; i > static_cast<size_type>(distance); i--){
                        allocator.destroy(first + i);
                        allocator.construct(first + i, *(first + i - 1));
                    }
                    allocator.destroy(&(*position));
                    allocator.construct(&(*position), val);
                    _size++;
                }
                return (begin() + distance);
            };
            //вставка n элементов val на определенное место
            void insert(iterator position, size_type n, const value_type& val){
                if (n == 0)
                    return;
                else if (max_size() - _size < n){
                    throw std::length_error("vector");
                }
                difference_type distance = position - begin();
                if (_size + n > _capacity){
                    size_type newCap = _capacity * 2 >= _size + n ? _capacity * 2 : _size + n;
                    pointer newArr = allocator.allocate(newCap);
                    std::uninitialized_copy(begin(), position, iterator(newArr));
                    for(size_type i = 0; i < n; i++){
                        allocator.construct(newArr + distance + i, val);
                    }
                    std::uninitialized_copy(position, end(), iterator(newArr + distance + n));
                    for(size_type i = 0; i < _size; i++){
                        allocator.destroy(first + i);
                    }
                    allocator.deallocate(first, _capacity);
                    _size += n;
                    _capacity = newCap;
                    first = newArr;
                }
                else{
                    for (size_type i = _size; i > static_cast<size_type>(distance); i--){
                        allocator.destroy(first + i + n - 1);
                        allocator.construct(first + i + n - 1, *(first + i - 1));
                    }
                    for (size_type i = 0; i < n; i++){
                        allocator.destroy(first + i + distance);
                        allocator.construct(first + i + distance, val);
                    }
                    _size += n;
                }
            }

            iterator erase(iterator position){
                // if (position > end() || position < begin())
                //     return;
                size_type distance = position - begin();
                for (size_type i = distance; i < _size - 1; ++i){
                    allocator.destroy(first + i);
                    allocator.construct(first + i, *(first + i + 1));
                }
                _size--;
                allocator.destroy(first + _size - 1);
                return iterator(first + distance);
            }

            iterator erase(iterator _first, iterator _last) {
                difference_type start = std::distance(begin(), _first);
                difference_type copy = std::distance(_last, end());
                bool lastEnd = (_last == end());
                while (_first != _last){
                    allocator.destroy(&(*_first));
                    _first++;
                }
                size_type i = start;
                while(_last < end()){
                    if (this->first + start)
                        allocator.destroy(first + i);
                    allocator.construct(first + i, *_last);
                    i++;
                    _last++;
                }
                for (size_type i = start + copy; i < _size; i++)
                    allocator.destroy(first + i);
                _size = start + copy;
                if (lastEnd == true)
                    return end();
                else
                    return iterator(first + start);
            }
    };

//||-------------------------------------"end scope"-------------------------------------||

//||-------------------------------------"completed"-------------------------------------||
/// Non-member function overload
    typedef std::size_t size_type ;
    template <class T, class Alloc>
    bool operator==(const vector<T, Alloc>&lhs, const vector<T, Alloc>& rhs){
        if (lhs.size() != rhs.size())
            return (false);
        for (size_t i = 0; i < rhs.size(); i++){
            if (lhs[i] != rhs[i])
                return false;
        }
        return (true);
    }
    template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc>&lhs, const vector<T, Alloc>&rhs){
        return (!(lhs == rhs));
    }
    template <class T, class Alloc>
    bool operator<(const vector<T, Alloc>&lhs, const vector<T, Alloc>&rhs){ //realize lexicgraphicCompare
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template <class T, class Alloc>
    bool operator>(const vector<T, Alloc>&lhs, const vector<T, Alloc>&rhs){
        return (rhs < lhs);
    }
    template <class T, class Alloc>
    bool operator>=(const vector<T, Alloc>&lhs, const vector<T, Alloc>&rhs){
        return (!(lhs < rhs));
    }
    template <class T, class Alloc>
    bool operator<=(const vector<T, Alloc>&lhs, const vector<T, Alloc>&rhs){
        return (!(rhs < lhs));
    }
    
};
//||-------------------------------------"end scope"-------------------------------------||
namespace std{
template <class T, class Alloc>
    void swap(ft::vector<T, Alloc>&lhs, ft::vector<T, Alloc>&rhs){
        lhs.swap(rhs);
    };
}

#endif
