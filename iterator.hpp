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
    template<class It>
    class random_access_iterator
    {
        private:
            It *it;
        public:
            typedef It value_type;
            typedef ptrdiff_t difference_type;
            typedef value_type* pointer;
            typedef value_type& reference;
            typedef typename ft::random_access_iterator_tag iterator_category;

            random_access_iterator(): it(NULL) {};
            random_access_iterator(const random_access_iterator& rhs) { it = NULL; *this = rhs; };
            random_access_iterator(pointer ptr): it(ptr) {};
            random_access_iterator& operator=(const random_access_iterator & rhs) { it = rhs.get_private_pointer(); return *this; };
            virtual ~random_access_iterator() { };
            pointer get_private_pointer(void) const {return it;};
            operator random_access_iterator<const It>(void) const { return random_access_iterator<const It>(this->it);}


            reference operator*() const { return *it; };
            pointer operator->() const { return it; };
            random_access_iterator& operator++ () {++it; return *this;};
            random_access_iterator operator++ (int) {random_access_iterator tmp(*this); ++(*this); return *this;};
            random_access_iterator& operator-- () {--it; return *this;};
            random_access_iterator operator-- (int) {random_access_iterator tmp(*this); --(*this); return *this;};
            random_access_iterator operator+ (const difference_type rhs) const {return random_access_iterator(it + rhs);};
            random_access_iterator operator+ (const random_access_iterator& rhs) const {return random_access_iterator(*this + rhs.it);};
            random_access_iterator operator- (const difference_type rhs) const {return random_access_iterator(it - rhs);};
            reference operator[] (const difference_type _n) const {return *(*this + _n);};
            random_access_iterator& operator+= (const difference_type rhs) {(it += rhs); return *this;};
            random_access_iterator& operator-= (const difference_type rhs) {(it -= rhs); return *this;};
    };
        
    // template<class It>
    // random_access_iterator<It>& operator= (const It& rhs) { *it = rhs; return *this; }; // to reconsider

    template<class It>
    inline bool operator==(const ft::random_access_iterator<It>& lhs, const ft::random_access_iterator<It>& rhs) { return lhs.get_private_pointer() == rhs.get_private_pointer(); }
    template<class It>
    inline bool operator!=(const ft::random_access_iterator<It>& lhs, const ft::random_access_iterator<It>& rhs) { return !(lhs.get_private_pointer() == rhs.get_private_pointer()); };
    template<class It>
    inline bool operator< (const ft::random_access_iterator<It>& lhs, const ft::random_access_iterator<It>& rhs) {return (lhs.get_private_pointer() < rhs.get_private_pointer());};
    template<class It>
    inline bool operator> (const ft::random_access_iterator<It>& lhs, const ft::random_access_iterator<It>& rhs) {return (lhs.get_private_pointer() > rhs.get_private_pointer());};
    template<class It>
    inline bool operator<= (const ft::random_access_iterator<It>& lhs, const ft::random_access_iterator<It>& rhs) {return (lhs.get_private_pointer() <= rhs.get_private_pointer());};
    template<class It>
    inline bool operator>= (const ft::random_access_iterator<It>& lhs, const ft::random_access_iterator<It>& rhs) {return (lhs.get_private_pointer() >= rhs.get_private_pointer());};
    template<class It>
    inline typename ft::random_access_iterator<It>::difference_type operator- (const ft::random_access_iterator<It>& lhs, const ft::random_access_iterator<It>& rhs) {ptrdiff_t temp = lhs - rhs; return temp;};
    
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
