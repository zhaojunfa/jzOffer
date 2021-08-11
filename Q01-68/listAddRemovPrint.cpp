/*05_02 链表添加和删除P56\
 *06_01从尾到头打印链表
*/

#include <iostream>
#include <stack>
#include "dataStructure.h"
using namespace std;

void AddToTail(ListNode **pHead,int value){
    //
    ListNode *pNew = new ListNode();
    pNew->m_pNext = nullptr;
    pNew->m_nValue = value;
    //possibly pHead is nullptr
    if(pHead == nullptr)
        return;
    //possibly *pHead is nullptr(list empty)
    if(*pHead == nullptr)
        *pHead = pNew;
    else{
        ListNode *tempHead = *pHead;
        while(tempHead->m_pNext != nullptr)
            tempHead = tempHead->m_pNext;
        tempHead->m_pNext = pNew;
    }
}

void removeNode(ListNode **pHead,int value){
    //possibly pHead or *pHead is nullptr
    if(pHead == nullptr || *pHead == nullptr)
        return;
    //possibly (*pHead)->m_nValue = value
    if((*pHead)->m_nValue == value){
        auto temp = *pHead;
        *pHead = (*pHead)->m_pNext;
        delete temp;
        return;
    }
    //
    auto temp = *pHead;
    while(temp->m_pNext != nullptr && temp->m_pNext->m_nValue != value)
        temp = temp->m_pNext;
    if(temp->m_pNext == nullptr)//value not found
        return;
    auto tobeDel = temp->m_pNext;
    temp->m_pNext = temp->m_pNext->m_pNext;
    delete tobeDel;
    tobeDel = nullptr;
}

//正向打印链表
void printList(ListNode *pHead){
    while(pHead != nullptr){
        cout << pHead->m_nValue << "->";
        pHead = pHead->m_pNext;
    }
    cout << "nullptr\n";
}

/*
 * 06_01从尾到头打印链表
 * 输入一个链表的头结点从尾到头反过来打印每个节点的值
 * 用stack或者递归（链表太长的话可能会栈溢出）
*/
void printListReversingly(ListNode *pHead){
    stack<int> nodes;
    if(pHead == nullptr)
        return;
    while(pHead != nullptr){
        nodes.push(pHead->m_nValue);
        pHead = pHead->m_pNext;
    }
    while(!nodes.empty()){
        auto topEle = nodes.top();
        nodes.pop();
        cout << topEle <<"->";
    }
}



int main(){
    ListNode *head = nullptr;
    AddToTail(&head,1);
    AddToTail(&head,2);
    AddToTail(&head,3);
    AddToTail(&head,4);
    AddToTail(&head,5);
    //removeNode(&head,1);//test
    printList(head);
    printListReversingly(head);
    return 0;
}


