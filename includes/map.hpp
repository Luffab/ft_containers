/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatilly <fatilly@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 03:26:37 by fatilly           #+#    #+#             */
/*   Updated: 2022/12/09 03:26:40 by fatilly          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "iterators/map_iterator.hpp"
#include "pair.hpp"
#include "node.hpp"
#include "iterators/reverse_iterator.hpp"

#include <memory>

namespace ft
{
	template <typename K, typename T, typename Compare = std::less<K>, typename Alloc = std::allocator<ft::pair<const K,T> > >
	class map
	{
		public:
			typedef	K													key_type;
			typedef T													mapped_type;
			typedef	ft::pair<const key_type, mapped_type>				value_type;
			typedef Compare												key_compare;
			typedef Alloc												allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef AVLTree<value_type, key_compare, allocator_type>	tree;
			typedef typename tree::nodePtr								nodePtr;
			typedef	ft::mapiterator<pointer, nodePtr>					iterator;
			typedef	ft::mapiterator<const_pointer, nodePtr>				const_iterator;
			typedef	ft::reverse_iterator<iterator>						reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>				const_reverse_iterator;
			typedef	typename allocator_type::difference_type 			difference_type;
			typedef	typename allocator_type::size_type 					size_type;

			class	value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
					key_compare comp;
					value_compare(key_compare c) : comp(c) {}
				public:
					bool operator()(const value_type& lhs, const value_type& rhs) const
					{
						return comp(lhs.first, rhs.first);
					}
			};

		private:
			tree			root;
			key_compare		cmp;
			allocator_type	tree_alloc;

		public:
			explicit	map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : root(), cmp(comp), tree_alloc(alloc) {}
			template <typename InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : root(), cmp(comp), tree_alloc(alloc)
			{
				while (first != last)
				{
					insert(*first);
					first++;
				}
			}
			map(const map& x) : root(), cmp(x.cmp), tree_alloc(x.tree_alloc)
			{
				*this = x;
			}
			map& operator= (const map& x)
			{
				if (this == &x)
					return *this;
				root.clear();
				if (x.size())
					insert(x.begin(), x.end());
				tree_alloc = x.tree_alloc;
				cmp = x.cmp;
				return (*this);
			}
			mapped_type& operator[] (const key_type& k)
			{
				value_type data = ft::make_pair(k, mapped_type());
				nodePtr	node = root.findd(data);
				if (!node || node == root.getEnd())
				{
					root.insert(data);
					node = root.findd(data);
				}
				return (node->data.second);
			}
			~map() {}

/*
			--------------------------
			|                        |
			|   ITERATOR FUNCTIONS   |
			|                        |
			--------------------------
*/

			iterator	begin()
			{
				return (iterator(root.getMin()));
			}
			const_iterator	begin() const
			{
				return (const_iterator(root.getMin()));
			}
			iterator	end()
			{
				return (iterator(root.getEnd()));
			}
			const_iterator	end() const
			{
				return (const_iterator(root.getEnd()));
			}
			reverse_iterator	rbegin()
			{
				return (reverse_iterator(this->end()));
			}
			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator(this->end()));
			}
			reverse_iterator	rend()
			{
				return (reverse_iterator(this->begin()));
			}
			const_reverse_iterator	rend() const
			{
				return (const_reverse_iterator(this->begin()));
			}

