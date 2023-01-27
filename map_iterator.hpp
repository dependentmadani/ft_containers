#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <memory>
# include "utility.hpp"

namespace ft
{
    template<class T, class Category, class tree, class node>
    class Bidirectional_iterator
    {
        public:
            typedef T           value_type;
            typedef Category    iterator_category;
            typedef ptrdiff_t   difference_type;
            typedef T*          pointer;
            typedef T&          reference;
            typedef tree        tree_type;
            typedef node        node_type;
        
        private:
            //the address of avl object associated with the iterator.
            tree_type*  tree;
            //the current location in the tree
            node_type*  node;

        public:
            Bidirectional_iterator(): tree(NULL), node(NULL) { };
            Bidirectional_iterator(node_type* n, tree_type* t): node(n), tree(t) { };
            Bidirectional_iterator(const Bidirectional_iterator& other) {*this = other;};
            ~Bidirectional_iterator() {};
            Bidirectional_iterator& operator= (const Bidirectional_iterator& other) {
                if (*this != other)
                {
                    tree = other.tree;
                    node = other.node;
                }
                return (*this);
            }

            friend bool operator== (const Bidirectional_iterator& lhs, const Bidirectional_iterator& rhs) {return lhs.node == rhs.node;};
            friend bool operator!= (const Bidirectional_iterator& lhs, const Bidirectional_iterator& rhs) {return !(lhs == rhs);};

            reference operator* () const {return node->value;};
            pointer operator-> () const {return &(node->value);};

            operator Bidirectional_iterator<const value_type, const iterator_category, const tree_type, const node_type>() 
            {
                return Bidirectional_iterator<const value_type, const iterator_category, const tree_type, const node_type>(node, tree);
            };

            Bidirectional_iterator& operator++ ()
            {
                node_type*   tmp;
                if (node == NULL)
                {
                    node = tree->root;
                    while (node != NULL)
                        node = node->left_child;
                }
                else
                {
                    if (node->right_child != NULL)
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
                }
                return *this;
            }

            Bidirectional_iterator& operator++ (int)
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
                    node = tree->root;
                    while (node != NULL)
                        node = node->right_child;
                }
                else
                {
                    if (node->left_child != NULL)
                    {
                        node = node->left_child;
                        while (node->right_child != NULL)
                            node = node->right_child;
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
                }
                return *this;
            }

            Bidirectional_iterator& operator--(int)
            {
                Bidirectional_iterator tmp = *this;
                --(*this);
                return tmp;
            }

            node_type* get_node()
            {
                return node;
            }
    };
}

#endif