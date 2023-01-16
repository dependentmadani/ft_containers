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
# include "iterator.hpp"
# include "iterator_traits.hpp"
# include "reverse_iterator.hpp"
# include "utility.hpp"

namespace ft
{
    template<class T, class Allocator = std::allocator<T> >
    class vector
    {
        public:
            typedef T                                                       value_type;
            typedef Allocator                                               allocator_type;
            typedef size_t                                                  size_type;
            typedef ptrdiff_t                                               difference_type;
            typedef value_type&                                             reference;
            typedef const value_type&                                       const_reference;
            typedef typename Allocator::pointer                             pointer;
            typedef typename Allocator::const_pointer                       const_pointer;
            typedef typename ft::random_access_iterator<value_type>         iterator;
            typedef typename ft::random_access_iterator<const value_type>   const_iterator;
            typedef typename ft::reverse_iterator<iterator>                 reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>           const_reverse_iterator;
        protected:
            pointer                                                     _begin;
            pointer                                                     _end;
            pointer                                                     _data;
            allocator_type                                              _allocator;
            size_type                                                   _capacity;
            size_type                                                   _size;
        public:
            
            //The default constructor. Creates a vector of length zero. The vector will use the 
            //allocator alloc for all storage management.
            explicit vector( const allocator_type& alloc = allocator_type())
            {
                _data = NULL;
                _begin = NULL;
                _end = NULL;
                _allocator = alloc;
                _capacity = 0;
                _size = 0;
            };
            //Creates a vector of length count, containing n copies of the default value for type T.
            //Requires that T have a default constructor. The vector will use the allocator Allocator()
            //for all storage management.
            explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator())
            {
                _data = NULL;
                _begin = NULL;
                _end = NULL;
                _size = 0;
                _capacity = 0;
                _allocator = alloc;
                if (count > max_size())
                    throw std::length_error("length error");
                _data = _allocator.allocate(count);
                _begin = _data;
                if (_data)
                for (size_t i =0; i < count; ++i)
                    _allocator.construct(_data + i, value);
                _end = _data + count;
                _capacity = count;
                _size = count;
            }
            //Creates a vector of length last - first, filled with all values obtained by dereferencing
            //the InputIt oon the range [first, last). The vector will use the allocator alloc for all storage management.
            template<class InputIt>
            vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(),
            typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
            {
                _data = NULL;
                _begin = NULL;
                _end = NULL;
                _size = 0;
                _capacity = 0;
                _allocator = alloc;
                this->assign(first, last);
            }
            // Creates a copy of other
            vector( const vector& other)
            {
                _capacity = 0;
                _size = 0;
                *this = other;
            }
            // destructs the vector
            ~vector()
            {
                if (_size > 0)
                {
                    for (size_t i = 0; i > _size; i++)
                        _allocator.destroy(_data + i);
                }
                if (_begin != NULL)
                    _allocator.deallocate(_data, _capacity);
                _size = 0;
                _capacity = 0;
                _begin = NULL;
                _end = NULL;
            }

            vector& operator= (const vector& other )
            {
                if (*this != other)
                {
                    for (size_t i = 0; i > _size; i++)
                        _allocator.destroy(_data + i);
                    if (_capacity != 0)
                        _allocator.deallocate(_data, _capacity);
                    _capacity = other.capacity();
                    _size = other.size();
                    _data = _allocator.allocate(_capacity);
                    _begin = _data;
                    for (size_t i = 0; i < _size; ++i)
                    {
                        _allocator.construct(&_data[i], other._data[i]);
                    }
                    _end= _data + _size;
                }
                return *this;
            }

