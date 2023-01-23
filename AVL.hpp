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

            //return the max value in the tree map
            T max(node_type* node) const
            {
                while (root->right != NULL)
                    root = root->right;
                return root->value;
            }

            //return the min value in the tree map
            T min(node_type* node) const
            {
                while (root->left != NULL)
                    root = root->left;
                return root->value;
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
                if (root != NULL)
                    return root->height;
                return 0;
            }

            //check if the tree is empty or not
            bool empty() const
            {
                return node_number;
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
                this->clear(root);
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


        private:

            //private function of clear to use private attribe root to clear it
            void clear(node_type* node)
            {
                if (node != NULL)
                {
                    _allocator.destroy(node->value);
                    if (node->right_child != NULL)
                        clean(node->left_child);
                    if (node->left_child != NULL)
                        clean(node->left_child);
                    _allocator_node.deallocate(node, 1);
                }
                node = NULL;
            }

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

            //it updates the values of height and balanced factor each time there is modification in the tree
            void update_bf_height(node_type* node)
            {
                int left_side_height;
                int right_side_height;

                if (node->left_child == NULL)
                    left_side_height = -1;
                else
                    left_side_height = node->left_child->height;
                if (node->right_child == NULL)
                    right_side_height = -1;
                else
                    right_side_height = node->right_child->height;
                node->balanced_factor = right_side_height - left_side_height;
                node->height = std::max(right_side_height, left_side_height) + 1;
            }            

            //make a right rotation to fix the balance
            node_type* right_rotation(node_type* node)
            {
                node_type* new_parent;
                new_parent = node->left_child;
                node->left_child = new_parent->right_child;
                new_parent->right_child = node; //to check it ????
                new_parent->parent = node->parent; //to check it ????
                node->parent = new_parent;
                if (node->left_child != NULL)
                    node->left_child->right_child = new_parent->right_child;
                update(new_parent);
                update(node);
                return new_parent;
            }

            //make a left rotation to help fix the balance of tree
            node_type* left_rotation(node_type* node)
            {
                node_type* new_parent;
                new_parent = node->right_child;
                node->left_child = new_parent->left_child;
                new_parent->right_child = node; // to check it ??
                new_parent->parent = node->parent; // to check it ???
                node->parent = new_parent;
                if (node->right_child != NULL)
                    node->right_child->right_child = new_parent->left_child;
                update(new_parent);
                update(node);
                return new_parent;
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
                node->left_child = left_rotation(node);
                return right_rotation(node);
            }

            //balancing the tree map
            node_type* balance(node_type* node)
            {
                if (node->balanced_factor == 2)
                {
                    if (node->right_child->balanced_factor >= 0)
                        return right_right_case(node);
                    else
                        return right_left_case(node);
                }
                else if (node->balanced_factor == -2)
                {
                    if (node->left_child->balanced_factor <= 0)
                        return left_left_case(node);
                    else
                        return left_right_case(node);
                }
                return node;
            }

            //private function of searching for a key
            map_value* searching(node_type* node, key_type& value)
            {
                if (node == NULL)
                    return 0;
                if (node->value.first == key)
                    return &(node->value.second);
                if (_compare(node->value.first, value) == false)
                    return searching(node->left_child, value);
                else
                    return searching(node->right_child, value);
            }

            node_type* find_node(node_type* node, key_type value) const
            {
                if (node == NULL)
                    return 0;
                if (node->value.first == key)
                    return (node);
                if (_compare(node->value.first, value) == false)
                    return find_node(node->left_child, value);
                else
                    return find_node(node->right_child, value);    
            }

    };

}

#endif