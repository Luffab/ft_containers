/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatilly <fatilly@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 03:27:16 by fatilly           #+#    #+#             */
/*   Updated: 2022/12/09 03:27:17 by fatilly          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include <cstddef>
#include <iostream>

namespace ft
{
    template <class Iterator>
    class iterator_traits
	{
	public:
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };
	
    template <class T>
    class iterator_traits<T *>
	{
	public:
        typedef	ptrdiff_t difference_type;
        typedef	T value_type;
        typedef	T* pointer;
        typedef	T& reference;
        typedef	std::random_access_iterator_tag iterator_category;
    };
	
    template <class T>
    class iterator_traits<const T *>
    {
	public:
        typedef	ptrdiff_t difference_type;
        typedef	T value_type;
        typedef	const T *pointer;
        typedef	const T &reference;
        typedef	std::random_access_iterator_tag iterator_category;
    };

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	};

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	};

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	};

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate p)
	{
		while (first1 != last1)
		{
			if (!p(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	};
	
	template <typename T>
	struct is_integral
	{
		static const bool value = false;
	};
	
	template <>
	struct is_integral<int>
	{
		static const bool value = true;
	};

	template <bool Cond, class T = void>
	struct enable_if
	{
	};
	
	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};
};

#endif