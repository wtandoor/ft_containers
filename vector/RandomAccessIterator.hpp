#ifndef RANDOMACCESSITERATOR_HPP
#define RANDOMACCESSITERATOR_HPP

namespace ft {
    template<typename T> class RandomAccessIterator {
        private:
            pointer _ptr;
        public:
            typedef typename ft::iterator_traits<T*>::value_type                value_type;
            typedef typename ft::iterator_traits<T*>::pointer                   pointer;
            typedef typename ft::iterator_traits<T*>::reference                 reference;
            typedef typename ft::iterator_traits<T*>::difference_type           difference_type;
            typedef std::random_access_iterator_tag                             iterator_category;
            RandomAccessIterator() : _ptr(){

            };

            RandomAccessIterator(pointer a) : _ptr(a){

            };

            virtual ~RandomAccessIterator(){

            };

            pointer base(void) const{
                return (_ptr);
            };

            RandomAccessIterator(const RandomAccessIterator<typename ft::remove_const<T>::type> &src) : _ptr(src._ptr){

            };

            RandomAccessIterator<T, IsConst> & operator=(RandomAccessIterator<typename ft::remove_const<T>::type> const &src){
                this->_ptr = src._ptr;
                return (*this);
            };

            operator RandomAccessIterator<T, true>() const{
                return(RandomAccessIterator<T,true>(this->_ptr));
            }
//Operators///
            
            RandomAccessIterator & operator++(){
                ++_ptr;
                return (*this);
            };

            RandomAccessIterator & operator++(int){
                RandomAccessIterator tmp(*this);
                _ptr++;
                return (tmp);
            }

            RandomAccessIterator & operator--(){
                --_ptr;
                return (*this);
            }

            RandomAccessIterator & operator--(int){
                RandomAccessIterator tmp(*this);
                --_ptr;
                return (tmp)
            }

            RandomAccessIterator operator+(const difference_type & right) const{
                return (_ptr + right);
            }

            RandomAccessIterator operator-(const difference_type & right) const{
                return (_ptr - right);
            }

            RandomAccessIterator & operator+=(const difference_type & right) {
                _ptr += right;
                return (*this);
            }

            RandomAccessIterator & operator-=(const difference_type & right){
                _ptr -= right;
                return (*this);
            }

            pointer operator->(){
                return(this->_ptr);
            }

            value_type & operator*(){
                return(*_ptr);
            }

            reference operator[] (difference_type n) const{
                return (*(_ptr + n));
            }

            difference_type operator-(const RandomAccessIterator<T, true> & right){
                return(_ptr - right.base());
            }

            difference_type operator-(const RandomAccessIterator<T, false> & reght){
                return(_ptr - right.base());
            }
    };
}

#endif 