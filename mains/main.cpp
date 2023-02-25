/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:41:33 by mbadaoui          #+#    #+#             */
/*   Updated: 2023/02/19 14:41:34 by mbadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <stack>
#include <map>
#include <iostream>
#include <iterator>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <random>
#include "../map/map.hpp"
#include "../vector/vector.hpp"
#include "../stack/stack.hpp"

#define BLUE "\e[0;34m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[1;33m"
#define RESET "\e[0m"

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
#define TIME_FAC 5 // the ft::map methods can be slower up to std::map methods * TIME_FAC (MAX 20)

typedef std::pair<std::map<int, std::string>::iterator, std::map<int, std::string>::iterator> iter_def;
typedef ft::pair<ft::map<int, std::string>::iterator, ft::map<int, std::string>::iterator> ft_iter_def;
typedef std::pair<std::map<int, std::string>::const_iterator, std::map<int, std::string>::const_iterator> const_iter_def;
typedef ft::pair<ft::map<int, std::string>::const_iterator, ft::map<int, std::string>::const_iterator> ft_const_iter_def;

#define TEST_CASE(fn)                                                                                                             \
    cout << GREEN << "\t======================================================================================" << RESET << endl; \
    cout << endl;                                                                                                                 \
    cout << BLUE << "\t   Running " << #fn << " ... \t\t\t\t\t\t" << RESET << std::endl;                                          \
    fn();                                                                                                                         \
    cout << endl;                                                                                                                 \
    cout << GREEN << "\t======================================================================================" << RESET << endl;
using namespace std;

time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return (msecs_time);
}

template <typename Iter1, typename Iter2>
bool comparemaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        if (first1->first != first2->first || first1->second != first2->second)
            return false;
    return true;
}

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp
{
    bool operator()(const char &lhs, const char &rhs) const
    {
        return lhs < rhs;
    }
};

bool testmapConstructors()
{
    bool cond;
    std::map<char, int> first;
    ft::map<char, int> m_first;

    for (size_t i = 97; i < 110; i++)
    {
        first[i - 97] = i;
        m_first[i - 97] = i;
    }

    std::map<char, int> copy(first);
    ft::map<char, int> m_copy(m_first);

    cond = first.size() == m_first.size() && comparemaps(first.begin(), first.end(), m_first.begin(), m_first.end());

    std::map<char, int> second(first.begin(), first.end());
    ft::map<char, int> m_second(m_first.begin(), m_first.end());

    cond = cond && second.size() == m_second.size() && comparemaps(second.begin(), second.end(), m_second.begin(), m_second.end());
    std::map<char, int> third(second);
    ft::map<char, int> m_third(m_second);

    cond = cond && third.size() == m_third.size() && comparemaps(third.begin(), third.end(), m_third.begin(), m_third.end());

    std::map<char, int, classcomp> fourth;  // class as Compare
    ft::map<char, int, classcomp> m_fourth; // class as Compare

    cond = fourth.size() == m_fourth.size() && cond && comparemaps(fourth.begin(), fourth.end(), m_fourth.begin(), m_fourth.end());

    bool (*fn_pt)(char, char) = fncomp;
    std::map<char, int, bool (*)(char, char)> fifth(fn_pt);  // function pointer as Compare
    ft::map<char, int, bool (*)(char, char)> m_fifth(fn_pt); // function pointer as Compare

    cond = fifth.size() == m_fifth.size() && cond && comparemaps(fifth.begin(), fifth.end(), m_fifth.begin(), m_fifth.end());

    first = std::map<char, int>();
    m_first = ft::map<char, int>();

    cond = copy.size() == m_copy.size() && cond && comparemaps(copy.begin(), copy.end(), m_copy.begin(), m_copy.end());

    return cond;
}

void map_iterator_tests(void)
{
    /*------------ std::map ---------*/
    std::map<int, char> m;
    std::map<int, char>::iterator it, it1;

    ft::map<int, char> my_m;
    ft::map<int, char>::iterator my_it, my_it1, tmp;

    for (int i = 0; i < 10; ++i)
    {
        my_m.insert(ft::make_pair(i, static_cast<char>(i + 97)));
        m.insert(std::make_pair(i, static_cast<char>(i + 97)));
    }

    it = m.begin();
    it1 = ++(m.begin());
    my_it = my_m.begin();
    my_it1 = ++(my_m.begin());
    /*----------------------------------*/
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        ft::map<int, char>::iterator ob(my_it);
        EQUAL(&(*my_it) == &(*ob));
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " iterator to const_iterator "
              << "] --------------------]\t\t\033[0m";
    {
        ft::map<int, char>::const_iterator c_it, c_ob(my_it);
        c_it = my_it;
        EQUAL(&(*my_it) == &(*c_it) && (&(*my_it) == &(*c_ob)));
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it == it1) == (my_it == my_it1));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it != it1) == (my_it != my_it1));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((((*my_it).second = '6') == '6') && ((*my_it).first == ((*my_m.begin()).first)));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
              << "] --------------------]\t\t\033[0m";
    {
        /*--------------- std::map-------------------- */
        std::map<int, std::string> m;
        ft::map<int, std::string> my_m;

        for (int i = 0; i < 5; ++i)
        {
            m.insert(std::make_pair(13, "HELLO"));
            my_m.insert(ft::make_pair(13, "HELLO"));
        }

        ft::map<int, std::string>::iterator my_it = my_m.begin();
        std::map<int, std::string>::iterator it = m.begin();
        /*---------------------------------------------- */
        EQUAL(it->second.length() == my_it->second.length());
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++it operator "
              << "] --------------------]\t\t\033[0m";
    {
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;

            std::map<int, std::string> m;
            ft::map<int, std::string> ft_m;
            for (size_t i = 0; i < 1e6; ++i)
            {
                m.insert(std::make_pair(i, "value"));
                ft_m.insert(ft::make_pair(i, "value"));
            }
            start = get_time();
            for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it)
                ;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            for (ft::map<int, std::string>::iterator it = ft_m.begin(); it != ft_m.end(); ++it)
                ;
            ualarm(0, 0);
        }
        bool cond(false);
        {
            int res(0);
            int myints[] = {12, 82, 37, 64, 15};
            ft::map<int, int> m;
            for (size_t i = 0; i < 5; ++i)
                m.insert(ft::make_pair(myints[i], i));
            for (ft::map<int, int>::iterator it = m.begin(); it != m.end(); ++it)
                res += it->first;
            cond = res == 210;
        }
        {
            int res(0), tmp;
            int myints[] = {12, 82, 37, 64, 15};
            ft::map<int, int> m;
            for (size_t i = 0; i < 5; ++i)
                m.insert(ft::make_pair(myints[i], i));
            ft::map<int, int>::iterator it = m.begin(), eit = --m.end();
            tmp = eit->first;
            m.erase(eit);
            for (; it != m.end(); ++it)
                res += it->first;
            cond = cond && (res == (210 - tmp));
        }
        ++my_it; // I incremented here to make sure that the object changes
        EQUAL(*my_it == *my_it1);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --it operator "
              << "] --------------------]\t\t\033[0m";
    {
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;

            std::map<int, std::string> m;
            ft::map<int, std::string> ft_m;
            for (size_t i = 0; i < 1e6; ++i)
            {
                m.insert(std::make_pair(i, "value"));
                ft_m.insert(ft::make_pair(i, "value"));
            }
            start = get_time();
            std::map<int, std::string>::iterator it = --m.end();
            for (; it != m.begin(); --it)
                ;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            ft::map<int, std::string>::iterator ft_it = --ft_m.end();
            for (; ft_it != ft_m.begin(); --ft_it)
                ;
            ualarm(0, 0);
        }
        int res(0);
        {
            int myints[] = {12, 82, 37, 64, 15};
            ft::map<int, int> m;
            for (size_t i = 0; i < 5; ++i)
                m.insert(ft::make_pair(myints[i], i));
            ft::map<int, int>::iterator it = --m.end();
            for (;; --it)
            {
                if (it == m.begin())
                {
                    res += it->first;
                    break;
                }
                res += it->first;
            }
        }
        --my_it; // I decremented here to make sure that the object changes
        EQUAL(*my_it != *my_it1);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it++ operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it++;
    EQUAL(*my_it != *tmp && *my_it == *my_it1);
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it-- operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it--;
    EQUAL(*my_it != *tmp && *my_it == *(my_m.begin()));
}

void map_const_iterator_tests(void)
{
    /*------------ std::map ---------*/
    std::map<int, char> m;
    std::map<int, char>::const_iterator it, it1;

    ft::map<int, char> my_m;
    ft::map<int, char>::const_iterator my_it, my_it1, tmp;

    for (int i = 0; i < 10; ++i)
    {
        my_m.insert(ft::make_pair(i, static_cast<char>(i + 97)));
        m.insert(std::make_pair(i, static_cast<char>(i + 97)));
    }

    it = m.begin();
    it1 = ++(m.begin());
    my_it = my_m.begin();
    my_it1 = ++(my_m.begin());
    /*----------------------------------*/

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        ft::map<int, char>::const_iterator ob(my_it);
        EQUAL(*my_it == *ob);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it == it1) == (my_it == my_it1));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it != it1) == (my_it != my_it1));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
              << "] --------------------]\t\t\033[0m";
    {
        /*--------------- std::map-------------------- */
        std::map<int, std::string> m;
        ft::map<int, std::string> my_m;

        for (int i = 0; i < 5; ++i)
        {
            m.insert(std::make_pair(13, "HELLO"));
            my_m.insert(ft::make_pair(13, "HELLO"));
        }

        ft::map<int, std::string>::iterator my_it = my_m.begin();
        std::map<int, std::string>::iterator it = m.begin();
        /*---------------------------------------------- */
        EQUAL(it->second.length() == my_it->second.length());
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++it operator "
              << "] --------------------]\t\t\033[0m";
    ++my_it; // I incremented here to make sure that the object changes
    EQUAL(*my_it == *my_it1);
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --it operator "
              << "] --------------------]\t\t\033[0m";
    --my_it; // I decremented here to make sure that the object changes
    EQUAL(*my_it != *my_it1);
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it++ operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it++;
    EQUAL(*my_it != *tmp && *my_it == *my_it1);
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it-- operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it--;
    EQUAL(*my_it != *tmp && *my_it == *(my_m.begin()));
}

void map_reverse_iterator_tests(void)
{
    /*------------ std::reverse_iterator ---------*/
    std::map<int, char> m;
    for (int i = 0; i < 1e2; i++)
        m.insert(std::make_pair(i, 'A'));

    std::reverse_iterator<std::map<int, char>::iterator> rit(m.end()), rit_1(--m.end());

    ft::reverse_iterator<std::map<int, char>::iterator> my_rit(m.end()), my_rit1(--m.end());
    /*----------------------------------*/
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        ft::reverse_iterator<std::map<int, char>::iterator> ob(my_rit);
        EQUAL(*my_rit == *ob);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " riterator to const_riterator "
              << "] --------------------]\t\t\033[0m";
    {
        ft::map<int, char> my_m;
        for (int i = 0; i < 1e2; i++)
            my_m.insert(ft::make_pair(i, 'A'));

        ft::map<int, char>::reverse_iterator my_rit2(my_m.end());
        ft::map<int, char>::const_reverse_iterator c_it, c_ob(my_m.end());
        c_it = my_rit2;
        EQUAL(my_rit2->first == c_it->first && my_rit2->first == c_ob->first);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " base function "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit->first == (rit_1.base()->first)) && (my_rit->first == my_rit1.base()->first));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit == rit_1) == (my_rit == my_rit1));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit != rit_1) == (my_rit != my_rit1));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_rit->first == (--m.end())->first) && ((my_rit->first) == ((--m.end())->first))) && ((rit->first == (--m.end())->first) && ((rit->first) == ((--m.end())->first))));

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((((*my_rit).first == (*(--m.end())).first) && (((*my_rit).first) == ((*(--m.end())).first))) && (((*rit).first == (*(--m.end())).first) && ((*(rit)).first) == ((*(--m.end())).first)));

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++rit operator "
              << "] --------------------]\t\t\033[0m";
    ++my_rit; // I incremented here to make sure that the object changes
    ++rit;
    EQUAL(&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --rit operator "
              << "] --------------------]\t\t\033[0m";
    --my_rit; // I incremented here to make sure that the object changes
    --rit;
    EQUAL((my_rit->first == (--my_rit1)->first) && (rit->first == (--rit_1)->first));
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit++ operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::reverse_iterator<std::map<int, char>::iterator> tmp(rit++);
        ft::reverse_iterator<std::map<int, char>::iterator> my_tmp(my_rit++);
        EQUAL(tmp->first == (--rit)->first && my_tmp->first == (--my_rit)->first);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit-- operator "
              << "] --------------------]\t\t\033[0m";
    {
        rit++;
        my_rit++;
        std::reverse_iterator<std::map<int, char>::iterator> tmp(rit--);
        ft::reverse_iterator<std::map<int, char>::iterator> my_tmp(my_rit--);
        EQUAL(tmp->first == (++rit)->first && my_tmp->first == (++my_rit)->first);
    }
}

