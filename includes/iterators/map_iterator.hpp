/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatilly <fatilly@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 03:22:27 by fatilly           #+#    #+#             */
/*   Updated: 2022/12/09 03:28:02 by fatilly          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../utils.hpp"

namespace ft
{
	template <typename T, typename nodePtr>
	class mapiterator
	{
		public:
			typedef typename iterator_traits<T>::difference_type  	difference_type;
			typedef typename iterator_traits<T>::value_type  		value_type;
			typedef typename iterator_traits<T>::pointer  			pointer;
			typedef typename iterator_traits<T>::reference			reference;
			typedef std::bidirectional_iterator_tag					iterator_category;

			nodePtr	node;
		public:
			mapiterator() : node(NULL) {}
			explicit mapiterator(nodePtr ptr) : node(ptr) {}
			template <typename Iter, typename nodeptr>
			mapiterator (const mapiterator<Iter, nodeptr>& it) : node(it.node) {}
			nodePtr base() const
			{
				return (node);
			}
			reference operator*() const
			{
				return (node->data);
			}
			pointer operator->() const
			{
				return (&(node->data));
			}
			mapiterator& operator++()
			{
				node = incr();
				return (*this);
			}
			mapiterator operator++(int)
			{
				mapiterator tmp(*this);
				++(*this);
				return (tmp);
			}
			mapiterator& operator--()
			{
				node = decr();
				return (*this);
			}
			mapiterator operator--(int)
			{
				mapiterator tmp(*this);
				--(*this);
				return (tmp);
			}

			bool operator== (const mapiterator& lhs)
			{
				return (base() == lhs.base());
			}

			bool operator!= (const mapiterator& lhs)
			{
				return (!(base() == lhs.base()));
			}

		private:
			nodePtr	incr()
			{
				nodePtr	parent = node->parent;
				nodePtr	tmp = node;
				if (tmp->right)
				{
					tmp = tmp->right;
					while (tmp->left)
						tmp = tmp->left;
					return tmp;
				}
				else
				{
					while (parent && tmp == parent->right)
					{
						tmp = parent;
						parent = tmp->parent;
					}
					return (parent);
				}
			}
			nodePtr	decr()
			{
				nodePtr	parent = node->parent;
				nodePtr	tmp = node;
				if (tmp->left)
				{
					tmp = tmp->left;
					while (tmp->right)
						tmp = tmp->right;
					return tmp;
				}
				else
				{
					while (parent && tmp == parent->left)
					{
						tmp = parent;
						parent = tmp->parent;
					}
					return (parent);
				}
			}
	};
}