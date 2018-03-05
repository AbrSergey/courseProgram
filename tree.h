#ifndef TREE_H
#define TREE_H
#include <iostream>
#include "treenode.h"

class Tree
{
//    template< typename Type >
//    friend Type max(const Type &, const Type &);

public:
    Tree();
    ~Tree();

    void insert(unsigned int, int status);
    void remove(const unsigned int &);

    TreeNode * root();
    TreeNode * left();

    void pre_order() const;
    void in_order() const;
    void post_order() const;

    int depth() const;

    void print() const;

private:
    TreeNode *_root = NULL;

    void insert_helper(TreeNode **, unsigned int , int status);
    void remove_helper(TreeNode **, const unsigned int &);

    void pre_order_helper(TreeNode *) const;
    void in_order_helper(TreeNode *) const;
    void post_order_helper(TreeNode *) const;

    void delete_helper(TreeNode *);

    int depth_helper(TreeNode *) const;

    void print_helper(TreeNode*, int) const;
};
#endif // TREE_H
