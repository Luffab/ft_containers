/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatilly <fatilly@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 03:27:22 by fatilly           #+#    #+#             */
/*   Updated: 2022/12/09 03:27:23 by fatilly          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include "iterators/vector_iterator.hpp"
#include "iterators/reverse_iterator.hpp"

#include "utils.hpp"

namespace ft
{
	template< typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		public :
		//type definitions
			typedef T										value_type;
			typedef Allocator								allocator_type;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef ft::vector_iterator<T>					iterator;
			typedef ft::vector_iterator<const T>			const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		
		private :
		//variables
			value_type*		_data;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_allocator;
		
		public :
		//default constructor
			explicit	vector(const allocator_type& alloc = allocator_type()): _data(NULL), _size(0), _capacity(0), _allocator(alloc) {}
		
		//fill constructor
			explicit	vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				_data = NULL;
				_size = n;
				_capacity = n;
				_allocator = alloc;
				_data = _allocator.allocate(n);
				size_type i = 0;
				while (i < _size)
				{
					_allocator.construct(&_data[i], val);
					i++;
				}	
			}
		
		//range constructor
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0)
			{
				size_type n = last - first;
				_data = NULL;
				_size = n;
				_capacity = n;
				_allocator = alloc;
				_data = _allocator.allocate(n);
				n = 0;
				while (first != last)
				{
					_allocator.construct(&_data[n], *first);
					n++;
					first++;
				}
			}
		
		//copy constructor
			vector(const vector& x)
			{
				_allocator.deallocate(_data, _capacity);
				_size = x.size();
				_capacity = x.capacity();
				_allocator = x.get_allocator();
				_data = _allocator.allocate(_capacity);
				size_type i = 0;
				while (i < _size)
				{
					_allocator.construct(&_data[i], x._data[i]);
					i++;
				}
			}
		
		//destructor
			~vector(void)
			{
				clear();
				if (_data)
					_allocator.deallocate(_data, _capacity);
			}
		
		//assignment operator
			vector& operator=(const vector& other)
			{
				if(*this == other)
					return *this;
				clear();
				_allocator.deallocate(_data, _capacity);
				_size = other.size();
				_capacity = other.capacity();
				_allocator = other.get_allocator();
				_data = _allocator.allocate(_capacity);
				size_type i = 0;
				while (i < _size)
				{
					_allocator.construct(&_data[i], other._data[i]);
					i++;
				}
				return *this;
			}
		
		/////////////////////////
		//					   //
		//      ITERATORS      //
		//					   //
		/////////////////////////
			iterator		begin() {return (iterator(_data));}
			iterator		end() {return (iterator(&_data[_size]));}
			const_iterator	begin() const {return (const_iterator(_data));}
			const_iterator	end() const {return (const_iterator(&_data[_size]));}
			reverse_iterator rbegin() {return (reverse_iterator(end()));}
			reverse_iterator rend() {return (reverse_iterator(begin()));}
			const_reverse_iterator rbegin() const {return (const_reverse_iterator(end()));}
			const_reverse_iterator rend() const {return (const_reverse_iterator(begin()));}
		
		////////////////////////
		//					  //
		//      CAPACITY      //
		//					  //
		////////////////////////
			size_type	size() const {return _size;}
			size_type	max_size() const {return _allocator.max_size();}
			
			void resize (size_type n, value_type val = value_type())
			{
				if (n < _size)
				{
					size_type i = n;
					while (i < _size)
					{
						_allocator.destroy(&_data[i]);
						i++;
					}
					_size = n;
				}
				else if (n > _size)
				{
					size_type i = _size;
					if (n > _capacity)
					{
						if (_capacity == 0)
							_capacity = 1;
						while (_capacity < n)
							_capacity *= 2;
						reallocVector(_capacity);
					}
					while (i < n)
					{
						_allocator.construct(&_data[_size], val);
						_size += 1;
						i++;
					}
				}
			}
			
			size_type	capacity() const {return _capacity;}
			
			bool		empty() const
			{
				if (_size == 0)
					return true;
				else
					return false;
			}

			void		reserve(size_type n)
			{
				if (n > _capacity)
					reallocVector(n);
			}
			
		//////////////////////////////
		//							//
		//      ELEMENT ACCESS      //
		//							//
		//////////////////////////////
			reference		operator[] (size_type n) {return _data[n];}
			const_reference	operator[] (size_type n) const {return _data[n];};
			
			reference at (size_type n)
			{
				if (n >= _size)
					throw (std::out_of_range("vector"));
				return _data[n];
			}
		
			const_reference at (size_type n) const
			{
				if (n >= _size)
					throw (std::out_of_range("vector"));
				return _data[n];
			}
			
			reference		front(){return _data[0];}
			const_reference	front() const {return _data[0];}
			reference		back() {return _data[_size - 1];}
			const_reference	back() const {return _data[_size - 1];}
		
		/////////////////////////
		//					   //
		//      MODIFIERS      //
		//					   //
		/////////////////////////
			//fill assign
			void assign(size_type n, const value_type& val)
			{
				size_type i = 0;
				while (i < _size)
				{
					_allocator.destroy(&_data[i]);
					i++;
				}
				if (n > _capacity)
					reserve(n);
				i = 0;
				while (i < n)
				{
					_allocator.construct(&_data[i], val);
					i++;
				}
				_size = n;
			}

			//range assign
			template <typename InputIterator>	typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type	assign(InputIterator first, InputIterator last)
			{
				size_type i = 0;
				size_type n = last - first;
				while (i < _size)
				{
					_allocator.destroy(&_data[i]);
					i++;
				}
				if (n > _capacity)
					reserve(n);
				i = 0;
				while (first != last)
				{
					_allocator.construct(&_data[i], *first);
					i++;
					first++;
				}
				_size = n;
			}
			
			void	push_back(const value_type& val)
			{
				if (_capacity == 0)
				{
					_capacity += 1;
					_data = _allocator.allocate(1);
				}
				else if (_capacity == _size)
					reallocVector(_capacity *2);
				_allocator.construct(&_data[_size], val);
				_size += 1;
			}
		
			void	pop_back()
			{
				_allocator.destroy(&_data[_size - 1]);
				_size -= 1;
			}
			
			//single value insert
			iterator	insert(iterator position, const value_type& val)
			{
				iterator it = begin();
				value_type* new_data;
				size_type new_capacity = _capacity;
				
				if (_size >= _capacity)
				{
					new_data = _allocator.allocate(new_capacity * 2);
					new_capacity = new_capacity * 2;
				}
				else
					new_data = _allocator.allocate(new_capacity);
				size_type i = 0;	
				while (it != position)
				{
					_allocator.construct(&new_data[i], _data[i]);
					_allocator.destroy(&_data[i]);
					i++;
					it++;
				}
				size_type insert_index = i;
				_allocator.construct(&new_data[i], val);
				_size += 1;
				i++;
				while (i < _size)
				{
					_allocator.construct(&new_data[i], _data[i - 1]);
					_allocator.destroy(&_data[i - 1]);
					i++;
				}
				_allocator.deallocate(&_data[0], _capacity);
				_capacity = new_capacity;
				_data = new_data;
				iterator return_it(&new_data[insert_index]);
				return return_it;
			}
			
			//fill insert
			void	insert(iterator position, size_type n, const value_type& val)
			{
				iterator it = begin();
				value_type* new_data;
				size_type new_capacity = _capacity;
				
				if (new_capacity == 0)
					new_capacity = 1;
				while (new_capacity < (_size + n))
					new_capacity *= 2;
				new_data = _allocator.allocate(new_capacity);
				size_type i = 0;
				while (it != position)
				{
					_allocator.construct(&new_data[i], _data[i]);
					_allocator.destroy(&_data[i]);
					i++;
					it++;
				}
				size_type j = 0;
				size_type k = i;
				while (j < n)
				{
					_allocator.construct(&new_data[i], val);
					_size += 1;
					i++;
					j++;
				}
				while (i < _size)
				{
					_allocator.construct(&new_data[i], _data[k]);
					_allocator.destroy(&_data[k]);
					i++;
					k++;
				}
				_allocator.deallocate(&_data[0], _capacity);
				_data = new_data;
				_capacity = new_capacity;
			}

			//range insert
			template <typename InputIterator>	typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type	insert(iterator position, InputIterator first, InputIterator last)
			{
				iterator it = begin();
				size_type i = 0;
				size_type n = last - first;
				value_type* new_data;
				size_type new_capacity = _capacity;
				
				while (new_capacity < (_size + n))
					new_capacity *= 2;
				new_data = _allocator.allocate(new_capacity);
				while (it != position)
				{
					_allocator.construct(&new_data[i], _data[i]);
					_allocator.destroy(&_data[i]);
					i++;
					it++;
				}
				size_type j = i;
				while (first != last)
				{
					_allocator.construct(&new_data[i], *first);
					i++;
					first++;
				}
				while (j < _size)
				{
					_allocator.construct(&new_data[i], _data[j]);
					_allocator.destroy(&_data[j]);
					i++;
					j++;
				}
				_size = _size + n;
				_allocator.deallocate(&_data[0], _capacity);
				_data = new_data;
				_capacity = new_capacity;
			}
			
			//single value erase
			iterator	erase(iterator position)
			{
				iterator it = begin();
				value_type* new_data;
				new_data = _allocator.allocate(_capacity);
				size_type i = 0;
				
				while (it != position)
				{
					_allocator.construct(&new_data[i], _data[i]);
					_allocator.destroy(&_data[i]);
					i++;
					it++;
				}
				size_type erase_index = i;
				_allocator.destroy(&_data[i]);	
				_size -= 1;
				while (i < _size)
				{
					_allocator.construct(&new_data[i], _data[i + 1]);
					_allocator.destroy(&_data[i + 1]);
					i++;
				}
				_allocator.deallocate(&_data[0], _capacity);
				_data = new_data;
				iterator return_it(&new_data[erase_index]);
				return return_it;
			}
			
			//range erase
			iterator	erase(iterator first, iterator last)
			{
				iterator it = begin();
				value_type* new_data;
				new_data = _allocator.allocate(_capacity);
				size_type i = 0;
				
				while (it != first)
				{
					_allocator.construct(&new_data[i], _data[i]);
					_allocator.destroy(&_data[i]);
					i++;
					it++;
				}
				size_type j = i;
				size_type erase_index = j;
				while (it != last)
				{
					_allocator.destroy(&_data[i]);
					i++;
					it++;
					_size -= 1;
				}
				while (j < _size)
				{
					_allocator.construct(&new_data[j], _data[i]);
					_allocator.destroy(&_data[i]);
					i++;
					j++;
				}
				_allocator.deallocate(&_data[0], _capacity);
				_data = new_data;
				iterator return_it(&new_data[erase_index]);
				return return_it;
			}
			
			void	swap(vector& x)
			{
				value_type* 	tmp_data = _data;
				size_type		tmp_size = _size;
				size_type		tmp_capacity = _capacity;
				allocator_type	tmp_allocator = _allocator;

				_data = x._data;
				_size = x._size;
				_capacity = x._capacity;
				_allocator = x._allocator;

				x._data = tmp_data;
				x._size = tmp_size;
				x._capacity = tmp_capacity;
				x._allocator = tmp_allocator;
			}
			
			void	clear()
			{
				size_type i = 0;
				while (i < _size)
				{
					_allocator.destroy(&_data[i]);
					i++;
				}
				_size = 0;
			}
		
		/////////////////////////
		//					   //
		//      Allocator      //
		//					   //
		/////////////////////////
			allocator_type	get_allocator() const {return _allocator;}
		
		private :
			void	reallocVector(size_type new_capacity)
			{
				value_type* new_data;
				
				new_data = _allocator.allocate(new_capacity);
				size_type i = 0;
				while (i < _size)
				{
					_allocator.construct(&new_data[i], _data[i]);
					_allocator.destroy(&_data[i]);
					i++;
				}
				_allocator.deallocate(&_data[0], _capacity);
				_capacity = new_capacity;
				_data = new_data;
			}
	};
	
	/////////////////////////////////////////////
	//					   					   //
	//      NON-MEMBER FUNCTION OVERLOADS      //
	//					   					   //
	/////////////////////////////////////////////
		template <class T, class Alloc>
		bool operator==(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
		{
			typename ft::vector<T>::const_iterator	lit;
			typename ft::vector<T>::const_iterator	rit;
		
			lit = lhs.begin();
			rit = rhs.begin();
			if (lhs.size() != rhs.size())
				return false;
			while (lit != lhs.end())
			{
				if (*lit != *rit)
					return false;
				lit++;
				rit++;
			}
			return true;
		}
		
		template <class T, class Alloc>
		bool operator!=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
		{
			return !(lhs == rhs);
		}
		
		template <class T, class Alloc>
		bool operator<(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
		{
			typename ft::vector<T>::const_iterator lit;
			typename ft::vector<T>::const_iterator rit;
	
			lit = lhs.begin();
			rit = rhs.begin();
		
			while (lit != lhs.end())
			{
				if (rit == rhs.end() || (*lit) > (*rit))
					return false;
				else if ((*lit) < (*rit))
					return true;
				lit++;
				rit++;
			}
			return rit != rhs.end();
		}
		
		template <class T, class Alloc>
		bool operator<=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
		{
			return !(rhs < lhs);
		}
		
		template <class T, class Alloc>
		bool operator>(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
		{
			return (rhs < lhs);
		}
		
		template <class T, class Alloc>
		bool operator>=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
		{
			return !(lhs < rhs);
		}
		
		template <class T, class Alloc>
		void swap (vector<T,Alloc> &x, vector<T,Alloc> &y)
		{
			x.swap(y);
		}
}


#endif