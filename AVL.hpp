#ifndef AVL_HPP
# define AVL_HPP

# include "utility.hpp"
# include <memory>
# include <functional>
# include <algorithm>

namespace ft
{
    template<class Pair>
    struct AVL
    {
        Pair value;
        AVL* parent;
        AVL* left_child;
        AVL* right_child;
        int height;
        int balanced_factor;
        AVL (Pair& other): value(other) {};
    };

    template<class T, class Compare= std::less<typename T::first_type>, class Allocator= std::allocator<T> >
    class avl_tree
    {
        public:
            typedef AVL<T>                                                  node_type;
            typedef typename T::first_type                                  key_type;
            typedef typename T::second_type                                 map_value;
            typedef typename Allocator::rebind<node_type>::other            Allocator_node;

            node_type   *root;
            int         node_number;
        
        private:
            Compare         _compare;
            Allocator_node  _allocator_node;
            Allocator       _allocator;
        
        public:

            avl_tree( ): root(NULL), node_number(0) {};
            ~avl_tree( ): { this->clear(); };
            avl_tree( const avl_tree& other) { *this = other; };
            avl_tree& operator= (const avl_tree& other) {
                _compare = other._compare;
                _allocator_node = other._allocator_node;
                _allocator = other._allocator;
                insert_all_nodes(other.root);
                return (*this);
            }

            // possibility to insert a tree in a tree
            //this function insert all the nodes in the root
            void insert_all_nodes(node_type *node)
            {
                if (node != NULL)
                    insertion(node->value);
                    if (node->left_child != NULL)
                        insert_all_nodes(node->left_child);
                    else if (node->right_child != NULL)
                        insert_all_nodes(node->right_child);
            }

            // this function takes the values of a type and insert it the root
            node_type* insertion(T value)
            {
                if (!available(root, value))
                {
                    root = insert(root, value);
                    node_number++;
                    return root;
                }
                return NULL;
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

        private:
            //this private function checks if a value of type T does exist in the tree or not
            bool available_in_tree(node_type* node, T value) const
            {
                if (node != NULL)
                    return false;
                if (node->value.first == value.first)
                    return true;
                if (_compare(value.first, node->value.first) == true)
                    return available_in_tree(node->left_child, value);
                if (_compare(value.first, node->value.first) == false)
                    return available_in_tree(node->right_child, value);
                return true;
            }

            //this function checks if a value of type key_type does exist in the tree or not
            bool available_in_tree(node_type* node, key_type value) const
            {
                if (node != NULL)
                    return false;
                if (node->value.first == value.first)
                    return true;
                if (_compare(value.first, node->value.first) == true)
                    return available_in_tree(node->left_child, value);
                if (_compare(value.first, node->value.first) == false)
                    return available_in_tree(node->right_child, value);
                return true;
            }
        
            //this private function is used to insert a value in root node, which is used
            // by the public insertion function.
            node_type* insertion(node_type* node, T value)
            {
                if (node == NULL)
                {
                    root = _allocator_node.allocate(1);
                    _allocator.construct(&root->value, value);
                    root->height = 0;
                    root->balanced_factor = 0;
                    root->left_child = NULL;
                    root->right_child = NULL;
                    root->parent = NULL;
                    return (root);
                }
                if (_compare(value.first, node->value.first) == true)
                {
                    node_type* left_node = insertion(node->left_child, value);
                    node->left_child = left_node;
                    left_node->parent = node; // unuseful
                }
                else
                {
                    node_type* right_node = insertion(node->right_child, value);
                    node->right_child = right_node;
                    right_node->parent = node; // unuseful
                }
                update_bf_height(node);
                return balance_tree(node);
            }
            
    };

}

#endif