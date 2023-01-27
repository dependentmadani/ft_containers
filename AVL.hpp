#ifndef AVL_HPP
# define AVL_HPP

# include "utility.hpp"
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

            int deletion(key_type value)
            {
                if (available_in_tree(root, value))
                {
                    root = deletion(root, key);
                    --node_number;
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
                cout << endl;
                for (int i = SPACE; i < space; i++)
                  cout << " ";
                cout << node->value.first << "\n";
                print2D(node->left_child, space);
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
                    node->left_child = insertion(node->left_child, value);
                else
                    node->right_child = nsertion(node->right_child, value);
                update_bf_height(node);
                balance_tree(node);
                return node;
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

            // node_type* right_rotation(node_type* node)
            // {
            //     node_type* new_parent;
            //     new_parent = node->left_child;
            //     node->left_child = new_parent->right_child;
            //     new_parent->right_child = node; //to check it ????
            //     new_parent->parent = node->parent; //to check it ????
            //     node->parent = new_parent;
            //     if (node->left_child != NULL)
            //         node->left_child->right_child = new_parent->right_child;
            //     update(new_parent);
            //     update(node);
            //     return new_parent;
            // }

            // node_type* left_rotation(node_type* node)
            // {
            //     node_type* new_parent;
            //     new_parent = node->right_child;
            //     node->left_child = new_parent->left_child;
            //     new_parent->right_child = node; // to check it ??
            //     new_parent->parent = node->parent; // to check it ???
            //     node->parent = new_parent;
            //     if (node->right_child != NULL)
            //         node->right_child->right_child = new_parent->left_child;
            //     update(new_parent);
            //     update(node);
            //     return new_parent;
            // }

            //make a right rotation to fix the balance
            node_type* right_rotation(node_type* node)
            {
                node_type* x_node = node->left_child;
                node_type* y_node = node->right_child;

                x_node->right_child = node;
                node->left_child = y_node;
                update(x_node);
                update(node);
                return x_node;
            }

            // //make a left rotation to help fix the balance of tree
            node_type* left_rotation(node_type* node)
            {
                node_type* x_node = node->right_child;
                node_type* y_node = node->left_child;

                x_node->left_child = node;
                node->right_child = y_node;
                update(x_node);
                update(node);
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
                node->left_child = left_rotation(node);
                return right_rotation(node);
            }

            //balancing the tree map
            node_type* balance(node_type* node)
            {
                //right right case of balance
                if (node->balanced_factor > 1 && node->right_child->balanced_factor >= 0)
                    return right_right_case(node);
                //right left case of balance
                else if (node->balanced_factor > 1 && node->right_child->balanced_factor < 0)
                    return right_left_case(node);
                //left left case of balance
                else if (node->balanced_factor > 1 && node->left_child->balanced_factor <= 0)
                    return left_left_case(node);
                //left right case of balance
                else if (node->balanced_factor > 1 && node->left_child->balanced_factor > 0)
                    return left_right_case(node);
                //return the node pointer if no balance is needed
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

            // node_type* deletion(node_type* node, key_type value)
            // {
            //     if (node == NULL)
            //         return NULL;
            //     if (_compare(value, node->value.first) == true && node->left_child != NULL)
            //         node->left_child = deletion(node->left_child, value); // remove node->left_child != NULL if it didnt work
            //     else if (_compare(value, node->value.first) == false && node->right_child != NULL)
            //         node->right_child = deletion(node->right_child, value); // check node->value.first != key if it didnt work
            //     else
            //     {
            //         //the case when there is one child, either left or right child
            //         if ( node->left_child != NULL && node->right_child == NULL )
            //         {
            //             root = node->left_child;
            //             root->parent = node->parent;
            //             _allocator.destroy(&(node->value));
            //             _allocator_node.deallocate(node, 1);
            //             node = NULL;
            //             return root;
            //         }
            //         else if ( node->left_child == NULL && node->right_child != NULL )
            //         {
            //             root = node->right_child;
            //             root->parent = node->parent;
            //             _allocator.destroy(&(node->value));
            //             _allocator_node.deallocate(node, 1);
            //             node = NULL;
            //             return root;
            //         }
            //         // the case where the node has 2 children, we should replace the content of the nodes
            //         // with its successor and it reduces to the deletion of the node with either one child
            //         // or none.
            //         else if ( node->left_child != NULL && node->right_child != NULL )
            //         {
            //             node_type* parent = node->parent;
            //             if (node->left_child->height >= node->right_child->height)
            //             {
            //                 T s = max(node->left_child);
            //                 _allocator.construct(&node->value, s);
            //                 node->parent = parent;
            //                 node->left_child = deletion(node->left_child, s.first);
            //             }
            //             else
            //             {
            //                 T s = min(node->right_child);
            //                 _allocator.construct(&node->value, s);
            //                 node->parent = parent;
            //                 node->right_child = deletion(node->right_child, s.first);
            //             }
            //         }
            //         else
            //         {
            //             _allocator.destroy(&(node->value));
            //             _allocator_node.deallocate(node, 1);
            //             node = NULL;
            //             return node;
            //         }
            //         update(node);
            //         balance(node);
            //         return (node);
            //     }
            // }
            node_type* deletion(node_type* node, key_type value)
            {
                if (node == NULL)
                    return NULL;
                else if (_compare(value, node->value.first))
                    node->left_child = deletion(node->left_child, value);
                else if (_compare(value, node->value.first) == false )
                    node->right_child = deletion(node->right_child, value);
                else
                {
                    if (node->left_child == NULL)
                    {
                        node_type* temp = node->right_child;
                        _allocator.destroy(&(node->value));
                        _allocator_node.deallocate(node, 1);
                        node = NULL;
                        return temp;
                    }
                    else if (node->right_child == NULL)
                    {
                        node_type* temp = node->left_child;
                        _allocator.destroy(&(node->value));
                        _allocator_node.deallocate(node, 1);
                        node = NULL;
                        return temp;
                    }
                    else
                    {
                        node_type* temp = min(node->right_child);
                        node->value = temp->value;
                        node->right_child = deletion(node->right_child, temp->value);
                    }
                }
            }

    };

}

#endif