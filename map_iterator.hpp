#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <memory>
# include "utility.hpp"
# include "AVL.hpp"

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
            Bidirectional_iterator(node_type* n, tree_type* t): node(n), _tree(t) { };
            Bidirectional_iterator(const Bidirectional_iterator& other) {*this = other;};
            ~Bidirectional_iterator() {};
            Bidirectional_iterator& operator= (const Bidirectional_iterator& other) {
                _tree = other._tree;
                node = other.node;
                return (*this);
            }

            bool operator== (const Bidirectional_iterator& rhs) {return node == rhs.node;};
            bool operator!= (const Bidirectional_iterator& rhs) {return node != rhs.node;};

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
                    // std::cout << "kan hna" << std::endl;
                // std::cout << "check value: " << "\n" << node->value.first << std::endl;
                return *this;
            }

            Bidirectional_iterator operator--(int)
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