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
    class reverse_iterator: public ft::iterator <ft::iterator_traits<Iter>::iterator_category,
                                                ft::iterator_traits<Iter>::value__type,
                                                ft::iterator_traits<Iter>::difference_type,
                                                ft::iterator_traits<Iter>::pointer,
                                                ft::iterator_traits<Iter>::reference>
    {
        protected:
            Iter current;
        public:
            typedef typename Iter iterator_type;
            typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
            typedef typename ft::iterator_traits<Iter>::value_type value_type;
            typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
            typedef typename ft::iterator_traits<Iter>::pointer pointer;
            typedef typename ft::iterator_traits<Iter>::reference reference;

            reverse_iterator();
            explicit reverse_iterator( iterator_type x );
            template<class U> reverse_iterator( const reverse_iterator<U>& other );
            template<class U> reverse_iterator& operator=( const reverse_iterator<U>& other );
            iterator_type base() const;
    };
}

# endif
