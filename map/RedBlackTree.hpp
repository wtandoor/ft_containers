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
    node_pointer tree_min(node_pointer n) const{//checked
        while (n != NULL && !is_nil(n->_left))
            n = n->_left;
        return n;
    }

    node_pointer tree_max(node_pointer n) const{//checked
        while (n != NULL && is_nil(n->_right)) {
            n = n->_right;
        }
        return n;
    }

void 	_rotate_right(node_pointer	node){
			node_pointer y;

			y = node->_left;
			node->_left = y->_right;
			if (!is_nil(y->_right))
				y->_right->_parent = node;
			y->_parent = node->_parent;
			if (node->_parent == NULL)
				_root = y;
			else if (node == node->_parent->_left)
				node->_parent->_left = y;
			else
				node->_parent->_right = y;
			y->_right = node;
			node->_parent = y;
		}

void 	_rotate_left(node_pointer	node){
			node_pointer y;

			y = node->_right;
			node->_right = y->_left;
			if (!is_nil(y->_left))
				y->_left->_parent = node;
			y->_parent = node->_parent;
			if (node->_parent == NULL)
				_root = y;
			else if (node == node->_parent->_left)
				node->_parent->_left = y;
			else
				node->_parent->_right = y;
			y->_left = node;
			node->_parent = y;
		}

		node_pointer	_insert(node_pointer new_node){
			if (_root == _header)
				_root = new_node;
			else
				_insert_to_node(_root, new_node);
		   return new_node;	
		}

		node_pointer	_insert_to_node(node_pointer kekis, node_pointer new_node){
			if (_compare(*new_node->_value, *kekis->_value)){
				if (!is_nil(kekis->_left))
					return (_insert_to_node(kekis->_left, new_node));
				kekis->_left = new_node;
			}
			else{
				if (!is_nil(kekis->_right))
					return (_insert_to_node(kekis->_right, new_node));
				kekis->_right = new_node;
			}
			new_node->_parent = kekis;
			return (new_node);
		}

		node_pointer _insert_into_tree(node_pointer new_node, node_pointer where){
			if (_root == _header)
				_root = new_node;
			else
				_insert_to_node(where, new_node);
			return (new_node);
		}

        void _insert_fixup(node_pointer node){
            std::cout << "here\n";
			if (node != _root && node->_parent != _root){
                std::cout << "preloop\n" << std::endl;
				while (node != _root && !node->_parent->is_black){
                    std::cout << "loop\n" << std::endl;
					if (node->_parent == node->_parent->_parent->_left){
						node_pointer uncle = node->_parent->_parent->_right;
						if (!uncle->is_black){
							node->_parent->is_black = true;
							uncle->is_black = true;
							node->_parent->_parent->is_black = false;
							node = node->_parent->_parent;
						}
						else {
							if (node == node->_parent->_right){
								node = node->_parent;
								_rotate_left(node);
                                std::cout << "left1\n";
							}
							node->_parent->is_black = true;
							node->_parent->_parent->is_black = false;
							_rotate_right(node->_parent->_parent);
                            std::cout << "right1\n";
						}
					}
					else{
						node_pointer uncle = node->_parent->_parent->_left;
						if (!uncle->is_black){
							node->_parent->is_black = true;
							uncle->is_black = true;
							node->_parent->_parent->is_black = false;
							node = node->_parent->_parent;
						}
						else{
							if (node == node->_parent->_left){
								node = node->_parent;
								_rotate_right(node);
                                std::cout << "right\n"; 
							}
							node->_parent->is_black = true;
							node->_parent->_parent->is_black = false;
							_rotate_left(node->_parent->_parent);
                            std::cout << "left\n";
						}
					}
				}
			}
			_root->is_black = true;
		}

    bool is_nil(node_pointer node) const {//checked
        return node == _nil || node == _header;
    }

    void clear_node(node_pointer node){ //checked
        if (node && !is_nil(node)) {
            clear_node(node->_right);
            clear_node(node->_left);
            _alloc.destroy(node->_value);
            _alloc.deallocate(node->_value, 1);
            _node_alloc.deallocate(node, 1);
        }
    }

    void transplant(node_pointer position, node_pointer node){//checked
        if (position == _root){
            _root = node;
        } else if (position == position->_parent->_left) {
            position->_parent->_left = node;
        } else 
            position->_parent->_right = node;
        node->_parent = position->_parent;
    }

    void free_node(node_pointer node){ //checked
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
            _header->_value = _alloc.allocate(1);
            _alloc.construct(_header->_value, Value());
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

    node_pointer copy_node(node_pointer other){
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
    }

        node_pointer	search(const value_type &value, node_pointer node) const {
			if(!node || is_nil(node))
				return NULL;
			if (_compare(value, *node->_value))
				return search(value, node->_left);
			if (_compare(*node->_value, value))
				return search(value, node->_right);
			return node;
		}

    iterator find(const value_type& value){
        node_pointer res = search(value, _root);
        return res == NULL ? end() : iterator(res);
    }

    const_iterator find(const value_type& value) const {
        node_pointer res = search(value, _root);
        return res == NULL ? end() : const_iterator(res);
    }

        ft::pair<iterator, bool>  insert(value_type const &value){
			node_pointer find_val = search(value, _root);
            std::cout << "after search\n";
			if (find_val)
				return ft::pair<iterator, bool>(iterator(find_val), false);
			node_pointer new_node = _node_alloc.allocate(1);
            std::cout << "before const\n";
			_node_alloc.construct(new_node, Node<value_type>(create_value(value)));
            std::cout << "after const\n";
			new_node->_left = _nil;
			new_node->_right = _nil;
            std::cout << "before iit\n";
			_insert_into_tree(new_node, _root);
            std::cout << "after iit\n";
			ft::pair<iterator, bool> res(iterator(new_node), true);
            std::cout << "before fixup\n";
			_insert_fixup(new_node);
            std::cout << "after fixup\n";
			_size++;
			new_node = tree_max(_root);
            std::cout << "kekis\n";
			new_node->_right = _header;
			_header->_parent = new_node;
            std::cout << "навалил\n";
			return res;
		}

    iterator insert(iterator position, const value_type& value){
			node_pointer new_node = search(value, _root);
			if (new_node)
				return (iterator(new_node));
			new_node = _node_alloc.allocate(1);
			_node_alloc.construct(new_node, Node<value_type>(create_value(value)));
			new_node->_left = _nil;
			new_node->_right = _nil;
			if (position == begin()){
				if (position != end() && _compare(value, *position))
					_insert_into_tree(new_node, tree_min(_root));
				else
					_insert_into_tree(new_node, _root);
			}
			else if (position == end()){
				if (position != begin() && _compare(*(--position), value))
					_insert_into_tree(new_node, _header->_parent);
				else
					_insert_into_tree(new_node, _root);
			}
			else
				_insert_into_tree(new_node, _root);
			_insert_fixup(new_node);
			_size++;
			node_pointer max_of_tree = tree_max(_root);
			max_of_tree->_right = _header;
			_header->_parent = max_of_tree;
			return (iterator(new_node));
		}

    template<class InputIt>
	void insert(typename ft::enable_if< !ft::is_integral<InputIt>::value, InputIt >::type first, InputIt last) {
	    for (; first != last; ++first)
		    insert(*first);
	}

    void erase(iterator pos){
		node_pointer y = pos.node(), x, for_free = y;
		bool y_original_is_black = y->is_black;
		if (is_nil(y->_left)){
			x = y->_right;
			transplant(y, y->_right);
		} else if (is_nil(y->_right)){
			x = y->_left;
			transplant(y, y->_left);
		} else {
			node_pointer z = y;
			y = tree_min(z->_right);
			y_original_is_black = y->is_black;
			x = y->_right;
			if (y->_parent != z){
				transplant(y, y->_right);
				y->_right = z->_right;
				z->_right->_parent = y;
			}
			transplant(z, y);
			y->_left = z->_left;
			y->_left->_parent = y;
			y->is_black = z->is_black;
		}
		free_node(for_free);
		if (y_original_is_black)
			erase_fixup(x);
		_size--;
		_nil->_parent = NULL;
		if (_size == 0)
			_root = _header;
		else{
			if (_size != 1)
				x = tree_max(_root);
			else
				x = _root;
			x->_right = _header;
			_header->_parent = x;
		}
	}

    size_type erase(const value_type& value){
		node_pointer res = search(value, _root);
		if (res)
			erase(iterator(res));
		return (res != NULL);
	}

	void erase(iterator first, iterator last){
		while (first != last)
			erase(first++);
	}

void erase_fixup(node_pointer x){
		node_pointer brother;
		while (x != _root && x->is_black){
			if (x == x->_parent->_left){
				brother = x->_parent->_right;
				if (!brother->is_black){
					brother->is_black = true;
					x->_parent->is_black = false;
					_rotate_left(x->_parent);
					brother = x->_parent->_right;
				}
				//case 2
				if (brother->_left->is_black && brother->_right->is_black){
					brother->is_black = false;
					x = x->_parent;
				}
				else{
					//case 3
					if (brother->_right->is_black){
						brother->_left->is_black = true;
						brother->is_black = false;
						_rotate_right(brother);
						brother = x->_parent->_right;
					}
					//case 4
					brother->is_black = x->_parent->is_black;
					x->_parent->is_black = true;
					brother->_right->is_black = true;
					_rotate_left(x->_parent);
					x = _root;
				}
			}else{
				brother = x->_parent->_left;
					//case 1
				if (!brother->is_black){
					brother->is_black = true;
					x->_parent->is_black = false;
					_rotate_right(x->_parent);
			    	brother = x->_parent->_left;
				}
					//case 2
				if (brother->_right->is_black && brother->_left->is_black){
					brother->is_black = false;
					x = x->_parent;
				}else{
				//case 3
					if (brother->_left->is_black){
						brother->_right->is_black = true;
						brother->is_black = false;
						_rotate_left(brother);
						brother = x->_parent->_left;
					}
					//case 4
					brother->is_black = x->_parent->is_black;
					x->_parent->is_black = true;
					brother->_left->is_black = true;
					_rotate_right(x->_parent);
					x = _root;
				}
			}
		}
	}


    //____________________________Constructors_________________________________//

    RedBlackTree(const Compare &compare, const allocator_type& a = allocator_type()): //checked
        _alloc(a), _node_alloc(node_allocator()), _compare(compare), _root(0), _size(0){
        init_nil_head();
        _root = _header;
    }

    RedBlackTree() : _root(0), _alloc(allocator_type()), _node_alloc(node_allocator()),
        _compare(value_compare()), _size(0){//checked
        init_nil_head();
        _root = _header;
    }

    RedBlackTree(const RedBlackTree& other) : _compare(other._compare), _root(NULL){ //checked
        *this = other;
    }

    template<class InputIt>
		RedBlackTree(typename ft::enable_if< !ft::is_integral<InputIt>::value, InputIt >::type first, InputIt last,
		   const value_compare& comp, const allocator_type& alloc = allocator_type()):	_alloc(alloc),
		   																				_node_alloc(node_allocator()),
																						_compare(comp) {
			init_nil_head();
			_root = _header;
			for (; first != last; ++first)
				insert(*first);
		}

    RedBlackTree & operator=(const RedBlackTree& other){//checked
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
            this->_root = this->_header;
        else {
            this->_root = copy_node(other._root);
            copy_child(this->_root, other._root);
        }
        this->_size = other._size;
        return *this;
    }

    ~RedBlackTree(){ //checked
        clear_node(_root);
        _alloc.destroy(_header->_value);
        _alloc.deallocate(_header->_value, 1);
        _node_alloc.deallocate(_nil, 1);
        _node_alloc.deallocate(_header, 1);
    }
//_______________________________________________________________________________________________________________//
    size_type size() const { //checked
        return _size;
    }

    size_type max_size() const { //checked
        return _alloc.max_size();
    }

    bool empty() const{ //checked
        return _size == 0;
    }

    value_compare value_comp() const {
        return _compare;
    }

    void clear(){
        clear_node(_root);
        _root = _header;
        _header->_parent = NULL;
        _size = 0;
    }

    size_type count(const value_type& value) const {
        return find(value) != end();
    }

    iterator lower_bound(const value_type& value){
        iterator last = end();
        for(iterator first = begin(); first != last; ++first){
            if (_compare(*first, value))
                return first;
        }
        return last;
    }

    const_iterator lower_bound(const value_type& value) const{
        const_iterator last = end();
        for(const_iterator first = begin(); first != last; ++first){
            if (_compare(*first, value))
                return first;
        }
        return last;
    }

    iterator upper_bound(const value_type& value){
        iterator last = end();
        for (iterator first = begin(); first != last; ++first){
            if (_compare(value, *first))
                return first;
        }
        return last;
    }

    const_iterator upper_bound(const value_type& value) const{
        const_iterator last = end();
        for (const_iterator first = begin(); first != last; ++first){
            if (_compare(value, *first))
                return first;
        }
        return last;
    }

    void swap(RedBlackTree &other){
        std::swap(this->_root, other._root);
        std::swap(this->_nil, other._nil);
        std::swap(this->_header, other._header);
        std::swap(this->_size, other._size);
        std::swap(this->_node_alloc, other._node_alloc);
        std::swap(this->_alloc, other._alloc);
        std::swap(this->_compare, other._compare);
    }

    ft::pair<iterator, iterator> equal_range(const value_type &value){
        return ft::make_pair(lower_bound(value), upper_bound(value));
    }

    allocator_type get_allocator() const {
        return _alloc;
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