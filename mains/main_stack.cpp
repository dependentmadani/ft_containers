/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:41:21 by mbadaoui          #+#    #+#             */
/*   Updated: 2023/02/19 14:41:22 by mbadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_stack.hpp"

int main()
{
	std::cout << RED << "________________________________________________________________________________________________________" << std::endl;
    std::cout << RED << "**** The test is taking so much time to test the all cases and the time complexity of each method ****" << std::endl;
    std::cout << RED << "--------------------------------------------------------------------------------------------------------" << RESET << std::endl;
    signal(SIGALRM, alarm_handler);

    std::cout << YELLOW << "Testing Constructors;" << RESET << std::endl;
    TEST_CASE(testConstructors);

    std::cout << YELLOW << "Testing member methods;" << RESET << std::endl;
    TEST_CASE(testMemberMethods);

    std::cout << YELLOW << "Testing relational operators;" << RESET << std::endl;
    TEST_CASE(testRelationalOperators);

	return 0;
}
