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


        node_pointer tree_min(node_pointer n) const {
            while(n != NULL && ! is_nill(n->left))
                n = n->left;
            return (n);
        };

        node_pointer tree_max(node_pointer n) const {
            while(n != NULL && !is_nill(n->right))
                n = n->right;
            return (n);
        };

        void rotate_right(node_pointer node){
            node_pointer y;
            y = node->left;
            node->left = y->right;
            if (!is_nill(y->right))
                y->right->parent = node;
            y->parent = node->parent;
            if (node->parent == NULL)
                _root  = y;
            else if (node == node->parent->left)
                node->parent->left = y;
            else
                node->parent->right = y;
            y->right = node;
            node->parent = y;
        }

        void rotate_left(node_pointer node){
            node_pointer y;

            y = node->right;
            node->right = y->left;
            if (!is_nill(y->left))
                y->left->parent = node;
            y->parent = node->parent;
            if (node->parent == NULL)
                _root = y;
            else if (node == node->parent->left)
                node->parent->left = y;
            else
                node->parent->right = y;
            y->left = node;
            node->parent = y;
        }

        node_pointer insert(node_pointer new_node){
            if (_root == _header)
                _root = new_node;
            else
                insert_to_node(_root, new_node);
            return new_node;
        }

        node_pointer insert_to_node(node_pointer root, node_pointer new_node){
            if (_compare(*new_node->value, *root->value)){
                if (!is_nill(root->left))
                    return (insert_to_node(root->left, new_node));
                root->left = new_node;
            } else {
                if (!is_nill(root->right))
                    return(insert_to_node(root->right, new_node));
                root->right = new_node;
            }
            new_node->parent = root;
            return new_node;
        }

        node_pointer insert_into_tree(node_pointer new_node, node_pointer where){
            if (_root == _header)
                _root == new_node;
            else
                insert_to_node(where, new_node);
            return new_node;
        };

        void insert_fixup(node_pointer node){

        }

        bool is_nill(node_pointer node) const {
            return node == _nill || node == _header;
        }

        void clear_node(node_pointer node){
            if (node && !is_nill(node)){
                clear_node(node->right);
                clear_node(node->left);
                _alloc.destroy(node->value);
                _alloc.deallocate(node->value, 1);
                _node_alloc.deallocate(node, 1);
            }
        }

        void init_nill_head(){
            _nill = _node_alloc.allocate(1);
            _node_alloc.construct(_nill, Node<T>());
            _nill->is_black = true;
            _nill->is_nill = true;
            _header = _node_alloc.allocate(1);
            _node_alloc.construct(_header, Node<T>());
            _header->value =  _alloc.allocate(1);
            _alloc.construct(_header->value, T());
            _header->is_black = true;
        }

        void transplant(node_pointer where, node_pointer what){
            if (where == _root)
                _root = what;
            else if (where == where->parent->left)
                where->parent->left = what;
            else
                where->parent->right = what;
            what->parent = where->parent;
        }

        void free_node(node_pointer node){
            _alloc.destroy(node->value);
            _alloc.deallocate(node->value, 1);
            _node_alloc.deallocate(node, 1);
        }

    public:
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
            new_node->is_nill = other->is_nill;
            if (other->value){
                new_node->value = _alloc.allocate(1);
                _alloc.construct(new_node->value, *other->value);
            }
            return new_node;
        }

//____________________________Constructors_________________________________//

        RedBlackTree(const Compare &comp, const allocator_type& alloc = allocator_type()): _alloc(alloc), _node_alloc(node_allocator()), _compare(comp), _root(0), _size(0){
            init_nill_head();
            _root = _header;
        };

        RedBlackTree(): _root(0), _alloc(allocator_type()), _node_alloc(node_allocator()),_compare(value_compare()), _size(0){
            init_nill_head();
            _root = _header;
        };

        RedBlackTree(const RedBlackTree& src) : _compare(src._compare), _root(NULL){
            *this = src;
        };

        template<class InputIter>
        RedBlackTree(typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type first, InputIter last, const value_compare& comp, const allocator_type& alloc = allocator_type()): _alloc(alloc), _node_alloc(node_allocator), _compare(comp){
            init_nill_head();
            _root = _header;
            for (; first != last, ++first)
                insert(*first);
        };

        RedBlackTree & operator=(const RedBlackTree & right){
            if (this == &right)
                return *this;
            this->_node_alloc = right._node_alloc;
            this->_alloc = right._alloc;
            this->_compare = right._compare;
            if (this->_root == NULL)
                init_nill_head();
            else
                clear_node(_root);
            if (right._size == 0)
                this->_root = this->_header;
            else {
                this->_root = copy_node(right._root);
                copy_child(this->_root, right._root);
            }
            this->_size = right._size;
            return (*this);
        };

        ~RedBlackTree(){
            clear_node(_root);
            _alloc.destroy(_header->value);
            _alloc.deallocate(_header->value, 1);
            _node_alloc.deallocate(_nill, 1);
            _node_alloc.deallocate(_header, 1);
        };

        size_type size() const{
            return (_size);
        };

        size_type max_size() const{
            return (_alloc.max_size());
        };

        bool empty() const{
            return (_size == 0);
        };

        value_compare value_comp() const{
            return (_compare);
        };

        void clear(){
            clear_node(_root);
            _root = _header;
            _header->parent = NULL;
            _size = 0;
        };

        size_type count(const value_type & val) const {
            return (find(val) != end());
        };

        iterator lower_bound(const value_type &val){
            iterator last = end();
            for (iterator first = begin(); first != last; ++first){
                if (!_compare(*first, val))
                    return (first);
            }
            return last;
        };

        const_iterator lower_bound(const value_type &val){
            const_iterator last = end();
            for (const_iterator first = begin(); first != last; ++first){
                if (!_compare(*first, val))
                    return (first);
            }
            return last;
        };

        const_iterator upper_bound(const value_type &val){
            const_iterator last = end();
            for (const_iterator first = begin(); first != last; ++first) {
                if (_compare(val, *first))
                    return first;
            }
            return last;
        };

        iterator upper_bound(const value_type &val){
            iterator last = end();
            for (iterator first = begin(); first != last; ++first) {
                if (_compare(val, *first))
                    return first;
            }
            return last;
        };



        ft::pair<iterator, iterator> equal_range(const value_type & value){
            return (ft::make_pair(lower_bound(value), upper_bound(value)));
        };

        allocator_type get_allocator() const {
            return (this->_alloc);
        };

        void swap(RedBlackTree &other){
            std::swap(this->_root, other._root);
            std::swap(this->_nill, other._nill);
            std::swap(this->_header, other._header);
            std::swap(this->_alloc, other._alloc);
            std::swap(this->_size, other._size);
            std::swap(this->_compare, other._compare);
            std::swap(this->_node_alloc, other._node_alloc);
        };
        
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