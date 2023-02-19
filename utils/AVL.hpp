/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbadaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:42:21 by mbadaoui          #+#    #+#             */
/*   Updated: 2023/02/19 14:42:22 by mbadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_HPP
# define AVL_HPP

# include "utility.hpp"
# include "enable_if.hpp"
# include "pair.hpp"
# include <memory>
# include <functional>
# include <algorithm>

namespace ft
{
    #define SPACE 10

    template<class Pair>
    struct AVL
    {
        Pair value;
        AVL* parent;
        AVL* left_child;
        AVL* right_child;
        int height;
        int balanced_factor;

        AVL(): Pair(), parent(NULL), left_child(NULL), right_child(NULL), height(0), balanced_factor(0) {};
        ~AVL() {};
        bool operator== (const AVL& rhs) const{
			return (value == rhs.value && balanced_factor == rhs.balanced_factor && height == rhs.height
				&& left_child == rhs.left_child && right_child == rhs.right_child
					&& parent == rhs.parent);
		}
        AVL (Pair& other): value(other) {};
    };

    template<class T, class Compare= std::less<typename T::first_type>, class Allocator= std::allocator<T> >
    class avl_tree
    {
        public:
            typedef AVL<T>                                                  node_type;
            typedef typename T::first_type                                  key_type;
            typedef typename T::second_type                                 map_value;
            typedef typename Allocator::template rebind<node_type>::other            Allocator_node;

            node_type*  root;
            int         node_number;
        
        private:
            Compare         _compare;
            Allocator_node  _allocator_node;
            Allocator       _allocator;
        
        public:

            avl_tree(): root(NULL), node_number(0) {};
            ~avl_tree() { this->clear(); };
            avl_tree( const avl_tree& other) { *this = other; };
            avl_tree& operator= (const avl_tree& other) {
                _compare = other._compare;
                _allocator = other._allocator;
                _allocator_node = other._allocator_node;
                insert_all_nodes(other.root);
                return (*this);
            }

            // possibility to insert a tree in a tree
            //this function insert all the nodes in the root
            void insert_all_nodes(node_type *node)
            {
                if (node != NULL)
                {
                    insertion(node->value);
                    if (node->left_child != NULL)
                        insert_all_nodes(node->left_child);
                    if (node->right_child != NULL)
                        insert_all_nodes(node->right_child);
                }
            }

            // this function takes the values of a type and insert it the root
            node_type* insertion(T value)
            {
                if (!available_in_tree(root, value))
                {
                    root = insertion(root, value);
                    node_number += 1;
                    return this->find_node(value.first);
                }
                return this->find_node(value.first);
            }

            //return the max value in the tree map
            T max(node_type* node) const
            {
                while (node->right_child != NULL)
                    node = node->right_child;
                return node->value;
            }

            //return the min value in the tree map
            T min(node_type* node) const
            {
                while (node->left_child != NULL)
                    node = node->left_child;
                return node->value;
            }

            //this function checks if a value of type T does exist in the tree or not
            bool available_in_tree(T value) const
            {
                return available_in_tree(root, value);
            }

            //this function checks if a value of type key_value does exist in the tree or not
            bool available_in_tree(key_type value) const
            {
                return available_in_tree(root, value);
            }

            //get the height of a tree root, which is the number of edges between the root and the last leaf
            int height() const
            {
                if (root == NULL)
                    return 0;
                return root->height;
            }

            //check if the tree is empty or not
            bool empty() const
            {
                return node_number == 0;
            }

            //return number of nodes in the tree
            int size_tree() const
            {
                return node_number;
            }

            //clear the tree for allocation and value
            void clear()
            {
                node_number = 0;
                clear(root);
                root = NULL;
            }

            size_t   max_size() const
            {
                return std::min<size_t>(_allocator_node.max_size(), _allocator.max_size());
            }

            //return the value where there is the value
            map_value* searching(key_type& value)
            {
                return searching(root, value);
            }

            //return the node where there is the value
            node_type* find_node(T value) const
            {
                return find_node(root, value.first);
            }

            node_type* find_node(key_type value) const
            {
                return find_node(root, value);
            }

            int deletion(key_type value)
            {
                if (available_in_tree(root, value))
                {
                    root = deletion(root, value);
                    node_number -= 1;
                    return 1;
                }
                return 0;
            }

            void    swap( avl_tree &avl )
            {
                std::swap(_allocator, avl._allocator);
                std::swap(_allocator_node, avl._allocator_node);
                std::swap(_compare, avl._compare);
                std::swap(root, avl.root);
                std::swap(node_number, avl.node_number);
            }

            void print2D(node_type* node, int space)
            {
                if (node == NULL)
                  return;
                space += SPACE;
                print2D(node->right_child, space);
                std::cout << std::endl;
                for (int i = SPACE; i < space; i++)
                  std::cout << " ";
                std::cout << node->value.first << std::endl;
                print2D(node->left_child, space);
            }


        private:

            //private function of clear to use private attribe root to clear it
            void clear(node_type* node)
            {
                if (node == NULL)
                    return ;
                clear(node->left_child);
                clear(node->right_child);
                _allocator.destroy(&(node->value));
                _allocator_node.deallocate(node, 1);
            }

            //this private function checks if a value of type T does exist in the tree or not
            bool available_in_tree(node_type* node, T value) const
            {
                if (node == NULL)
                    return false;
                if (node->value.first == value.first)
                    return true;
                int check = _compare(value.first, node->value.first);
                if (check == true)
                    return available_in_tree(node->left_child, value);
                if (check == false)
                    return available_in_tree(node->right_child, value);
                return true;
            }

            //this function checks if a value of type key_type does exist in the tree or not
            bool available_in_tree(node_type* node, key_type value) const
            {
                if (node == NULL)
                    return false;
                if (node->value.first == value)
                    return true;
                int check = _compare(value, node->value.first);
                if (check == true)
                    return available_in_tree(node->left_child, value);
                if (check == false)
                    return available_in_tree(node->right_child, value);
                return true;
            }
        
            //this private function is used to insert a value in root node, which is used
            // by the public insertion function.
            node_type* insertion(node_type* node, T value)
            {
                if (node == NULL)
                {
                    node = _allocator_node.allocate(1);
                    _allocator.construct(&node->value, value);
                    node->height = 0;
                    node->balanced_factor = 0;
                    node->left_child = NULL;
                    node->right_child = NULL;
                    node->parent = NULL;
                    return (node);
                }
                int checker = _compare(value.first, node->value.first);
                if (checker == true)
                {
                    node_type* tmp = insertion(node->left_child, value);
                    node->left_child = tmp;
                    tmp->parent = node;
                }
                else
                {
                    node_type* tmp = insertion(node->right_child, value);
                    node->right_child = tmp;
                    tmp->parent = node;
                }
                update_bf_height(node);
                return balance(node);
            }

            //it updates the values of height and balanced factor each time there is modification in the tree
            void update_bf_height(node_type* node)
            {
                int left_side_height = 0;
                int right_side_height = 0;

                if (node->left_child == NULL)
                    left_side_height = -1;
                else if (node->left_child != NULL)
                    left_side_height = node->left_child->height;
                if (node->right_child == NULL)
                    right_side_height = -1;
                else if (node->right_child != NULL)
                    right_side_height = node->right_child->height;
                node->balanced_factor = right_side_height - left_side_height;
                node->height = std::max(right_side_height, left_side_height) + 1;
            }            

            //make a right rotation to fix the balance
            node_type* right_rotation(node_type* node)
            {
                node_type* x_node = node->left_child;
                node_type* y_node = x_node->right_child;

                x_node->right_child = node;
                node->left_child = y_node;
                x_node->parent = node->parent;
                node->parent = x_node;
                if (node->left_child != NULL)
                    node->left_child->parent = x_node->right_child;
                update_bf_height(node);
                update_bf_height(x_node);
                return x_node;
            }

            //make a left rotation to help fix the balance of tree
            node_type* left_rotation(node_type* node)
            {
                node_type* x_node = node->right_child;
                node_type* y_node = x_node->left_child;

                x_node->left_child = node;
                node->right_child = y_node;
                x_node->parent = node->parent;
                node->parent = x_node;
                if (node->right_child != NULL)
                    node->right_child->parent = x_node->left_child;
                update_bf_height(node);
                update_bf_height(x_node);
                return x_node;
            }

            //implement three cases of rotation
            node_type* left_left_case(node_type* node)
            {
                return right_rotation(node);
            }

            node_type* right_right_case(node_type* node)
            {
                return left_rotation(node);
            }

            node_type* right_left_case(node_type* node)
            {
                node->right_child = right_rotation(node->right_child);
                return left_rotation(node);
            }

            node_type* left_right_case(node_type* node)
            {
                node->left_child = left_rotation(node->left_child);
                return right_rotation(node);
            }

            //balancing the tree map
            node_type* balance(node_type* node)
            {
                //right right case of balance
                if (node->balanced_factor > 1 && node->right_child->balanced_factor >= 0)
                    return right_right_case(node);
                //right left case of balance
                else if (node->balanced_factor > 1)
                    return right_left_case(node);
                //left left case of balance
                else if (node->balanced_factor < -1 && node->left_child->balanced_factor <= 0)
                    return left_left_case(node);
                //left right case of balance
                else if (node->balanced_factor < -1)
                    return left_right_case(node);
                //return the node pointer if no balance is needed
                return node;
            }

            //private function of searching for a key
            map_value* searching(node_type* node, key_type& value)
            {
                if (node == NULL)
                    return 0;
                if (node->value.first == value)
                    return &(node->value.second);
                if (_compare(node->value.first, value) == false)
                    return searching(node->left_child, value);
                else
                    return searching(node->right_child, value);
            }

            node_type* find_node(node_type* node, key_type value) const
            {
                if (node == NULL)
                    return NULL;
                if (node->value.first == value)
                    return (node);
                if (_compare(node->value.first, value) == false)
                    return find_node(node->left_child, value);
                else
                    return find_node(node->right_child, value);    
            }

            node_type* deletion(node_type* node, key_type value)
            {
                if (node == NULL)
                    return NULL;
                int checker = _compare(value, node->value.first);
                if (checker == true)
                    node->left_child = deletion(node->left_child, value); // remove node->left_child != NULL if it didnt work
                else if (checker == false && node->right_child != NULL && node->value.first != value)
                    node->right_child = deletion(node->right_child, value); // check node->value.first != key if it didnt work
                else
                {
                    //the case when there is one child, either left or right child
                    if ( (node->left_child != NULL && node->right_child == NULL) 
                        || (node->left_child == NULL && node->right_child != NULL) )
                    {
                        node_type* tmp = (node->left_child != NULL) ? node->left_child : node->right_child;
                        root = tmp;
                        root->parent = node->parent;
                        tmp = NULL;
                        _allocator.destroy(&(node->value));
                        _allocator_node.deallocate(node, 1);
                        node = NULL;
                        return root;
                    }
                    // the case where the node has 2 children, we should replace the content of the nodes
                    // with its successor and it reduces to the deletion of the node with either one child
                    // or none.
                    else if ( node->left_child != NULL && node->right_child != NULL )
                    {
                        node_type* parent = node->parent;
                        if (node->left_child->height > node->right_child->height)
                        {
                            T tmp = max(node->left_child);
                            _allocator.destroy(&node->value);
                            _allocator.construct(&node->value, tmp);
                            node->parent = parent;
                            node->left_child = deletion(node->left_child, tmp.first);
                        }
                        else
                        {
                            T tmp = min(node->right_child);
                            _allocator.destroy(&node->value);
                            _allocator.construct(&node->value, tmp);
                            node->parent = parent;
                            node->right_child = deletion(node->right_child, tmp.first);
                        }
                    }
                    else
                    {
                        _allocator.destroy(&(node->value));
                        _allocator_node.deallocate(node, 1);
                        node = NULL;
                        return NULL;
                    }
                }
                update_bf_height(node);
                return balance(node);
            }

    };

}

#endif
