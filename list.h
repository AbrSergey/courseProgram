#ifndef LIST_H
#define LIST_H
#include <iostream>

struct element
{
    int x;
    element *Next;
};

class List
{
private:
    element *head;
public:
    List() {head=NULL;}
    ~List();
    void Add(int x);
    void Show();
    bool HeadIsNull();
};

#endif // LIST_H
