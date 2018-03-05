#ifndef TREENODE_H
#define TREENODE_H

class TreeNode
{
    friend class Tree;

public:
    TreeNode();
    TreeNode(const unsigned int &);

    unsigned int get_data() const;

private:
    unsigned int _data;
    TreeNode *_left;
    TreeNode*_right;
};

#endif // TREENODE_H
