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

            vector& operator= (const vector& other );

            reference at ( size_type pos );
            const_reference at ( size_type pos ) const;

            reference operator[] (size_type pos );
            const_reference operator[] ( size_type pos ) const;

            reference front();
            const_reference front() const;

            reference back();
            const_reference back() const;

            T* data();
            const T* data() const;
            
            iterator begin();
            const_iterator begin() const;
            iterator end();
            const_iterator end() const;
            reverse_iterator rbegin();
            const_reverse_iterator rbegin() const;
            reverse_iterator rend();
            const_reverse_iterator rend() const;

            void assign( size_type count, const T& value);
            template<class InputIt>
            void assign( InputIt first, InputIt last);

            allocator_type get_allocator() const;

            bool empty() const;

            size_type size() const;
            size_type max_size() const;

            void reserve( size_type new_cap );
            size_type capacity() const;

            void clear();

            //insert value before pos, It returns iterator pointing to the inserted value
            iterator insert ( const_iterator pos, const T& value );
            //insert count copies of the value before pos, it returns iterator pointing to the first element
            //inserted, or pos if count == 0.
            iterator insert ( const_iterator pos, size_type count, const T& value);
            //insert elements from range [first,last) before pos
            //this overload has the same effect as ovverload of previous function if InputIt is an intergral type.
            //The behavior is undefined if first and last are iterators into *this.
            //It returns iteratorpoiting to the first element inserted, or pos if first == last.
            template<class InputIt>
            iterator insert ( const_iterator pos, InputIt firstm InputUt last );

            //removes the element at pos
            iterator erase( iterator pos );
            //removes the elements in the range [first, last)
            iterator erase( iterator first , iterator last );

            void push_back( const T& value );

            void pop_back();

            //resize the container to contain count elements.
            void resize( size_type count, T value = T() );

            void swap ( vector& other );
    };

    template<class T , class Alloc>
    inline bool operator== (const ft::vector<T, Alloc>& lhs,
                            const ft::vector<T,Alloc>&rhs);

    template<class T, class Alloc>
    inline bool operator!= (const ft::vector<T, Alloc>& lhs,
                            const ft::vector<T,Alloc>&rhs);
    
    template<class T, class Alloc>
    inline bool operator< (const ft::vector<T, Alloc>& lhs,
                            const ft::vector<T,Alloc>&rhs);
    
    template<class T, class Alloc>
    inline bool operator<= (const ft::vector<T, Alloc>& lhs,
                            const ft::vector<T,Alloc>&rhs);
    
    template<class T, class Alloc>
    inline bool operator> (const ft::vector<T, Alloc>& lhs,
                            const ft::vector<T,Alloc>&rhs);

    template<class T, class Alloc>
    inline bool operator>= (const ft::vector<T, Alloc>& lhs,
                            const ft::vector<T,Alloc>&rhs);
    
    template<class T, class Alloc>
    inline void swap (ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs);
}

#include <vector>

#endif
