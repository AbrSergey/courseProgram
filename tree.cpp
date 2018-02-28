#include <iostream>
#include "tree.h"

template< typename T >
Tree< T >::Tree(): _root(0) {}

template< typename T >
Tree< T >::~Tree()
{
    delete_helper(_root);
}

template< typename T >
void Tree< T >::delete_helper(TreeNode< T > *node)
{
    if (node != 0)
    {
        delete_helper(node->_left);
        delete_helper(node->_right);

        delete node;
    }
}

template< typename T >
void Tree< T >::insert(const T &data)
{
    insert_helper(&_root, data);
}

template< typename T >
void Tree< T >::insert_helper(TreeNode< T > **node, const T &data)
{
    if (*node == 0)
        *node = new TreeNode< T > (data);
    else
    {
        if ((*node)->_data > data)
            insert_helper(&((*node)->_left), data);
        else
        {
            if ((*node)->_data < data)
                insert_helper(&((*node)->_right), data);
        }
    }
}

template< typename T >
void Tree< T >::remove(const T &data)
{
    remove_helper(&_root, data);
}

template< typename T >
void Tree< T >::remove_helper(TreeNode< T > **node, const T &data)
{
    if ((*node)->_data == data)
    {
        TreeNode< T > *del_node = *node;

        if ((*node)->_left == 0 && (*node)->_right == 0)
        {
            *node = 0;

            delete del_node;
        }
        else
        {
            if ((*node)->_left == 0)
            {
                *node = (*node)->_right;

                delete del_node;
            }
            else
            {
                if ((*node)->_right == 0)
                {
                    *node = (*node)->_left;

                    delete del_node;
                }
                else
                {
                    TreeNode< T > *p = *node;
                    TreeNode< T > *i = (*node)->_left;

                    while (i->_right != 0)
                    {
                        p = i;
                        i = i->_right;
                    }

                    *node = i;
                    p->_right = i->_left;
                    i->_right = del_node->_right;
                    i->_left = p;

                    delete del_node;
                }
            }
        }
    }
    else
    {
        if ((*node)->_data > data)
            remove_helper(&((*node)->_left), data);
        else
        {
            if ((*node)->_data < data)
                remove_helper(&((*node)->_right), data);
        }
    }
}

template< typename T >
void Tree< T >::pre_order() const
{
    pre_order_helper(_root);
}

template< typename T >
void Tree< T >::pre_order_helper(TreeNode< T > *node) const
{
    if (node != 0)
    {
        std::cout << node->_data << "  ";

        pre_order_helper(node->_left);
        pre_order_helper(node->_right);
    }
}

template< typename T >
void Tree< T >::in_order() const
{
    in_order_helper(_root);
}

template< typename T >
void Tree< T >::in_order_helper(TreeNode< T > *node) const
{
    if (node != 0)
    {
        in_order_helper(node->_left);

        std::cout << node->_data << "  ";

        in_order_helper(node->_right);
    }
}

template< typename T >
void Tree< T >::post_order() const
{
    post_order_helper(_root);
}

template< typename T >
void Tree< T >::post_order_helper(TreeNode< T > *node) const
{
    if (node != 0)
    {
        post_order_helper(node->_left);
        post_order_helper(node->_right);

        std::cout << node->_data << "  ";
    }
}

template< typename T >
int Tree< T >::depth() const
{
    return depth_helper(_root);
}

template< typename T >
int Tree< T >::depth_helper(TreeNode< T > *node) const
{
    if (node->_left == 0 && node->_right == 0)
        return 1;
    else
    {
        if (node->_left == 0)
            return 1 + depth_helper(node->_right);
        else
        {
            if (node->_right == 0)
                return 1 + depth_helper(node->_left);
            else
                return 1 + max(depth_helper(node->_left), depth_helper(node->_right));
        }
    }
}

template< typename T >
void Tree< T >::print() const
{
    print_helper(_root, 0);
}

template< typename T >
void Tree< T >::print_helper(TreeNode< T > *node, int spaces) const
{
    while (node != 0)
    {
        print_helper(node->_right, spaces + 5);

        for (int i = 1; i < spaces; ++i)
            std::cout << ' ';

        std::cout << node->_data << std::endl;

        node = node->_left;
        spaces += 5;
    }
}

template< typename Type >
Type max(const Type &left, const Type &right)
{
    return left > right ? left : right;
}
