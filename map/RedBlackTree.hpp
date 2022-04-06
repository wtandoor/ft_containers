#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#include <memory>
#include "../vector/reverse_iterator.hpp"
#include "../utility/utility.hpp"

template<class T, class Compare = std::less<T>, class Alloc = std::allocator<T>>
class RedBlackTree{
    public:
        typedef T value_type;
        typedef Compare value_compare;
        typedef Alloc allocator_type;
        typedef typename Alloc::template rebind<Node<T>::other node_allocator;
        typedef typename node_allocator::pointer node_pointer;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef std::ptrdiff_t difference_type;
        typedef std::size_t size_type;
        typedef TreeIter<T> iterator;
        typedef TreeIter<const T> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    private:
        allocator_type _alloc;
        node_allocator _node_alloc;
        value_compare _compare;
        node_pointer _nill;
        node_pointer _root;
        node_pointer _header;
        size_type _size;

    public:
//___________________________(iterators 8/8)_______________________________//
        iterator end(){
            return iterator(_header);
        };

        const_iterator end() const{
            return const_iterator(_header);
        };

        iterator begin(){
            if (_size)
                return iterator(tree_min(_root));
            return iterator(_header);
        };

        const_iterator begin() const{
            if (_size)
                return const_iterator(tree_min(_root));
            return const_iterator(_header);
        };

        reverse_iterator rbegin(){
            return reverse_iterator(end());
        };

        const_reverse_iterator rbegin() const{
            return const_reverse_iterator(end());
        };

        reverse_iterator rend(){
            return reverse_iterator(begin());
        };

        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        };

        pointer create_value(const value_type &value){
            pointer new_val = _alloc.allocate(1);
            _alloc.construct(new_val, value);
            return new_val;
        };

        node_pointer copy_node(node_pointer other){
            node_pointer new_node = _node_alloc.allocate(1);
            _node_alloc.construct(new_node, Node<T>());
            new_node->is_black = other->is_black;
            new_node->is_nill = 
        }
};

#endif