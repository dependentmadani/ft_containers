#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
    template<class T, class Container= ft::vector<T> >
    class stack
    {
        public:
            typedef Container                           container_type;
            typedef typename Container::value_type      value_type;
            typedef typename Container::size_type       size_type;
            typedef typename Container::reference       reference;
            typedef typename Container::const_reference const_reference;
        protected:
            Container                                   c;
        public:
            //constructors of stack:
            explicit stack(const Container& cont= Container())
            {
                c = cont;
            }

            //copy constructor:
            stack(const stack& other)
            {
                c = other.c;
            }

            //destructor:
            ~stack()
            {}

            //copy assignment operator = for stack:
            stack& operator= (const stack& other)
            {
                if (*this != other)
                    this->c = other.c;
                return *this;
            }
            
            //top of the stack
            reference top()
            {
                return c.back();
            }

            //top of the stack
            const_reference top() const
            {
                return c.back();
            }

            //check if the stack is empty
            bool empty() const
            {
                return c.empty();
            }

            //check the size of stack
            size_type size() const
            {
                return c.size();
            }

            //add a value at the end of the stack
            void push(const value_type& value)
            {
                c.push_back(value);
            }

            //remove value from the end of the stack
            void pop()
            {
                c.pop_back();
            }

            friend bool operator==( const stack<T,Container> &lhs, const stack<T,Container> &rhs )
            {
                return lhs.c == rhs.c;
            }

            friend bool operator!=( const stack<T,Container> &lhs, const stack<T,Container> &rhs )
            {
                return lhs.c != rhs.c;
            }

            friend bool operator<( const stack<T,Container> &lhs, const stack<T,Container> &rhs )
            {
                return lhs.c < rhs.c;
            }

            friend bool operator<=( const stack<T,Container> &lhs, const stack<T,Container> &rhs )
            {
                return lhs.c <= rhs.c;
            }

            friend bool operator>( const stack<T,Container> &lhs, const stack<T,Container> &rhs )
            {
                return lhs.c > rhs.c;
            }

            friend bool operator>=( const stack<T,Container> &lhs, const stack<T,Container> &rhs )
            {
                return lhs.c >= rhs.c;
            }

    };
}

#endif