/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:44:28 by mbadaoui          #+#    #+#             */
/*   Updated: 2023/01/06 17:44:31 by mbadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include "../iterators/iterator.hpp"
# include "../iterators/iterator_traits.hpp"
# include "../iterators/reverse_iterator.hpp"
# include "../utility.hpp"

namespace ft
{
    template<class T, class Allocator = std::allocator<T>>
    class vector
    {
        public:
            typedef T                                                   value_type;
            typedef Allocator                                           allocator_type;
            typedef size_t                                              size_type;
            typedef ptrdiff_t                                           difference_type;
            typedef value_type&                                         reference;
            typedef const value_type&                                   const_reference;
            typedef typename Allocator::pointer                         pointer;
            typedef typename Allocator::const_pointer                   const_pointer;
            typedef typename ft::random_access_iterator<pointer>        iterator;
            typedef typename ft::random_access_iterator<const_pointer>  const_iterator;
            typedef typename ft::reverse_iterator<iterator>             reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>       const_reverse_iterator;
        protected:
            pointer                                                     _begin;
            pointer                                                     _end;
            pointer                                                     _data;
            std::allocator<T>                                           _allocator;
            size_type                                                   _capacity;
            size_type                                                   _size;
        public:
            
            //The default constructor. Creates a vector of length zero. The vector will use the 
            //allocator alloc for all storage management.
            explicit vector( const allocator_type& alloc = allocator_type())
            {
                _data = nullptr;
                _begin = nullptr;
                _end = nullptr;
                _allocator = alloc;
                _capacity = 0;
                _size = 0;
            };
            //Creates a vector of length count, containing n copies of the default value for type T.
            //Requires that T have a default constructor. The vector will use the allocator Allocator()
            //for all storage management.
            explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator())
            {
                _data = nullptr;
                _begin = nullptr;
                _end = nullptr;
                _size = 0;
                _capacity = 0;
                _allocator = alloc;
                if (count > max_size())
                    throw std::length_error("length error");
                _data = _allocator.allocate(count);
                _begin = _data;
                if (_data)
                for (int i =0; i < count; ++i)
                    _allocate.construct(_data + i, value);
                _end = _data + count;
                _capacity = count;
                _size = count;
            }
            //Creates a vector of length last - first, filled with all values obtained by dereferencing
            //the InputIt oon the range [first, last). The vector will use the allocator alloc for all storage management.
            template<class InputIt>
            vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(),
            typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr)
            {
                _data = nullptr;
                _begin = nullptr;
                _end = nullptr;
                _size = 0;
                _capacity = 0;
                _allocator = alloc;
                _capacity = difference_type(last - first);
                _data = _allocator.allocate(_size);
                _begin = _data;
                for (; first != last; ++first)
                {
                    _allocate.construct(_data + _size, *first);
                    ++_size;
                }
                _end = _data + _size;
            }
            // Creates a copy of other
            vector( const vector& other)
            {
                *this = other;
            }
            // destructs the vector
            ~vector()
            {
                if (_size > 0)
                {
                    for (int i = 0; i > _size; i++)
                        _allocator.destroy(_data + i);
                }
                if (_begin != nullptr)
                    _allocator.deallocate(_data, _size);
                _size = 0;
                _capacity = 0;
                _begin = nullptr;
                _end = nullptr;
            }

            vector& operator= (const vector& other )
            {
                if (*this != other)
                {
                    for (int i = 0; i > _size; i++)
                        _allocator.destroy(_data + i);
                    if (_begin != nullptr)
                        _allocator.deallocate(_data, _size);
                    _size = 0;
                    _capacity = 0;
                    _allocator = Allocator();
                    _data = _allocator.allocate(other.size());
                    iterator it = other.begin();
                    _begin = it;
                    for (; it != other.end(); it++)
                    {
                        _allocator.construct(_data + i, it);
                        ++_size;
                    }
                    _end= it;
                    _capacity = _size;
                }
                return *this;
            }

            reference at ( size_type pos )
            {
                if (pos >= size())
                    std::out_of_range("position out of range");
                return (this->_begin[pos]);
            }
            const_reference at ( size_type pos ) const
            {
                if (pos >= size())
                    std::out_of_range("position out of range");
                return (this->_begin[pos]);
            }

            reference operator[] (size_type pos )
            {
                return (this->_begin[pos]);
            }
            const_reference operator[] ( size_type pos ) const
            {
                return (this->_begin[pos]);
            }

            reference front()
            {
                return *(this->_begin);
            }
            const_reference front() const
            {
                return *(this->_begin);
            }

            reference back()
            {
                return *(this->_end - 1);
            }
            const_reference back() const
            {

                return *(this->_end - 1);
            }

            T* data()
            {
                return this->_data;
            }
            const T* data() const
            {
                return this->_data;
            }
            
            iterator begin()
            {
                return iterator(this->_begin);
            }
            const_iterator begin() const
            {
                return const_iterator(this->_begin);
            }
            iterator end()
            {
                return iterator(this->_end);
            }
            const_iterator end() const
            {
                return const_iterator(this->_end);
            }
            reverse_iterator rbegin()
            {
                return reverse_iterator(end());
            }
            const_reverse_iterator rbegin() const
            {
                return const_reverse_iterator(end());
            }
            reverse_iterator rend()
            {
                return reverse_iterator(begin());
            }
            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(begin());
            }

            void assign( size_type count, const T& value)
            {
                if (this->size() > 0)
                {
                    for (int i = 0; i < this->size(); i++)
                        _allocator.destroy(_data + i);
                    _allocator.deallocate(_data, this->size());
                }
                _allocator = Allocator();
                _data = _allocator.allocate(count);
                _begin = _data;
                _capacity = count;
                _size = 0;
                for (int i = 0; i < count; i++)
                {
                    _allocator.construct(_data + i, value);
                    ++_size;
                }
                _end = _data + _size;
            }
            template<class InputIt>
            void assign( InputIt first, InputIt last,
            typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr)
            {
                if (this->size() > 0)
                {
                    for (int i = 0; i < this->size(); i++)
                        _allocator.destroy(_data + i);
                    _allocator.deallocate(_data, this->size());
                }
                _allocator = Allocator();
                _data = _allocator.allocate(difference_type(last - first));
                _begin = _data;
                _capacity = difference_type(last - first);
                _size = 0;
                for (; first != last; ++first)
                {
                    _allocator.construct(_data + _size, *first);
                    ++_size;
                }
                _end = _data + _size;
            }

            allocator_type get_allocator() const
            {
                return this->_allocator;
            }

            bool empty() const
            {
                return (this->begin() == this->end());
            }

            size_type size() const
            {
                return this->_size;
            }
            size_type max_size() const
            {
                return this->_allocator.max_size();
            }

            void reserve( size_type new_cap )
            {
                
            }
            size_type capacity() const;

            void clear();

            //insert value before pos, It returns iterator pointing to the inserted value
            iterator insert ( const_iterator pos, const T& value );
            //insert count copies of the value before pos, it returns iterator pointing to the first element
            //inserted, or pos if count == 0.
            iterator insert ( const_iterator pos, size_type count, const T& value);
            //insert elements from range [first,last) before pos
            //this overload has the same effect as ovverload of previous function if InputIt is an intergral type.
            //The behavior is undefined if first and last are iterators into *this.
            //It returns iteratorpoiting to the first element inserted, or pos if first == last.
            template<class InputIt>
            iterator insert ( const_iterator pos, InputIt firstm InputUt last );

            //removes the element at pos
            iterator erase( iterator pos );
            //removes the elements in the range [first, last)
            iterator erase( iterator first , iterator last );

            void push_back( const T& value );

            void pop_back();

            //resize the container to contain count elements.
            void resize( size_type count, T value = T() );

            void swap ( vector& other );
    };

    template<class T , class Alloc>
    inline bool operator== (const ft::vector<T, Alloc>& lhs,
                            const ft::vector<T,Alloc>&rhs);

    template<class T, class Alloc>
    inline bool operator!= (const ft::vector<T, Alloc>& lhs,
                            const ft::vector<T,Alloc>&rhs);
    
    template<class T, class Alloc>
    inline bool operator< (const ft::vector<T, Alloc>& lhs,
                            const ft::vector<T,Alloc>&rhs);
    
    template<class T, class Alloc>
    inline bool operator<= (const ft::vector<T, Alloc>& lhs,
                            const ft::vector<T,Alloc>&rhs);
    
    template<class T, class Alloc>
    inline bool operator> (const ft::vector<T, Alloc>& lhs,
                            const ft::vector<T,Alloc>&rhs);

    template<class T, class Alloc>
    inline bool operator>= (const ft::vector<T, Alloc>& lhs,
                            const ft::vector<T,Alloc>&rhs);
    
    template<class T, class Alloc>
    inline void swap (ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs);
}

#include <vector>

#endif
