/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:30:56 by mbadaoui          #+#    #+#             */
/*   Updated: 2023/01/04 22:30:58 by mbadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"
# include "../Map/map_iterator.hpp"
# include "utility.hpp"
# include "enable_if.hpp"
# include "pair.hpp"

namespace ft
{
    template<typename Iter>
    class reverse_iterator
    {
        public:
            typedef Iter                                                    iterator_type;
            typedef typename ft::iterator_traits<Iter>::iterator_category   iterator_category;
            typedef typename ft::iterator_traits<Iter>::value_type          value_type;
            typedef typename ft::iterator_traits<Iter>::difference_type     difference_type;
            typedef typename ft::iterator_traits<Iter>::pointer             pointer;
            typedef typename ft::iterator_traits<Iter>::reference           reference;
        private:
            iterator_type current;
        public:

            reverse_iterator(): current() {};
            explicit reverse_iterator( iterator_type x ): current(x) {};
            template<typename U> reverse_iterator( const reverse_iterator<U>& other ): current(other.base()) {};
            // template<typename U> reverse_iterator& operator=( const reverse_iterator<U>& other )
            // {
            //     this->current = other.base();
            //     return *this;
            // };
            iterator_type base() const {return current;};
            reference operator* () const {Iter tmp = current; return *--tmp;};
            pointer operator-> () const {return &(operator*());};
            reference operator[] (difference_type n) const {return *(*this + n);};
            reverse_iterator& operator++ () {--current; return *this;};
            reverse_iterator operator++ (int) {reverse_iterator temp(*this); ++(*this); return temp;};
            reverse_iterator& operator+= (difference_type n) {current -= n; return *this;};
            reverse_iterator operator+ (difference_type n ) const {return reverse_iterator(current - n);};
            reverse_iterator& operator-- () {current++; return *this;};
            reverse_iterator operator-- (int) {reverse_iterator temp(*this); --(*this); return temp;};
            reverse_iterator& operator-= (difference_type n) {current += n; return *this;};
            reverse_iterator operator- (difference_type n ) const {return reverse_iterator(current + n);};
    };
    template<class Iterator> bool operator== (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() == rhs.base();
    };
    template<class Iterator1, class Iterator2> bool operator== (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() == rhs.base();
    };

    template<class Iterator> bool operator!= (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs)
    {
        return lhs.base()!= rhs.base();
    };
    template<class Iterator1, class Iterator2> bool operator!= (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base()!= rhs.base();
    };

    template<class Iterator> bool operator< (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() > rhs.base();
    };
    template<class Iterator1, class Iterator2> bool operator< (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() > rhs.base();
    };

    template<class Iterator> bool operator<= (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() >= rhs.base();
    };
    template<class Iterator1, class Iterator2> bool operator<= (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() >= rhs.base();
    };

    template<class Iterator> bool operator> (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() < rhs.base();
    };
    template<class Iterator1, class Iterator2> bool operator> (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() < rhs.base();
    };

    template<class Iterator> bool operator>= (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() <= rhs.base();
    };
    template<class Iterator1, class Iterator2> bool operator>= (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() <= rhs.base();
    };

    template<class Iterator> reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it)
    {
        return it + n;
    };
    template<class Iterator1, class iterator2> bool operator+ (typename reverse_iterator<Iterator1>::difference_type n, const reverse_iterator<iterator2>& it)
    {
        return it + n;
    };

    template<class Iterator1, class Iterator2> typename reverse_iterator<Iterator1>::difference_type operator- (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        return rhs.base() - lhs.base();
    };

}

# endif
