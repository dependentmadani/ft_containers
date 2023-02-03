#include "../map.hpp"
#include "../AVL.hpp"
 
// Driver Code
int main()
{
    ft::avl_tree<int> *root = NULL;
     
    /* Constructing tree given in
    the above figure */
    root = insertion(10);
    root = insertion(20);
    root = insertion(30);
    root = insertion(40);
    root = insertion(50);
    root = insertion(25);
     
    /* The constructed AVL Tree would be
                30
            / \
            20 40
            / \ \
        10 25 50
    */
    std::cout << "Preorder traversal of the "
            "constructed AVL tree is \n";
    root.preOrder(root);
     
    return 0;
}