/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatilly <fatilly@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 03:26:59 by fatilly           #+#    #+#             */
/*   Updated: 2022/12/09 03:27:00 by fatilly          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template <typename K, typename T>
	struct pair
	{
		typedef	K		first_type;
		typedef	T		second_type;

		first_type		first;
		second_type		second;

		pair() : first(), second() {}
		template<typename U, typename V>
		pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
		pair (const first_type& a, const second_type& b) : first(a), second(b) {}
		pair& operator= (const pair& pr)
		{
			if (this == &pr)
				return (*this);
			first = pr.first;
			second = pr.second;
			return (*this);
		}
	};

	template <typename K, typename T>
	bool operator== (const pair<K,T>& lhs, const pair<K,T>& rhs)
	{ 
		return ((lhs.first == rhs.first) && (lhs.second == rhs.second)); 
	}

	template <typename K, typename T>
	bool operator!= (const pair<K,T>& lhs, const pair<K,T>& rhs)
	{ 
		return (!(lhs == rhs)); 
	}

	template <typename K, typename T>
	bool operator<  (const pair<K,T>& lhs, const pair<K,T>& rhs)
	{ 
		return ((lhs.first < rhs.first) || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); 
	}

	template <typename K, typename T>
	bool operator<= (const pair<K,T>& lhs, const pair<K,T>& rhs)
	{ 
		return (!(rhs < lhs)); 
	}

	template <typename K, typename T>
	bool operator>  (const pair<K,T>& lhs, const pair<K,T>& rhs)
	{ 
		return (rhs < lhs); 
	}

	template <typename K, typename T>
	bool operator>= (const pair<K,T>& lhs, const pair<K,T>& rhs)
	{ 
		return (!(lhs < rhs)); 
	}

	template <typename K, typename T>
	pair<K,T> make_pair (K x, T y)
	{
		return (pair<K, T>(x, y));
	}
}

#endif