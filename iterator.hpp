/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:52:22 by mbadaoui          #+#    #+#             */
/*   Updated: 2023/01/04 22:52:24 by mbadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include "iterator_traits.hpp"

namespace ft
{
    template<class Iterator>
    class random_access_iterator
    {
        public:
            typedef Iterator                                          value_type;
            typedef ptrdiff_t                                   difference_type;
            typedef value_type*                                 pointer;
            typedef value_type&                                 reference;
            typedef typename std::random_access_iterator_tag    iterator_category;
        private:
            pointer it;
        public:

            random_access_iterator(): it(NULL) {};
            random_access_iterator(const random_access_iterator& rhs) { it = NULL; *this = rhs; };
            random_access_iterator(pointer ptr): it(ptr) {};
            random_access_iterator& operator=(const random_access_iterator & rhs) { it = rhs.get_private_pointer(); return *this; };
            ~random_access_iterator() { };
            
            operator random_access_iterator<Iterator const>(void) const { return random_access_iterator<Iterator const>(it);}
            
            pointer get_private_pointer(void) const {return it;};

            reference operator*() const { return *it; };
            pointer operator->() const { return it; };
            random_access_iterator& operator++ () {++it; return *this;};
            random_access_iterator operator++ (int) {random_access_iterator tmp(*this); ++(*this); return *this;};
            random_access_iterator& operator-- () {--it; return *this;};
            random_access_iterator operator-- (int) {random_access_iterator tmp(*this); --(*this); return *this;};
            random_access_iterator operator+ (const difference_type& rhs) const {return random_access_iterator(it + rhs);};
            difference_type operator+ (const random_access_iterator& rhs) const {return it + rhs.it;};
            random_access_iterator operator- (const difference_type& rhs) const {return random_access_iterator(it - rhs);};
            difference_type operator- (const random_access_iterator& rhs) const {return it - rhs.it;};
            reference operator[] (const difference_type _n) const {return *(*this + _n);};
            random_access_iterator& operator+= (const difference_type rhs) {(it += rhs); return *this;};
            random_access_iterator& operator-= (const difference_type rhs) {(it -= rhs); return *this;};

            bool operator==(const random_access_iterator& rhs) const { return it == rhs.get_private_pointer(); }
            bool operator!=(const random_access_iterator& rhs) const { return !(it == rhs.get_private_pointer()); };
            bool operator< (const random_access_iterator& rhs) const {return (it < rhs.get_private_pointer());};
            bool operator> (const random_access_iterator& rhs) const {return (it > rhs.get_private_pointer());};
            bool operator<= (const random_access_iterator& rhs) const {return (it <= rhs.get_private_pointer());};
            bool operator>= (const random_access_iterator& rhs) const {return (it >= rhs.get_private_pointer());};
    };

    template<class Iterator>
    ft::random_access_iterator<Iterator> operator- (typename ft::random_access_iterator<Iterator>::difference_type lhs, typename ft::random_access_iterator<Iterator>& rhs) 
    {
        return lhs - rhs;
    };
    template<class Iterator>
    ft::random_access_iterator<Iterator> operator+ (typename ft::random_access_iterator<Iterator>::difference_type lhs, typename ft::random_access_iterator<Iterator>& rhs) 
    {
        return rhs + lhs;
    };
        
    // template<class It>
    // random_access_iterator<It>& operator= (const It& rhs) { *it = rhs; return *this; }; // to reconsider

    
    /*
    The iterator structure is a base class from which all other iterator types can be derived.
    This structure defines an interface that consists of five public types, as you see below.
    These types are used primarily by classes derived from iterator and by the iterator_traits class.
    */
    template<class Category, class T, class Distance = ptrdiff_t, 
            class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;
    };

}

#include <iterator>

#endif
