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
            // typedef RandomAccessIterator<value_type> iterator;
            // typedef RandomAccessIterator<const value_type> const_iterator;
            // typedef reverse_iterator<iterator> reverse_iterator;
            // typedef reverse_iterator<const_iterator> const_reverse_iterator;
        private:
            pointer first;// указатель на первый элемент
            size_type _size, _capacity; //размер и емкость
            allocator_type allocator; //обьект для выделения памяти
        public:
            //default constructor w/o args
            explicit vector(const allocator_type& alloc = allocator_type()) : first(0), _size(0), _capacity(0), allocator(alloc){
            
            };

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
            //destructor
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

            // добавить конструктор вектора с помощью двух итераторов которые указывают на начало и конец вектора(любой элемент)

            //Iterator
            // iterator begin(){ //итератор на первый элемент
            //     return (iterator(first));
            // };

            // iterator end(){ // на последний 
            //     return(iterator(first + size));
            // };

            // const_iterator begin() const { // конст на первый
            //     return(const_iterator(first));
            // };

            // const_iterator end() const { // конст на последний 
            //     return(const_iterator(first + size));
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

            // work with capacity, size, resize and etc.

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

            //Элементы доступа

            reference operator[](size_type i){
                if (i > _capacity)//{
                    // if (_size < _capacity)
                        // return (*(first + _size + 1));
                // }
                return (*(first + i));
            };

            const_reference operator[](size_type i) const {
                return (*(first + i));
            };

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

		    reference front(){
	    		return(*first);
		    };
		
		    const_reference front() const{
			    return(*first);
		    };
		
		    reference back(){
			    return(*(first + _size - 1));
		    };
		
		    const_reference back() const{
			    return(*(first + _size - 1));
		    };            
    };
}

#endif