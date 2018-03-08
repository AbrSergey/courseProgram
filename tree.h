#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <assert.h>
//#include "treenode.h"

struct TreeNode{
    unsigned int _data;
    TreeNode * _left;
    TreeNode * _right;
    TreeNode * _parent;
    TreeNode * _neighbor_right;

    TreeNode(): _data(0), _left(0), _right(0), _parent(0), _neighbor_right(0) {}

    TreeNode(unsigned int data): _data(data), _left(0), _right(0), _parent(0), _neighbor_right(0) {}

    unsigned int get_data() const { return _data; } // don't use

    void insert (unsigned int data, const bool status)
    {
        if (!status){
            _left = new TreeNode(data);
            _left->_parent = this;

            if (_right != NULL) _left->_neighbor_right = _right;
        }
        else{
            _right = new TreeNode(data);
            _right->_parent = this;

            if (_left != NULL) _left->_neighbor_right = _right;
        }
    }

    void delete_branch ()
    {
        if (_left == NULL || _right == NULL){
            TreeNode * node = _parent;
            _parent->delete_branch();
            delete this;
        }
    }
};

class Tree
{
//    template< typename Type >
//    friend Type max(const Type &, const Type &);

public:
    Tree ();
    Tree (unsigned int);
    ~Tree ();

//    void insert(unsigned int, int);
//    void remove(const unsigned int &);

    TreeNode * root();
//    TreeNode * left();

//    void pre_order() const;
//    void in_order() const;
//    void post_order() const;

//    int depth() const;

    void print() const;

private:
    TreeNode *_root = NULL;

//    void insert_helper(TreeNode **, unsigned int , int status);
//    void remove_helper(TreeNode **, const unsigned int &);

//    void pre_order_helper(TreeNode *) const;
//    void in_order_helper(TreeNode *) const;
//    void post_order_helper(TreeNode *) const;

    void delete_helper(TreeNode *);

//    int depth_helper(TreeNode *) const;

    void print_helper(TreeNode*, int) const;
};
#endif // TREE_H
