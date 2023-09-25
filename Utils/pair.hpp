/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:42:50 by mbadaoui          #+#    #+#             */
/*   Updated: 2023/02/19 14:42:52 by mbadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP


namespace ft
{
    /*
    pair is a class template that provides a way to store two heterogeneous objects as a single unit.
    A pair is a specific case of a tuple with two elements.
    If neither T1 or T2 is a possibly cv-qualified class type with non-trivial destructor, or array thereof,
    the destructor of pair is trivial.
    */
    template<typename T1, typename T2>
    struct pair
    {
        public:
            typedef T1 first_type;
            typedef T2 second_type;

            first_type first;
            second_type second;

            pair() : first(), second() {};
            pair(  const first_type &a, const second_type &b ) : first(a), second(b) {};
            template<typename X, typename Y>
            pair( const pair<X,Y> &pr ) : first(pr.first), second(pr.second) {};
            ~pair() {};

            pair& operator=( const pair& o )
            {
                if (this != &o){
                first = o.first;
                second = o.second;
                }
                return *this;
            };
    };
    template<class T1, class T2>
    ft::pair<T1, T2> make_pair(T1 t, T2 u)
    {
        return pair<T1, T2>(t, u);
    }

    template<class T1, class T2>
    bool operator== (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
    {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }

    template<class T1, class T2>
    bool operator!= (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
    {
        return !(lhs == rhs);
    }

    template<class T1, class T2>
    bool operator< (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
    {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }
    
    template<class T1, class T2>
    bool operator<= (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
    {
        return !(rhs < lhs);
    }
    
    template<class T1, class T2>
    bool operator> (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
    {
        return rhs < lhs;
    }

    template<class T1, class T2>
    bool operator>= (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
    {
        return !(lhs < rhs);
    }
}

#endif
