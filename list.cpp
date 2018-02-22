#include <iostream>
#include "list.h"

List::~List()
{
//    while (m_head){
//        Node *temp = m_head->m_next;
//        delete m_head;
//        m_head = temp;
//    }
}

void List::Add(int x)
{
    Node *temp = new Node;
    temp->x = x;
    temp->m_next = m_head;
    m_head = temp;
}

void List::Show()
{
    Node *temp = m_head;

    while (temp != NULL){
        std::cout << temp->x << " ";
        temp = m_head->m_next;
    }
}

bool List::HeadIsNull()
{
    if (m_head != NULL) return false;
    return true;
}
