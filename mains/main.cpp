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

#include "main_vector.hpp"
#include "main_stack.hpp"
#include "main_map.hpp"

#define TIME_FAC 10 // the ft::map methods can be slower up to std::map methods * TIME_FAC (MAX 20)

time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return (msecs_time);
}

int main()
{
    {
        std::cout << "----------- vector tests -----------" << std::endl;
        signal(SIGALRM, alarm_handler);
        iterator_tests();
        const_iterator_tests();
        reverse_iterator_tests();
        reverse_iterator_with_ft_vector();
        vector_tests();
    }
    {
        std::cout << "----------- stack tests -----------" << std::endl;
        signal(SIGALRM, alarm_handler);

        std::cout << YELLOW << "Testing Constructors;" << RESET << std::endl;
        TEST_CASE(testConstructors);

        std::cout << YELLOW << "Testing member methods;" << RESET << std::endl;
        TEST_CASE(testMemberMethods);

        std::cout << YELLOW << "Testing relational operators;" << RESET << std::endl;
        TEST_CASE(testRelationalOperators);
    }
    {
        std::cout << "----------- map tests -----------" << std::endl;
        signal(SIGALRM, alarm_handler);

        std::cout << YELLOW << "Testing Iterators;" << RESET << std::endl;
        TEST_CASE(iterator_tests);
        TEST_CASE(const_iterator_tests);
        TEST_CASE(reverse_iterator_tests);
        std::cout << std::endl;

        std::cout << YELLOW << "Testing Constructors;" << RESET << std::endl;
        TEST_CASE(testConstructors);
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