void MaptestConstructors()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " empty constructor "
              << "] --------------------]\t\t\033[0m";
    {
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;

            start = get_time();
            std::map<int, std::string> m;
            for (int i = 0; i < 1e6; ++i)
                m.insert(std::make_pair(i, "fill constructor test"));
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);

            ft::map<int, std::string> my_m;
            for (int i = 0; i < 1e6; ++i)
                my_m.insert(ft::make_pair(i, "fill constructor test"));
            ualarm(0, 0);
        }
        /*----------------------------------------------------------------------------------------------*/
        /*--------------- fill tow vectors with a 10 strings ------*/
        ft::map<int, std::string> my_m;
        std::map<int, std::string> m;
        for (int i = 0; i < 10; i++)
        {
            m.insert(std::make_pair(i, "Hello"));
            my_m.insert(ft::make_pair(i, "Hello"));
        }

        /*---------------------------------------------------------*/
        /*--------------- declare tow strings to store the results ------*/
        std::string res, my_res;
        /*---------------------------------------------------------*/
        for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it) // fill res from std::map
            res += it->second;
        for (ft::map<int, std::string>::iterator it = my_m.begin(); it != my_m.end(); ++it) // fill res from std::map
            my_res += it->second;
        EQUAL(res == my_res);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " range constructor "
              << "] --------------------]\t\t\033[0m";
    {
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            std::map<int, std::string> m;
            ft::map<int, std::string> my_m;

            for (size_t i = 0; i < 1e6; i++)
            {
                m.insert(std::make_pair(i, "range constructor test"));
                my_m.insert(ft::make_pair(i, "range constructor test"));
            }

            start = get_time();
            std::map<int, std::string> m1(m.begin(), m.end());
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            ft::map<int, std::string> my_m1(my_m.begin(), my_m.end());
            ualarm(0, 0);
        }
        /*-----------------------------------------------------------------------------------------------*/
        /*--------------- fill std::map with 10 strings and ft::map with range of iterators ------*/
        std::map<int, std::string> m;
        ft::map<int, std::string> my_m;
        for (size_t i = 0; i < 10; i++)
        {
            m.insert(std::make_pair(i, "range constructor test"));
            my_m.insert(ft::make_pair(i, "range constructor test"));
        }

        ft::map<int, std::string> my_m1(my_m.begin(), my_m.end()); // this one is to check if the range works with ft::map
        /*----------------------------------------------------------------------------------------------*/
        /*--------------- declare tow strings to store the results ------*/
        std::string res, my_res, my_res1;
        int sum(0), my_sum(0), my_sum1(0);
        /*--------------------------------------------------------*/
        for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it)
        { // fill res from std::map
            res += it->second;
            sum += it->first;
        }

        for (ft::map<int, std::string>::iterator it = my_m.begin(); it != my_m.end(); ++it)
        { // fill my_res from ft::map
            my_res += it->second;
            my_sum += it->first;
        }

        for (ft::map<int, std::string>::iterator it = my_m1.begin(); it != my_m1.end(); ++it)
        { // fill my_res1 from ft::map
            my_res1 += it->second;
            my_sum1 += it->first;
        }
        EQUAL(res == my_res && my_res == my_res1);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            std::map<int, char> m;
            ft::map<int, char> my_m;

            for (size_t i = 0; i < 1e3; i++)
            {
                m.insert(std::make_pair(i, 'X'));
                my_m.insert(ft::make_pair(i, 'X'));
            }

            start = get_time();
            std::map<int, char> copy_m(m);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * 20) : 20;

            alarm(diff);
            ft::map<int, char> my_copy_m(my_m);
            alarm(0);
        }
        /*---------------------------------------------------------------------------------------------*/
        /*---------------------------- declare a vector and fill with 'a', and create a copy of it ------------------*/
        ft::map<int, char> m1;
        for (int i = 0; i < 10; i++)
            m1.insert(ft::make_pair(i, 'a'));
        ft::map<int, char> copy_m(m1);
        /*-----------------------------------------------------------------------------------------------------------*/
        /*--------------- declare tow strings to store the results ------*/
        std::string res, res1;
        /*--------------------------------------------------------*/
        for (ft::map<int, char>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += it->second;

        for (ft::map<int, char>::iterator it = copy_m.begin(); it != copy_m.end(); ++it) // fill res from copy_m
            res1 += it->second;
        EQUAL(res == res1);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " Constructors with costum compare "
              << "] --------------------]\t\t\033[0m";
    EQUAL(testmapConstructors());
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator= (lhs.size = rhs.size) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            std::map<int, std::string> m1;
            std::map<int, std::string> m2;
            ft::map<int, std::string> ft_m1;
            ft::map<int, std::string> ft_m2;
            for (int i = 0; i < 1e6; ++i)
            {
                m1.insert(std::make_pair(i, "string1"));
                m2.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string1"));
                ft_m2.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1 = m2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::map ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1 = ft_m2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::map ---------------------*/
        std::map<int, std::string> m1;
        std::map<int, std::string> m2;
        ft::map<int, std::string> ft_m1;
        ft::map<int, std::string> ft_m2;
        for (int i = 0; i < 10; ++i)
        {
            m1.insert(std::make_pair(i, "string1"));
            m2.insert(std::make_pair(i, "string2"));
            ft_m1.insert(ft::make_pair(i, "string1"));
            ft_m2.insert(ft::make_pair(i, "string2"));
        }

        m1 = m2;
        ft_m1 = ft_m2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::map<int, std::string>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += it->first;

        for (ft::map<int, std::string>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
            ft_res += it->first;

        EQUAL(res == ft_res);
    }

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator= deep copy "
              << "] --------------------]\t\t\033[0m";
    {
        std::map<int, std::string> m1;
        std::map<int, std::string> m2;
        ft::map<int, std::string> ft_m2;
        ft::map<int, std::string> ft_m1;
        for (int i = 0; i < 1e4; ++i)
        {
            m2.insert(std::make_pair(i, "string2"));
            ft_m2.insert(ft::make_pair(i, "string2"));
        }

        m1 = m2;
        ft_m1 = ft_m2;
        m2.begin()->second = "hello";
        ft_m2.begin()->second = "hello";

        EQUAL((m1.begin()->second != m2.begin()->second) && (ft_m1.begin()->second != ft_m2.begin()->second));
    }

    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 2 : test with diff size vecotrs ----------------------------------------------------------------------*/
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size < rhs.size) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::map ---------------------*/
            std::map<int, std::string> m1;
            std::map<int, std::string> m2;
            ft::map<int, std::string> ft_m1;
            ft::map<int, std::string> ft_m2;

            for (int i = 0; i < 1e4; ++i)
            {
                m1.insert(std::make_pair(i, "string1"));
                ft_m1.insert(ft::make_pair(i, "string1"));
            }

            for (int i = 0; i < 1e6; ++i)
            {
                m2.insert(std::make_pair(i, "string2"));
                ft_m2.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1 = m2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::map ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1 = ft_m2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::map ---------------------*/
        std::map<int, std::string> m1;
        std::map<int, std::string> m2;
        ft::map<int, std::string> ft_m1;
        ft::map<int, std::string> ft_m2;
        for(size_t i = 0; i < 100; ++i)
        {
            m2.insert(std::make_pair(i, "value"));
            ft_m2.insert(ft::make_pair(i, "value"));
        }
        m1 = m2;
        /*-----------------------------------------------------*/
        /*------------------ ft::map ---------------------*/
        ft_m1 = ft_m2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::map<int, std::string>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += it->second;

        for (ft::map<int, std::string>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
            ft_res += it->second;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 3 : test with diff size vecotrs ----------------------------------------------------------------------*/
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size > rhs.size) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::map ---------------------*/
            std::map<int, std::string> m1;
            std::map<int, std::string> m2;
            ft::map<int, std::string> ft_m1;
            ft::map<int, std::string> ft_m2;

            for (int i = 0; i < 1e4; ++i)
            {
                m1.insert(std::make_pair(i, "string1"));
                ft_m1.insert(ft::make_pair(i, "string1"));
            }

            for (int i = 0; i < 1e2; ++i)
            {
                m2.insert(std::make_pair(i, "string2"));
                ft_m2.insert(ft::make_pair(i, "string2"));
            }
            start = get_time();
            m1 = m2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::map ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1 = ft_m2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::map ---------------------*/
        std::map<int, std::string> m1;
        std::map<int, std::string> m2;
        ft::map<int, std::string> ft_m1;
        ft::map<int, std::string> ft_m2;

        for (int i = 0; i < 20; ++i)
        {
            m1.insert(std::make_pair(i, "string1"));
            ft_m1.insert(ft::make_pair(i, "string1"));
        }

        for (int i = 0; i < 10; ++i)
        {
            m2.insert(std::make_pair(i, "string2"));
            ft_m2.insert(ft::make_pair(i, "string2"));
        }
        m1 = m2;
        /*-----------------------------------------------------*/
        /*------------------ ft::map ---------------------*/
        ft_m1 = ft_m2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::map<int, std::string>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += it->second;

        for (ft::map<int, std::string>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
            ft_res += it->second;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 4 : test with one empty vector ----------------------------------------------------------------------*/
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size = 0) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            std::map<int, std::string> m1;
            std::map<int, std::string> m2;
            ft::map<int, std::string> ft_m1;
            ft::map<int, std::string> ft_m2;

            for (int i = 0; i < 1e6; ++i)
            {
                m2.insert(std::make_pair(i, "string2"));
                ft_m2.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1 = m2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::map ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1 = ft_m2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::map ---------------------*/
        std::map<int, std::string> m1;
        std::map<int, std::string> m2;
        ft::map<int, std::string> ft_m1;
        ft::map<int, std::string> ft_m2;

        for (int i = 0; i < 10; ++i)
        {
            m2.insert(std::make_pair(i, "string2"));
            ft_m2.insert(ft::make_pair(i, "string2"));
        }
        m1 = m2;
        /*-----------------------------------------------------*/
        /*------------------ ft::map ---------------------*/

        ft_m1 = ft_m2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::map<int, std::string>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += it->second;

        for (ft::map<int, std::string>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
            ft_res += it->second;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 5 : test with one empty vector ----------------------------------------------------------------------*/
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (rhs.size = 0) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::nap ---------------------*/
            std::map<int, std::string> m1;
            std::map<int, std::string> m2;
            ft::map<int, std::string> ft_m1;
            ft::map<int, std::string> ft_m2;

            for (int i = 0; i < 1e6; ++i)
            {
                m1.insert(std::make_pair(i, "string1"));
                ft_m1.insert(ft::make_pair(i, "string1"));
            }
            start = get_time();
            m1 = m2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::map ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1 = ft_m2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::map ---------------------*/
        std::map<int, std::string> m1;
        std::map<int, std::string> m2;
        ft::map<int, std::string> ft_m1;
        ft::map<int, std::string> ft_m2;

        for (int i = 0; i < 10; ++i)
        {
            m1.insert(std::make_pair(i, "string2"));
            ft_m1.insert(ft::make_pair(i, "string2"));
        }
        m1 = m2;
        /*-----------------------------------------------------*/
        /*------------------ ft::map ---------------------*/
        ft_m1 = ft_m2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::map<int, std::string>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += it->second;

        for (ft::map<int, std::string>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
            ft_res += it->second;

        EQUAL(res == ft_res);
    }
}

void testIterators()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " begin and end methods "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::map<int, std::string> ft_m1;
            for (size_t i = 0; i < 1e6; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1.begin();
            m1.end();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1.begin();
            ft_m1.end();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::maps ---------------------*/
        std::map<int, std::string> m1;
        ft::map<int, std::string> ft_m1;

        for (size_t i = 0; i < 10; i++)
        {
            m1.insert(std::make_pair(i, "string2"));
            ft_m1.insert(ft::make_pair(i, "string2"));
        }

        std::map<int, std::string> const m2(m1.begin(), m1.end());
        ft::map<int, std::string> const ft_m2(ft_m1.begin(), ft_m1.end());

        /*-----------------------------------------------------*/
        /*------------------ ft::maps ---------------------*/
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res, c_res, c_ft_res;
        /*----------------------------------------------------*/
        for (std::map<int, std::string>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += it->second;
        for (std::map<int, std::string>::const_iterator rit = m2.begin(); rit != m2.end(); ++rit) // fill c_res from const m1
            c_res += rit->second;

        for (ft::map<int, std::string>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
            ft_res += it->second;
        for (ft::map<int, std::string>::const_iterator rit = ft_m2.begin(); rit != ft_m2.end(); ++rit) // fill c_ft_res from const ft_m1
            c_ft_res += rit->second;
        
        int arr[] = {12, 82, 37, 64, 15};
        ft::map<int, int> end_test;
        for(size_t i = 0; i < 5; ++i)
            end_test.insert(ft::make_pair(arr[i], i));
        ft::map<int, int>::iterator eit = end_test.end();
        eit--;
        EQUAL(res == ft_res && c_res == c_ft_res && eit->first == 82);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rbegin and rend methods "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::map<int, std::string> ft_m1;
            for (size_t i = 0; i < 1e6; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1.rbegin();
            m1.rend();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1.rbegin();
            ft_m1.rend();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::maps ---------------------*/
        std::map<int, std::string> m1;
        ft::map<int, std::string> ft_m1;

        for (size_t i = 0; i < 10; i++)
        {
            m1.insert(std::make_pair(i, "string2"));
            ft_m1.insert(ft::make_pair(i, "string2"));
        }

        std::map<int, std::string> const m2(m1.rbegin(), m1.rend());
        ft::map<int, std::string> const ft_m2(ft_m1.rbegin(), ft_m1.rend());

        /*-----------------------------------------------------*/
        /*------------------ ft::maps ---------------------*/
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res, c_res, c_ft_res;
        /*----------------------------------------------------*/
        for (std::map<int, std::string>::reverse_iterator it = m1.rbegin(); it != m1.rend(); ++it) // fill res from m1
            res += it->second;
        for (std::map<int, std::string>::const_reverse_iterator rit = m2.rbegin(); rit != m2.rend(); ++rit) // fill c_res from const m1
            c_res += rit->second;

        for (ft::map<int, std::string>::reverse_iterator it = ft_m1.rbegin(); it != ft_m1.rend(); ++it) // fill ft_res from ft_m1
            ft_res += it->second;
        for (ft::map<int, std::string>::const_reverse_iterator rit = ft_m2.rbegin(); rit != ft_m2.rend(); ++rit) // fill c_ft_res from const ft_m1
            c_ft_res += rit->second;
        int arr[] = {12, 82, 37, 64, 15};
        ft::map<int, int> end_test;
        for(size_t i = 0; i < 5; ++i)
            end_test.insert(ft::make_pair(arr[i], i));
        ft::map<int, int>::reverse_iterator rit = end_test.rend();
        rit--;
        EQUAL(res == ft_res && c_res == c_ft_res && rit->first == 12);
    }
}

void testCapacityMethods()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " size method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::map<int, std::string> ft_m1;
            for (size_t i = 0; i < 1e6; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1.size();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1.size();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::maps ---------------------*/
        std::map<int, std::string> m1; // fill constructor
        ft::map<int, std::string> ft_m1;
        for (size_t i = 0; i < 10; i++)
        {
            m1.insert(std::make_pair(i, "string2"));
            ft_m1.insert(ft::make_pair(i, "string2"));
        }

        std::map<int, std::string> m2;                         // empty constructor
        std::map<int, std::string> m3(m1.begin(), m1.end());   // range constructor with normal iterators
        std::map<int, std::string> m4(m3);                     // copy constructor
        std::map<int, std::string> m5(m1.rbegin(), m1.rend()); // range constructor with reverse iterators
        /*-----------------------------------------------------*/
        /*------------------ ft::maps ---------------------*/
        ft::map<int, std::string> ft_m2;
        ft::map<int, std::string> ft_m3(ft_m1.begin(), ft_m1.end());
        ft::map<int, std::string> ft_m4(ft_m1);
        ft::map<int, std::string> ft_m5(ft_m1.rbegin(), ft_m1.rend());
        /*----------------------------------------------------*/
        EQUAL(m1.size() == ft_m1.size() && m2.size() == ft_m2.size() && m3.size() == ft_m3.size() && m5.size() == ft_m5.size() && m4.size() == ft_m4.size());
    }

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " empty method "
              << "] --------------------]\t\t\033[0m";
    {
        std::map<int, std::string> m1;
        std::map<int, std::string> m2;
        ft::map<int, std::string> ft_m1;
        ft::map<int, std::string> ft_m2;
        m1[0] = "stringsrtring";
        ft_m1[0] = "stringsrtring";
        EQUAL(m1.empty() == ft_m1.empty() && m2.empty() == ft_m2.empty());
    }
}

void testElementAccess()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator [] "
              << "] --------------------]\t\t\033[0m";
    {
        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::map<int, std::string> ft_m1;

            for (size_t i = 0; i < 1e6; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string2"));
            }
            start = get_time();
            m1[1e6] = "string";
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1[1e6] = "string";
            ualarm(0, 0);
            /*----------------------------------------------------*/
            /*------------------ std::maps ---------------------*/
            start = get_time();
            m1[1e6 - 100] = "string";
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1[1e6 - 100] = "string";
            ualarm(0, 0);
            /*----------------------------------------------------*/
            /*------------------ std::maps ---------------------*/
            start = get_time();
            m1[1e6 - 100] = m1[1e5];
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1[1e6 - 100] = ft_m1[1e5];
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        std::map<char, std::string> m;
        ft::map<char, std::string> ft_m;

        m['a'] = "an element";
        m['b'] = "another element";
        m['c'] = m['b'];
        m['a'] = "test";

        ft_m['a'] = "an element";
        ft_m['b'] = "another element";
        ft_m['c'] = ft_m['b'];
        ft_m['a'] = "test";

        EQUAL(m['a'] == ft_m['a'] && m['b'] == ft_m['b'] && m['c'] == ft_m['c'] && m.size() == ft_m.size());
    }
}

void testModifiers()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " insert method "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond(false);
        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::map<int, std::string> ft_m1;

            start = get_time();
            for (size_t i = 0; i < 1e6; i++)
                m1.insert(std::make_pair(i, "string2"));
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::maps ---------------------*/
            ualarm(diff * 1e3, 0);
            for (size_t i = 0; i < 1e6; i++)
                ft_m1.insert(ft::make_pair(i, "string2"));

            ualarm(0, 0);
            /*----------------------------------------------------*/
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m_range;
            ft::map<int, std::string> ft_m_range;

            start = get_time();
            m_range.insert(m1.begin(), m1.end());
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m_range.insert(ft_m1.begin(), ft_m1.end());
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }

        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::map<int, std::string> ft_m1;

            start = get_time();
            m1.insert(std::make_pair(1e9, "string2"));
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1.insert(ft::make_pair(1e9, "string2"));
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }

        std::map<char, int> m;
        ft::map<char, int> ft_m;

        cond = m.size() == ft_m.size() && m.empty() == ft_m.empty();

        // first insert function version (single parameter):
        m.insert(std::pair<char, int>('a', 100));
        m.insert(std::pair<char, int>('z', 200));

        ft_m.insert(ft::pair<char, int>('a', 100));
        ft_m.insert(ft::pair<char, int>('z', 200));

        cond = cond && (m.size() == ft_m.size() && m.empty() == ft_m.empty());

        std::pair<std::map<char, int>::iterator, bool> ret;
        ft::pair<ft::map<char, int>::iterator, bool> ft_ret;

        ret = m.insert(std::pair<char, int>('z', 500));
        ft_ret = ft_m.insert(ft::pair<char, int>('z', 500));

        cond = cond && ret.second == ft_ret.second;

        // second insert function version (with hint position):
        std::map<char, int>::iterator it = m.begin();
        ft::map<char, int>::iterator ft_it = ft_m.begin();
        m.insert(it, std::pair<char, int>('b', 300));
        m.insert(it, std::pair<char, int>('c', 400));

        ft_m.insert(ft_it, ft::pair<char, int>('b', 300));
        ft_m.insert(ft_it, ft::pair<char, int>('c', 400));

        cond = cond && (m.size() == ft_m.size() && m.empty() == ft_m.empty());

        // third insert function version (range insertion):
        std::map<char, int> anothermap;
        ft::map<char, int> ft_anothermap;
        anothermap.insert(m.begin(), m.find('c'));
        ft_anothermap.insert(ft_m.begin(), ft_m.find('c'));
        cond = cond && (anothermap.size() == ft_anothermap.size() && anothermap.empty() == ft_anothermap.empty());

        cond = cond && comparemaps(ft_m.begin(), ft_m.end(), m.begin(), m.end()) && comparemaps(ft_anothermap.begin(), ft_anothermap.end(), anothermap.begin(), anothermap.end());
        EQUAL(cond);
    }

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " erase method "
              << "] --------------------]\t\t\033[0m";

    {
        bool cond(false);
        // erasing all the elements in the map;
        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::map<int, std::string> ft_m1;
            for (size_t i = 0; i < 1e6; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1.erase(m1.begin(), m1.end());
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1.erase(ft_m1.begin(), ft_m1.end());
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        std::map<char, int> m;
        ft::map<char, int> ft_m;
        std::map<char, int>::iterator it;
        ft::map<char, int>::iterator ft_it;

        // insert some values:
        ft_m['a'] = 10;
        ft_m['b'] = 20;
        ft_m['c'] = 30;
        ft_m['d'] = 40;
        ft_m['e'] = 50;
        ft_m['f'] = 60;

        m['a'] = 10;
        m['b'] = 20;
        m['c'] = 30;
        m['d'] = 40;
        m['e'] = 50;
        m['f'] = 60;

        cond = m.size() == ft_m.size() && comparemaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        it = m.find('b');
        ft_it = ft_m.find('b');

        cond = cond && (it->first == ft_it->first) && (it->second == ft_it->second);
        m.erase(it);       // erasing by iterator
        ft_m.erase(ft_it); // erasing by iterator

        cond = cond && comparemaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        int ret = m.erase('c');       // erasing by key
        int ft_ret = ft_m.erase('c'); // erasing by key

        cond = cond && ret == ft_ret && comparemaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        it = m.find('e');
        ft_it = ft_m.find('e');

        cond = cond && (it->first == ft_it->first) && (it->second == ft_it->second) && m.size() == ft_m.size();

        m.erase(it, m.end());          // erasing by range
        ft_m.erase(ft_it, ft_m.end()); // erasing by range

        cond = cond && m.empty() == ft_m.empty() && comparemaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        /* ---------- Testing some edge cases ---------- */

        std::map<int, std::string> m2;
        ft::map<int, std::string> ft_m2;

        for (size_t i = 0; i < 1e5; i++)
        {
            m2.insert(std::make_pair(i, "string1"));
            ft_m2.insert(ft::make_pair(i, "string1"));
        }

        std::map<int, std::string>::reverse_iterator it2 = m2.rbegin();
        ft::map<int, std::string>::reverse_iterator ft_it2 = ft_m2.rbegin();

        m2.erase(m2.begin());
        ft_m2.erase(ft_m2.begin());

        cond = cond && m2.size() == ft_m2.size() && comparemaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());

        m2.erase(it2->first);
        ft_m2.erase(ft_it2->first);

        cond = cond && m2.size() == ft_m2.size() && comparemaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());

        std::map<int, std::string> m3;
        ft::map<int, std::string> ft_m3;
        std::vector<int> vec;
        std::vector<int> ft_vec;
        std::random_device randDev;
        std::mt19937 generator(randDev());
        std::uniform_int_distribution<int> distr(0, 1e8);

        for (size_t i = 0; i < 1e6; i++)
        {
            m3.insert(std::make_pair(i, "string1"));
            ft_m3.insert(ft::make_pair(i, "string1"));
        }

        for (size_t i = 0; i < 1e6; ++i)
        {
            int n = distr(generator);
            int ret1 = m3.erase(n);
            int ret2 = ft_m3.erase(n);

            if (ret1 != ret2)
            {
                cond = false;
                break;
            }
        }

        if (!m3.empty())
        {
            m3.erase(m3.begin(), m3.end());
            m3.erase(m3.begin(), m3.end());
        }
        if (!ft_m3.empty())
        {
            ft_m3.erase(ft_m3.begin(), ft_m3.end());
            ft_m3.erase(ft_m3.begin(), ft_m3.end());
        }
        cond = cond && (m3.size() == ft_m3.size() && comparemaps(m3.begin(), m3.end(), ft_m3.begin(), ft_m3.end()));

        EQUAL(cond);
    }

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " swap method "
              << "] --------------------]\t\t\033[0m";

    {
        {
            time_t start, end, diff;

            /* ------------------ a > b ------------------ */
            std::map<int, std::string> m1, m2;
            ft::map<int, std::string> ft_m1, ft_m2;
            for (size_t i = 0; i < 1e6; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1.swap(m2);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1.swap(ft_m2);
            ualarm(0, 0);
            /*----------------------------------------------------*/

            /* ------------------ a and b are not empty ------------------ */
            for (size_t i = 0; i < 1e4; i++)
            {
                m2.insert(std::make_pair(i, "string2"));
                ft_m2.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1.swap(m2);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1.swap(ft_m2);
            ualarm(0, 0);
            /*----------------------------------------------------*/

            /* ------------------ a == b ------------------ */
            m1 = m2 = std::map<int, std::string>();
            ft_m1 = ft_m2 = ft::map<int, std::string>();
            start = get_time();
            m2.swap(m1);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m2.swap(ft_m1);
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        bool cond = false;
        std::map<char, int> foo, bar;
        ft::map<char, int> ft_foo, ft_bar;

        foo['x'] = 100;
        foo['y'] = 200;

        ft_foo['x'] = 100;
        ft_foo['y'] = 200;

        cond = foo.size() == ft_foo.size() && bar.size() == ft_bar.size();

        bar['a'] = 11;
        bar['b'] = 22;
        bar['c'] = 33;

        ft_bar['a'] = 11;
        ft_bar['b'] = 22;
        ft_bar['c'] = 33;

        cond = cond && foo.size() == ft_foo.size() && bar.size() == ft_bar.size() && comparemaps(foo.begin(), foo.end(), ft_foo.begin(), ft_foo.end()) && comparemaps(bar.begin(), bar.end(), ft_bar.begin(), ft_bar.end());

        foo.swap(bar);
        ft_foo.swap(ft_bar);

        cond = cond && foo.size() == ft_foo.size() && bar.size() == ft_bar.size() && comparemaps(foo.begin(), foo.end(), ft_foo.begin(), ft_foo.end()) && comparemaps(bar.begin(), bar.end(), ft_bar.begin(), ft_bar.end());

        std::map<std::string, std::string, std::greater<std::string> > m1, m2;
        ft::map<std::string, std::string, std::greater<std::string> > ft_m1, ft_m2;

        m1["γ"] = "gamma";
        m1["β"] = "beta";
        m1["α"] = "alpha";
        m1["γ"] = "gamma";

        m2["ε"] = "eplsilon";
        m2["δ"] = "delta";
        m2["ε"] = "epsilon";

        ft_m1["γ"] = "gamma";
        ft_m1["β"] = "beta";
        ft_m1["α"] = "alpha";
        ft_m1["γ"] = "gamma";

        ft_m2["ε"] = "eplsilon";
        ft_m2["δ"] = "delta";
        ft_m2["ε"] = "epsilon";

        const std::pair<std::string, std::string> &ref = *(m1.begin());
        const std::map<std::string, std::string, std::greater<std::string> >::iterator iter = std::next(m1.begin());
        const ft::pair<std::string, std::string> &ft_ref = *(ft_m1.begin());
        const ft::map<std::string, std::string, std::greater<std::string> >::iterator ft_iter = std::next(ft_m1.begin());

        // std::cout << "──────── before swap ────────\n"
        //           << "m1: " << m1 << "m2: " << m2 << "ref: " << ref
        //           << "\niter: " << *iter << '\n';

        cond = cond && ref.first == ft_ref.first && ref.second == ft_ref.second && iter->second == ft_iter->second && iter->first == ft_iter->first && m1.size() == ft_m1.size() && m2.size() && ft_m2.size();

        m1.swap(m2);
        ft_m1.swap(ft_m2);

        // _---------------_ << ──────── after swap ──────── >> _---------------_

        cond = cond && ref.first == ft_ref.first && ref.second == ft_ref.second && iter->second == ft_iter->second && iter->first == ft_iter->first && m1.size() == ft_m1.size() && m2.size() && ft_m2.size();

        EQUAL(cond);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " clear method "
              << "] --------------------]\t\t\033[0m";

    {
        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::map<int, std::string> ft_m1;
            for (size_t i = 0; i < 1e6; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();
            m1.clear();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1.clear();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        bool cond(false);
        std::map<char, int> m;
        ft::map<char, int> ft_m;

        m['x'] = 100;
        m['y'] = 200;
        m['z'] = 300;

        ft_m['x'] = 100;
        ft_m['y'] = 200;
        ft_m['z'] = 300;

        cond = m.size() == ft_m.size();

        m.clear();
        ft_m.clear();

        cond = cond && m.empty() == ft_m.empty() && comparemaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        m['a'] = 1101;
        m['b'] = 2202;
        ft_m['a'] = 1101;
        ft_m['b'] = 2202;

        cond = cond && m.size() == ft_m.size() && comparemaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        m = std::map<char, int>();
        ft_m = ft::map<char, int>();

        m.clear();
        ft_m.clear();

        cond = cond && m.size() == ft_m.size() && comparemaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        EQUAL(cond);
    }
}

struct ModCmp
{
    bool operator()(const int lhs, const int rhs) const
    {
        return (lhs % 97) < (rhs % 97);
    }
};

void testObservers()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " key_comp method "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond(true);
        std::map<int, int> m;
        ft::map<int, int> ft_m;
        std::map<int, int>::key_compare comp = m.key_comp();
        ft::map<int, int>::key_compare mycomp = ft_m.key_comp();

        for (size_t i = 0; i < 1e2; i++)
        {
            m.insert(std::make_pair(i, -1));
            ft_m.insert(ft::make_pair(i, -1));
        }

        int highest = m.rbegin()->first;       // key value of last element
        int ft_highest = ft_m.rbegin()->first; // key value of last element

        std::map<int, int>::iterator it = m.begin();
        ft::map<int, int>::iterator ft_it = ft_m.begin();
        do
        {
            if (!(it->first == ft_it->first && it->second == ft_it->second))
            {
                cond = false;
                break;
            }

        } while (comp((*it++).first, highest) && mycomp((*ft_it++).first, ft_highest));
        EQUAL(cond);
    }

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " value_comp method "
              << "] --------------------]\t\t\033[0m";
    {
        int sum(0);
        int s_key(0);
        ft::map<char, int> mymap;

        mymap['x'] = 1001;
        mymap['y'] = 2002;
        mymap['z'] = 3003;

        ft::pair<char, int> highest = *mymap.rbegin(); // last element

        ft::map<char, int>::iterator it = mymap.begin();
        do
        {
            sum += it->second;
            s_key += it->first;
        } while (mymap.value_comp()(*it++, highest));

        EQUAL(sum == 6006 && s_key == 363);
    }
}
void testNonMemberSwap()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " non-member swap method "
              << "] --------------------]\t\t\033[0m";
    {
        int res(0), ft_res(0), key_res(0), ft_key_res(0);
        ft::map<char, int> foo, bar;

        foo['x'] = 100;
        foo['y'] = 200;

        bar['a'] = 11;
        bar['b'] = 22;
        bar['c'] = 33;

        swap(foo, bar);

        for (ft::map<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
        {
            res += it->second;
            key_res += it->first;
        }

        for (ft::map<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
        {
            ft_res += it->second;
            ft_key_res += it->first;
        }
        EQUAL((res == 66) && (ft_res = 300) && (key_res == ('a' + 'b' + 'c')) && (ft_key_res == ('x' + 'y')));
    }
}

void testOperations()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " find method "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond(true);
        {
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::map<int, std::string> ft_m1;
            for (size_t i = 0; i < 1e6; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(ft::make_pair(i, "string2"));
            }

            start = get_time();

            for (size_t i = 1e1; i < 1e5; i += 10)
                m1.find(i);

            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::maps ---------------------*/
            ualarm(diff * 1e3, 0);
            for (size_t i = 1e1; i < 1e5; i += 10)
                ft_m1.find(i);
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }

        std::vector<int> vec;
        std::vector<int> ft_vec;
        std::random_device randDev;
        std::mt19937 generator(randDev());
        std::uniform_int_distribution<int> distr(0, 1e8);

        std::map<int, std::string> m1;
        ft::map<int, std::string> ft_m1;
        std::map<int, std::string>::iterator it;
        ft::map<int, std::string>::iterator ft_it;

        for (size_t i = 0; i < 1e6; i++)
        {
            m1.insert(std::make_pair(i, "string2"));
            ft_m1.insert(ft::make_pair(i, "string2"));
        }

        for (size_t i = 0; i < 1e6; i++)
        {
            int n = distr(generator);
            it = m1.find(n);
            ft_it = ft_m1.find(n);
            if (it == m1.end() && ft_it == ft_m1.end())
                continue;
            if (it == m1.end() && ft_it != ft_m1.end())
            {
                cond = false;
                break;
            }
            else
            {
                vec.push_back(it->first);
                ft_vec.push_back(ft_it->first);
            }
        }

        std::map<char, int> m;
        ft::map<char, int> ft_m;
        std::map<char, int>::iterator it2;
        ft::map<char, int>::iterator ft_it2;

        m['a'] = 50;
        m['b'] = 100;
        m['c'] = 150;
        m['d'] = 200;

        ft_m['a'] = 50;
        ft_m['b'] = 100;
        ft_m['c'] = 150;
        ft_m['d'] = 200;

        it2 = m.find('b');
        ft_it2 = ft_m.find('b');

        cond = cond && it2->first == ft_it2->first && it2->second == ft_it2->second;

        if (it2 != m.end())
            m.erase(it2);
        if (ft_it2 != ft_m.end())
            ft_m.erase(ft_it2);

        cond = cond && comparemaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        EQUAL(cond && vec == ft_vec);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " count method "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond;
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            bool res, ft_res;

            std::map<int, std::string> m;
            ft::map<int, std::string> ft_m;
            for (size_t i = 0; i < 1e6; ++i)
            {
                m.insert(std::make_pair(i, "value"));
                ft_m.insert(ft::make_pair(i, "value"));
            }
            start = get_time();
            res = m.count(1e6 - 10);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            ft_res = ft_m.count(1e6 - 10);
            ualarm(0, 0);
            cond = ft_res == res;
        }
        std::map<int, std::string> m;
        ft::map<int, std::string> ft_m;
        int arr[] = {20, 10, 100, 15, 60, 90, 65, 200, 150}; // size = 9
        for (size_t i = 0; i < 9; ++i)
        {
            m.insert(std::make_pair(arr[i], "value"));
            ft_m.insert(ft::make_pair(arr[i], "value"));
        }
        cond = (cond && (m.count(65) == ft_m.count(65) && m.count(300) == ft_m.count(300)));
        EQUAL(cond);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " lower_bound method "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond;
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            int res, ft_res;

            std::map<int, std::string> m;
            ft::map<int, std::string> ft_m;
            for (size_t i = 0; i < 1e6; ++i)
            {
                m.insert(std::make_pair(i, "value"));
                ft_m.insert(ft::make_pair(i, "value"));
            }
            start = get_time();
            res = m.lower_bound(1e5)->first;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            ft_res = ft_m.lower_bound(1e5)->first;
            ualarm(0, 0);
            cond = ft_res == res;
        }
        std::map<int, std::string> m;
        ft::map<int, std::string> ft_m;
        int arr[] = {20, 10, 100, 15, 60, 90, 65, 200, 150}; // size = 9
        for (size_t i = 0; i < 9; ++i)
        {
            m.insert(std::make_pair(arr[i], "value"));
            ft_m.insert(ft::make_pair(arr[i], "value"));
        }
        std::map<int, std::string> const c_m(m.begin(), m.end());
        ft::map<int, std::string> const c_ft_m(ft_m.begin(), ft_m.end());
        cond = (cond && (m.lower_bound(15)->first == ft_m.lower_bound(15)->first));
        cond = (cond && (m.lower_bound(65)->first == ft_m.lower_bound(65)->first));
        cond = (cond && (m.lower_bound(63)->first == ft_m.lower_bound(63)->first));
        cond = (cond && (m.lower_bound(120)->first == ft_m.lower_bound(120)->first));
        cond = (cond && (m.lower_bound(70)->first == ft_m.lower_bound(70)->first));

        cond = (cond && (c_m.lower_bound(15)->first == c_ft_m.lower_bound(15)->first));
        cond = (cond && (c_m.lower_bound(65)->first == c_ft_m.lower_bound(65)->first));
        cond = (cond && (c_m.lower_bound(63)->first == c_ft_m.lower_bound(63)->first));
        cond = (cond && (c_m.lower_bound(120)->first == c_ft_m.lower_bound(120)->first));
        cond = (cond && (c_m.lower_bound(70)->first == c_ft_m.lower_bound(70)->first));
        EQUAL(cond);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " upper_bound method "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond;
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            int res, ft_res;

            std::map<int, std::string> m;
            ft::map<int, std::string> ft_m;
            for (size_t i = 0; i < 1e6; ++i)
            {
                m.insert(std::make_pair(i, "value"));
                ft_m.insert(ft::make_pair(i, "value"));
            }
            start = get_time();
            res = m.upper_bound(1e5)->first;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            ft_res = ft_m.upper_bound(1e5)->first;
            ualarm(0, 0);
            cond = ft_res == res;
        }
        std::map<int, std::string> m;
        ft::map<int, std::string> ft_m;
        int arr[] = {20, 10, 100, 15, 60, 90, 65, 200, 150}; // size = 9
        for (size_t i = 0; i < 9; ++i)
        {
            m.insert(std::make_pair(arr[i], "value"));
            ft_m.insert(ft::make_pair(arr[i], "value"));
        }
        std::map<int, std::string> const c_m(m.begin(), m.end());
        ft::map<int, std::string> const c_ft_m(ft_m.begin(), ft_m.end());
        cond = (cond && (m.upper_bound(15)->first == ft_m.upper_bound(15)->first));
        cond = (cond && (m.upper_bound(65)->first == ft_m.upper_bound(65)->first));
        cond = (cond && (m.upper_bound(63)->first == ft_m.upper_bound(63)->first));
        cond = (cond && (m.upper_bound(120)->first == ft_m.upper_bound(120)->first));
        cond = (cond && (m.upper_bound(70)->first == ft_m.upper_bound(70)->first));
        cond = (cond && (m.upper_bound(150)->first == ft_m.upper_bound(150)->first));

        cond = (cond && (c_m.upper_bound(15)->first == c_ft_m.upper_bound(15)->first));
        cond = (cond && (c_m.upper_bound(65)->first == c_ft_m.upper_bound(65)->first));
        cond = (cond && (c_m.upper_bound(63)->first == c_ft_m.upper_bound(63)->first));
        cond = (cond && (c_m.upper_bound(120)->first == c_ft_m.upper_bound(120)->first));
        cond = (cond && (c_m.upper_bound(70)->first == c_ft_m.upper_bound(70)->first));
        cond = (cond && (c_m.upper_bound(150)->first == c_ft_m.upper_bound(150)->first));
        EQUAL(cond);
    }
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " equal_range method "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond;
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            iter_def res;
            ft_iter_def ft_res;

            std::map<int, std::string> m;
            ft::map<int, std::string> ft_m;
            for (size_t i = 0; i < 1e6; ++i)
            {
                m.insert(std::make_pair(i, "value"));
                ft_m.insert(ft::make_pair(i, "value"));
            }
            start = get_time();
            res = m.equal_range(1e5);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            ft_res = ft_m.equal_range(1e5);
            ualarm(0, 0);
            cond = (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first);
        }
        iter_def res;
        ft_iter_def ft_res;
        const_iter_def c_res;
        ft_const_iter_def ft_c_res;
        std::map<int, std::string> m;
        ft::map<int, std::string> ft_m;
        int arr[] = {20, 10, 100, 15, 60, 90, 65, 200, 150}; // size = 9
        for (size_t i = 0; i < 9; ++i)
        {
            m.insert(std::make_pair(arr[i], "value"));
            ft_m.insert(ft::make_pair(arr[i], "value"));
        }
        std::map<int, std::string> const c_m(m.begin(), m.end());
        ft::map<int, std::string> const c_ft_m(ft_m.begin(), ft_m.end());

        res = m.equal_range(15);
        ft_res = ft_m.equal_range(15);
        cond = (cond && (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first));
        res = m.equal_range(65);
        ft_res = ft_m.equal_range(65);
        cond = (cond && (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first));
        res = m.equal_range(63);
        ft_res = ft_m.equal_range(63);
        cond = (cond && (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first));
        res = m.equal_range(120);
        ft_res = ft_m.equal_range(120);
        cond = (cond && (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first));
        res = m.equal_range(70);
        ft_res = ft_m.equal_range(70);
        cond = (cond && (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first));
        res = m.equal_range(150);
        ft_res = ft_m.equal_range(150);
        cond = (cond && (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first));

        c_res = c_m.equal_range(15);
        ft_c_res = c_ft_m.equal_range(15);
        cond = (cond && (ft_c_res.first->first == c_res.first->first) && (ft_c_res.second->first == c_res.second->first));
        c_res = c_m.equal_range(65);
        ft_c_res = c_ft_m.equal_range(65);
        cond = (cond && (ft_c_res.first->first == c_res.first->first) && (ft_c_res.second->first == c_res.second->first));
        c_res = c_m.equal_range(63);
        ft_c_res = c_ft_m.equal_range(63);
        cond = (cond && (ft_c_res.first->first == c_res.first->first) && (ft_c_res.second->first == c_res.second->first));
        c_res = c_m.equal_range(120);
        ft_c_res = c_ft_m.equal_range(120);
        cond = (cond && (ft_c_res.first->first == c_res.first->first) && (ft_c_res.second->first == c_res.second->first));
        c_res = c_m.equal_range(70);
        ft_c_res = c_ft_m.equal_range(70);
        cond = (cond && (ft_c_res.first->first == c_res.first->first) && (ft_c_res.second->first == c_res.second->first));
        c_res = c_m.equal_range(150);
        ft_c_res = c_ft_m.equal_range(150);
        cond = (cond && (ft_c_res.first->first == c_res.first->first) && (ft_c_res.second->first == c_res.second->first));
        EQUAL(cond);
    }
}

