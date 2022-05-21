
template <class Value>
struct Node {
public:
    Value *_value;
    Node *_parent;
    Node *_left;
    Node *_right;
    bool is_black;
    bool is_nil;











    Node (Value *value = 0) : _value(value), _parent(0), _left(0), _right(0), is_black(false), is_nil(false) {}

    Node(Node const& other){
        _value = other._value;
        _parent = other._parent;
        _left = other._left;
        _right = other._right;
        is_black = other.is_black;
        is_nil = other.is_nil;
    }

    Node & operator=(Node const& other){
        _value = other._value;
        _parent = other._parent;
        _left = other._left;
        _right = other._right;
        is_black = other.is_black;
        is_nil = other.is_nil;
        return *this;
    }

    virtual ~Node(){}
};

template <typename T>
class TreeIterator{
public:
    typedef std::bidirectional_iterator_tag                     iterator_category;
    typedef typename ft::iterator_traits<T*>::value_type        value_type;
    typedef typename ft::iterator_traits<T*>::reference         reference;
    typedef typename ft::iterator_traits<T*>::pointer           pointer;
    typedef typename ft::iterator_traits<T*>::difference_type   difference_type;
    typedef Node<typename ft::remove_const<value_type>::type>*  node_pointer;

private:

    node_pointer    _node;
    node_pointer tree_min(node_pointer n) const {
        while (n->_left != NULL && !n->_left->is_nil) {
            n = n->_left;
        }
        return n;
    }
    node_pointer tree_max(node_pointer n) const {
        while (n->_right != NULL && !n->_right->is_nill) {
            n = n->_right;
        }
        return n;
    }

public:
    TreeIterator(){};

    TreeIterator(void *node): _node(static_cast<node_pointer>(node)){}

    TreeIterator(const TreeIterator<typename ft::remove_const<value_type>::type> & other){
        *this = other;
    }

    TreeIterator & operator=(const TreeIterator<typename ft::remove_const<value_type>::type> & other){
        this->_node = other._node;
        return *this;
    }

    reference operator*() const{
        return *(_node->_value);
    }

    pointer operator->() const {
        return _node->_value;
    }

    TreeIterator& operator++(){
        if (_node->_right != NULL && !_node->_right->is_nil)
            _node = tree_min(_node->_right);
        else {
            node_pointer n = _node->_parent;
            while (n != NULL && _node == n->_right) {
                _node = n;
                n = n->_parent;
            }
            _node = n;
        }
        return *this;
    }

    TreeIterator& operator++(int){
        TreeIterator<value_type> temp = *this;
    }
};
