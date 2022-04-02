#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "../utility/utility.hpp"

namespace ft{
    template <class Iterator> class reverse_iterator {
        public:
            typedef Iterator iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename iterator_traits<Iterator>::value_type value_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::pointer pointer;
            typedef typename iterator_traits<Iterator>::reference reference;
        private:
            iterator_type base_iterator;
        public:
            reverse_iterator() : base_iterator(){

            };

            explicit reverse_iterator(iterator_type it) : base_iterator(it){

            };

            template <class Iterator1>
            reverse_iterator(const reverse_iterator<Iterator1>& reverse_it){
                base_iterator = reverse_it.base_iterator;
            };
            
            iterator_type base() const {
                return (this->base_iterator);
            };

            reference operator*() const{
                iterator_type temp = base_iterator;
                return (*--temp);
            };

            reverse_iterator operator+(difference_type i) const{
                return (reverse_iterator(base_iterator - i));
            };

            reverse_iterator & operator++(){
                --base_iterator;
                return (*this);
            };

            reverse_iterator operator++(int){
                reverse_iterator temp = *this;
                ++(*this);
                return temp;
            };

            reverse_iterator & operator+=(difference_type i){
                this->base_iterator -= i;
                return (*this);
            };

            reverse_iterator operator-(difference_type i) const{
                return (reverse_iterator(this->base_iterator + i));
            };

            reverse_iterator& operator--() {
                ++base_iterator;
                return (*this);
            };

            reverse_iterator operator--(int){
                reverse_iterator temp = *this;
                --(*this);
                return (temp);
            };

            reverse_iterator& operator-=(difference_type i){
                base_iterator += i;
                return (*this);
            };

            pointer operator->() const{
                return &(operator*());
            };

            reference operator[](difference_type i) const{
                return (base_iterator[-i - 1]);
            };
    };
    template <class Iterator>
    bool operator==(const reverse_iterator<Iterator>&lhs, const reverse_iterator<Iterator>&rhs){
        return (lhs.base() == rhs.base());
    };
    template <class Iterator>
    bool operator!=(const reverse_iterator<Iterator>&lhs, const reverse_iterator<Iterator>&rhs){
        return (!(lhs == rhs));
    };
    template <class Iterator>
    bool operator<(const reverse_iterator<Iterator>&lhs, const reverse_iterator<Iterator>&rhs);
    template <class Iterator>
    bool operator>(const reverse_iterator<Iterator>&lhs, const reverse_iterator<Iterator>&ths);
    template <class Iterator>
    bool operator<=(const reverse_iterator<Iterator>&lhs, const reverse_iterator<Iterator>&rhs);
    template <class Iterator>
    bool operator>=(const reverse_iterator<Iterator>&lhs, const reverse_iterator<Iterator>&rhs);
    template<class Iterator>
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type i, const reverse_iterator<Iterator>& reverse_it){
        return (reverse_it + i);
    };
    template<class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>&lhs, const reverse_iterator<Iterator>&rhs){
        return (lhs.base() - rhs.base());
    }
}

#endif