            reference at ( size_type pos )
            {
                if (pos >= size())
                    throw std::out_of_range("position out of range");
                return (this->_begin[pos]);
            }
            const_reference at ( size_type pos ) const
            {
                if (pos >= size())
                    throw std::out_of_range("position out of range");
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
                return reverse_iterator(this->_end );
            }
            const_reverse_iterator rbegin() const
            {
                return const_reverse_iterator(this->_end );
            }
            reverse_iterator rend()
            {
                return reverse_iterator(this->_begin);
            }
            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(this->_begin);
            }

            void assign( size_type count, const T& value)
            {
                if (this->size() > 0)
                {
                    for (size_t i = 0; i < this->size(); i++)
                        _allocator.destroy(_data + i);
                    _allocator.deallocate(_data, this->capacity());
                }
                _allocator = Allocator();
                _data = _allocator.allocate(count);
                _begin = _data;
                _capacity = count;
                _size = 0;
                for (size_t i = 0; i < count; i++)
                {
                    _allocator.construct(_data + i, value);
                    ++_size;
                }
                _end = _data + _size;
            }
            
            template<class InputIt>
            void assign( InputIt first, InputIt last,
            typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
            {
                size_t size = 0;
                InputIt tmp = first;

                while (tmp != last)
                {
                    tmp++;
                    size++;
                }
                this->clear();
                this->reserve(size);
                for (; first != last; ++first)
                    this->push_back(*first);
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
                if (new_cap > this->max_size())
                    std::length_error("vector");
                if (new_cap > _capacity)
                {
                    T* newElements = _allocator.allocate(new_cap);
                    for (size_t i = 0; i < this->size(); i++)
                    {
                        newElements[i] = _begin[i];
                    }
                    for (size_t i = 0; i < this->size(); i++)
                        _allocator.destroy(_data + i);
                    _allocator.deallocate(_data, this->capacity());
                    _data = newElements;
                    _begin = _data;
                    _end = _data + this->size();
                    _capacity = new_cap;
                }
            }
            size_type capacity() const
            {
                return _capacity;
            }

            void clear()
            {
                for (size_t i = 0; i < _size; i++)
                    _allocator.destroy(_data + i);
                _allocator.deallocate(_data, _size);
                _data = _allocator.allocate(_capacity);
                _begin = _data;
                _size = 0;
                _end = _data + _size;
            }

            //insert value before pos, It returns iterator pointing to the inserted value
            iterator insert ( iterator pos, const T& value )
            {
                size_t position = pos - this->begin();
                
                insert(pos, 1, value);
                return iterator(this->begin() + position);
            }
            //insert count copies of the value before pos, it returns iterator pointing to the first element
            //inserted, or pos if count == 0.
            void insert ( iterator pos, size_type count, const T& value)
            {
                difference_type old_position = this->end() - this->begin();
                difference_type position = pos - this->begin();

                if ( count == 0 )
                    return ;
                resize(_size + count);
                iterator old_end = this->begin() + old_position;
                pos = this->begin() + position;
                iterator new_end = this->end();
                while (old_end != pos)
                    *--new_end = *--old_end;
                
                while (count > 0)
                {
                    *pos++ = value;
                    count--;
                }
            }
            //insert elements from range [first,last) before pos
            //this overload has the same effect as ovverload of previous function if InputIt is an intergral type.
            //The behavior is undefined if first and last are iterators into *this.
            //It returns iteratorpoiting to the first element inserted, or pos if first == last.
            template<class InputIt>
            void insert ( iterator pos, InputIt first, InputIt last,
            typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
            {
                size_type old_position = Iterator_difference(_begin, _end);
                size_type position = 0;
                iterator tmp = _begin;
                while (tmp != pos)
                {
                    ++tmp;
                    position++;
                }

                resize(_size + Iterator_difference(first, last));
                iterator old_end = this->begin() + old_position;
                pos = this->begin() + position;
                iterator new_end = this->end();
                while (old_end != pos)
                    *--new_end = *--old_end;
                for (; first != last;)
                    *pos++ = *first++;
                _end = _begin + _size;
            }

            //removes the element at pos
            iterator erase( iterator pos )
            {
                return (this->erase(pos, pos + 1));
            }
            //removes the elements in the range [first, last)
            iterator erase( iterator first , iterator last )
            {
                size_type range = last - first, start = first - begin();

				for (size_type i=0; (i < range && i < _size); i++)
				{
					_allocator.destroy(_data +start + i);
					if (start + range + i < _size)
						_allocator.construct(&_data[i + start], _data[i+start+range]);
				}
				for (size_type i = start + range; i < _size; i++)
				{
					_allocator.destroy(_data + i);
					if (range + i < _size)
						_allocator.construct(&_data[i], _data[i+range]);
				}
				_size -= range;
                _end = _begin + _size;
				return iterator(_data + start);

            }

            void push_back( const T& value )
            {
                if (_size >= _capacity)
                {
                    if (_size == 0)
                        reserve(1);
                    else
                        reserve(_size * 2);
                }
                _allocator.construct(&_data[_size], value);
                _size++;
                _end = _begin + _size;
            }

            void pop_back()
            {
                if (!empty())
                {
                    _allocator.destroy(&_data[_size]);
                    _end = _end - 1;
                    --_size;
                }
            }

            //resize the container to contain count elements.
            void resize( size_type count, T value = T() )
            {
                size_t new_capacity;

                if (count < _size)
                {
                    for (size_t i = count; i < _size ; i++)
                        _allocator.destroy(_data + i);
                    _end = _begin + count;
                    _size = count;
                }
                else if (count > _size)
                {
                    if (count > _capacity)
                    {
                        if (_capacity == 0)
                            new_capacity = 1;
                        else
                            new_capacity = _capacity * 2;
                        if (new_capacity < count)
                            new_capacity = count;
                        this->reserve(new_capacity);
                    }
                    for (size_t i = _size; i < count; i++)
                        _allocator.construct(_data + i, value);
                    _end = _begin + count;
                    _size = count;
                }
            }

            void swap ( vector& other )
            {
                pointer tmp_begin = other._begin;
                pointer tmp_end = other._end;
                pointer tmp_data = other._data;
                allocator_type tmp_allocator = other._allocator;
                size_type tmp_capacity = other._capacity;
                size_type tmp_size = other._size;

                other._begin = _begin;
                other._end = _end;
                other._data = _data;
                other._allocator = _allocator;
                other._capacity = _capacity;
                other._size = _size;

                _begin = tmp_begin;
                _end = tmp_end;
                _data = tmp_data;
                _allocator = tmp_allocator;
                _capacity = tmp_capacity;
                _size = tmp_size;
                
            }
    };

    template<class T , class Alloc> bool operator== (const ft::vector<T, Alloc>& lhs,
                            const ft::vector<T,Alloc>& rhs)
    {
        size_t i = 0;

        if (lhs.size() != rhs.size())
            return false;
        while (i < rhs.size())
        {
            if (lhs[i] != rhs[i])
                return false;
            i++;
        }
        return true;
    };

    template<class T, class Alloc> bool operator!= (const ft::vector<T, Alloc>& lhs,
                            const ft::vector<T,Alloc>& rhs)
    {
        if (lhs == rhs)
            return false;
        return true;
    };
    
    template<class T, class Alloc> bool operator< (const ft::vector<T, Alloc>& lhs,
                            const ft::vector<T,Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    };
    
    template<class T, class Alloc>bool operator<= (const ft::vector<T, Alloc>& lhs,
                            const ft::vector<T,Alloc>& rhs)
    {
        return !(rhs < lhs);
    };
    
    template<class T, class Alloc> bool operator> (const ft::vector<T, Alloc>& lhs,
                            const ft::vector<T,Alloc>& rhs)
    {
        return (rhs < lhs);
    };

    template<class T, class Alloc> bool operator>= (const ft::vector<T, Alloc>& lhs,
                            const ft::vector<T,Alloc>& rhs)
    {
        return !(lhs < rhs);
    };
    
    template<class T, class Alloc> void swap (ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs)
    {
        lhs.swap(rhs);
    };
}

#endif
