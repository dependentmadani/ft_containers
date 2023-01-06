/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:44:28 by mbadaoui          #+#    #+#             */
/*   Updated: 2023/01/06 17:44:31 by mbadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "../iterators/iterator.hpp"
# include "../iterators/iterator_traits.hpp"
# include "../iterators/reverse_iterator.hpp"

namespace ft
{
    template<class T, class Allocator = std::allocator<T>>
    class vector
    {
        private:

        public:
            typedef T                                                   value_type;
            typedef Allocator                                           allocator_type;
            typedef size_t                                              size_type;
            typedef ptrdiff_t                                           difference_type;
            typedef value_type&                                         reference;
            typedef const value_type&                                   const_reference;
            typedef typename Allocator::pointer                         pointer;
            typedef typename Allocator::const_pointer                   const_pointer;
            typedef typename ft::random_access_iterator<pointer>        iterator;
            typedef typename ft::random_access_iterator<const_pointer>  const_iterator;
            typedef typename ft::reverse_iterator<iterator>             reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>       const_reverse_iterator;
    
            //The default constructor. Creates a vector of length zero. The vector will use the 
            //allocator alloc for all storage management.
            explicit vector( const allocator_type& alloc = allocator_type()) {};
            //Creates a vector of length count, containing n copies of the default value for type T.
            //Requires that T have a default constructor. The vector will use the allocator Allocator()
            //for all storage management.
            explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator());
            //Creates a vector of length last - first, filled with all values obtained by dereferencing
            //the InputIt oon the range [first, last). The vector will use the allocator alloc for all storage management.
            template<class InputIt>
            vector( InputIt first, InputIt last, const Allocator& alloc = Allocator());
            // Creates a copy of other
            vector( const vector& other);
            // destructs the vector
            ~vector();

            

    };
}

#include <vector>

#endif
