#ifndef MAP_HPP
# define MAP_HPP

# include "AVL.hpp"
# include "utility.hpp"
# include "vector.hpp"
# include "map_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
    template<class Key, class T, class Compare = std::less<Key>,
            class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {
        public:
            typedef Key                                 key_type;
            typedef T                                   mapped_type;
            typedef typename ft::pair<cont Key, T>      value_type;
            typedef size_t                              size_type;
            typedef ptrdiff_t                           difference_type;
            typedef Compare                             key_compare;
            typedef Allocator                           allocator_type;
            typedef value_type&                         reference;
            typedef const value_type&                   const_reference;
            typedef typename Allocator::pointer         pointer;
            typedef typename Allocator::const_pointer   const_pointer;
            typedef typename ft::AVL<ft::pair<const Key, T>>    node_type;
            typedef typename ft::avl_tree<ft::pair<const Key, T>, Compare, Allocator>                                                           tree_type;
            typedef typename ft::Bidirectional_iterator<value_type, std::bidirectional_iterator_tag, tree_type, node_type>                      iterator;
            typedef typename ft::Bidirectional_iterator<const value_type, std::bidirectional_iterator_tag, const tree_type, const node_type>    const_iterator;
            typedef typename ft::reverse_iterator<iterator>         reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>   const_reverse_iterator;

            class value_compare: public std::binary_function<value_type, value_type, bool>
            {
                friend class map;
                public:
                    typedef bool result_type;
                    typedef value_type  first_argument_type;
                    typedef value_type  second_argument_type;
                    bool operator() (const value_type& lhs, const value_type& rhs) const
                    {
                        return c(lhs.first, rhs.first);
                    }
                protected:
                    Compare c;
                    value_compare( Compare cmp ): c(cmp) { };
            };
            typedef value_compare                   value_compare;

        private:
            key_compare                             _compare;
            allocator_type                          _allocator;
            tree_type                               _tree;
        
        public:

            //constructors
            explicit map(const Compare& comp, const Allocator& alloc = Allocator()): _compare(key_compare()), _allocator(alloc), _tree(NULL) { };

            //construct using iterators
            template<class InputIt>
            map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
            {
                while (first != last)
                {
                    _tree.insertion(*first);
                    ++first;
                }
            };

            //copy constructor
            map(const map& other): _tree(NULL) { *this = other; };

            //destructor that use tree destructor
            ~map() { };

            //copy assignment operator of map
            map& operator= (const map& other)
            {
                if (*this != other)
                {
                    _tree.clear();
                    _allocator = other._allocator;
                    _compare = other._compare;
                    _tree = other._tree;
                }
                return *this;
            };

            //return the allocator of the container
            allocator_type get_allocator() const
            {
                return _allocator;
            };

            //return reference to the mapped value of the requested element
            T& at(const Key& key) 
            {
                iterator tmp = lower_bound(key);
                if (tmp == end() || key_compare()(key, (*tmp).first))
                    throw out_of_range("map::at");
                return (*tmp).second;
            };

            const T& at(const Key& key) const
            {
                const_iterator tmp = lower_bound(key);
                if (tmp == end() || key_compare()(key, (*tmp).first))
                    throw out_of_range("map::at");
                return (*tmp).second;
            };

            //reference to the mapped value of the new element if no element with key existed.
            T& operator[] (const Key& key)
            {
                iterator check = find(key);
                if (check != end())
                    return check->second;
                this->insert(ft::make_pair(key, mapped_type()));
                return (this->find(key).get_node())->value.second;
            };

            //returns a read/write iterator that points to the first pair in the map
            //iteration is done in ascending order according to the keys
            iterator begin()
            {
                node_type* b = _tree.root;
                while (b != NULL && b->left_child != NULL)
                    b = b->left_child;
                return iterator(b, &_tree);
            }

            const_iterator begin() const
            {
                node_type* cb = _tree.root;
                while (cb != NULL && cb->left_child != NULL)
                    cb = cb->left_child;
                return const_iterator(cb, &_tree);
            }

            iterator end()
            {
                return iterator(NULL, &_tree);
            }

            const_iterator end() const
            {
                return const_iterator(NULL, &_tree);
            }

            reverse_iterator rbegin()
            {
                return reverse_iterator(this->end());
            }

            const_reverse_iterator rbegin() const
            {
                return const_reverse_iterator(this->end());
            }

            reverse_iterator rend()
            {
                return reverse_iterator(this->begin());
            }

            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(this->begin());
            }

            //return true if the container is empty, false otherwise
            bool empty() const
            {
                return _tree.empty();
            }

            //return the number of elements in the container
            size_type size() const
            {
                return _tree.size_tree();
            }

            //return the maximum number of elements
            size_type max_size() const
            {
                return _allocator.max_size();
            }

            //erases all elements from the container
            void clear()
            {
                _tree.clear();
            }

            //returns a pair consisting of an iterator to the inserted element
            ft::pair<iterator, bool> insert (const value_type& value)
            {
                if (_tree.available_in_tree(value))
                    return ft::make_pair(iterator(_tree.find_node(value), &_tree), false);
                return ft::make_pair(iterator(_tree.insertion(value), &_tree), true);
            }

            //return an iteratr to the inserted element
            iterator insert(iterator pos, const value_type& value)
            {
                (void)pos; //will not work with pos, cause the tree is balanced and the value will be in the appropriate position
                return iterator(_tree.insertion(value), &_tree);
            }

            //inserts all elements from range [first, last) of the container using iterators
            template<class InputIt>
            void insert(InputIt first, InputIt last)
            {
                for (; first != last; ++first)
                    _tree.insertion(*first);
            }

            //removes the element at pos
            void erase(iterator pos)
            {
                _tree.deletion(pos.get_node()->value.first);
            }

            //removes the elements in range [first, last) which must be a valid range in *this
            void erase(iterator first, iterator last)
            {
                for (; first != last && first != end(); ++first)
                    _tree.deletion(first.get_node()->value.first);
            }

            //removes the element (if one exists) with the key equivalent to "key"
            size_type erase(const Key& key)
            {
                return _tree.deletion(key);
            }

            //swap the content of a container to another container
            void swap(map& other)
            {
                if (_tree.node_number && other._tree.node_number)
                {
                    std::swap(_compare, other._compare);
                    std::swap(_allocator, other._allocator);
                    _tree.swap(other._tree);
                }
            }

            //return 1 if the key is available, otherwise 0 if not found
            size_type count(const Key& key)
            {
                return _tree.available_in_tree(key);
            }

            //returns iterator to an element with key equivalent to key
            iterator find(const Key& key)
            {
                if (this->count())
                    return iterator(_tree.find_node(key), &_tree);
                return this->end();
            }

            const_iterator find(const Key& key) const
            {
                return const_iterator(find(key));
            }

            //return a pair containing a itertors defining the wanted range.
            ft::pair<iterator, iterator> equal_range(const Key& key)
            {
                return ft::make_pair(lower_bound(key), upper_bound(key));
            }

            ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
            {
                return ft::make_pair(lower_bound(key), upper_bound(key));
            }

            //return iterator pointing to the first element that is not less
            //than key. If no such element is found, end() is returned
            iterator lower_bound( const Key& key)
            {
                
            }

            const_iterator lower_bound( const Key& key) const
            {

            }

    };
}
#include <map>


#endif