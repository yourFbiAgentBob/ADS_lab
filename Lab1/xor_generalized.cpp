#include<bits/stdc++.h>
using namespace std;

class Node
{
    public:
    int data;
    Node* ptr;
};

Node* XOR (Node *a, Node *b)
{
    return (Node*) ((uintptr_t) (a) ^ (uintptr_t) (b));
}

Node* insert_begin(Node *head, int data)
{
    Node *new_node = new Node();
    new_node->data = data;
    new_node->ptr = head;

    if (head != NULL)
    {
        head->ptr = XOR(new_node, head->ptr);
    }
    head = new_node;
    return head;
}

Node* insert_end(Node *head, int data)
{
    Node *new_node = new Node();
    new_node->data = data;
    Node *prev = NULL;
    Node *curr = head;
    Node *next;
    if(head == NULL){
        head = new_node;
        head->ptr = NULL;
        return head;

    }
    while (XOR(prev, curr->ptr) != NULL) {  
        next = XOR (prev, curr->ptr);  
        prev = curr;  
        curr = next;  
    }
    new_node->ptr = curr;
    curr->ptr = XOR(prev, new_node);
    return head;
}

Node* delete_end(Node *head)
{
    Node *prev = NULL;
    Node *curr = head;
    Node *next = XOR(prev, curr->ptr);
    if(head == NULL){
        return NULL;

    }
    while (next != NULL) {  
        prev = curr;  
        curr = next;  
        next = XOR(prev, curr->ptr);  
    }
    if(prev != NULL){
        prev->ptr = XOR(prev->ptr, curr);
    }
    delete curr;
    return head;
}

Node* delete_begin(Node *head)
{
    if(head == NULL){
        return NULL;

    }
    Node *temp = XOR(head->ptr,NULL);
    temp->ptr = XOR(head, temp->ptr);
    delete head;
    return temp;
}

void printList (Node *head)
{
    Node *curr = head;
    Node *prev = NULL;
    Node *next;

    cout << "Linked List is: \n";

    while (curr != NULL)
    {
        cout<<curr->data<<" ";
        next = XOR (prev, curr->ptr);
        prev = curr;
        curr = next;
    }
    cout<<endl;
}
int main() {
int n;
cout<<"Insert in the beginning"<<endl;
cout<<"Enter the no. of elements"<<endl;
cin>>n;
int data;
Node* head = NULL;
cout<<"Enter the elements"<<endl;
for(int i = 0; i < n; i++){
   cin>>data;
  head = insert_begin(head, data);
}
printList(head);
cout<<"Insert in the end"<<endl;
cout<<"Enter the no. of elements"<<endl;
cin>>n;
Node* head1 = NULL;
cout<<"Enter the elements"<<endl;
for(int i = 0; i < n; i++){
   cin>>data;
  head1 = insert_end(head1, data);
}
printList(head1);

cout<<"After deleting the last node from the second list ";
head1 = delete_end(head1);
printList(head1);
cout<<"After deleting the first node from the second list ";
head1 = delete_begin(head1);
printList(head1);

return 0;
}