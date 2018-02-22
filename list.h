#ifndef LIST_H
#define LIST_H
#include <iostream>

struct Node
{
    int x;
    Node *m_next;
};

class List
{
private:
    Node *m_head;
public:
    List() {m_head=NULL;}
    ~List();
    void Add(int x);
    void Show();
    bool HeadIsNull();
};

#endif // LIST_H
