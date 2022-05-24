#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#include <memory>
#include "../vector/reverse_iterator.hpp"
#include "tree_iterator.hpp"
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
        typedef TreeIterator<T>                                         iterator;
        typedef TreeIterator<const T>                                   const_iterator;
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
    iterator begin(){
        return iterator(_size == 0 ? _header : iterator(tree_min(_root)));
    }

    const_iterator begin() const {
        return const_iterator(_size == 0 ? _header : const_iterator(tree_min(_root)));
    }

    iterator end(){
        return iterator(_header);
    }

    const_iterator end() const {
        return const_iterator(_header);
    }

    reverse_iterator rbegin(){
        return reverse_iterator(end());
    }
    
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend(){
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    pointer create_value(const value_type & value){
        pointer new_val = _alloc.allocate(1);
        _alloc.construct(new_val, value);
        return new_val;
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

    template<class InputIt>
    RedBlackTree(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last, const value_compare& comp, const allocator_type& alloc = allocator_type()): _alloc(alloc) {
        init_nil_head();
        _root = _header;
        for (; first != last; ++first)
            insert(*first); //insert(value)
    }

    RedBlackTree & operator=(const RedBlackTree& other){
        if (this == &other)
            return *this;
        _node_alloc = other._node_alloc;
        _alloc = other._alloc;
        _compare = other._compare;
        if (_root == NULL)
            init_nil_head();
        else
            clear_node(_root);
        if (other._size == 0)
            _root = _header;
        else {//copy_node/ copy_child
            _root = copy_node(other._root);
            copy_child(_root, other._root);
        }
        _size = other._size;
        return *this;
    }

    ~RedBlackTree(){
        clear_node(_root);
        _alloc.destroy(_header->_value);
        _alloc.deallocate(_header->_value, 1);
        _node_alloc.deallocate(_nil, 1);
        _node_alloc.deallocate(_header, 1);
    }
//_______________________________________________________________________________________________________________//
    size_type size() const {
        return _size;
    }

    size_type max_size() const {
        return _alloc.max_size();
    }

    bool empty() const{
        return _size == 0;
    }

    value_compare value_comp() const {
        return _compare;
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