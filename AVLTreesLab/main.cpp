//
//  main.cpp
//  AVLTreesLab
//
//  Created by Jonathan Cecil on 02/09/21.
//

#include <iostream>
using namespace std;

class Node
{
    public:
    int key;
    Node *left;
    Node *right;
    int height;
};
//to find height fo a node
int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
//to calculate max
int max(int a, int b)
{
    return (a > b)? a : b;
}
//creating a new node
Node* newNode(int key)
{
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}
//Right Rotation
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *z = x->right;
    x->right = y;
    y->left = z;
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    return x;
}
//Left Rotation
Node *leftRotate(Node *y)
{
    Node *x = y->right;
    Node *z = x->left;
    x->left = y;
    y->right = z;
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    return x;
}
//to get the balance factor
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
//Recurssive function to insert a noe and create an AVL Tree
Node* insert(Node* node, int key)
{
    if (node == NULL)
        return(newNode(key));
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;
    node->height = 1 + max(height(node->left),
                        height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)//Left Left
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)// Right Right Case
        return leftRotate(node);
    if (balance > 1 && key > node->left->key)//Left-Right Case
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key)// Right Left Case
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
//Preorder traversal
void preorder(Node *root)
{
    if(root != NULL)
    {
        cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }
}
//Inorder traversal
void inorder(Node*root)
{
    if(root != NULL)
    {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}
//Question 1
void DisplayRange(Node * root, int k1, int k2)
{
    if(NULL==root)
        return;
    if ( k1 < root->key )
           DisplayRange(root->left, k1, k2);
    if ( k1 <= root->key && k2 >= root->key )
            cout<<root->key<<" ";
    DisplayRange(root->right, k1, k2);
}
//Question 2
void DisplayBigger(Node *root, int k1)
{
    if(NULL==root)
        return;
    if(k1> root->key)
        DisplayBigger(root->right, k1);
    if(k1>=root->key)
        cout<<root->key<<" ";
    DisplayBigger(root->left, k1);
}
//Question 3
void DisplaySmaller(Node *root, int k1)
{
    if(NULL==root)
        return;
    if(k1< root->key)
        DisplaySmaller(root->left, k1);
    if(k1<=root->key)
        cout<<root->key<<" ";
    DisplaySmaller(root->right, k1);
}
//Question 4
void NumberofNodes(Node *root, int k)
{
    if(NULL==root)
        return;
    if(k < root->key)
        NumberofNodes(root->left, k);
    if(k>root->key)
        NumberofNodes(root->right, k);
    if(k==root->key)
        inorder(root);
}
//Main 
int main()
{
    Node *root = NULL;
    int n;
    int temp;
    cout<<"Please enter the number of nodes in the tree"<<endl;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter the key of the node"<<endl;
        cin>>temp;
        root = insert(root, temp);
    }
    cout<<"The preorder traversal of the entered AVL tree is :";
    preorder(root);
    cout<<endl;
    cout<<"The inorder traversal of the entered AVL tree is :";
    inorder(root);
    cout<<endl;
    int k1, k2;
    cout<<"enter the lower bound to display range"<<endl;
    cin>>k1;
    cout<<"enter the upperbound to display range"<<endl;
    cin>>k2;
    DisplayRange(root, k1, k2);
    cout<<endl;
    cout<<"Enter the upper bound to display nodes with smaller keys"<<endl;
    cin>>k2;
    cout<<"\n";
    DisplayBigger(root, k2);
    cout<<endl;
    cout<<"Enter the lower bound to display nodes with Larger keys"<<endl;
    cin>>k2;
    cout<<"\n";
    DisplaySmaller(root, k2);
    cout<<endl;
    cout<<"Enter the key for finding the subtree of it"<<endl;
    cin>>k1;
    cout<<"\n";
    NumberofNodes(root, k1);
    return 0;
}


