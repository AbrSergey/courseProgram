#ifndef TREE_H
#define TREE_H

#include "treenode.h"

template< typename T >
class Tree
{
//    template< typename Type >
//    friend Type max(const Type &, const Type &);

public:
    Tree();
    ~Tree();

    void insert(const T &);
    void remove(const T &);

    void pre_order() const;
    void in_order() const;
    void post_order() const;

    int depth() const;

    void print() const;

private:
    TreeNode< T > *_root;

    void insert_helper(TreeNode< T > **, const T &);
    void remove_helper(TreeNode< T > **, const T &);

    void pre_order_helper(TreeNode< T > *) const;
    void in_order_helper(TreeNode< T > *) const;
    void post_order_helper(TreeNode< T > *) const;

    void delete_helper(TreeNode< T > *);

    int depth_helper(TreeNode< T > *) const;

    void print_helper(TreeNode< T >*, int) const;
};
#endif // TREE_H
