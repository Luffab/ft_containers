/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatilly <fatilly@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:35:15 by fatilly           #+#    #+#             */
/*   Updated: 2022/12/09 03:27:51 by fatilly          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include <iostream>

namespace ft
{
	template <typename T, typename Category = std::random_access_iterator_tag, typename Distance = std::ptrdiff_t, typename Pointer = T*, typename Reference = T&>
	class vector_iterator
	{
		public :
		//type definitions
			typedef	T			value_type;
			typedef	Distance	difference_type;
			typedef	Pointer		pointer;
			typedef	Reference	reference;
			typedef	Category	iterator_category;
		
		private :
		//variables
			pointer _ptr;
			
		public :				
		//default contructor
			vector_iterator(void) {_ptr = NULL;}
		
		//fill contructor
			vector_iterator(pointer ptr) : _ptr(ptr) {}
		
		//copy contructor
			vector_iterator(const vector_iterator &src) {_ptr = src.getPointer();}
		
		//destructor
			~vector_iterator(void) {}
		
		//getter
			pointer	getPointer(void) const {return _ptr;}
		
		//operators overload
			vector_iterator& operator=(const vector_iterator &other)
			{
				if (*this == *&other)
					return *this;
				_ptr = other.getPointer();
				return *this;
			}
			
			operator vector_iterator<const T>(void) const
			{
				return vector_iterator<const T>(_ptr);
			}
			
			bool operator!=(const vector_iterator<const T> &other) const
			{
				return (_ptr != other.getPointer());
			}

			bool operator==(const vector_iterator<const T> &other) const
			{
				return (_ptr == other.getPointer());
			}
			
			value_type operator[](int n) const
			{
				return _ptr[n];
			}

			vector_iterator& operator++(void)
			{
				_ptr++;
				return *this;
			}

			vector_iterator& operator--(void)
			{
				_ptr--;
				return *this;
			}
		
			vector_iterator	operator++(int)
			{
				vector_iterator	tmp;
			
				tmp = *this;
				this->_ptr++;
				return tmp;
			}
			
			vector_iterator	operator--(int)
			{
				vector_iterator	tmp(*this);
			
				this->_ptr--;
				return tmp;
			}
			
			vector_iterator operator+(int n) const
			{
				vector_iterator tmp(*this);
				
				tmp += n;
				return tmp;
			}

			vector_iterator operator-(int n) const
			{
				vector_iterator tmp(*this);
				
				tmp -= n;
				return tmp;
			}
			
			int operator-(vector_iterator<const T> const &other) const
			{
				return (_ptr - other.getPointer());
			}
			
			int operator+(vector_iterator<const T> const &other) const
			{
				return (_ptr + other.getPointer());
			}
			
			vector_iterator &operator+=(int n)
			{
				_ptr += n;
				return *this;
			}
			
			vector_iterator &operator-=(int n)
			{
				_ptr -= n;
				return *this;
			}
			
			bool operator>(const vector_iterator<const T> &other) const
			{
				return(_ptr > other.get_internal_pointer());
			}
			
			bool operator<(const vector_iterator<const T> &other) const
			{
				return(_ptr < other.get_internal_pointer());
			}
			
			bool operator>=(const vector_iterator<const T> &other) const
			{
				return(_ptr >= other.get_internal_pointer());
			}
			
			bool operator<=(const vector_iterator<const T> &other) const
			{
				return (_ptr <= other.get_internal_pointer());
			}
			
			reference operator*(void)
			{
				return (*_ptr);
			}
			
			pointer operator->(void)
			{
				return (_ptr);
			}
	};

	class input_iterator_tag
	{};
}

#endif