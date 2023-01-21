#ifndef AVL_HPP
# define AVL_HPP

# include <memory>
# include <functional>

namespace ft
{
    template<class Pair>
    struct AVL
    {
        Pair value;
        AVL* root;
        AVL* left;
        AVL* right;
        int height;
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
                insert_node(other.root);
                return (*this);
            }

            
    };

}

#endif