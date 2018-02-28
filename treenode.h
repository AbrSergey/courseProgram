#ifndef TREENODE_H
#define TREENODE_H


template< typename T > class Tree;

template< typename T >
class TreeNode
{
    friend class Tree< T >;

public:
    TreeNode();
    TreeNode(const T &);

    T get_data() const;

private:
    T _data;
    TreeNode< T > *_left;
    TreeNode< T > *_right;
};

#endif // TREENODE_H
