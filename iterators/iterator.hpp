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
# define IERATOR_HPP

# include <cstddef>
#include <algorithm>

namespace ft
{
    template<class It>
    class random_access_iterator: public ft::iterator<ft::random_access_iterator_tag>
    {
        private:
            It *it;
        public:
            typedef It value_type;
            typedef ptrdiff_t difference_type;
            typedef value_type* pointer;
            typedef value_type& reference;
            typedef ft::random_access_iterator_tag iterator_category;

            random_access_iterator() {it = nullptr;};
            random_access_iterator(const random_access_iterator& rhs) { *it = rhs.it; };
            random_access_iterator& operator=(const random_access_iterator& rhs) { *it = rhs.it; return *this; };
            ~random_access_iterator() { delete it; };

            bool operator==(const random_access_iterator& lhs, const random_access_iterator& rhs) const { return lhs.it == rhs.it; }
            bool operator!=(const random_access_iterator& lhs, const random_access_iterator& rhs) const { return !(lhs.it == rhs.it); };
            reference operator*() const { return *it; };
            pointer operator->() const { return it; };
            random_access_iterator& operator= (const It& rhs) { return rhs; }; // to reconsider
            random_access_iterator& operator++ () {++it; return *this;};
            random_access_iterator operator++ (int) {random_access_iterator tmp(*this); ++(*this); return *this;};
            random_access_iterator& operator-- () {--it; return *this;};
            random_access_iterator operator-- (int) {random_access_iterator tmp(*this); --(*this); return *this;};
            random_access_iterator operator+ (const difference_type rhs) const {return random_access_iterator(it + rhs);};
            random_access_iterator operator+ (const random_access_iterator& rhs) const {return random_access_iterator(*this + rhs.it);};
            random_access_iterator operator- (const difference_type rhs) const {return random_access_iterator(it - rhs);};
            difference_type operator- (const random_access_iterator& lhs, const random_access_iterator& rhs) const {ptrdiff_t temp = lhs - rhs; return temp;};
            bool operator< (=const random_access_iterator& rhs) const {return (it < rhs.it);};
            bool operator> (=const random_access_iterator& rhs) const {return (it > rhs.it);};
            bool operator<= (=const random_access_iterator& rhs) const {return (it <= rhs.it);};
            bool operator>= (=const random_access_iterator& rhs) const {return (it >= rhs.it);};
            random_access_iterator& operator+= (const difference_type rhs) {(it += rhs); return *this;};
            random_access_iterator& operator-= (const difference_type rhs) {(it -= rhs; return *this;)};
            reference operator[] (const difference_type _n) const {return *(*this + _n);};
    };
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

#endif
