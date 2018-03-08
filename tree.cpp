#include <iostream>
#include <assert.h>
#include "tree.h"

int max(const int &left, const int &right);

Tree::Tree(): _root(0) {}

Tree::Tree(unsigned int data)
{
    _root = new TreeNode(data);
}

Tree::~Tree()
{
    delete_helper(_root);
}

void Tree::delete_helper(TreeNode *node)
{
    if (node != 0)
    {
        delete_helper(node->_left);
        delete_helper(node->_right);

        delete node;
    }
}

//void Tree::insert(unsigned int data, int status = 2) // 0 - left, 1 - right, 2 - root
//{
//    assert(status == 0 | status == 1 | status == 2);

//    insert_helper(&_root, data, status);
//}

//void Tree::insert_helper(TreeNode **node, unsigned int data, int status)
//{
//    if (status == 2)
//        *node = new TreeNode (data);

//    else if (status == 0)
//        insert_helper(&((*node)->_left), data, 2);

//    else if (status == 1)
//        insert_helper(&((*node)->_right), data, 2);

////    if (*node == 0)
////        *node = new TreeNode (data);
////    else
////    {
////        if ((*node)->_data > data)
////            insert_helper(&((*node)->_left), data);
////        else
////        {
////            if ((*node)->_data < data)
////                insert_helper(&((*node)->_right), data);
////        }
////    }
//}

//void Tree::remove(const unsigned int &data)
//{
//    remove_helper(&_root, data);
//}

TreeNode *Tree::root()
{
    assert(_root != NULL);
    return _root;
}

//TreeNode *Tree::left()
//{
//    assert(_root->_left == NULL);
//    return _root->_left;
//}

//void Tree::remove_helper(TreeNode **node, const unsigned int &data)
//{
//    if ((*node)->_data == data)
//    {
//        TreeNode *del_node = *node;

//        if ((*node)->_left == 0 && (*node)->_right == 0)
//        {
//            *node = 0;

//            delete del_node;
//        }
//        else
//        {
//            if ((*node)->_left == 0)
//            {
//                *node = (*node)->_right;

//                delete del_node;
//            }
//            else
//            {
//                if ((*node)->_right == 0)
//                {
//                    *node = (*node)->_left;

//                    delete del_node;
//                }
//                else
//                {
//                    TreeNode *p = *node;
//                    TreeNode *i = (*node)->_left;

//                    while (i->_right != 0)
//                    {
//                        p = i;
//                        i = i->_right;
//                    }

//                    *node = i;
//                    p->_right = i->_left;
//                    i->_right = del_node->_right;
//                    i->_left = p;

//                    delete del_node;
//                }
//            }
//        }
//    }
//    else
//    {
//        if ((*node)->_data > data)
//            remove_helper(&((*node)->_left), data);
//        else
//        {
//            if ((*node)->_data < data)
//                remove_helper(&((*node)->_right), data);
//        }
//    }
//}

//void Tree::pre_order() const
//{
//    pre_order_helper(_root);
//}

//void Tree::pre_order_helper(TreeNode *node) const
//{
//    if (node != 0)
//    {
//        std::cout << node->_data << "  ";

//        pre_order_helper(node->_left);
//        pre_order_helper(node->_right);
//    }
//}

//void Tree::in_order() const
//{
//    in_order_helper(_root);
//}

//void Tree::in_order_helper(TreeNode *node) const
//{
//    if (node != 0)
//    {
//        in_order_helper(node->_left);

//        std::cout << node->_data << "  ";

//        in_order_helper(node->_right);
//    }
//}

//void Tree::post_order() const
//{
//    post_order_helper(_root);
//}

//void Tree::post_order_helper(TreeNode *node) const
//{
//    if (node != 0)
//    {
//        post_order_helper(node->_left);
//        post_order_helper(node->_right);

//        std::cout << node->_data << "  ";
//    }
//}

//int Tree::depth() const
//{
//    return depth_helper(_root);
//}

//int Tree::depth_helper(TreeNode *node) const
//{
//    if (node->_left == 0 && node->_right == 0)
//        return 1;
//    else
//    {
//        if (node->_left == 0)
//            return 1 + depth_helper(node->_right);
//        else
//        {
//            if (node->_right == 0)
//                return 1 + depth_helper(node->_left);
//            else
//                return 1 + max(depth_helper(node->_left), depth_helper(node->_right));
//        }
//    }
//}

void Tree::print() const
{
    print_helper(_root, 0);
}

void Tree::print_helper(TreeNode *node, int spaces) const
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

int max(const int &left, const int &right)
{
    return left > right ? left : right;
}
