/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:56:35 by mbadaoui          #+#    #+#             */
/*   Updated: 2023/01/06 12:56:36 by mbadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

# include <iostream>

namespace ft
{
    template <class InputIt>
    size_t Iterator_difference(InputIt first, InputIt last)
    {
        size_t i = 0;
        for (; first != last; ++first)
            i++;

        return i;
    }
    /*
    Compares the elements in the range [first1m last1) with those in the range
    beginning at first2, and returns true if all of the elements in both ranges match.
    The elements are compared using operator== (or pred, in the second function)
    */
    template<class InputIt1, class InputIt2>
    inline bool equal( InputIt1 first1, InputIt2 last1, InputIt2 first2)
    {
        while (first1 != last1)
        {
            if (!(*first1 == *first2))
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }

    /*
    BinaryPredicate is a set of requirements expected by some of the standard library
    facilities from the user-provided arguments
    the syntax is: bin_pred(*iter1, *iter2), or bin_pred(*iter, value)
    */
    template<class InputIt1,
            class InputIt2,
            class BinaryPredicate >
    bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
    {
        for (; first1 != last1; ++first1, (void)++first2)
        {
            if (!p(*first1, *first2))
                return false;
        }
        return true;
    }

    /*
    Checks if the first range [first1, last1) is lexicographically less than the second range [first2, last2).
    - Elements are compared using operator<
    - Elements are compared using the given binary comparison function comp.
    */
    template<class InputIt1, class InputIt2>
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    template<class InputIt1, class InputIt2, class Compare >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
    {
        for (; (first1!= last1) && (first2!= last2); ++first1, (void) ++first2)
        {
            if (comp(*first1, *first2))
                return true;
            if (comp(*first2, *first1))
                return false;
        }
        return false;
    }
}

#endif
