#include "treenode.h"

template< typename T >
TreeNode< T >::TreeNode(): _left(0), _right(0) {}

template< typename T >
TreeNode< T >::TreeNode(const T &data): _data(data), _left(0), _right(0) {}

template< typename T >
T TreeNode< T >::get_data() const
{
    return _data;
}
