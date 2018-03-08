#include "treenode.h"

TreeNode::TreeNode(): _left(0), _right(0), _parent(0), _neighbor_right(0) {}

TreeNode::TreeNode(const unsigned int & data, const TreeNode *, const TreeNode *):
    _data(data), _left(0), _right(0) {}

unsigned int TreeNode::get_data() const
{
    return _data;
}
