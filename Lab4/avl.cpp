#include<bits/stdc++.h>
using namespace std;
class Node
{
public:
 int key;//val
 Node *left;
 Node *right;
 int height;
};
int max(int a,int b)
{
    return (a>b)?a:b;
}
int height(Node *node)
{
if(node==NULL)
{
return 0;
}
return node->height;
}
Node *newNode(int key)
{
    Node *node=new Node();//alloc mem
    node->key=key;
    node->left=NULL;
    node->right=NULL;
    node->height=1;//height +1 for every node
    return node;
}
Node* rightRotate(Node *y)
{
  Node *x=y->left;
  Node *T2=x->right;
  x->right=y;
  y->left=T2;
  //recalcing heights
  y->height=max(height(y->left),height(y->right))+1;
  x->height=max(height(x->left),height(x->right))+1;
  return x;//new root
}
Node *leftRotate(Node *x)
{
Node *y=x->right;
Node *T2=y->left;
y->left=x;
x->right=T2;
y->height=max(height(y->left),height(y->right))+1;
x->height=max(height(x->left),height(x->right))+1;
return y;//new root
}

//balance factor
int getBalance(Node *node)
{
    if(node==NULL)
    {
        return 0;
    }
    return height(node->left)-height(node->right);
}
Node* insert(Node *node,int key)
{
if(node==NULL)
{
   return newNode(key);
}
if(key<node->key)
{
  node->left=insert(node->left,key);
}
else if(key>node->key)
{
node->right=insert(node->right,key);
}
else//no duplicates
 return node;
node->height=1+max(height(node->left),height(node->right));
int balance=getBalance(node);
//now checking for diff cases
//LL
if(balance>1 && key<node->left->key)
{
return rightRotate(node);
}
//RR
if(balance<-1&& key>node->right->key)
{
return leftRotate(node);
}
//LR
if(balance>1 && key>node->left->key)
{
node->left=leftRotate(node->left);
return rightRotate(node);
}
//RL
if(balance<-1 && key<node->right->key)
{
node->right=rightRotate(node->right);
return leftRotate(node);
}
return node;
}
Node *minValueNode(Node *node)
{
Node *current=node;
while(current->left!=NULL)
{
current=current->left;
}
return current;
}
Node* deleteNode(Node *root,int key)
{
//BST deletion
if(root==NULL)
   return root;
if(key<root->key)
{
   root->left=deleteNode(root->left,key);
}
else if(key>root->key)
{
   root->right=deleteNode(root->right,key);
}
else
{
  if ((root->left == NULL) || (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;//setting left or right child value in roots place

            free(temp);
        } else {
            Node *temp = minValueNode(root->right);//min in RST
            root->key = temp->key;//replace node with min in RST
            root->right = deleteNode(root->right, temp->key);//now can delete
        }
}
 if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) 
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
void preOrder(Node *root)
{
  if(root!=NULL)
  {
      cout<<root->key<<" ";
      preOrder(root->left);
      preOrder(root->right);
  }
}
int main()
{
   int choice,n,val;
    Node *root=NULL;
   while(true)
   {
   cout<<"1.Insert 2.Delete 3.Display:";
   cin>>choice;
   switch(choice)
   {
         case 1:
                cout << "Enter element to be inserted: ";
                cin >> val;
                root = insert(root, val);
                break;
            case 2:
                cout << "Enter element to be deleted: ";
                cin >> val;
                root = deleteNode(root, val);
                break;
            case 3:
                cout << "AVL Tree: " << endl;
                preOrder(root);
                cout << "\n\n";
                break;
            default:
                exit(0);
   }
   }
    return 0;
}