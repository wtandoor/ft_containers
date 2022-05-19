#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#include <memory>
#include "../vector/reverse_iterator.hpp"
#include "../utility/utility.hpp"

template<class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class RedBlackTree{
    public:
        typedef T                                                   value_type;
        typedef Compare                                             value_compare;
        typedef Alloc                                               allocator_type;
        typedef typename Alloc::template rebind<Node<T> >::other    node_allocator;
        typedef typename node_allocator::pointer                    node_pointer;
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;
        typedef std::ptrdiff_t                                      difference_type;
        typedef std::size_t                                         size_type;
        typedef TreeIter<T>                                         iterator;
        typedef TreeIter<const T>                                   const_iterator;
        typedef ft::reverse_iterator<iterator>                      reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                const_reverse_iterator;

    private:
        allocator_type  _alloc;
        node_allocator  _node_alloc;
        value_compare   _compare;
        node_pointer    _nil;
        node_pointer    _root;
        node_pointer    _header;
        size_type       _size;

    public:

//____________________________Constructors_________________________________//



        
};

template<class Content, class Compare, class Alloc>
bool operator<(const RedBlackTree<Content, Compare, Alloc> &lhs, const RedBlackTree<Content, Compare, Alloc>& rhs){
    return(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
};

template<class Content, class Compare, class Alloc>
bool operator>(const RedBlackTree<Content, Compare, Alloc>&lhs, const RedBlackTree<Content,Compare,Alloc>&rhs){
    return(lhs < rhs);
};

template<class Content, class Compare, class Alloc>
bool operator==(const RedBlackTree<Content, Compare, Alloc>&lhs, const RedBlackTree<Content, Compare, Alloc> & rhs){
    return(lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
};

template<class Content, class Compare, class Alloc>
void swap(const RedBlackTree<Content, Compare, Alloc>& lhs, const RedBlackTree<Content, Compare, Alloc> & rhs){
    lhs.swap(rhs);
};

#endif