/*
			-------------------------
			|                       |
			|   MEMBERS FUNCTIONS   |
			|                       |
			-------------------------
*/

			allocator_type	get_allocator() const
			{
				return (this->tree_alloc);
			}
			size_type	size() const
			{
				return (root.size());
			}
			bool	empty() const
			{
				return (size() == 0);
			}
			size_type	max_size() const
			{
				return (root.max_size());
			}
			void	clear()
			{
				root.clear();
			}

			pair<iterator, bool>	insert(const value_type& val)
			{
				nodePtr	node = root.findd(val);
				bool	notInserted = false;
				if (!node || node == root.getEnd())
				{
					root.insert(val);
					node = root.findd(val);
					notInserted = true;
				}
				return (ft::make_pair(iterator(node), notInserted));
			}
			iterator	insert(iterator position, const value_type& val)
			{
				static_cast<void>(position);
				nodePtr	node = root.findd(val);
				if (!node || node == root.getEnd())
				{
					root.insert(val);
					node = root.findd(val);
				}
				return (iterator(node));
			}
			template <typename InputIterator>
			void	insert(InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					insert(*first);
					first++;
				}
			}
			void	erase(iterator position)
			{
				nodePtr node = position.base();
				if (node)
					root.erase(*position);
			}
			size_type	erase(const key_type& k)
			{
				nodePtr node = root.findd(ft::make_pair(k, mapped_type()));
				if (!node || node == root.getEnd())
					return (0);
				root.erase(node->data);
				return (1);
			}
			void	erase (iterator first, iterator last)
			{
				iterator tmp;
				while (first != last)
				{
					tmp = first++;
					erase(tmp);
					if (first == iterator(root.getEnd()))
						return ;
				}
			}
			void	swap (map& x)
			{
				allocator_type	alloc = x.get_allocator();
				key_compare		cmp = x.cmp;
				x.tree_alloc = this->get_allocator();
				x.cmp = this->cmp;
				this->tree_alloc = alloc;
				this->cmp = cmp;
				root.swap(x.root);
			}
			iterator	find (const key_type& k)
			{
				nodePtr	node = root.findd(ft::make_pair(k, mapped_type()));
				return (iterator(node));
			}
			const_iterator	find (const key_type& k) const
			{
				nodePtr	node = root.findd(ft::make_pair(k, mapped_type()));
				return (const_iterator(node));
			}
			size_type	count (const key_type& k) const
			{
				const_iterator beg = begin();
				const_iterator endd = end();

				while (beg != endd)
				{
					if ((*(beg++)).first == k)
						return (1);
				}
				return (0);
			}
			key_compare	key_comp() const
			{
				return (this->cmp);
			}
			value_compare	value_comp() const
			{
				return (value_compare(cmp));
			}
			iterator	lower_bound (const key_type& k)
			{
				iterator it = find(k);
				if (it.base() == root.getEnd())
					it = iterator(root.lowerBound(ft::make_pair(k, mapped_type())));
				return (it);
			}
			const_iterator	lower_bound (const key_type& k) const
			{
				const_iterator cit = find(k);
				if (cit.base() == root.getEnd())
					cit = const_iterator(root.lowerBound(ft::make_pair(k, mapped_type())));
				return (cit);
			}
			iterator	upper_bound (const key_type& k)
			{
				iterator it = find(k);
				if (it.base() != root.getEnd())
					++it;
				else
					it = iterator(root.upperBound(ft::make_pair(k, mapped_type())));
				return (it);
			}
			const_iterator	upper_bound (const key_type& k) const
			{
				const_iterator cit = find(k);
				if (cit.base() != root.getEnd())
					++cit;
				else
					cit = const_iterator(root.upperBound(ft::make_pair(k, mapped_type())));
				return (cit);
			}
			pair<const_iterator,const_iterator>	equal_range (const key_type& k) const
			{
				return (ft::make_pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k)));
			}
			pair<iterator,iterator>	equal_range (const key_type& k)
			{
				return (ft::make_pair<iterator,iterator>(lower_bound(k), upper_bound(k)));
			}
	};

/*
	-----------------------
	|                     |
	|   MAP COMPARISONS   |
	|                     |
	-----------------------
*/

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		typename ft::map<Key, T>::iterator lit;
		typename ft::map<Key, T>::iterator rit;

		lit = lhs.begin();
		rit = rhs.begin();
		if (lhs.size() != rhs.size())
			return (false);
		while (lit != lhs.end())
		{
			if (lit->second != rit->second)
				return (false);
			lit++;
			rit++;
		}
		return (true);
	}
	
	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return (!(rhs == lhs));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		typename ft::map<Key, T>::iterator lit;
        typename ft::map<Key, T>::iterator rit;

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

	template<class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool	operator>(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template<class Key, class T, class Compare, class Alloc>
	void	swap(ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
