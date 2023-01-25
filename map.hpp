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

            
    };
}


#endif