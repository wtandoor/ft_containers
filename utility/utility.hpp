#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft{
    template<class T>struct remove_const {
        typedef T type;
    };

    template<class T> struct remove_const<const T>
    {
        typedef T type;
    };
    
    template <class Iterator> class iterator_traits{
        public:
            typedef typename Iterator::difference_type  difference_type;
            typedef typename Iterator::value_type       value_type;
            typedef typename Iterator::pointer          pointer;
            typedef typename Iterator::reference        reference;
            typedef typename Iterator::iterator_category    iterator_category;
    };
    
    template <class T> class iterator_traits<T*>{
        public:
            typedef std::ptrdiff_t difference_type;
            typedef T              value_type;
            typedef T*             pointer;
            typedef T&             reference;
            typedef std::random_access_iterator_tag iterator_category;
    };

    template <class T> class iterator_traits<const T*>{
        public:
            typedef std::ptrdiff_t difference_type;
            typedef const T              value_type;
            typedef const T*             pointer;
            typedef const T&             reference;
            typedef std::random_access_iterator_tag iterator_category;
    };

    template<class T1, class T2> struct pair {
        typedef T1 firstType;
        typedef T2 secondType;

        firstType first;
        secondType second;

        pair() : first(), second(){}
        template <class F, class S>
        pair(const pair<F, S> &copy):first(copy.first), second(copy.second){}
        pair(const pair & copy) : first(copy.first), second(copy.second){}
        pair(const firstType &a, const secondType &b):first(a), second(b){}
        pair & operator=(const pair & right){
            first = right.first;
            second = right.second;
            return (*this);
        }
    };

    template<class T1, class T2>
    bool operator==(const pair<T1, T2>&lhs, const pair<T1, T2>& rhs){
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template<class T1, class T2>
    bool operator!=(const pair<T1, T2>&lhs, const pair<T1, T2>&rhs){
        return !(lhs == rhs);
    }

    template<class T1, class T2>
    bool operator<(const pair<T1, T2>&lhs, const pair<T1, T2>&rhs){
        return lhs.first < rhs.first  || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }
    
    template<class T1, class T2>
    bool operator<=(const pair<T1, T2>&lhs, const pair<T1, T2>&rhs){
        return !(rhs < lhs);
    }

    template<class T1, class T2>
    bool operator>(const pair<T1, T2>&lhs, const pair<T1, T2>&rhs){
        return rhs < lhs;
    }

    template<class T1, class T2>
    bool operator>=(const pair<T1, T2>&lhs, const pair<T1, T2>& rhs){
        return !(lhs < rhs);
    } 

    template<class T1, class T2>
    pair<T1, T2> make_pair(T1 lhs, T2 rhs){
        return pair<T1, T2>(lhs, rhs);
    }

    template<class T, bool var>
    struct integral_constant{
        static const bool value = var;
        typedef T value_type;
        typedef integral_constant type;
        operator value_type() const {
            return value;
        }
    };

    template <class T> struct is_integral : public ft::integral_constant<T, false> {};
    template <> struct is_integral<bool>: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<char>: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<signed char>: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned char>: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<wchar_t>: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<short>: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<char16_t>: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned short>: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<int>: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned int>: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<long>: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned long>: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<long long>: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned long long>: public ft::integral_constant<bool, true> {};

    template<bool A, class T, class F>
    struct conditional {
        typedef F type;
    };
    
    template<class T, class F>
    struct conditional<true, T, F> {
        typedef T type;
    };

    template<bool A, class T = void>
        struct enable_if{};

    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };

    template<class T1, class T2>
    bool lexicographical_compare(T1 first1, T1 last1, T2 first2, T2 last2){
        for (int i = 0 ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
        return (first1 == last1 && (first2 != last2));
    }
    
    template<class T1, class T2>
    bool equal(T1 first1, T1 last1, T2 first2){
        while (first1 != last1){
            if (!(*first1 == *first2))
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }

    template<class T1, class T2, class CompareMethod>
    bool lexicographical_compare(T1 first1, T1 last1, T2 first2, T2 last2, CompareMethod comp){
        for (int i = 0 ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
            if (comp(*first1, *first2)) return true;
            if (comp(*first2, *first1)) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }
}

#endif