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

            T& operator[] (const Key& key)
            {
                
            };

    };
}
#include <map>


#endif