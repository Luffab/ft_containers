/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatilly <fatilly@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 03:27:07 by fatilly           #+#    #+#             */
/*   Updated: 2022/12/09 03:27:08 by fatilly          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;
		
		protected:
			container_type	_container;
		
		public:
			explicit stack<T, Container>(const Container &container = Container())
			{
				_container = container;
			}
	
			stack<T, Container>( const stack<T>& other ) { *this = other; }
			~stack<T, Container>( void ) { }

			stack		&operator=( const stack<T> &other )
			{
				if (this != &other)
					this->_container = other._container;
				return *this;
			}

			bool		empty(void) const
			{
				return _container.empty();
			}
	
			size_type	size(void) const
			{
				return _container.size();
			}
			
			reference	top(void)
			{
				return _container.back();
			}
	
			const_reference	&top(void) const
			{
				return _container.back();
			}
	
			void push(const value_type &val)
			{
				_container.push_back(val);
			}
	
			void pop(void)
			{
				_container.pop_back();
			}

			friend bool operator==(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{
				return (lhs._container == rhs._container);
			}
		
			friend bool operator!=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{
				return (lhs._container != rhs._container);
			}
		
			friend bool operator<(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{
				return (lhs._container < rhs._container);
			}
		
			friend bool operator<=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{
				return (lhs._container <= rhs._container);
			}
		
			friend bool operator>(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{
				return (lhs._container > rhs._container);
			}
		
			friend bool operator>=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{
				return (lhs._container >= rhs._container);
			}
	};
}

#endif