void testAllocatorMethodes()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " get_allocator method "
              << "] --------------------]\t\t\033[0m";
    {
        int psize;
        ft::map<char, int> mymap;
        ft::pair<const char, int> *p;

        // allocate an array of 5 elements using mymap's allocator:
        p = mymap.get_allocator().allocate(5);

        psize = sizeof(std::map<char, int>::value_type) * 5;
        EQUAL(psize == 40);
        mymap.get_allocator().deallocate(p, 5);
    }
}
void testRetionalOperators()
{

    /* ---------------  pretty simple tests --------------- */
    std::map<char, int> foo, bar;
    ft::map<char, int> ft_foo, ft_bar;
    bool res;
    bool ft_res;
    foo['a'] = 100;
    foo['b'] = 200;
    bar['a'] = 10;
    bar['z'] = 1000;

    ft_foo['a'] = 100;
    ft_foo['b'] = 200;
    ft_bar['a'] = 10;
    ft_bar['z'] = 1000;

    std::map<int, std::string> m, m1;
    ft::map<int, std::string> ft_m, ft_m1;
    for (size_t i = 0; i < 1e6; ++i)
    {
        m.insert(std::make_pair(i, "value"));
        ft_m.insert(ft::make_pair(i, "value"));
    }
    for (size_t i = 0; i < 1e6; ++i)
    {
        m1.insert(std::make_pair(i + 1, "value1"));
        ft_m1.insert(ft::make_pair(i + 1, "value1"));
    }

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator == "
              << "] --------------------]\t\t\033[0m";
    /*---------------------------------- time limit test --------------------------------------------*/
    {
        time_t start, end, diff;
        start = get_time();
        res = m == m1;
        end = get_time();
        diff = end - start;
        diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        ualarm(diff * 1e3, 0);
        ft_res = ft_m == ft_m1;
        ualarm(0, 0);
    }

    EQUAL(((foo == bar) == (ft_foo == ft_bar)) && res == ft_res);

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator != "
              << "] --------------------]\t\t\033[0m";
    /*---------------------------------- time limit test --------------------------------------------*/
    {
        time_t start, end, diff;

        start = get_time();
        res = m != m1;
        end = get_time();
        diff = end - start;
        diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        ualarm(diff * 1e3, 0);
        ft_res = ft_m != ft_m1;
        ualarm(0, 0);
    }
    EQUAL((foo != bar) == (ft_foo != ft_bar) && res == ft_res);

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator > "
              << "] --------------------]\t\t\033[0m";
    /*---------------------------------- time limit test --------------------------------------------*/
    {
        time_t start, end, diff;
        start = get_time();
        res = m > m1;
        end = get_time();
        diff = end - start;
        diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        ualarm(diff * 1e3, 0);
        ft_res = ft_m > ft_m1;
        ualarm(0, 0);
    }
    EQUAL(((foo > bar) == (ft_foo > ft_bar)) && (res == ft_res));

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator >= "
              << "] --------------------]\t\t\033[0m";
    /*---------------------------------- time limit test --------------------------------------------*/
    {
        time_t start, end, diff;

        start = get_time();
        res = m >= m1;
        end = get_time();
        diff = end - start;
        diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        ualarm(diff * 1e3, 0);
        ft_res = ft_m >= ft_m1;
        ualarm(0, 0);
    }
    EQUAL(((foo >= bar) == (ft_foo >= ft_bar)) && (res == ft_res));

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator < "
              << "] --------------------]\t\t\033[0m";
    /*---------------------------------- time limit test --------------------------------------------*/
    {
        time_t start, end, diff;

        start = get_time();
        res = m < m1;
        end = get_time();
        diff = end - start;
        diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        ualarm(diff * 1e3, 0);
        ft_res = ft_m < ft_m1;
        ualarm(0, 0);
    }
    EQUAL(((foo < bar) == (ft_foo < ft_bar)) && (res == ft_res));

    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator <= "
              << "] --------------------]\t\t\033[0m";
    /*---------------------------------- time limit test --------------------------------------------*/
    {
        time_t start, end, diff;

        start = get_time();
        res = m <= m1;
        end = get_time();
        diff = end - start;
        diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        ualarm(diff * 1e3, 0);
        ft_res = ft_m <= ft_m1;
        ualarm(0, 0);
    }
    EQUAL(((foo <= bar) == (ft_foo <= ft_bar)) && (res == ft_res));
}

