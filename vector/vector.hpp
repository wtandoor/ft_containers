#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include "../utility/utility.hpp"

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
                    return *this;
                }

                RandomAccessIterator & operator++(int){
                    RandomAccessIterator tmp(*this);
                    ++_pointer;
                    return tmp;
                }
                

                RandomAccessIterator & operator--(){
                    _pointer--;
                    return *this;
                }

                RandomAccessIterator & operator--(int){
                    RandomAccessIterator tmp(*this);
                    _pointer--;
                    return tmp;
                }

                RandomAccessIterator & operator+(const difference_type & other) const{
                    return _pointer + other;
                }

                RandomAccessIterator & operator-(const difference_type & other) const{
                    return _pointer - other;
                }

                RandomAccessIterator & operator+=(const difference_type & other){
                    _pointer = _pointer + other;
                    return *this;
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
            template<class Input>
            vector(Input input1, Input second, const allocator_type & alloc = allocator_type(), typename enable_if<!is_integral<Input>::value>::type* = 0): allocator(alloc){
                if (input1 > second)
                    throw std::length_error("vector");
                _size = second - input1;
                _capacity = _size;
                first = allocator.allocate(_capacity);
                for(difference_type i = 0; i < static_cast<difference_type>(_size);i++){
                    allocator.construct(first + i, *(first + i));
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

            iterator end(){ // на последний 
                return(iterator(first + _size));
            };

            const_iterator begin() const { // конст на первый
                return(const_iterator(first));
            };

            const_iterator end() const { // конст на последний 
                return(const_iterator(first + _size));
            };

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
    };

//||-------------------------------------"end scope"-------------------------------------||

//||-------------------------------------"completed"-------------------------------------||
/// Non-member function overload
    typedef std::size_t size_type;
    template <typename T, typename Alloc>
    bool operator==(const vector<T, Alloc>&lhs, const vector<T, Alloc>& rhs){
        if (lhs.size() != rhs.size())
            return (false);
        return (equals(lhs.begin(), lhs.end(), rhs.begin()));
    }
    template <typename T, typename Alloc>
    bool operator!=(const vector<T, Alloc>&lhs, const vector<T, Alloc>&rhs){
        return (!(lhs == rhs));
    }
    template <typename T, typename Alloc>
    bool operator<(const vector<T, Alloc>&lhs, const vector<T, Alloc>&rhs){ //realize lexicgraphicCompare
        return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template <typename T, typename Alloc>
    bool operator>(const vector<T, Alloc>&lhs, const vector<T, Alloc>&rhs){
        return (rhs < lhs);
    }
    template <typename T, typename Alloc>
    bool operator>=(const vector<T, Alloc>&lhs, const vector<T, Alloc>&rhs){
        return (!(lhs < rhs));
    }
    template <typename T, typename Alloc>
    bool operator<=(const vector<T, Alloc>&lhs, const vector<T, Alloc>&rhs){
        return (!(rhs < lhs));
    }
    
};
//||-------------------------------------"end scope"-------------------------------------||
namespace{
template <class T, class Alloc>
    void swap(vector<T, Alloc>&lhs, vector<T, Alloc>&rhs){
        lhs.swap(rhs);
    };
}

#endif
