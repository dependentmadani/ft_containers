# include <iostream>
# include <string>
# include <vector>

// --- Class foo
template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

template <typename T>
std::ostream	&operator<<(std::ostream &o, foo<T> const &bar) {
	o << bar.getValue();
	return o;
}
// --- End of class foo

template <typename T>
T	inc(T it, int n)
{
	while (n-- > 0)
		++it;
	return (it);
}

template <typename T>
T	dec(T it, int n)
{
	while (n-- > 0)
		--it;
	return (it);
}

#include "vector.hpp"
#include <iostream>

#define T_SIZE_TYPE typename TESTED_NAMESPACE::vector<T>::size_type
#define TESTED_NAMESPACE ft

template <typename T>
void	printSize(TESTED_NAMESPACE::vector<T> const &vct, bool print_content = true)
{
	const T_SIZE_TYPE size = vct.size();
	const T_SIZE_TYPE capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename TESTED_NAMESPACE::vector<T>::const_iterator it = vct.begin();
		typename TESTED_NAMESPACE::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

// #define TESTED_TYPE int
// #include <list>

// int		main(void)
// {
// 	std::list<TESTED_TYPE> lst;
// 	std::list<TESTED_TYPE>::iterator lst_it;
// 	for (int i = 1; i < 5; ++i)
// 		lst.push_back(i * 3);

// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(lst.begin(), lst.end());
// 	printSize(vct);

// 	lst_it = lst.begin();
// 	for (int i = 1; lst_it != lst.end(); ++i)
// 		*lst_it++ = i * 5;
// 	vct.assign(lst.begin(), lst.end());
// 	printSize(vct);

// 	vct.insert(vct.end(), lst.rbegin(), lst.rend());
// 	printSize(vct);
// 	std::cout << "###############################################" << std::endl;
// 	return (0);
// }

#define TESTED_TYPE int

int		main(void)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(5);
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin(), ite = vct.end();

	std::cout << "len: " << (ite - it) << std::endl;
	for (; it != ite; ++it)
		*it = (ite - it);

	it = vct.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		*it = ++i * 5;

	it = vct.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_copy(vct);
	for (int i = 0; it != ite; ++it)
		*it = ++i * 7;
	vct_copy.push_back(42);
	vct_copy.push_back(21);

	std::cout << "\t-- PART ONE --" << std::endl;
	printSize(vct);
	printSize(vct_range);
	printSize(vct_copy);

	vct = vct_copy;
	vct_copy = vct_range;
	vct_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	printSize(vct);
	printSize(vct_range);
	printSize(vct_copy);

	// std::cout << "test the std *******************" << std::endl;

	// #define TESTED_NAMESPACE std
	// TESTED_NAMESPACE::vector<TESTED_TYPE> vct1(5);
	// TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct1.begin(), ite = vct1.end();

	// std::cout << "len: " << (ite - it) << std::endl;
	// for (; it != ite; ++it)
	// 	*it = (ite - it);

	// it = vct.begin();
	// TESTED_NAMESPACE::vector<TESTED_TYPE> vct_range1(it, --(--ite));
	// for (int i = 0; it != ite; ++it)
	// 	*it = ++i * 5;

	// it = vct.begin();
	// TESTED_NAMESPACE::vector<TESTED_TYPE> vct_copy1(vct1);
	// for (int i = 0; it != ite; ++it)
	// 	*it = ++i * 7;
	// vct_copy1.push_back(42);
	// vct_copy1.push_back(21);

	// std::cout << "\t-- PART ONE --" << std::endl;
	// printSize(vct1);
	// printSize(vct_range1);
	// printSize(vct_copy1);

	// vct1 = vct_copy1;
	// vct_copy1 = vct_range1;
	// vct_range1.clear();

	// std::cout << "\t-- PART TWO --" << std::endl;
	// printSize(vct1);
	// printSize(vct_range1);
	// printSize(vct_copy1);
	return (0);
}
