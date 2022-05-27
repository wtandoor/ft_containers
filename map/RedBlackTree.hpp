#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#include <memory>
#include "../vector/reverse_iterator.hpp"
#include "tree_iterator.hpp"
#include "../utility/utility.hpp"

template<class Value, class Compare = std::less<Value>, class Alloc = std::allocator<Value> >
class RedBlackTree{
    public:
        typedef Value                                                   value_type;
        typedef Compare                                             value_compare;
        typedef Alloc                                               allocator_type;
        typedef typename Alloc::template rebind<Node<Value> >::other    node_allocator;
        typedef typename node_allocator::pointer                    node_pointer;
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;
        typedef std::ptrdiff_t                                      difference_type;
        typedef std::size_t                                         size_type;
        typedef TreeIterator<Value>                                         iterator;
        typedef TreeIterator<const Value>                                   const_iterator;
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
    node_pointer tree_min(node_pointer n) const{
        while (n != NULL && !is_nil(n->_left))
            n = n->_left;
        return n;
    }

    node_pointer tree_max(node_pointer n) const{
        while (n != NULL && is_nil(n->_right)) {
            n = n->_right;
        }
        return n;
    }

    void _rotate_right(node_pointer node){
        node_pointer n;

        n = node->_left;
        node->_left = n->_right;
        if (!is_nil(n->_right))
            n->_right->_parent = node;
        n->_parent = node->_parent;
        if (node->_parent == NULL)
            _root = n;
        else if (node == node->_parent->_left)
            node->_parent->_left = n;
        else
            node->_parent->_right = n;
        n->_right = node;
        node->_parent = n;
    }

    void _rotate_left(node_pointer node){
        node_pointer n;

        n = node->_right;
        node->_right = n->_left;
        if (!is_nil(n->_left))
            n->_left->_parent = node;
        n->_parent = node->_parent;
        if (node->_parent == NULL)
            _root = n;
        else if (node == node->_parent->_left)
            node->_parent->_left = n;
        else
            node->_parent->_right = n;
        n->_left = node;
        node->_parent = n;
    }

    node_pointer _insert(node_pointer new_node){
        if (_root == _header)
            _root = new_node;
        else
            _insert_to_node(_root, new_node);
        return new_node;
    }

    node_pointer _insert_to_node(node_pointer root, node_pointer new_node){
        if (_compare(*new_node->_value, *root->_value)){
            if (!is_nil(_root->_left))
                return _insert_to_node(_root->_left, new_node);
            _root->_left = new_node;
        } else {
            if (!is_nil(_root->_right))
                return _insert_to_node(_root->_right, new_node)
            _root->_right = new_node;
        }
        new_node->_parent = _root;
        return new_node;
    }

    node_pointer _insert_into_tree(node_pointer new_node, node_pointer position){
        if (_root = _header)
            _root  = new_node;
        else
            _insert_to_node(position, new_node);
        return new_node;
    }

    void _insert_fixup(node_pointer node){
        if (node != _root && node->_parent != _root) {
            while (node != _root && !node->_parent->is_black) {
                if (node->_parent == node->_parent->_parent->_left){
                    node_pointer uncle = node->_parent->_parent->_right;
                    if (!uncle->is_black){
                        node->_parent->is_black = true;
                        uncle->is_black = true;
                        node->_parent->_parent->is_black = false;
                        node = node->_parent->_parent;
                    } else {
                        if (node == node->_parent->_right){
                            node = node->_parent;
                            _rotate_left(node);
                        }
                        node->_parent->is_black = true;
                        node->_parent->_parent->is_black = false;
                        _rotate_right(node->_parent->_parent);
                    }
                } else {
                    node_pointer uncle = node->_parent->_parent->_left;
                    if (!uncle->is_black) {
                        node->_parent->is_black = true;
                        uncle->is_black = true;
                        node->_parent->_parent->is_black = false;
                        node = node->_parent->_parent;
                    } else {
                        if (node == node->_parent->_left) {
                            node = node->_parent;
                            _rotate_right(node);
                        }
                        node->_parent->is_black = true;
                        node->_parent->_parent->is_black = false;
                        _rotate_left(node->_parent->_parent);
                    }
                }
            }
        }
        _root->is_black = true;
    }

    bool is_nil(node_pointer node) const {
        return node == _nil || node == _header;
    }

    void clear_node(node_pointer node){
        if (node && !is_nil(node)) {
            clear_node(node->_right);
            clear_node(node->_left);
            _alloc.destroy(node->_value);
            _alloc.deallocate(node->_value, 1);
            _node_alloc.deallocate(node, 1);
        }
    }

    void transplant(node_pointer position, node_pointer node){
        if (position == _root){
            _root = node;
        } else if (position == position->_parent->_left) {
            position->_parent->_left = node;
        } else 
            position->_parent->_right = node;
        node->_parent = position->_parent;
    }

    void free_node(node_pointer node){
        _alloc.destroy(node->_value);
        _alloc.deallocate(node->_value, 1);
        _node_alloc.deallocate(node, 1);
    }

    void init_nil_head(){
            _nil = _node_alloc.allocate(1);
            _node_alloc.construct(_nil, Node<Value>());
            _nil->is_black = true;
            _nil->is_nil = true;
            _header = _node_alloc.allocate(1);
            _node_alloc.construct(_header, Node<Value>());
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

    void copy_node(node_pointer other){
        node_pointer new_node = _node_alloc.allocate(1);
        _node_alloc.construct(new_node, Node<Value>());
        new_node->is_black = other->is_black;
        new_node->is_nil = other->is_nil;
        if (other->_value){
            new_node->_value = _alloc.allocate(1);
            _alloc.construct(new_node->_value, *other->_value);
        }
        return new_node;
    }

    void copy_child(node_pointer my_node, node_pointer other){
        if (other->_left->is_nil)
            my_node->_left = _nil;
        else {
            my_node->_left = copy_node(other->_left);
            my_node->_left->_parent = my_node;
            copy_child(my_node->_left, other->_left);
        }
        if (other->_right->is_nil)
            my_node->_right = _nil;
        else if (other->_right->_right == NULL){
            my_node->_right = _header;
            _header->_parent = my_node;
        } else {
            my_node->_right = copy_node(other->_right);
            my_node->_right->_parent = my_node;
            copy_child(my_node->_right, other->_right);
        }
    }//search , find, pair, inserts, erases, 




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