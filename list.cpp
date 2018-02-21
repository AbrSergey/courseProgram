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
    temp->Next=Head;
    Head=temp;
}

void List::Show()
{
    element *temp=Head;

    while (temp!=NULL){
        std::cout<<temp->x<<" ";
        temp=temp->Next;
    }
}
