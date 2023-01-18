/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatilly <fatilly@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 03:26:48 by fatilly           #+#    #+#             */
/*   Updated: 2022/12/09 03:26:50 by fatilly          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

#include "pair.hpp"

namespace ft
{
	
/*
	-------------------
	|                 |
	|   NODE STRUCT   |
	|                 |
	-------------------
*/
	template <class T>
	struct Node 
	{
		T		data;
		Node	*parent;
		Node	*left;
		Node	*right;
		int		balanceFactor;
		int		height;
		
		Node() : parent(NULL), left(NULL), right(NULL) {}
		Node(const T& data) : data(data){}
		Node(const T& data, const int height) : data(data), parent(NULL), left(NULL), right(NULL), balanceFactor(0), height(height) {}
	};

/*
	---------------------
	|                   |
	|   AVLTree class   |
	|                   |
	---------------------
*/

	template <class T, class Compare, class Alloc>
	class AVLTree
	{
		public:
			typedef T																value_type;
			typedef Compare															key_compare;
			typedef Node<T>*														nodePtr;
			typedef typename Alloc::template rebind<Node<T> >::other				allocator_type;
			typedef	typename allocator_type::size_type 								size_type;
			typedef	typename allocator_type::difference_type 			difference_type;
			
		private:
			nodePtr			root;
			nodePtr			end;
			allocator_type	allocmap;
			key_compare		cmp;
			size_type		mapsize;
		
		public:
			AVLTree(const allocator_type& alloc = allocator_type(), const key_compare& cmp = key_compare()) : root(NULL), end(NULL), allocmap(alloc), cmp(cmp), mapsize(0)
			{
				end = allocmap.allocate(1);
			}
			~AVLTree()
			{
				clear();
				allocmap.deallocate(end, 1);
				end = NULL;
			}
			size_type size() const
			{
				return mapsize;
			}
			size_type max_size() const
			{
				return allocmap.max_size();
			}
			allocator_type get_allocator() const
			{
				return (this->allocmap);
			}
			nodePtr	getEnd() const
			{
				return (this->end);
			}
			nodePtr	getMin(nodePtr node = NULL) const
			{
				if (!node)
					node = root;
				while (node && node->left)
					node = node->left;
				return node;
			}
			nodePtr	getMax(nodePtr node = NULL)
			{
				if (!node)
					node = root;
				while (node && node->right)
					node = node->right;
				return node;
			}
			nodePtr	lowerBound(const value_type& data)
			{
				nodePtr node = getMin();
                while (node != end)
                {
                    if (!cmp(node->data.first, data.first))
                        return (node);
                    node = successor(node);
                }
                return (end);
			}
			nodePtr	upperBound(const value_type& data)
			{
				nodePtr node = getMin();
                while (node != end)
                {
                    if (cmp(data.first, node->data.first))
                        return (node);
                    node = successor(node);
                }
                return (end);
			}
			void	swap(AVLTree& tree)
			{
				nodePtr			tmp_root = root;
				nodePtr			tmp_end = end;
				allocator_type	tmp_alloc = allocmap;
				key_compare		tmp_cmp = cmp;
				size_type		tmp_size = mapsize;

				root = tree.root;
				end = tree.end;
				allocmap = tree.allocmap;
				cmp = tree.cmp;
				mapsize = tree.mapsize;
				
				tree.root = tmp_root;
				tree.end = tmp_end;
				tree.allocmap = tmp_alloc;
				tree.cmp = tmp_cmp;
				tree.mapsize = tmp_size;
			}
			void	clear()
			{
				clear(root);
				mapsize = 0;
			}
			nodePtr	findd(const value_type& data)
			{
				return find(data, root);
			}
			void	insert(const value_type data)
			{
				insert(data, root, end);
				end->left = root;
				root->parent = end;
			}
			void	erase(const value_type& data)
			{
				erase(root, data);
				end->left = root;
				if (root)
					root->parent = end;
			}
		private:
			void	eraseHelper(nodePtr &node, nodePtr& parent)
			{
				nodePtr tmp;
				if (node->right)
					tmp = node->right;
				else
					tmp = node->left;
				if (tmp)
					tmp->parent = parent;
				allocmap.deallocate(node, 1);
				node = tmp;
				mapsize--;
			}
			void	erase (nodePtr &node, const value_type& data)
			{
				if (!node)
					return ;
				if (node->data.first == data.first)
				{
					if (!node->left || !node->right)
					{
						eraseHelper(node, node->parent);
						return ;
					}
					else
					{
						if (node->left->height > node->right->height)
						{
							value_type value(getMax(node->left)->data);
							allocmap.construct(node, value);
							erase(node->left, value);
						}
						else
						{
							value_type value(getMin(node->right)->data);
							allocmap.construct(node, value);
							erase(node->right, value);
						}
					}
				}
				else if (cmp(data.first, node->data.first))
					erase(node->left, data);
				else
					erase(node->right, data);
				update(node);
				balance(node);
			}
			void	insert(const value_type& data, nodePtr &node, nodePtr& parent)
			{
				if (!node)
				{
					node = allocmap.allocate(1);
					allocmap.construct(node, data, 0);
					node->parent = parent;
					mapsize++;
					return ;
				}
				if (cmp(data.first, node->data.first))
					insert(data, node->left, node);
				else
					insert(data, node->right, node);
				update(node);
				balance(node);
			}
			nodePtr	find(const value_type& data, nodePtr& node)
			{
				if (!node || node == end)
					return (end);
				if (data.first == node->data.first)
					return (node);
				if (cmp(data.first, node->data.first))
					return (find(data, node->left));
				return (find(data, node->right));
			}
			nodePtr	successor(nodePtr node)
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
			void	clear(nodePtr &node)
			{
				if (node)
				{
					clear(node->left);
					clear(node->right);
					allocmap.deallocate(node, 1);
					node = NULL;
				}
			}
			void	update(nodePtr node)
			{
				int	leftNodeHeight = -1;
				int	rightNodeHeight = -1;
				
				if (node->left)
					leftNodeHeight = node->left->height;
				if (node->right)
					rightNodeHeight = node->right->height;
				int diff;
				if (leftNodeHeight > rightNodeHeight)
					diff = leftNodeHeight;
				else
					diff = rightNodeHeight;
				node->height = 1 + diff;
				node->balanceFactor = rightNodeHeight - leftNodeHeight;
			}
			void	balance(nodePtr &node)
			{
				if (node->balanceFactor < -1)
				{
					if (node->left->balanceFactor <= 0)
						leftLeftCase(node);
					else
						leftRightCase(node);
				}
				else if (node->balanceFactor > 1)
				{
					if (node->right->balanceFactor >= 0)
						rightRightCase(node);
					else
						rightLeftCase(node);
				}
			}
			void	leftRotation(nodePtr &node)
			{
				nodePtr	parent = node->parent;
				nodePtr	root = node->right;
				node->right = root->left;
				if (node->right)
					node->right->parent = node;
				node->parent = root;
				root->left = node;
				root->parent = parent;
				node = root;
				update(node->left);
				update(node);
			}		
			void	rightRotation(nodePtr &node)
			{
				nodePtr	parent = node->parent;
				nodePtr	root = node->left;
				node->left = root->right;
				if (node->left)
					node->left->parent = node;
				node->parent = root;
				root->right = node;
				root->parent = parent;
				node = root;
				update(node->right);
				update(node);
			}		
			void	leftLeftCase(nodePtr &node)
			{
				rightRotation(node);
			}
			void	leftRightCase(nodePtr &node)
			{
				leftRotation(node->left);
				rightRotation(node);
			}
			void	rightRightCase(nodePtr &node)
			{
				leftRotation(node);
				
			}
			void	rightLeftCase(nodePtr &node)
			{
				rightRotation(node->right);
				leftRotation(node);
			}
	};
}

#endif