/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 21:18:56 by mbadaoui          #+#    #+#             */
/*   Updated: 2023/01/04 21:18:57 by mbadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <cstddef>

namespace ft
{
    /*
    Definers of the category of itertor. Each tag is an empty type.
    
    The category tag classes are used as compile tags for algorithm selection.
    The template function needs to findd the most specific category of its iterator
    argument so that it can use the most efficient algorithm at compile time.
    */
    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };
    /*
    Member types of iterator_traits
    */
    template<class Iter>
    struct iterator_traits
    {
        typedef typename Iter::difference_type difference_type;
        typedef typename Iter::value_type value_type;
        typedef typename Iter::pointer pointer;
        typedef typename Iter::reference reference;
        typedef typename Iter::iterator_category iterator_category;
    };
    /*
    Specializations:
    This type trait may be specialized for user-provided types
    that may be used as iterators
    */
    template<class T>
    struct iterator_traits<T*>
    {
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
        typedef ft::random_access_iterator_tag iterator_category;
    };
    /*
    For const T* specialization member types
    */
   template<class T>
   struct iterator_traits<const T*>
   {
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef ft::random_access_iterator_tag iterator_category;
   };
}

#endif
