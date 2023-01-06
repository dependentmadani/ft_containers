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

namespace ft
{
    /*
    enable_if
    It is used to allow function overloading based on
    arbitrary properties of type. Relies on SFINE
    (if invalid argument or return type is formed during
    instantiation of function template, the instantiation
    is removed instead of compilation error).
    Often used in c++ template metaprogramming,
    Boots libraries, and c++ STL.
    */
    template<bool Cond, class T = void>
    struct enable_if { };
    template<class T> struct enable_if<true, T> // T is define only if Cond is true
    { 
        typedef T type;
    };

    template <typename T> struct is_integral
    {
        static bool const value = false;
        operator value_type()
        {
            return value;
        };
    };
    template <> struct is_integral<bool> { static bool const value = true;};
    template <> struct is_integral<char> { static bool const value = true;};
    template <> struct is_integral<char16_t> { static bool const value = true;};
    template <> struct is_integral<char32_t> { static bool const value = true;};
    template <> struct is_integral<wchar_t> { static bool const value = true;};
    template <> struct is_integral<signed char> { static bool const value = true;};
    template <> struct is_integral<short int> { static bool const value = true;};
    template <> struct is_integral<int> { static bool const value = true;};
    template <> struct is_integral<long int> { static bool const value = true;};
    template <> struct is_integral<long long int> { static bool const value = true;};
    template <> struct is_integral<unsigned char> { static bool const value = true;};
    template <> struct is_integral<unsigned short int> { static bool const value = true;};
    template <> struct is_integral<unsigned int> { static bool const value = true;};
    template <> struct is_integral<unsigned long int> { static bool const value = true;};
    template <> struct is_integral<unsigned long long int> { static bool const value = true;};


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
    inline bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
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
    inline bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first 2 < *first1)
                return false;
        }
        return (first1 == last1) && (first2 == last2);
    }

    template<class InputIt1, class InputIt2, class Compare >
    inline bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
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

    /*
    pair is a class template that provides a way to store two heterogeneous objects as a single unit.
    A pair is a specific case of a tuple with two elements.
    If neither T1 or T2 is a possibly cv-qualified class type with non-trivial destructor, or array thereof,
    the destructor of pair is trivial.
    */
    template<class T1, class T2>
    class pair
    {
        public:
            typedef T1 first_type;
            typedef T2 second_type;

            T1 first;
            T2 second;

            pair();
            pair( const T1& x, const T2& y );
            template<class U1, class U2> pair(const pair<U1, U2>& p);
            pair( const pair& p);
            pair& operator= (const pair& other);
    };
    template<class T1, class T2>
    ft::pair<T1, T2> make_pair(T1 t, T2 u)
    {
        return pair<T1, T2>(t, u);
    }

    template<class T1, class T2>
    inline bool operator== (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
    {
        return (lhs.first == rhs.first && lhs.second == rhs.second)
    }

    template<class T1, class T2>
    inline bool operator!= (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
    {
        return !(lhs == rhs);
    }

    template<class T1, class T2>
    inline bool operator< (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
    {
        return lhs < rhs || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }
    
    template<class T1, class T2>
    inline bool operator<= (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
    {
        return !(rhs < lhs);
    }
    
    template<class T1, class T2>
    inline bool operator> (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
    {
        return rhs < lhs;
    }

    template<class T1, class T2>
    inline bool operator>= (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
    {
        return !(lhs < rhs);
    }
}
# include <utility>
#endif
