/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:41:57 by mbadaoui          #+#    #+#             */
/*   Updated: 2023/02/19 14:41:57 by mbadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <memory>
# include "../Utils/pair.hpp"
# include "../Utils/enable_if.hpp"
# include "../Utils/utility.hpp"
# include "../Utils/AVL.hpp"

namespace ft
{
    template<class T, class Category, class tree_t, class node_t>
    class Bidirectional_iterator
    {
        public:
            typedef T           value_type;
            typedef Category    iterator_category;
            typedef ptrdiff_t   difference_type;
            typedef T*          pointer;
            typedef T&          reference;
            typedef tree_t        tree_type;
            typedef node_t        node_type;
        
        private:
            //the address of avl object associated with the iterator.
            tree_type*  _tree;
            //the current location in the tree
            node_type*  node;

        public:
            Bidirectional_iterator(): _tree(), node() { };
            Bidirectional_iterator(node_type* n, tree_type* t): _tree(t), node(n) { };
            Bidirectional_iterator(const Bidirectional_iterator& other) {*this = other;};
            ~Bidirectional_iterator() {};
            Bidirectional_iterator& operator= (const Bidirectional_iterator& other) {
                _tree = other._tree;
                node = other.node;
                return (*this);
            }

            friend bool operator== (const Bidirectional_iterator<T, Category, tree_t, node_t>& lhs, const Bidirectional_iterator<T, Category, tree_t, node_t>& rhs)
            {
                return (lhs.node == rhs.node);
            }
            friend bool operator!= (const Bidirectional_iterator<T, Category, tree_t, node_t>& lhs, const Bidirectional_iterator<T, Category, tree_t, node_t>& rhs)
            {
                return !(lhs.node == rhs.node);
            }

            reference operator* () const {return node->value;};
            pointer operator-> () const {return &(node->value);};

            operator Bidirectional_iterator<const T, iterator_category, const tree_type, const node_type>() const
            {
                return Bidirectional_iterator<const T, iterator_category, const tree_type, const node_type>(node, _tree);
            };

            Bidirectional_iterator& operator++ ()
            {
                node_type*   tmp;
                if (node == NULL)
                {
                    node = _tree->root;
                    while (node != NULL && node->left_child != NULL)
                        node = node->left_child;
                }
                else if (node->right_child != NULL)
                {
                    node = node->right_child;
                    while (node->left_child != NULL)
                        node = node->left_child;
                }
                else
                {
                    tmp = node->parent;
                    while (tmp != NULL && node == tmp->right_child)
                    {
                        node = tmp;
                        tmp = tmp->parent;
                    }
                    node = tmp;
                }
                return *this;
            }

            Bidirectional_iterator operator++ (int)
            {
                Bidirectional_iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            Bidirectional_iterator& operator--()
            {
                node_type*   tmp;
                
                if (node == NULL)
                {
                    node = _tree->root;
                    while (node != NULL && node->right_child != NULL)
                        node = node->right_child;
                }
                else if (node->left_child != NULL)
                {
                    node = node->left_child;
                    while (node->right_child != NULL)
                        node = node->right_child;
                }
                else
                {
                    tmp = node->parent;
                    while (tmp != NULL && node == tmp->left_child)
                    {
                        node = tmp;
                        tmp = tmp->parent;
                    }
                    node = tmp;
                }
                return *this;
            }

            Bidirectional_iterator operator--(int)
            {
                Bidirectional_iterator tmp = *this;
                --(*this);
                return tmp;
            }

            node_type* get_node() const
            {
                return node;
            }
    };

}

#endif
