#include <iostream>
#include "list.h"

List::~List()
{
//    while (Head!=NULL)
//    {
//        element *temp=Head->Next;
//        delete Head;
//        Head=temp;
//    }
}

void List::Add(int x)
{
    element *temp=new element;
    temp->x=x;
    temp->Next=head;
    head=temp;
}

void List::Show()
{
    element *temp=head;

    while (temp!=NULL){
        std::cout<<temp->x<<" ";
        temp=temp->Next;
    }
}

bool List::HeadIsNull()
{
    if (head != NULL) return false;
    return true;
}