void alarm_handler(int seg)
{
    (void)seg;
    std::cout << "\033[1;33mTLE\033[0m\n";
    kill(getpid(), SIGINT);
}

#if 1
void iterator_tests(void)
{
    std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< vector iterator tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
    /*------------ std::vector ---------*/
    std::vector<int> v(3, 4);
    std::vector<int>::iterator it, it1;
    it = v.begin();
    it1 = v.begin() + 1;
    /*----------------------------------*/
    /*------------ ft::vector ---------*/
    ft::vector<int> my_v(3, 4);
    ft::vector<int>::iterator my_it, my_it1, tmp;
    my_it = my_v.begin();
    my_it1 = my_v.begin() + 1;
    /*----------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        ft::vector<int>::iterator ob(my_it);
        EQUAL(&(*my_it) == &(*ob));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " iterator to const_iterator "
              << "] --------------------]\t\t\033[0m";
    {
        ft::vector<int>::const_iterator c_it, c_ob(my_it);
        c_it = my_it;
        EQUAL(&(*my_it) == &(*c_it) && (&(*my_it) == &(*c_ob)));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it == it1) == (my_it == my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it != it1) == (my_it != my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " > operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it > it1) == (my_it > my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " >= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it >= it1) == (my_it >= my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " < operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it < it1) == (my_it < my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " <= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it <= it1) == (my_it <= my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((*my_it = 6) == 6) && (*my_it == *(my_v.begin())));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
              << "] --------------------]\t\t\033[0m";
    {
        /*--------------- std::vector-------------------- */
        std::vector<std::string> v(3, "hello");
        std::vector<std::string>::iterator it = v.begin();
        /*---------------------------------------------- */
        /*--------------- ft::vector-------------------- */
        ft::vector<std::string> my_v(3, "hello");
        ft::vector<std::string>::iterator my_it = my_v.begin();
        /*---------------------------------------------- */
        EQUAL(it->length() == my_it->length());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(&(*my_it) == &(*(my_it1 - 1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " += operator "
              << "] --------------------]\t\t\033[0m";
    my_it += 1;
    EQUAL(&(*my_it) == &(*my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -= operator "
              << "] --------------------]\t\t\033[0m";
    my_it -= 1;
    EQUAL(&(*my_it) == &(*(my_it1 - 1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " [] operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_it[0] = 5) == 5) && (*my_it == 5));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++it operator "
              << "] --------------------]\t\t\033[0m";
    ++my_it; // I incremented here to make sure that the object changes
    EQUAL(&(*my_it) == &(*my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --it operator "
              << "] --------------------]\t\t\033[0m";
    --my_it; // I decremented here to make sure that the object changes
    EQUAL(&(*my_it) == &(*(my_it1 - 1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator (n + it) "
              << "] --------------------]\t\t\033[0m";
    EQUAL(&(*(1 + my_it)) == &(*(my_it1)) && (&(*my_it) == &(*(my_v.begin()))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator (it1 - it) "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_it1 - my_it == 1)) && ((my_it - my_it1) == -1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it++ operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it++;
    EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*my_it1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it-- operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it--;
    EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*(my_v.begin()))));
    std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}

void const_iterator_tests(void)
{
    std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< vector const_iterator tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
    /*------------ std::vector ---------*/
    std::vector<int> v(3, 4);
    std::vector<int>::const_iterator it, it1;
    it = v.begin();
    it1 = v.begin() + 1;
    /*----------------------------------*/
    /*------------ ft::vector ---------*/
    ft::vector<int> my_v(3, 4);
    ft::vector<int>::const_iterator my_it, my_it1, tmp;
    my_it = my_v.begin();
    my_it1 = my_v.begin() + 1;
    /*----------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        ft::vector<int>::const_iterator ob(my_it);
        EQUAL(&(*my_it) == &(*ob));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it == it1) == (my_it == my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it != it1) == (my_it != my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " > operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it > it1) == (my_it > my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " >= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it >= it1) == (my_it >= my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " < operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it < it1) == (my_it < my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " <= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it <= it1) == (my_it <= my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(*my_it == *(my_v.begin()) && (&(*my_it) == &(*(my_v.begin()))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
              << "] --------------------]\t\t\033[0m";
    {
        /*--------------- std::vector-------------------- */
        std::vector<std::string> v(3, "hello");
        std::vector<std::string>::const_iterator it = v.begin();
        /*---------------------------------------------- */
        /*--------------- ft::vector-------------------- */
        ft::vector<std::string> my_v(3, "hello");
        ft::vector<std::string>::const_iterator my_it = my_v.begin();
        /*---------------------------------------------- */
        EQUAL(it->length() == my_it->length());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(&(*my_it) == &(*(my_it1 - 1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " += operator "
              << "] --------------------]\t\t\033[0m";
    my_it += 1;
    EQUAL(&(*my_it) == &(*my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -= operator "
              << "] --------------------]\t\t\033[0m";
    my_it -= 1;
    EQUAL(&(*my_it) == &(*(my_it1 - 1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " [] operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((my_it[0] == *(my_v.begin())) && (&(my_it[0]) == &(*(my_v.begin()))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++it operator "
              << "] --------------------]\t\t\033[0m";
    ++my_it; // I incremented here to make sure that the object changes
    EQUAL(&(*my_it) == &(*my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --it operator "
              << "] --------------------]\t\t\033[0m";
    --my_it; // I decremented here to make sure that the object changes
    EQUAL(&(*my_it) == &(*(my_it1 - 1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator (n + it) "
              << "] --------------------]\t\t\033[0m";
    EQUAL(&(*(1 + my_it)) == &(*(my_it1)) && (&(*my_it) == &(*(my_v.begin()))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator (it1 - it) "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_it1 - my_it == 1)) && ((my_it - my_it1) == -1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it++ operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it++;
    EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*my_it1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it-- operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it--;
    EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*(my_v.begin()))));
    std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}

void reverse_iterator_tests(void)
{
    std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< reverse_iterator tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
    /*------------ std::reverse_iterator ---------*/
    std::vector<int> v(3, 4);
    std::reverse_iterator<std::vector<int>::iterator> rit(v.end()), rit_1(v.end() - 1);
    /*----------------------------------*/
    /*------------ ft::reverse_iterator ---------*/
    ft::reverse_iterator<std::vector<int>::iterator> my_rit(v.end()), my_rit1(v.end() - 1);
    /*----------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        ft::reverse_iterator<std::vector<int>::iterator> ob(my_rit);
        EQUAL(&(*my_rit) == &(*ob));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " riterator to const_riterator "
              << "] --------------------]\t\t\033[0m";
    {
        ft::vector<int> v(4, 5);
        ft::vector<int>::reverse_iterator my_rit2(v.end());
        ft::vector<int>::const_reverse_iterator c_it, c_ob(v.end());
        c_it = my_rit2;
        EQUAL(&(*my_rit2) == &(*c_it) && (&(*my_rit2) == &(*c_ob)));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " base function "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*rit) == &(*rit_1.base())) && (&(*my_rit) == &(*my_rit1.base())));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit == rit_1) == (my_rit == my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit != rit_1) == (my_rit != my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " > operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit > rit_1) == (my_rit > my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " >= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit >= rit_1) == (my_rit >= my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " < operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit < rit_1) == (my_rit < my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " <= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit <= rit_1) == (my_rit <= my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((*my_rit == *(v.end() - 1)) && (&(*my_rit) == &(*(v.end() - 1)))) && ((*rit == *(v.end() - 1)) && (&(*rit) == &(*(v.end() - 1)))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<std::string> v(3, "hello");
        std::reverse_iterator<std::vector<std::string>::iterator> rit(v.end());
        ft::reverse_iterator<std::vector<std::string>::iterator> my_rit(v.end());
        EQUAL(rit->length() == my_rit->length());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*(my_rit + 1)) == &(*my_rit1)) && (&(*(rit + 1)) == &(*rit_1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " += operator "
              << "] --------------------]\t\t\033[0m";
    my_rit += 1;
    rit += 1;
    EQUAL((&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -= operator "
              << "] --------------------]\t\t\033[0m";
    my_rit -= 1;
    rit -= 1;
    EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " [] operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_rit[0] = 5) == 5) && (rit[0] == 5));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++rit operator "
              << "] --------------------]\t\t\033[0m";
    ++my_rit; // I incremented here to make sure that the object changes
    ++rit;
    EQUAL(&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --rit operator "
              << "] --------------------]\t\t\033[0m";
    --my_rit; // I incremented here to make sure that the object changes
    --rit;
    EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator (n + rit) "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*(2 + my_rit)) == &(*(1 + my_rit1))) && (&(*(2 + rit)) == &(*(1 + rit_1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator (rit1 - rit) "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_rit - my_rit1) == (rit - rit_1)) && ((my_rit1 - my_rit) == (rit_1 - rit)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit++ operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::reverse_iterator<std::vector<int>::iterator> tmp(rit++);
        ft::reverse_iterator<std::vector<int>::iterator> my_tmp(my_rit++);
        EQUAL((&(*tmp) == &(*(--rit))) && (&(*my_tmp) == &(*(--my_rit))));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit-- operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::reverse_iterator<std::vector<int>::iterator> tmp(rit--);
        ft::reverse_iterator<std::vector<int>::iterator> my_tmp(my_rit--);
        EQUAL((&(*tmp) == &(*(++rit))) && (&(*my_tmp) == &(*(++my_rit))));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " *rit++ test "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<char> v(10);
        std::string res, my_res;
        std::reverse_iterator<std::vector<char>::iterator> start(v.end()), end(v.begin());
        ft::reverse_iterator<std::vector<char>::iterator> my_start(v.end()), my_end(v.begin());

        for (size_t i = 0; i < 10; ++i)
            v[i] = '0' + i;
        while (start != end)
            res.push_back(*start++);
        while (my_start != my_end)
            my_res.push_back(*my_start++);
        EQUAL(res == my_res);
    }
    std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}

void reverse_iterator_with_ft_vector(void)
{
    std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< reverse_iterator with ft::vector >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
    /*------------ std::reverse_iterator ---------*/
    std::vector<int> v(3, 4);
    std::vector<int>::reverse_iterator rit(v.end()), rit_1(v.end() - 1);
    /*----------------------------------*/
    /*------------ ft::reverse_iterator ---------*/
    ft::vector<int> my_v(3, 4);
    ft::vector<int>::reverse_iterator my_rit(my_v.end()), my_rit1(my_v.end() - 1);
    /*----------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        ft::vector<int>::reverse_iterator ob(my_rit);
        EQUAL(&(*my_rit) == &(*ob));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " base function "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*rit) == &(*rit_1.base())) && (&(*my_rit) == &(*my_rit1.base())));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit == rit_1) == (my_rit == my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit != rit_1) == (my_rit != my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " > operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit > rit_1) == (my_rit > my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " >= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit >= rit_1) == (my_rit >= my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " < operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit < rit_1) == (my_rit < my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " <= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit <= rit_1) == (my_rit <= my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((*my_rit == *(my_v.end() - 1)) && (&(*my_rit) == &(*(my_v.end() - 1)))) && ((*rit == *(v.end() - 1)) && (&(*rit) == &(*(v.end() - 1)))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<std::string> v(3, "hello");
        ft::vector<std::string> my_v(3, "hello");
        std::vector<std::string>::reverse_iterator rit(v.end());
        ft::vector<std::string>::reverse_iterator my_rit(my_v.end());
        EQUAL(rit->length() == my_rit->length());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*(my_rit + 1)) == &(*my_rit1)) && (&(*(rit + 1)) == &(*rit_1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " += operator "
              << "] --------------------]\t\t\033[0m";
    my_rit += 1;
    rit += 1;
    EQUAL((&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -= operator "
              << "] --------------------]\t\t\033[0m";
    my_rit -= 1;
    rit -= 1;
    EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " [] operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((my_rit[0] = 5) == 5);
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++rit operator "
              << "] --------------------]\t\t\033[0m";
    ++my_rit; // I incremented here to make sure that the object changes
    ++rit;
    EQUAL(&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --rit operator "
              << "] --------------------]\t\t\033[0m";
    --my_rit; // I incremented here to make sure that the object changes
    --rit;
    EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator (n + rit) "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*(2 + my_rit)) == &(*(1 + my_rit1))) && (&(*(2 + rit)) == &(*(1 + rit_1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator (rit1 - rit) "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_rit - my_rit1) == (rit - rit_1)) && ((my_rit1 - my_rit) == (rit_1 - rit)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit++ operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<int>::reverse_iterator tmp(rit++);
        ft::vector<int>::reverse_iterator my_tmp(my_rit++);
        EQUAL((&(*tmp) == &(*(--rit))) && (&(*my_tmp) == &(*(--my_rit))));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit-- operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<int>::reverse_iterator tmp(rit--);
        ft::vector<int>::reverse_iterator my_tmp(my_rit--);
        EQUAL((&(*tmp) == &(*(++rit))) && (&(*my_tmp) == &(*(++my_rit))));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " *rit++ test "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<char> v(10);
        ft::vector<char> my_v(10);
        std::string res, my_res;
        std::vector<char>::reverse_iterator start(v.end()), end(v.begin());
        ft::vector<char>::reverse_iterator my_start(my_v.end()), my_end(my_v.begin());
        for (size_t i = 0; i < 10; ++i)
            v[i] = '0' + i;
        size_t i = 0;
        for (ft::vector<char>::iterator it = my_v.begin(); it != my_v.end(); ++it)
            *it = '0' + i++;
        while (start != end)
            res.push_back(*start++);
        while (my_start != my_end)
            my_res.push_back(*my_start++);
        EQUAL(res == my_res);
    }
    std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}

void vector_tests(void)
{
    std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< vector tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " fill constructor "
              << "] --------------------]\t\t\033[0m";
    {
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;

            start = get_time();
            std::vector<std::string> v(1e5, "fill constructor test");
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            ft::vector<std::string> my_v(1e5, "fill constructor test");
            ualarm(0, 0);
        }
        /*----------------------------------------------------------------------------------------------*/
        /*--------------- fill tow vectors with a 10 strings ------*/
        ft::vector<std::string> my_v(10, "fill constructor test");
        std::vector<std::string> v(10, "fill constructor test");
        /*---------------------------------------------------------*/
        /*--------------- declare tow strings to store the results ------*/
        std::string res, my_res;
        /*---------------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it) // fill res from std::vector
            res += *it;

        for (ft::vector<std::string>::iterator it = my_v.begin(); it != my_v.end(); ++it) // fill my_res from ft::vector
            my_res += *it;
        EQUAL(res == my_res);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " range constructor "
              << "] --------------------]\t\t\033[0m";
    {
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            std::vector<std::string> v(1e5, "range constructor test");
            start = get_time();
            std::vector<std::string> v1(v.begin(), v.end());
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            ft::vector<std::string> my_v(v.begin(), v.end());
            ualarm(0, 0);
        }
        /*-----------------------------------------------------------------------------------------------*/
        /*--------------- fill std::vector with 10 strings and ft::vector with range of iterators ------*/
        std::vector<std::string> v(10, "range constructor test");
        ft::vector<std::string> my_v(10, "range constructor test");
        ft::vector<std::string> my_v1(my_v.begin(), my_v.end()); // this one is to check if the range works with ft::vector
        /*----------------------------------------------------------------------------------------------*/
        /*--------------- declare tow strings to store the results ------*/
        std::string res, my_res, my_res1;
        /*--------------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it) // fill res from std::vector
            res += *it;

        for (ft::vector<std::string>::iterator it = my_v.begin(); it != my_v.end(); ++it) // fill my_res from ft::vector
            my_res += *it;

        for (ft::vector<std::string>::iterator it = my_v1.begin(); it != my_v1.end(); ++it) // fill my_res1 from ft::vector
            my_res1 += *it;
        EQUAL(res == my_res && my_res == my_res1);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            std::vector<char> v(1e7, 'a');
            start = get_time();
            std::vector<char> copy_v(v);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * 20) : 20;

            ft::vector<char> my_v(1e7, 'a');
            alarm(diff);
            ft::vector<char> my_copy_v(my_v);
            alarm(0);
        }
        /*---------------------------------------------------------------------------------------------*/
        /*---------------------------- declare a vector and fill with 'a', and create a copy of it ------------------*/
        ft::vector<char> v1(10, 'a');
        ft::vector<char> copy_v(v1);
        /*-----------------------------------------------------------------------------------------------------------*/
        /*--------------- declare tow strings to store the results ------*/
        std::string res, res1;
        /*--------------------------------------------------------*/
        for (ft::vector<char>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;

        for (ft::vector<char>::iterator it = copy_v.begin(); it != copy_v.end(); ++it) // fill res from copy_v
            res1 += *it;
        EQUAL(res == res1);
    }
    /*------------------------------------------ = operator tests --------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 1 : test with equale size vecotrs ----------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size = rhs.size) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string1");
            std::vector<std::string> v2(1e6, "string2");
            start = get_time();
            v1 = v2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1(1e6, "string1");
            ft::vector<std::string> ft_v2(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1 = ft_v2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string1");
        std::vector<std::string> v2(10, "string2");
        v1 = v2;
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string1");
        ft::vector<std::string> ft_v2(10, "string2");
        ft_v1 = ft_v2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 2 : test with diff size vecotrs ----------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size < rhs.size) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e4, "string1");
            std::vector<std::string> v2(1e6, "string2");
            start = get_time();
            v1 = v2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1(1e4, "string1");
            ft::vector<std::string> ft_v2(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1 = ft_v2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string1");
        std::vector<std::string> v2(20, "string2");
        v1 = v2;
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string1");
        ft::vector<std::string> ft_v2(20, "string2");
        ft_v1 = ft_v2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 3 : test with diff size vecotrs ----------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size > rhs.size) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string1");
            std::vector<std::string> v2(1e4, "string2");
            start = get_time();
            v1 = v2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1(1e6, "string1");
            ft::vector<std::string> ft_v2(1e4, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1 = ft_v2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(20, "string1");
        std::vector<std::string> v2(10, "string2");
        v1 = v2;
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(20, "string1");
        ft::vector<std::string> ft_v2(10, "string2");
        ft_v1 = ft_v2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 4 : test with one empty vector ----------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size = 0) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1;
            std::vector<std::string> v2(1e6, "string2");
            start = get_time();
            v1 = v2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1;
            ft::vector<std::string> ft_v2(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1 = ft_v2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1;
        std::vector<std::string> v2(10, "string2");
        v1 = v2;
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1;
        ft::vector<std::string> ft_v2(10, "string2");
        ft_v1 = ft_v2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 5 : test with one empty vector ----------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (rhs.size = 0) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            std::vector<std::string> v2;
            start = get_time();
            v1 = v2;
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1(1e6, "string2");
            ft::vector<std::string> ft_v2;
            ualarm(diff * 1e3, 0);
            ft_v1 = ft_v2;
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<std::string> v2;
        v1 = v2;
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<std::string> ft_v2;
        ft_v1 = ft_v2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " begin and end methods "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.begin();
            v1.end();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.begin();
            ft_v1.end();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<std::string> const v2(10, "string2");
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<std::string> const ft_v2(10, "string2");
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res, c_res, c_ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;
        for (std::vector<std::string>::const_iterator rit = v2.begin(); rit != v2.end(); ++rit) // fill c_res from const v1
            c_res += *rit;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;
        for (ft::vector<std::string>::const_iterator rit = ft_v2.begin(); rit != ft_v2.end(); ++rit) // fill c_ft_res from const ft_v1
            c_ft_res += *rit;

        EQUAL(res == ft_res && c_res == c_ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rbegin and rend methods "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.rbegin();
            v1.rend();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.rbegin();
            ft_v1.rend();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<std::string> const v2(10, "string2");
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<std::string> const ft_v2(10, "string2");
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res, c_res, c_ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::reverse_iterator rit = v1.rbegin(); rit != v1.rend(); ++rit) // fill res from v1
            res += *rit;
        for (std::vector<std::string>::const_reverse_iterator rit = v2.rbegin(); rit != v2.rend(); ++rit) // fill c_res from const v1
            c_res += *rit;

        for (ft::vector<std::string>::reverse_iterator rit = ft_v1.rbegin(); rit != ft_v1.rend(); ++rit) // fill ft_res from ft_v1
            ft_res += *rit;
        for (ft::vector<std::string>::const_reverse_iterator rit = ft_v2.rbegin(); rit != ft_v2.rend(); ++rit) // fill c_ft_res from const ft_v1
            c_ft_res += *rit;

        EQUAL(res == ft_res && c_ft_res == c_res);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " size method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.size();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.size();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");          // fill constructor
        std::vector<std::string> v2;                         // empty constructor
        std::vector<std::string> v3(v1.begin(), v1.end());   // range constructor with normal iterators
        std::vector<std::string> v4(v3);                     // copy constructor
        std::vector<std::string> v5(v1.rbegin(), v1.rend()); // range constructor with reverse iterators
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<std::string> ft_v2;
        ft::vector<std::string> ft_v3(ft_v1.begin(), ft_v1.end());
        ft::vector<std::string> ft_v4(ft_v1);
        ft::vector<std::string> ft_v5(ft_v1.rbegin(), ft_v1.rend());
        /*----------------------------------------------------*/
        EQUAL(v1.size() == ft_v1.size() && v2.size() == ft_v2.size() && v3.size() == ft_v3.size() && v4.size() == ft_v4.size() && v5.size() == ft_v5.size());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " capacity method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.capacity();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.capacity();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");          // fill constructor
        std::vector<std::string> v2;                         // empty constructor
        std::vector<std::string> v3(v1.begin(), v1.end());   // range constructor with normal iterators
        std::vector<std::string> v4(v3);                     // copy constructor
        std::vector<std::string> v5(v1.rbegin(), v1.rend()); // range constructor with reverse iterators
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<std::string> ft_v2;
        ft::vector<std::string> ft_v3(ft_v1.begin(), ft_v1.end());
        ft::vector<std::string> ft_v4(ft_v1);
        ft::vector<std::string> ft_v5(ft_v1.rbegin(), ft_v1.rend());
        /*----------------------------------------------------*/
        EQUAL(v1.capacity() == ft_v1.capacity() && v2.capacity() == ft_v2.capacity() && v3.capacity() == ft_v3.capacity() && v4.capacity() == ft_v4.capacity() && v5.capacity() == ft_v5.capacity());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " max_size method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.max_size();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.max_size();
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------ std::vectors ---------------------*/

        std::vector<std::string> v1(10, "string");
        std::vector<int> v2;
        std::vector<double> v4;
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<int> ft_v2;
        ft::vector<double> ft_v4;
        /*----------------------------------------------------*/
        EQUAL(v1.max_size() == ft_v1.max_size() && v2.max_size() == ft_v2.max_size() && v4.max_size() == ft_v4.max_size());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " resize method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*
             * test with n greater than vector capacity
             */
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(10, "string2");
            start = get_time();
            v1.resize(1e6);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1(10, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.resize(1e6);
            ualarm(0, 0);
            /*----------------------------------------------------*/
            /*
             *	test with n lesser than capacity and greater than size
             */
            /*------------------ std::vectors ---------------------*/
            v1.resize(20);
            start = get_time();
            v1.resize(1e5);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft_v1.resize(20);
            ualarm(diff * 1e3, 0);
            ft_v1.resize(1e5);
            ualarm(0, 0);
            /*----------------------------------------------------*/
            /*
             * test with n lesser than capacity and lesser an size
             */
            /*------------------ std::vectors ---------------------*/
            v1.resize(100);
            start = get_time();
            v1.resize(50);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft_v1.resize(100);
            ualarm(diff * 1e3, 0);
            ft_v1.resize(50);
            ualarm(0, 0);
            /*----------------------------------------------------*/
        }
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, s4, ft_s1, ft_s2, ft_s3, ft_s4;
        std::string sit1, sit2, sit3, ft_sit1, ft_sit2, ft_sit3; // strings to store the result by iterators
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, z4, ft_z1, ft_z2, ft_z3, ft_z4;
        size_t c1, c2, c3, c4, ft_c1, ft_c2, ft_c3, ft_c4;
        /*
         * iterators to check the iterator validity
         *  it : iterator, eit : iterator to the end
         */
        std::vector<std::string>::iterator valid_it, valid_eit;
        ft::vector<std::string>::iterator ft_valid_it, ft_valid_eit;
        /*
         * test with n greater than vector capacity
         */
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        v1.resize(1e6, "hello");
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft_v1.resize(1e6, "hello");

        z1 = v1.size();
        ft_z1 = ft_v1.size();
        c1 = v1.capacity();
        ft_c1 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s1 += v1[i];

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
            ft_s1 += *it;
        /*----------------------------------------------------*/
        /*
         *	test with n lesser than capacity and greater than size
         */
        /*------------------ std::vectors ---------------------*/
        v1.resize(20);
        valid_it = v1.begin();
        valid_eit = v1.end();
        v1.resize(1e5);
        /*------------------ ft::vectors ---------------------*/
        ft_v1.resize(20);
        ft_valid_it = ft_v1.begin();
        ft_valid_eit = ft_v1.end();
        ft_v1.resize(1e5);

        z2 = v1.size();
        ft_z2 = ft_v1.size();
        c2 = v1.capacity();
        ft_c2 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s2 += v1[i];

        for (; valid_it != valid_eit; ++valid_it)
            sit1 += *valid_it;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
            ft_s2 += *it;

        for (; ft_valid_it != ft_valid_eit; ++ft_valid_it)
            ft_sit1 += *ft_valid_it;
        /*----------------------------------------------------*/
        /*
         * test with n lesser than capacity and lesser an size
         */
        /*------------------ std::vectors ---------------------*/
        valid_it = v1.begin();
        v1.resize(50);
        /*------------------ ft::vectors ---------------------*/
        ft_valid_it = ft_v1.begin();
        ft_v1.resize(50);

        z3 = v1.size();
        ft_z3 = ft_v1.size();
        c3 = v1.capacity();
        ft_c3 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s3 += v1[i];

        for (; valid_it != v1.end(); ++valid_it)
            sit2 += *valid_it;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
            ft_s3 += *it;

        for (; ft_valid_it != ft_v1.end(); ++ft_valid_it)
            ft_sit2 += *ft_valid_it;
        /*----------------------------------------------------*/
        /*
         * test with n = 0
         */
        /*------------------ std::vectors ---------------------*/
        valid_it = v1.begin();
        v1.resize(0, "string4");
        /*------------------ ft::vectors ---------------------*/
        ft_valid_it = ft_v1.begin();
        ft_v1.resize(0, "string4");

        z4 = v1.size();
        ft_z4 = ft_v1.size();
        c4 = v1.capacity();
        ft_c4 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s4 += v1[i];

        for (; valid_it != v1.end(); ++valid_it)
            sit3 += *valid_it;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
            ft_s4 += *it;

        for (; ft_valid_it != ft_v1.end(); ++ft_valid_it)
            ft_sit3 += *ft_valid_it;
        /*----------------------------------------------------*/
        EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1 && sit1 == ft_sit1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3 && sit2 == ft_sit2) && (s4 == ft_s4 && z4 == ft_z4 && c4 == ft_c4 && sit3 == ft_sit3));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " empty method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.empty();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.empty();
            ualarm(0, 0);
        }
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<int> v2;
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<int> ft_v2;

        EQUAL(v1.empty() == ft_v1.empty() && v2.empty() == ft_v2.empty());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " reserve method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(10, "string2");
            start = get_time();
            v1.reserve(1e6);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1(10, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.reserve(1e6);
            ualarm(0, 0);
        }
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
        std::string sit1, ft_sit1; // strings to store the result by iterators
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
        size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
        /*
         * iterators to check the iterator validity
         *  it : iterator, eit : iterator to the end
         */
        std::vector<std::string>::iterator valid_it, valid_eit;
        ft::vector<std::string>::iterator ft_valid_it, ft_valid_eit;
        // bool to check if the function throw or not
        bool exec_throwed = false;
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<char> v2;
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<char> ft_v2;
        try
        {
            ft_v1.reserve(ft_v1.max_size() + 1);
        }
        catch (std::length_error const &e)
        {
            (void)e;
            exec_throwed = true;
        }
        v1.reserve(100);
        ft_v1.reserve(100);

        z1 = v1.size();
        ft_z1 = ft_v1.size();
        c1 = v1.capacity();
        ft_c1 = ft_v1.capacity();

        for (size_t i = 0; i < v1.size(); ++i)
            s1 += v1[i];

        ft_valid_it = ft_v1.begin();
        for (; ft_valid_it != ft_v1.end(); ++ft_valid_it)
            ft_s1 += *ft_valid_it;

        valid_it = v1.begin();
        valid_eit = v1.end();
        ft_valid_it = ft_v1.begin();
        ft_valid_eit = ft_v1.end();
        v1.reserve(50);
        ft_v1.reserve(50);

        z2 = v1.size();
        ft_z2 = ft_v1.size();
        c2 = v1.capacity();
        ft_c2 = ft_v1.capacity();

        for (size_t i = 0; i < v1.size(); ++i)
            s2 += v1[i];

        for (; valid_it != valid_eit; ++valid_it)
            sit1 += *valid_it;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
            ft_s2 += *it;

        for (; ft_valid_it != ft_valid_eit; ++ft_valid_it)
            ft_sit1 += *ft_valid_it;

        v2.reserve(200);
        ft_v2.reserve(200);
        z3 = v2.size();
        ft_z3 = ft_v2.size();
        c3 = v2.capacity();
        ft_c3 = ft_v2.capacity();

        for (size_t i = 0; i < v2.size(); ++i)
            s3 += v2[i];

        for (ft::vector<char>::iterator it = ft_v2.begin(); it != ft_v2.end(); ++it)
            ft_s3 += *it;

        EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1 && sit1 == ft_sit1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3) && exec_throwed);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator[] method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1[1e6 - 1];
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1[1e6 - 1];
            ualarm(0, 0);
        }
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<char> const v2(10, '9');
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<char> const ft_v2(10, '9');
        /*
         * Strings to store the results
         */
        std::string s1, s2, ft_s1, ft_s2;

        for (size_t i = 0; i < v1.size(); ++i)
        {
            if (i == v1.size() - 1)
                v1[i] = "other";
            s1 += v1[i];
        }

        for (size_t i = 0; i < ft_v1.size(); ++i)
        {
            if (i == ft_v1.size() - 1)
                ft_v1[i] = "other";
            ft_s1 += ft_v1[i];
        }

        for (size_t i = 0; i < v2.size(); ++i)
            s2 += v2[i];

        for (size_t i = 0; i < ft_v2.size(); ++i)
            ft_s2 += ft_v2[i];

        EQUAL(s1 == ft_s1 && s2 == ft_s2);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " at method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.at(1e6 - 1);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.at(1e6 - 1);
            ualarm(0, 0);
        }
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<char> const v2(10, '9');
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<char> const ft_v2(10, '9');
        /*
         * Strings to store the results
         */
        std::string s1, s2, ft_s1, ft_s2;
        // bool to check if an exception is throwed
        bool exce_throwed = false;

        try
        {
            ft_v1.at(20);
        }
        catch (std::out_of_range const &e)
        {
            (void)e;
            exce_throwed = true;
        }
        for (size_t i = 0; i < v1.size(); ++i)
        {
            if (i == v1.size() - 1)
                v1.at(i) = "other";
            s1 += v1.at(i);
        }

        for (size_t i = 0; i < ft_v1.size(); ++i)
        {
            if (i == ft_v1.size() - 1)
                ft_v1.at(i) = "other";
            ft_s1 += ft_v1.at(i);
        }

        for (size_t i = 0; i < v2.size(); ++i)
            s2 += v2.at(i);
        for (size_t i = 0; i < ft_v2.size(); ++i)
            ft_s2 += ft_v2.at(i);

        EQUAL(s1 == ft_s1 && s2 == ft_s2 && exce_throwed);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " front method "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<int> const v2(10, 9);
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<int> const ft_v2(10, 9);

        v1.front() = "LEET";
        ft_v1.front() = "LEET";
        EQUAL(v1.front() == ft_v1.front() && v2.front() == ft_v2.front());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " back method "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<int> const v2(10, 9);
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<int> const ft_v2(10, 9);

        v1.back() = "LEET";
        ft_v1.back() = "LEET";
        EQUAL(v1.back() == ft_v1.back() && v2.back() == ft_v2.back());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " assign(fill) method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.assign(1e6 + 1, "assign");
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.assign(1e6 + 1, "assign");
            ualarm(0, 0);
        }
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<char> v2;
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<char> ft_v2;
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
        size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
        // test for n greater than the vector capactiy
        v1.assign(20, "assign");
        ft_v1.assign(20, "assign");

        z1 = v1.size();
        ft_z1 = ft_v1.size();
        c1 = v1.capacity();
        ft_c1 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s1 += v1.at(i);

        for (size_t i = 0; i < ft_v1.size(); ++i)
            ft_s1 += ft_v1.at(i);
        // test for n lesser than the vector capactiy
        v1.assign(10, "less");
        ft_v1.assign(10, "less");

        z2 = v1.size();
        ft_z2 = ft_v1.size();
        c2 = v1.capacity();
        ft_c2 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s3 += v1.at(i);

        for (size_t i = 0; i < ft_v1.size(); ++i)
            ft_s3 += ft_v1.at(i);
        // test for empty vectors
        v2.assign(20, 'h');
        ft_v2.assign(20, 'h');

        z3 = v2.size();
        ft_z3 = ft_v2.size();
        c3 = v2.capacity();
        ft_c3 = ft_v2.capacity();
        for (size_t i = 0; i < v2.size(); ++i)
            s2 += v2.at(i);

        for (size_t i = 0; i < ft_v2.size(); ++i)
            ft_s2 += ft_v2.at(i);

        EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " assign(range) method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            ft::vector<std::string> ft_v1(1e6, "string2");
            // std::vector<std::string>    v1(1e6, "string2");
            std::vector<std::string> v2(1e4, "string2");
            start = get_time();
            v2.assign(ft_v1.begin(), ft_v1.end());
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            // ft::vector<std::string>    ft_v1(1e6, "string2");
            ft::vector<std::string> ft_v2(1e4, "string2");
            ualarm(diff * 1e3, 0);
            ft_v2.assign(ft_v1.begin(), ft_v1.end());
            ualarm(0, 0);
        }
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(20, "less");
        std::vector<std::string> v2;
        std::vector<std::string> v3(10, "string2");
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v1(20, "less");
        ft::vector<std::string> ft_v2;
        ft::vector<std::string> ft_v3(10, "string2");
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
        size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
        // test for n greater than the vector capactiy
        v3.assign(v1.begin(), v1.end());
        ft_v3.assign(v1.begin(), v1.end());

        z1 = v3.size();
        c1 = v3.capacity();
        ft_z1 = ft_v3.size();
        ft_c1 = ft_v3.capacity();
        for (size_t i = 0; i < v3.size(); ++i)
            s1 += v3.at(i);

        for (size_t i = 0; i < ft_v3.size(); ++i)
            ft_s1 += ft_v3.at(i);
        // test for n lesser than the vector capactiy
        v1.assign(v3.begin(), v3.end());
        ft_v1.assign(ft_v3.begin(), ft_v3.end());

        z2 = v1.size();
        c2 = v1.capacity();
        ft_z2 = ft_v1.size();
        ft_c2 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s3 += v1.at(i);

        for (size_t i = 0; i < ft_v1.size(); ++i)
            ft_s3 += ft_v1.at(i);
        // test for empty vectors
        v2.assign(v1.begin(), v1.end());
        ft_v2.assign(ft_v1.begin(), ft_v1.end());

        z3 = v2.size();
        c3 = v2.capacity();
        ft_z3 = ft_v2.size();
        ft_c3 = ft_v2.capacity();
        for (size_t i = 0; i < v2.size(); ++i)
            s2 += v2.at(i);

        for (size_t i = 0; i < ft_v2.size(); ++i)
            ft_s2 += ft_v2.at(i);

        EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " push_back method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            // test 1: test with capacity greater than or equal the size + the new element (reallocation must'nt happen)
            /*------------------ std::vectors ---------------------*/
            {
                std::vector<std::string> v1(1e6, "string2");
                v1.reserve(1e6 + 1);
                start = get_time();
                v1.push_back("string1");
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v1(1e6, "string2");
                ft_v1.reserve(1e6 + 1);
                ualarm(diff * 1e3, 0);
                ft_v1.push_back("string1");
                ualarm(0, 0);
            }
            /*--------------------------------------------------------------------------------------*/
            // test 2: test with capacity lesser than the size + the new element (reallocation must happen)
            /*------------------ std::vectors ---------------------*/
            {
                std::vector<std::string> v1(1e6, "string2");
                start = get_time();
                v1.push_back("string1");
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                ft_v1.push_back("string1");
                ualarm(0, 0);
            }
            /*--------------------------------------------------------------------------------------*/
        }
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v;
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v;
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
        size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
        ft::vector<std::string>::iterator ft_it;
        // test for an empty vector
        v.push_back("hello");
        ft_v.push_back("hello");
        ft_it = ft_v.begin();
        ft_it->length();

        z1 = v.size();
        c1 = v.capacity();
        ft_z1 = ft_v.size();
        ft_c1 = ft_v.capacity();
        for (size_t i = 0; i < v.size(); ++i)
            s1 += v.at(i);

        for (size_t i = 0; i < ft_v.size(); ++i)
            ft_s1 += ft_v.at(i);
        /*---------------------------------------------*/
        // test for a vector with capacity >= size + the new element
        v.reserve(30);
        ft_v.reserve(30);
        v.push_back("string");
        ft_v.push_back("string");
        v.push_back("string");
        ft_v.push_back("string");

        z2 = v.size();
        c2 = v.capacity();
        ft_z2 = ft_v.size();
        ft_c2 = ft_v.capacity();
        for (size_t i = 0; i < v.size(); ++i)
            s2 += v.at(i);

        for (size_t i = 0; i < ft_v.size(); ++i)
            ft_s2 += ft_v.at(i);
        /*---------------------------------------------------------*/
        // test for a vector with capactiy < size + the new element
        for (size_t i = 0; i < 100; ++i)
            v.push_back("string");

        for (size_t i = 0; i < 100; ++i)
            ft_v.push_back("string");

        z3 = v.size();
        c3 = v.capacity();
        ft_z3 = ft_v.size();
        ft_c3 = ft_v.capacity();
        for (size_t i = 0; i < v.size(); ++i)
            s3 += v.at(i);

        for (size_t i = 0; i < ft_v.size(); ++i)
            ft_s3 += ft_v.at(i);

        EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " pop_back method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.pop_back();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.pop_back();
            ualarm(0, 0);
        }
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v(20, "string");
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v(20, "string");
        /*
         * Strings to store the results
         */
        std::string s1, ft_s1;
        /*
         * Var to store the size and the capacity
         */
        size_t z1, ft_z1;
        size_t c1, ft_c1;
        v.pop_back();
        ft_v.pop_back();
        z1 = v.size();
        ft_z1 = ft_v.size();
        c1 = v.capacity();
        ft_c1 = ft_v.capacity();
        for (size_t i = 0; i < v.size(); ++i)
            s1 += v[i];
        for (size_t i = 0; i < ft_v.size(); ++i)
            ft_s1 += ft_v[i];
        EQUAL(z1 == ft_z1 && c1 == ft_c1 && s1 == ft_s1);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " insert method (single element) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            // test 1: test with capacity greater than or equal the size + the new element (reallocation must'nt happen)
            /*------------------ std::vectors ---------------------*/
            {
                std::vector<std::string> v1(1e6, "string2");
                v1.reserve(1e6 + 1);
                start = get_time();
                v1.insert(v1.begin() + 1e5, "string1");
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v1(1e6, "string2");
                ft_v1.reserve(1e6 + 1);
                ualarm(diff * 1e3, 0);
                ft_v1.insert(ft_v1.begin() + 1e5, "string1");
                ualarm(0, 0);
            }
            /*--------------------------------------------------------------------------------------*/
            // test 2: test with capacity lesser than the size + the new element (reallocation must happen)
            /*------------------ std::vectors ---------------------*/
            {
                std::vector<std::string> v1(1e6, "string2");
                start = get_time();
                v1.insert(v1.begin() + 1e5, "string1");
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                ft_v1.insert(ft_v1.begin() + 1e5, "string1");
                ualarm(0, 0);
            }
        }
        /*--------------------------------------------------------------------------------------*/
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::vector<std::string>::size_type s, ft_s;
        ft::vector<std::string>::size_type c, ft_c;
        ft::vector<std::string>::iterator ft_it;
        std::vector<std::string>::iterator it;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*------------------------------- test 1: empty vector ----------------------------------------*/
        // insert at the begin
        {
            std::vector<std::string> v;
            ft::vector<std::string> ft_v;
            it = v.insert(v.begin(), "hello");
            ft_it = ft_v.insert(ft_v.begin(), "hello");
            ft_it->length();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c) && (*ft_it == *it));
        }
        // insert at the end
        {
            std::vector<std::string> v;
            ft::vector<std::string> ft_v;

            it = v.insert(v.end(), "hello");
            ft_it = ft_v.insert(ft_v.end(), "hello");
            ft_it->length();

            str.clear();
            ft_str.clear();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (*it == *ft_it));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 2: the vector capacity >= size + the new element ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");
            ft::vector<std::string>::iterator valid_it;

            v.reserve(30);
            ft_v.reserve(30);
            valid_it = ft_v.begin();
            it = v.insert(v.begin() + 10, "hello");
            ft_it = ft_v.insert(ft_v.begin() + 10, "hello");
            ft_it->length();

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (*it == *ft_it) && (&(*valid_it) == &(*ft_v.begin())));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 3: the vector capacity < size + the new element ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");

            it = v.insert(v.begin() + 10, "hello");
            ft_it = ft_v.insert(ft_v.begin() + 10, "hello");
            ft_it->length();

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (*it == *ft_it));
        }
        /*---------------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " insert method (fill) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            // test 1: test with capacity greater than or equal the size + n (reallocation must'nt happen)
            /*------------------ std::vectors ---------------------*/
            {
                std::vector<std::string> v1(1e6, "string2");
                v1.reserve(1e6 + 200);
                start = get_time();
                v1.insert(v1.begin() + 1e5, 100, "string1");
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v1(1e6, "string2");
                ft_v1.reserve(1e6 + 200);
                ualarm(diff * 1e3, 0);
                ft_v1.insert(ft_v1.begin() + 1e5, 100, "string1");
                ualarm(0, 0);
            }
            /*--------------------------------------------------------------------------------------*/
            // test 2: test with capacity lesser than the size + n (reallocation must happen)
            /*------------------ std::vectors ---------------------*/
            {
                std::vector<std::string> v1(1e6, "string2");
                start = get_time();
                v1.insert(v1.begin() + 1e5, 200, "string1");
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                ft_v1.insert(ft_v1.begin() + 1e5, 200, "string1");
                ualarm(0, 0);
            }
            /*--------------------------------------------------------------------------------------*/
        }
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::vector<std::string>::size_type s, ft_s;
        ft::vector<std::string>::size_type c, ft_c;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*------------------------------- test 1: empty vector ----------------------------------------*/
        // insert at the begin
        {
            std::vector<std::string> v;
            ft::vector<std::string> ft_v;
            v.insert(v.begin(), 100, "hello");
            ft_v.insert(ft_v.begin(), 100, "hello");
            ft_v.begin()->length();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        // insert at the end
        {
            std::vector<std::string> v;
            ft::vector<std::string> ft_v;

            v.insert(v.end(), "hello");
            ft_v.insert(ft_v.end(), "hello");
            ft_v.begin()->length();

            str.clear();
            ft_str.clear();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        // /*---------------------------------------------------------------------------------------------------*/
        // /*------------------------------- test 2: the vector capacity >= size + n ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");
            ft::vector<std::string>::iterator valid_it;

            v.reserve(100);
            ft_v.reserve(100);
            valid_it = ft_v.begin();
            v.insert(v.begin() + 15, 70, "hello");
            ft_v.insert(ft_v.begin() + 15, 70, "hello");

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (&(*valid_it) == &(*ft_v.begin())));
        }
        // /*---------------------------------------------------------------------------------------------------*/
        // /*------------------------------- test 3: the vector capacity < size + n && n > size ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");

            v.insert(v.begin() + 10, 100, "hello");
            ft_v.insert(ft_v.begin() + 10, 100, "hello");

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        // /*---------------------------------------------------------------------------------------------------*/
        // /*------------------------------- test 4: the vector capacity < size + n && n <= size ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");

            v.insert(v.begin() + 10, 15, "hello");
            ft_v.insert(ft_v.begin() + 10, 15, "hello");

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        // /*---------------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " insert method (range) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            // test 1: test with capacity greater than or equal the size + n (reallocation must'nt happen)
            /*------------------ std::vectors ---------------------*/
            {
                std::vector<std::string> v(100, "hello");
                std::vector<std::string> v1(1e6, "string2");
                v1.reserve(1e6 + 200);
                start = get_time();
                v1.insert(v1.begin() + 1e5, v.begin(), v.end());
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v(100, "hello");
                ft::vector<std::string> ft_v1(1e6, "string2");
                ft_v1.reserve(1e6 + 200);
                ualarm(diff * 1e3, 0);
                ft_v1.insert(ft_v1.begin() + 1e5, ft_v.begin(), ft_v.end());
                ualarm(0, 0);
            }
            /*--------------------------------------------------------------------------------------*/
            // test 2: test with capacity lesser than the size + n (reallocation must happen)
            /*------------------ std::vectors ---------------------*/
            {
                ft::vector<std::string> v(1e5, "hello");
                std::vector<std::string> v1(1e6, "string2");
                start = get_time();
                v1.insert(v1.begin() + 1e5, v.begin(), v.end());
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                ft_v1.insert(ft_v1.begin() + 1e5, v.begin(), v.end());
                ualarm(0, 0);
            }
            /*--------------------------------------------------------------------------------------*/
        }
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::vector<std::string>::size_type s, ft_s;
        ft::vector<std::string>::size_type c, ft_c;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*------------------------------- test 1: empty vector ----------------------------------------*/
        // insert at the begin
        {
            std::vector<std::string> v1(300, "string");
            std::vector<std::string> v;
            ft::vector<std::string> ft_v;
            v.insert(v.begin(), v1.begin(), v1.end());
            ft_v.insert(ft_v.begin(), v1.begin(), v1.end());
            ft_v.begin()->length();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        // insert at the end
        {
            std::vector<std::string> v;
            ft::vector<std::string> v1(300, "string");
            ft::vector<std::string> ft_v;

            v.insert(v.end(), v1.begin(), v1.end());
            ft_v.insert(ft_v.end(), v1.begin(), v1.end());
            ft_v.begin()->length();

            str.clear();
            ft_str.clear();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 2: the vector capacity >= size + n ----------------------------------------*/
        {
            std::vector<std::string> v1(70, "hello");
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");
            ft::vector<std::string>::iterator valid_it;

            v.reserve(100);
            ft_v.reserve(100);
            valid_it = ft_v.begin();
            v.insert(v.begin() + 15, v1.begin(), v1.end());
            ft_v.insert(ft_v.begin() + 15, v1.begin(), v1.end());

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (&(*valid_it) == &(*ft_v.begin())));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 3: the vector capacity < size + n && n > size ----------------------------------------*/
        {
            ft::vector<std::string> v1(100, "hello");
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");

            v.insert(v.begin() + 10, v1.begin(), v1.end());
            ft_v.insert(ft_v.begin() + 10, v1.begin(), v1.end());

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 4: the vector capacity < size + n && n <= size ----------------------------------------*/
        {
            std::vector<std::string> v1(15, "hello");
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");

            v.insert(v.begin() + 10, v1.begin(), v1.end());
            ft_v.insert(ft_v.begin() + 10, v1.begin(), v1.end());

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        /*---------------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " erase method (single element) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.erase(v1.begin() + 1e5);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.erase(ft_v1.begin() + 1e5);
            ualarm(0, 0);
        }
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::vector<std::string>::size_type s, ft_s;
        ft::vector<std::string>::size_type c, ft_c;
        /*
         * bool to store the comparison
         */
        bool cond;

        std::vector<std::string> v(200, "hello");
        ft::vector<std::string> ft_v(200, "hello");
        ft::vector<std::string>::iterator valid_it;
        std::vector<std::string>::iterator it;
        ft::vector<std::string>::iterator ft_it;
        valid_it = ft_v.begin() + 99;
        it = v.erase(v.begin() + 100);
        ft_it = ft_v.erase(ft_v.begin() + 100);
        ft_it->length();

        s = v.size();
        ft_s = ft_v.size();
        c = v.capacity();
        ft_c = ft_v.capacity();
        for (size_t i = 0; i < v.size(); ++i)
            str += v[i];
        for (size_t i = 0; i < ft_v.size(); ++i)
            ft_str += ft_v[i];
        cond = ((str == ft_str) && (s == ft_s) && (c == ft_c) && (&(*valid_it) == &(*(ft_v.begin() + 99))));
        cond = (cond && (std::distance(v.begin(), it) == std::distance(ft_v.begin(), ft_it)));
        EQUAL(cond);
    }

    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " erase method (range) "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.erase(v1.begin(), v1.end());
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.erase(ft_v1.begin(), ft_v1.end());
            ualarm(0, 0);
        }
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::vector<std::string>::size_type s, ft_s;
        ft::vector<std::string>::size_type c, ft_c;
        std::vector<std::string>::iterator it;
        ft::vector<std::string>::iterator ft_it;
        /*
         * bool to store the comparison
         */
        bool cond;
        /*------------------ test 1: erase from the begin to end -------------------*/
        {
            std::vector<std::string> v(100, "hello");
            ft::vector<std::string> ft_v(100, "hello");

            it = v.erase(v.begin(), v.end());
            ft_it = ft_v.erase(ft_v.begin(), ft_v.end());

            s = v.size();
            ft_s = ft_v.size();
            c = v.size();
            ft_c = ft_v.size();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && (std::distance(v.begin(), it) == std::distance(ft_v.begin(), ft_it)));
        }

        /*--------------------------------------------------------------------------*/
        /*------------------ test 2: erase from the begin to begin + 70 -------------------*/
        {
            std::vector<std::string> v(100, "hello");
            ft::vector<std::string> ft_v(100, "hello");

            it = v.erase(v.begin(), v.begin() + 70);
            ft_it = ft_v.erase(ft_v.begin(), ft_v.begin() + 70);
            ft_it->length();

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.size();
            ft_c = ft_v.size();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && (std::distance(v.begin(), it) == std::distance(ft_v.begin(), ft_it)));
        }
        /*--------------------------------------------------------------------------*/
        /*------------------ test 3: erase from the begin + 60 to end -------------------*/

        {
            std::vector<std::string> v(100, "hello");
            ft::vector<std::string> ft_v(100, "hello");

            it = v.erase(v.begin() + 60, v.end());
            ft_it = ft_v.erase(ft_v.begin() + 60, ft_v.end());

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.size();
            ft_c = ft_v.size();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && (std::distance(v.begin(), it) == std::distance(ft_v.begin(), ft_it)));
        }

        /*--------------------------------------------------------------------------*/
        /*------------------ test 4: erase from the begin + 20 to end - 30 -------------------*/
        {
            std::vector<std::string> v(100, "hello");
            ft::vector<std::string> ft_v(100, "hello");

            it = v.erase(v.begin() + 20, v.end() - 30);
            ft_it = ft_v.erase(ft_v.begin() + 20, ft_v.end() - 30);
            ft_it->length();

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.size();
            ft_c = ft_v.size();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && (std::distance(v.begin(), it) == std::distance(ft_v.begin(), ft_it)));
        }
        /*--------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " swap method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v(1e6, "string");
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v.swap(v1);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v(1e6, "string");
            ft::vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v.swap(ft_v1);
            ualarm(0, 0);
        }
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::vector<std::string>::size_type s, ft_s;
        ft::vector<std::string>::size_type c, ft_c;
        ft::vector<std::string>::iterator b1, b2;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*---------------------------------- test 1: equal size vectors ----------------------*/
        {
            std::vector<std::string> v(200, "hello");
            std::vector<std::string> v1(200, "string");
            ft::vector<std::string> ft_v(200, "hello");
            ft::vector<std::string> ft_v1(200, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            v.swap(v1);
            ft_v.swap(ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        /*---------------------------------- test 2: lhs > rhs ----------------------*/
        {
            std::vector<std::string> v(200, "hello");
            std::vector<std::string> v1(50, "string");
            ft::vector<std::string> ft_v(200, "hello");
            ft::vector<std::string> ft_v1(50, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            v.swap(v1);
            ft_v.swap(ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        /*---------------------------------- test 2: lhs < rhs ----------------------*/
        {
            std::vector<std::string> v(50, "hello");
            std::vector<std::string> v1(200, "string");
            ft::vector<std::string> ft_v(50, "hello");
            ft::vector<std::string> ft_v1(200, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            v.swap(v1);
            ft_v.swap(ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " clear method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v(1e6, "string");
            start = get_time();
            v.clear();
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v.clear();
            ualarm(0, 0);
        }
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::vector<std::string>::size_type s, ft_s;
        ft::vector<std::string>::size_type c, ft_c;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*---------------------------------- test 1: equal size vectors ----------------------*/
        {
            std::vector<std::string> v(200, "hello");
            ft::vector<std::string> ft_v(200, "hello");

            v.clear();
            ft_v.clear();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        /*--------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " get_allocator method "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<std::string> v(200, "hello");
        ft::vector<std::string> ft_v(200, "hello");

        EQUAL(v.get_allocator().max_size() == ft_v.get_allocator().max_size());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator== "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*----------------------------------- test 1: lhs.size == rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e6, "string");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v == v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v(1e6, "string");
                ft::vector<std::string> ft_v1(1e6, "string");
                ualarm(diff * 1e3, 0);
                (void)(ft_v == ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
            /*----------------------------------- test 2: lhs.size != rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e5, "hello");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v == v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v(1e5, "hello");
                ft::vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                (void)(ft_v == ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
        }
        bool cond;
        /*------------------------------------------ test 1: lhs.size == rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = ((v == v1) == (ft_v == ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v == v1) == (ft_v == ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v == v1) == (ft_v == ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 2: lhs.size < rhs.size ------------------*/
        {
            std::vector<int> v(50, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(50, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = (cond && (v == v1) == (ft_v == ft_v1));
            v[40] = 4;
            ft_v[40] = 4;
            cond = (cond && ((v == v1) == (ft_v == ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v == v1) == (ft_v == ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 3: lhs.size > rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(50, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(50, 5);

            cond = (cond && (v == v1) == (ft_v == ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v == v1) == (ft_v == ft_v1)));
            v1[40] = 3;
            ft_v1[40] = 3;
            cond = (cond && ((v == v1) == (ft_v == ft_v1)));
        }
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator!= "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*----------------------------------- test 1: lhs.size == rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e6, "string");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v != v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v(1e6, "string");
                ft::vector<std::string> ft_v1(1e6, "string");
                ualarm(diff * 1e3, 0);
                (void)(ft_v != ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
            /*----------------------------------- test 2: lhs.size != rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e5, "hello");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v != v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v(1e5, "hello");
                ft::vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                (void)(ft_v != ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
        }
        bool cond;
        /*------------------------------------------ test 1: lhs.size == rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = ((v != v1) == (ft_v != ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v != v1) == (ft_v != ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v != v1) == (ft_v != ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 2: lhs.size < rhs.size ------------------*/
        {
            std::vector<int> v(50, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(50, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = (cond && (v != v1) == (ft_v != ft_v1));
            v[40] = 4;
            ft_v[40] = 4;
            cond = (cond && ((v != v1) == (ft_v != ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v != v1) == (ft_v != ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 3: lhs.size > rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(50, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(50, 5);

            cond = (cond && (v != v1) == (ft_v != ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v != v1) == (ft_v != ft_v1)));
            v1[40] = 3;
            ft_v1[40] = 3;
            cond = (cond && ((v != v1) == (ft_v != ft_v1)));
        }
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator< "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*----------------------------------- test 1: lhs.size == rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e6, "string");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v < v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v(1e6, "string");
                ft::vector<std::string> ft_v1(1e6, "string");
                ualarm(diff * 1e3, 0);
                (void)(ft_v < ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
            /*----------------------------------- test 2: lhs.size != rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e5, "hello");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v < v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v(1e5, "hello");
                ft::vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                (void)(ft_v < ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
        }
        bool cond;
        /*------------------------------------------ test 1: lhs.size == rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = ((v < v1) == (ft_v < ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v < v1) == (ft_v < ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v < v1) == (ft_v < ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 2: lhs.size < rhs.size ------------------*/
        {
            std::vector<int> v(50, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(50, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = (cond && (v < v1) == (ft_v < ft_v1));
            v[40] = 4;
            ft_v[40] = 4;
            cond = (cond && ((v < v1) == (ft_v < ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v < v1) == (ft_v < ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 3: lhs.size > rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(50, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(50, 5);

            cond = (cond && (v < v1) == (ft_v < ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v < v1) == (ft_v < ft_v1)));
            v1[40] = 3;
            ft_v1[40] = 3;
            cond = (cond && ((v < v1) == (ft_v < ft_v1)));
        }
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator<= "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*----------------------------------- test 1: lhs.size == rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e6, "string");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v <= v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v(1e6, "string");
                ft::vector<std::string> ft_v1(1e6, "string");
                ualarm(diff * 1e3, 0);
                (void)(ft_v <= ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
            /*----------------------------------- test 2: lhs.size != rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e5, "hello");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v <= v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v(1e5, "hello");
                ft::vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                (void)(ft_v <= ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
        }
        bool cond;
        /*------------------------------------------ test 1: lhs.size == rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = ((v <= v1) == (ft_v <= ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v <= v1) == (ft_v <= ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v <= v1) == (ft_v <= ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 2: lhs.size < rhs.size ------------------*/
        {
            std::vector<int> v(50, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(50, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = (cond && (v <= v1) == (ft_v <= ft_v1));
            v[40] = 4;
            ft_v[40] = 4;
            cond = (cond && ((v <= v1) == (ft_v <= ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v <= v1) == (ft_v <= ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 3: lhs.size > rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(50, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(50, 5);

            cond = (cond && (v <= v1) == (ft_v <= ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v <= v1) == (ft_v <= ft_v1)));
            v1[40] = 3;
            ft_v1[40] = 3;
            cond = (cond && ((v <= v1) == (ft_v <= ft_v1)));
        }
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator> "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*----------------------------------- test 1: lhs.size == rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e6, "string");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v > v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v(1e6, "string");
                ft::vector<std::string> ft_v1(1e6, "string");
                ualarm(diff * 1e3, 0);
                (void)(ft_v > ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
            /*----------------------------------- test 2: lhs.size != rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e5, "hello");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v > v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v(1e5, "hello");
                ft::vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                (void)(ft_v > ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
        }
        bool cond;
        /*------------------------------------------ test 1: lhs.size == rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = ((v > v1) == (ft_v > ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v > v1) == (ft_v > ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v > v1) == (ft_v > ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 2: lhs.size < rhs.size ------------------*/
        {
            std::vector<int> v(50, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(50, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = (cond && (v > v1) == (ft_v > ft_v1));
            v[40] = 4;
            ft_v[40] = 4;
            cond = (cond && ((v > v1) == (ft_v > ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v > v1) == (ft_v > ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 3: lhs.size > rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(50, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(50, 5);

            cond = (cond && (v > v1) == (ft_v > ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v > v1) == (ft_v > ft_v1)));
            v1[40] = 3;
            ft_v1[40] = 3;
            cond = (cond && ((v > v1) == (ft_v > ft_v1)));
        }
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator>= "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*----------------------------------- test 1: lhs.size == rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e6, "string");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v >= v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v(1e6, "string");
                ft::vector<std::string> ft_v1(1e6, "string");
                ualarm(diff * 1e3, 0);
                (void)(ft_v >= ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
            /*----------------------------------- test 2: lhs.size != rhs.size ---------------------*/
            {
                /*------------------ std::vectors ---------------------*/
                std::vector<std::string> v(1e5, "hello");
                std::vector<std::string> v1(1e6, "string");
                start = get_time();
                (void)(v >= v1);
                end = get_time();
                diff = end - start;
                diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
                /*------------------ ft::vectors ---------------------*/
                ft::vector<std::string> ft_v(1e5, "hello");
                ft::vector<std::string> ft_v1(1e6, "string2");
                ualarm(diff * 1e3, 0);
                (void)(ft_v >= ft_v1);
                ualarm(0, 0);
            }
            /*---------------------------------------------------------------------------------------*/
        }
        bool cond;
        /*------------------------------------------ test 1: lhs.size == rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = ((v >= v1) == (ft_v >= ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v >= v1) == (ft_v >= ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v >= v1) == (ft_v >= ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 2: lhs.size < rhs.size ------------------*/
        {
            std::vector<int> v(50, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(50, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = (cond && (v >= v1) == (ft_v >= ft_v1));
            v[40] = 4;
            ft_v[40] = 4;
            cond = (cond && ((v >= v1) == (ft_v >= ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v >= v1) == (ft_v >= ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 3: lhs.size > rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(50, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(50, 5);

            cond = (cond && (v >= v1) == (ft_v >= ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v >= v1) == (ft_v >= ft_v1)));
            v1[40] = 3;
            ft_v1[40] = 3;
            cond = (cond && ((v >= v1) == (ft_v >= ft_v1)));
        }
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " swap "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v(1e6, "string");
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            swap(v, v1);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::vector<std::string> ft_v(1e6, "string");
            ft::vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            swap(ft_v, ft_v1);
            ualarm(0, 0);
        }
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::vector<std::string>::size_type s, ft_s;
        ft::vector<std::string>::size_type c, ft_c;
        ft::vector<std::string>::iterator b1, b2;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*---------------------------------- test 1: equal size vectors ----------------------*/
        {
            std::vector<std::string> v(200, "hello");
            std::vector<std::string> v1(200, "string");
            ft::vector<std::string> ft_v(200, "hello");
            ft::vector<std::string> ft_v1(200, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            swap(v, v1);
            swap(ft_v, ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        /*---------------------------------- test 2: lhs > rhs ----------------------*/
        {
            std::vector<std::string> v(200, "hello");
            std::vector<std::string> v1(50, "string");
            ft::vector<std::string> ft_v(200, "hello");
            ft::vector<std::string> ft_v1(50, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            swap(v, v1);
            swap(ft_v, ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        /*---------------------------------- test 2: lhs < rhs ----------------------*/
        {
            std::vector<std::string> v(50, "hello");
            std::vector<std::string> v1(200, "string");
            ft::vector<std::string> ft_v(50, "hello");
            ft::vector<std::string> ft_v1(200, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            swap(v, v1);
            swap(ft_v, ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
} // vec_end

void	testConstructors(void)
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " default constructor "
              << "] --------------------]\t\t\033[0m";
	{
		std::vector<int> myvector (2,200);
		ft::stack<int,std::vector<int> > s(myvector);
		EQUAL(s.size() == 2);
	}
}

void	testMemberMethods(void)
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " empty method "
              << "] --------------------]\t\t\033[0m";
	{
		ft::stack<int> mystack;
		int sum (0);

		for (int i=1;i<=10;i++) mystack.push(i);

		while (!mystack.empty())
		{
			sum += mystack.top();
			mystack.pop();
		}
		EQUAL(sum == 55);
	}
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " size method "
              << "] --------------------]\t\t\033[0m";
	{
		bool cond(false);
		ft::stack<int> myints;
		cond = myints.size() == 0;

		for (int i=0; i<5; i++) myints.push(i);
		cond = cond && (myints.size() == 5);

		myints.pop();
		cond = cond && (myints.size() == 4);
		EQUAL(cond);
	}
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " top method "
              << "] --------------------]\t\t\033[0m";
	{
		ft::stack<int> mystack;

		mystack.push(10);
		mystack.push(20);

		mystack.top() -= 5;
		std::vector<int> vec(10, 50);
		vec.push_back(300);
		ft::stack<int, std::vector<int> > const c_mystack(vec);

		EQUAL(mystack.top() == 15 && c_mystack.top() == 300);
	}
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " push & pop methods "
              << "] --------------------]\t\t\033[0m";
	{
		int sum(0);
		ft::stack<int> mystack;

		for (int i=0; i<5; ++i) mystack.push(i);

		while (!mystack.empty())
		{
			sum += mystack.top();
			mystack.pop();
		}
		EQUAL(sum == 10);
	}
}

void	testRelationalOperators(void)
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator== "
              << "] --------------------]\t\t\033[0m";
	{
		bool cond(false);
		std::vector<int>	vec(100, 2);
		std::vector<int>	vec1(100, 2);
		{
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = (mystack ==  mystack1) == (stack == stack1);
		}
		{
			vec.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack ==  mystack1) == (stack == stack1);
		}
		{
			vec.pop_back();
			vec1.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack ==  mystack1) == (stack == stack1);
		}
		EQUAL(cond);
	}
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator!= "
              << "] --------------------]\t\t\033[0m";
	{
		bool cond(false);
		std::vector<int>	vec(100, 2);
		std::vector<int>	vec1(100, 2);
		{
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = (mystack !=  mystack1) == (stack != stack1);
		}
		{
			vec.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack !=  mystack1) == (stack != stack1);
		}
		{
			vec.pop_back();
			vec1.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack !=  mystack1) == (stack != stack1);
		}
		EQUAL(cond);
	}
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator< "
              << "] --------------------]\t\t\033[0m";
	{
		bool cond(false);
		std::vector<int>	vec(100, 2);
		std::vector<int>	vec1(100, 2);
		{
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = (mystack < mystack1) == (stack < stack1);
		}
		{
			vec.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack < mystack1) == (stack < stack1);
		}
		{
			vec.pop_back();
			vec1.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack < mystack1) == (stack < stack1);
		}
		EQUAL(cond);
	}
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator<= "
              << "] --------------------]\t\t\033[0m";
	{
		bool cond(false);
		std::vector<int>	vec(100, 2);
		std::vector<int>	vec1(100, 2);
		{
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = (mystack <= mystack1) == (stack <= stack1);
		}
		{
			vec.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack <= mystack1) == (stack <= stack1);
		}
		{
			vec.pop_back();
			vec1.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack <= mystack1) == (stack <= stack1);
		}
		EQUAL(cond);
	}
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator> "
              << "] --------------------]\t\t\033[0m";
	{
		bool cond(false);
		std::vector<int>	vec(100, 2);
		std::vector<int>	vec1(100, 2);
		{
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = (mystack > mystack1) == (stack > stack1);
		}
		{
			vec.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack > mystack1) == (stack > stack1);
		}
		{
			vec.pop_back();
			vec1.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack > mystack1) == (stack > stack1);
		}
		EQUAL(cond);
	}
	std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator>= "
              << "] --------------------]\t\t\033[0m";
	{
		bool cond(false);
		std::vector<int>	vec(100, 2);
		std::vector<int>	vec1(100, 2);
		{
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = (mystack >= mystack1) == (stack >= stack1);
		}
		{
			vec.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack >= mystack1) == (stack >= stack1);
		}
		{
			vec.pop_back();
			vec1.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack >= mystack1) == (stack >= stack1);
		}
		EQUAL(cond);
	}
}

#endif

int main()
{
    {
        std::cout << RED << "*************************************************************" << std::endl;
        std::cout << RED << "*            ----------- vector tests -----------           *" << std::endl;
        std::cout << RED << "*************************************************************" << std::endl;
        signal(SIGALRM, alarm_handler);
        iterator_tests();
        const_iterator_tests();
        reverse_iterator_tests();
        reverse_iterator_with_ft_vector();
        vector_tests();
    }
    {
        std::cout << RED << "*************************************************************" << std::endl;
        std::cout << RED << "*            ----------- stack tests -----------            *" << std::endl;
        std::cout << RED << "*************************************************************" << std::endl;
        signal(SIGALRM, alarm_handler);

        std::cout << YELLOW << "Testing Constructors;" << RESET << std::endl;
        TEST_CASE(testConstructors);

        std::cout << YELLOW << "Testing member methods;" << RESET << std::endl;
        TEST_CASE(testMemberMethods);

        std::cout << YELLOW << "Testing relational operators;" << RESET << std::endl;
        TEST_CASE(testRelationalOperators);
    }
    {
        std::cout << RED << "*************************************************************" << std::endl;
        std::cout << RED << "*            -----------   map  tests -----------           *" << std::endl;
        std::cout << RED << "*************************************************************" << std::endl;
        signal(SIGALRM, alarm_handler);

        std::cout << YELLOW << "Testing Iterators;" << RESET << std::endl;
        TEST_CASE(map_iterator_tests);
        TEST_CASE(map_const_iterator_tests);
        TEST_CASE(map_reverse_iterator_tests);
        std::cout << std::endl;

        std::cout << YELLOW << "Testing Constructors;" << RESET << std::endl;
        TEST_CASE(MaptestConstructors);
        std::cout << std::endl;

        std::cout << YELLOW << "Testing Iterator Methods;" << RESET << std::endl;
        TEST_CASE(testIterators);
        std::cout << std::endl;

        std::cout << YELLOW << "Testing Capacity Methods;" << RESET << std::endl;
        TEST_CASE(testCapacityMethods)
        std::cout << std::endl;

        std::cout << YELLOW << "Testing Access Element Methods; " << RESET << std::endl;
        TEST_CASE(testElementAccess);
        std::cout << std::endl;

        std::cout << YELLOW << "Testing Modifiers Methods;" << RESET << std::endl;
        TEST_CASE(testModifiers)
        std::cout << std::endl;

        std::cout << YELLOW << "Testing Observers Methods;" << RESET << std::endl;
        TEST_CASE(testObservers)
        std::cout << std::endl;

        std::cout << YELLOW << "Testing Operations Methods;" << RESET << std::endl;
        TEST_CASE(testOperations)
        std::cout << std::endl;

        std::cout << YELLOW << "Testing Allocator Methods;" << RESET << std::endl;
        TEST_CASE(testAllocatorMethodes)
        std::cout << std::endl;

        std::cout << YELLOW << "Testing Retional Operators; " << RESET << std::endl;
        TEST_CASE(testRetionalOperators);
        std::cout << std::endl;

        std::cout << YELLOW << "Testing Non-Member Swap  ; " << RESET << std::endl;
        TEST_CASE(testNonMemberSwap);
        std::cout << std::endl;
    }
}
