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
    element *Head;
public:
    List() {Head=NULL;}
    ~List();
    void Add(int x);
    void Show();
};

#endif // LIST_H
