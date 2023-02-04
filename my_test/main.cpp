#include "../map.hpp"       // your map path.
#include "../vector.hpp" // your Vector path.
#include "../utility.hpp"  // path to ft::pair.
// #include "map-test-helper.hpp"
#include <map>

#include <vector>
#include <iostream>
#include <iterator>
#include <utility>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <random>
#include <typeinfo>

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

int main()
{

    std::cout << RED << "________________________________________________________________________________________________________" << std::endl;
    std::cout << RED << "**** The test is taking so much time to test the all cases and the time complexity of each method ****" << std::endl;
    std::cout << RED << "--------------------------------------------------------------------------------------------------------" << RESET << std::endl;
    signal(SIGALRM, alarm_handler);

    // std::cout << YELLOW << "Testing Iterators;" << RESET << std::endl;
    // TEST_CASE(iterator_tests);
    // TEST_CASE(const_iterator_tests);
    // TEST_CASE(reverse_iterator_tests);
    // std::cout << std::endl;

    // std::cout << YELLOW << "Testing Constructors;" << RESET << std::endl;
    // TEST_CASE(testConstructors);
    // std::cout << std::endl;

    // std::cout << YELLOW << "Testing Iterator Methods;" << RESET << std::endl;
    // TEST_CASE(testIterators);
    // std::cout << std::endl;

    // std::cout << YELLOW << "Testing Capacity Methods;" << RESET << std::endl;
    // TEST_CASE(testCapacityMethods)
    // std::cout << std::endl;

    // std::cout << YELLOW << "Testing Access Element Methods; " << RESET << std::endl;
    // TEST_CASE(testElementAccess);
    // std::cout << std::endl;

    // std::cout << YELLOW << "Testing Modifiers Methods;" << RESET << std::endl;
    // TEST_CASE(testModifiers)
    // std::cout << std::endl;

    // std::cout << YELLOW << "Testing Observers Methods;" << RESET << std::endl;
    // TEST_CASE(testObservers)
    // std::cout << std::endl;

    // std::cout << YELLOW << "Testing Operations Methods;" << RESET << std::endl;
    // TEST_CASE(testOperations)
    // std::cout << std::endl;

    // std::cout << YELLOW << "Testing Allocator Methods;" << RESET << std::endl;
    // TEST_CASE(testAllocatorMethodes)
    // std::cout << std::endl;

    std::cout << YELLOW << "Testing Retional Operators; " << RESET << std::endl;
    TEST_CASE(testRetionalOperators);
    std::cout << std::endl;

    // std::cout << YELLOW << "Testing Non-Member Swap  ; " << RESET << std::endl;
    // TEST_CASE(testNonMemberSwap);
    // std::cout << std::endl;
    return 0;
}