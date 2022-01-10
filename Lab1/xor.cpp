// Write a program to implement the following list: 
// An ordinary Doubly Linked List requires space for two address fields to store the 
// addresses of previous and next nodes. A memory efficient version of Doubly Linked List 
// can be created using only one space for address field with every node. This memory 
// efficient Doubly Linked List is called XOR Linked List or Memory Efficient as the list 
// uses bitwise XOR operation to save space for one address. In the XOR linked list, instead 
// of storing actual memory addresses, every node stores the XOR of addresses of previous 
// and next nodes.

#include<iostream>
#include<bits/stdc++.h>
#include<cinttypes>
using namespace std;
class Node
{
  public:
  int data;
  Node *npx;  
};
Node* XOR(Node * x,Node *y)
{//uintptr is needed for unsigned integer operations
return reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(x) ^ reinterpret_cast<uintptr_t>(y));
}
void insert(Node** head,int data)
{//passing doubole pointer so changes made in local scope are seen globally
Node* newNode=new Node();
newNode->data=data;
newNode->npx=*head;//inserting at beginning
if(*head!=NULL)
{//need to update link once more than 1 val is inserted
(*head)->npx=XOR(newNode,(*head)->npx);

}
*head=newNode;
}
void display(Node* head)
{
Node *prev=NULL;
Node *curr=head;
Node *next;
 while(curr!=NULL)
 {

     cout<<curr->data<<endl;
     next=XOR(curr->npx,prev);
    prev=curr;
    curr=next;
    
}
}
int main()
{
   Node *head=NULL;
   insert(&head,1);//passing head by reference
   insert(&head,2);
   insert(&head,3);
   display(head); 
return 0;
}