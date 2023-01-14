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
# include "iterator.hpp"

namespace ft
{
    template<class Iter>
    class reverse_iterator: public ft::iterator <typename ft::iterator_traits<Iter>::iterator_category,
                                                typename ft::iterator_traits<Iter>::value__type,
                                                typename ft::iterator_traits<Iter>::difference_type,
                                                typename ft::iterator_traits<Iter>::pointer,
                                                typename ft::iterator_traits<Iter>::reference>
    {
        protected:
            Iter current;
        public:
            typedef Iter iterator_type;
            typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
            typedef typename ft::iterator_traits<Iter>::value_type value_type;
            typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
            typedef typename ft::iterator_traits<Iter>::pointer pointer;
            typedef typename ft::iterator_traits<Iter>::reference reference;

            reverse_iterator(): current() {};
            explicit reverse_iterator( iterator_type x ): current(x) {};
            template<class U> reverse_iterator( const reverse_iterator<U>& other ): current(other.base()) {};
            template<class U> reverse_iterator& operator=( const reverse_iterator<U>& other )
            {current = other.base(); return *this;};
            iterator_type base() const {return current;};
            reference operator* () const {return *current;};
            pointer operator-> () const {return current;};
            reference operator[] (difference_type n) const {return *(*this + n);};
            reverse_iterator& operator++ () {--current; return *this;};
            reverse_iterator operator++ (int) {reverse_iterator temp(*this); --current; return temp;};
            reverse_iterator& operator+= (difference_type n) {current -= n; return *this;};
            reverse_iterator operator+ (difference_type n ) const {return reverse_iterator(current - n);};
            reverse_iterator& operator-- () {current++; return *this;};
            reverse_iterator operator-- (int) {reverse_iterator temp(*this); ++current; return temp;};
            reverse_iterator& operator-= (difference_type n) {current += n; return *this;};
            reverse_iterator operator- (difference_type n ) const {return reverse_iterator(current + n);};
    };
    template<class Iterator1, class Iterator2>
    inline bool operator== (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template<class Iterator1, class Iterator2>
    inline bool operator!= (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base()!= rhs.base();
    }

    template<class Iterator1, class Iterator2>
    inline bool operator< (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template<class Iterator1, class Iterator2>
    inline bool operator<= (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template<class Iterator1, class Iterator2>
    inline bool operator> (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template<class Iterator1, class Iterator2>
    inline bool operator>= (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template<class Iter>
    inline reverse_iterator<Iter> operator+ (typename ft::reverse_iterator<Iter>::difference_type n, const ft::reverse_iterator<Iter>& it)
    {
        return ft::reverse_iterator<Iter>(it.base() - n);
    }

    template<class Iterator1, class Iterator2>
    inline typename reverse_iterator<Iterator1>::difference_type operator- (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        return rhs.base() - lhs.base();
    }

}

# endif