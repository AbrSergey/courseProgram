#include "treenode.h"

TreeNode::TreeNode(): _left(0), _right(0) {}

TreeNode::TreeNode(const unsigned int & data): _data(data), _left(0), _right(0) {}

unsigned int TreeNode::get_data() const
{
    return _data;
}
