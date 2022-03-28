#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

namespace ft{
    template <class T, class Allocator = std::allocator<T> >
    class vector{
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
            typedef reverse_iterator<iterator> reverse_iterator;
            typedef reverse_iterator<const_iterator> const_reverse_iterator;
        private:
            pointer first;// указатель на первый элемент
            size_type size, capacity; //размер и емкость
            allocator_type allocator; //обьект для выделения памяти
        public:
            //default constructor w/o args
            explicit vector(const allocator_type& alloc = allocator_type()) : first(0), size(0), capacity(0), allocator(alloc){
            
            };

            //fill our vector
            explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : size(n), capacity(n), allocator(alloc){
                first = allocator.allocate(n);
                for(size_type i = 0; i < n; i++)
                    allocator.construct(first + i, val); //заполняем каждый элемент вектора дефолтным значением.(0, "")
            };

            //copy constructor
            vector(const vector& right):size(0), capacity(0) {
                (*this) = right;
            };
            //destructor
            //сначала мы разрушаем каждый обьект который храниться в выделенной нами памяти
            //Освобождает блок памяти, ранее выделенный с помощью allocate и еще не освобожденный.
            //Элементы в массиве не уничтожаются вызовом функции deallocate, поэтому сначала destroy()
            ~vector(){
                for (size_type i = 0; i < size, i++){
                    allocator.destroy(first + i);
                }
                if (capacity != 0)
                    allocator.deallocate(first, capacity);
            };

            // добавить конструктор вектора с помощью двух итераторов которые указывают на начало и конец вектора(любой элемент)

            //Iterator
            iterator begin(){ //итератор на первый элемент
                return (iterator(first));
            };

            iterator end(){ // на последний 
                return(iterator(first + size));
            };

            const_iterator begin() const { // конст на первый
                return(const_iterator(first));
            };

            const_iterator end() const { // конст на последний 
                return(const_iterator(first + size));
            };

            reverse_iterator rbegin(){ //итератор в обратную сторону на конец
                return (reverse_iterator(end()));
            };

            const_reverse_iterator rbegin() const { // конст -"-
                return (const_reverse_iterator(end()))
            };

            reverse_iterator rend(){ //итератор на начало 
                return (reverse_iterator(begin()));
            };

            const_reverse_iterator rend(){//конст итератор на начало
                return (const_reverse_iterator(begin()));
            };

            // work with capacity, size, resize and etc.
    };
}

#endif