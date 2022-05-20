#ifndef MAP_HPP
#define MAP_HPP

#include "RedBlackTree.hpp"
#include "../utility/utility.hpp"

namespace ft{
    template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T>>
    class map{
    public:
        typedef Key                                                 key_type;
        typedef T                                                   map_type;
        typedef std::size_t                                         size_type;
        typedef std::ptrdiff_t                                      difference_type;
        typedef Compare                                             key_compare;
        typedef pair<const Key, T>                                  value_type;
        typedef Allocator                                           allocator_type;
        typedef const value_type&                                   reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;

    private:
        class pair_compare{
            key_compare _compare;
        public:
            pair_compare(const key_compare & compare) : _compare(compare){}
            bool operator()(const value_type& x, const value_type& y) const {return (_compare(x.first, y.first))}
        };

    public:
        typedef pair_compare value_compare;
        typedef RedBlackTree<value_type, pair_compare, allocator_type>  tree_type;
        typedef typename tree_type::iterator                            iterator;
        typedef typename tree_type::const_iterator                      const_iterator;
        typedef typename tree_type::reverse_iterator                    reverse_iterator;
        typedef typename tree_type::const_reverse_iterator              const_reverse_iterator;

    private:
        allocator_type  _allocator;
        tree_type       _tree;
        key_compare     _compare;

    public:
        explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
            _allocator(alloc), _tree(comp, alloc), _compare(comp) {}

        template< class InputIterator >
        map(InputIterator first, InputIterator last, const Compare& compare = Compare(), const Allocator& alloc = Allocator()) :
            _allocator(alloc), _tree(first, last, compare, _allocator), _compare(compare){}

        map_type& operator[](const key_type& key){
            return(*((this->insert(ft::make_pair(key, map_type()))).first)).second;
        }

        allocator_type get_allocator() const{
            return (_tree.get_allocator());
        }

        size_type size() const {
            return (_tree.get_size());
        }

        size_type max_size() const {
            return (_tree.max_size());
        }

        bool empty() const {
            return (_tree.empty());
        }

        value_compare value_comp() const{
            return _tree.value_comp();
        }

        key_compare key_comp() const {
            return _tree.key_comp();
        }

        iterator begin(){
            return _tree.begin();
        }

        iterator end(){
            return _tree.end();
        }

        reverse_iterator rbegin(){
            return _tree.rbegin();
        }

        reverse_iterator rend(){
            return _tree.rend();
        }

        void clear(){
            _tree.clear();
        }

        pair<iterator, bool> insert(const value_type& value){
            return _tree.insert(value);
        }

        iterator insert(iterator hint, const value_type& value){
            return _tree.insert(hint, value);
        }


    };
}


#endif
