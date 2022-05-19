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
    //____________________________Helpers_________________________________//
    void init_nil_head(){
            _nil = _node_alloc.allocate(1);
            _node_alloc.construct(_nil, Node<T>());
            _nil->is_black = true;
            _nil->is_nil = true;
            _header = _node_alloc.allocate(1);
            _node_alloc.construct(_header, Node<T>());
            _header->value = _alloc.allocate(1);
            _alloc.construct(_header->value, Value());
            _header->is_black = true;
    }
    //____________________________Constructors_________________________________//

    RedBlackTree(const Compare &compare, const allocator_type& a = allocator_type()):
        _alloc(a), _node_alloc(node_allocator()), _compare(compare), _root(0), _size(0){
        init_nil_head();
        _root = _header;
    }

    RedBlackTree() : _root(0), _alloc(allocator_type()), _node_alloc(node_allocator()),
        _compare(value_compare()), _size(0){
        init_nil_head();
        _root = _header;
    }

    RedBlackTree(const RedBlackTree& other) : _compare(other._compare), _root(0){
        *this = other;
    }

        
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