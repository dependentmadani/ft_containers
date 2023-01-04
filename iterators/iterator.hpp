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

namespace ft
{
    /*
    The iterator structure is a base class from which all other iterator types can be derived.
    This structure defines an interface that consists of five public types, as you see below.
    These types are used primarily by classes derived from iterator and by the iterator_traits class.
    */
    template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
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
