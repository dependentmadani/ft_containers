/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:34:41 by mbadaoui          #+#    #+#             */
/*   Updated: 2023/01/05 19:34:42 by mbadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include <type_traits>

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

    template <typename T> struct is_integral{ static const bool value = false;};
    template <> struct is_integral<bool> { static const bool value = true;};
    template <> struct is_integral<char> { static const bool value = true;};
    template <> struct is_integral<char16_t> { static const bool value = true;};
    template <> struct is_integral<char32_t> { static const bool value = true;};
    template <> struct is_integral<wchar_t> { static const bool value = true;};
    template <> struct is_integral<signed char> { static const bool value = true;};
    template <> struct is_integral<short int> { static const bool value = true;};
    template <> struct is_integral<int> { static const bool value = true;};
    template <> struct is_integral<long int> { static const bool value = true;};
    template <> struct is_integral<long long int> { static const bool value = true;};
    template <> struct is_integral<unsigned char> { static const bool value = true;};
    template <> struct is_integral<unsigned short int> { static const bool value = true;};
    template <> struct is_integral<unsigned int> { static const bool value = true;};
    template <> struct is_integral<unsigned long int> { static const bool value = true;};
    template <> struct is_integral<unsigned long long int> { static const bool value = true;};

}

#endif
