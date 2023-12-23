#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node *left;
    Node *right;
    Node *parent;
    char color;
    Node(int data)
    {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->color = 'R';
    }
};
class RedBlackTree
{
private:
    Node *root;
    bool ll;
    bool rr;
    bool rl;
    bool lr;
public:
    RedBlackTree()
    {
        root = nullptr;
        ll = rr = rl = lr = false;
    }
    void insert(int value)
    {
        if (root == nullptr)
        {
            root = new Node(value);
            root -> color = 'B';
        }
        else 
        {
            root = insertHelper(root, value);
        }
    }
    Node* insertHelper(Node* root, int value)
    {
        bool f = false; // flag to check red-red conflict
        if (root == nullptr)
        {
            return new Node(value);
        }
        else if (value < root -> data)
        {
            root -> left = insertHelper(root -> left, value);
            root -> left -> parent = root;
            if (root != this -> root)
            {
                if (root -> color == 'R' && root -> left -> color == 'R')
                {
                    f = true;
                }
            }
        }
        else 
        {
            root -> right = insertHelper(root -> right, value);
            root -> right -> parent = root;
            if (root != this -> root)
            {
                if (root -> color == 'R' && root -> right -> color == 'R')
                {
                    f = true;
                }
            }
        }


        // apply rotations
        if (ll)
        {
            root = leftRotate(root);
            root -> color = 'B';
            root -> left -> color = 'R';
            ll = false;
        }
        else if (rr)
        {
            root = rightRotate(root);
            root -> color = 'B';
            root -> right -> color = 'R';
            rr = false;
        }
        else if (rl)
        {
            root -> right = rightRotate(root -> right);
            root -> right -> parent = root;
            root = leftRotate(root);
            root -> color = 'B';
            root -> left -> color = 'R';
            rl = false;
        }
        else if (lr)
        {
            root -> left = leftRotate(root -> left);
            root -> left -> parent = root;
            root = rightRotate(root);
            root -> color = 'B';
            root -> right -> color = 'R';
            lr = false;
        }




        // Handle red-red conflicts
        if (f)
        {
            // if node is inserted on the right side
            if (root -> parent -> right == root)
            {
                // if color of sibling of parent of newly inserted node is black apply rotations
                if (root -> parent -> left == nullptr || root -> parent -> left -> color == 'B')
                {
                    // if node is inserted on the left side of the red node
                    if (root -> left != nullptr && root -> left -> color == 'R')
                    {
                        rl = true;
                    }
                    // if node is inserted on the right side of the red node
                    else if (root -> right != nullptr && root -> right -> color == 'R')
                    {
                        ll = true;
                    }
                }
                else
                {
                    root -> parent -> left -> color = 'B';
                    root -> color = 'B';
                    if (root -> parent != this -> root)
                    {
                        root -> parent -> color = 'R';
                    }
                }
            }
            else
            {
                // if sibling color of parent of newly inserted node is black apply rotations
                if (root -> parent -> right == nullptr || root -> parent -> right -> color == 'B')
                {
                    // if node is inserted in the left side of red node
                    if (root -> left != nullptr && root -> left -> color == 'R')
                    {
                        rr = true;
                    }
                    // if node is inserted on the right side of red node
                    else if (root -> right != nullptr && root -> right -> color == 'R')
                    {
                        lr = true;
                    }
                }
                else // if sibling color of parent is red change the color of nodes till root
                {
                    root -> parent -> right -> color = 'B';
                    root -> color = 'B';
                    if (root -> parent != this -> root)
                    {
                        root -> parent -> color = 'R';
                    }
                }

            }
            f = false;
        }
            return root;
    }
    Node* rightRotate(Node* node)
    {
        Node* x = node -> left;
        Node* y = x -> right;
        node -> left = y;
        x -> right = node;
        node -> parent = x;
        if (y != nullptr)
        {
            y -> parent = node;
        }
        return x;
    }
    Node* leftRotate(Node* node)
    {
        Node* x = node -> right;
        Node* y = x -> left;
        x -> left = node;
        node -> right = y;
        node -> parent = x;
        if ( y != nullptr)
        {
            y -> parent = node;
        }
        return x;
    }
    void inorderTraversal(Node* root)
    {
        if (root != nullptr)
        {
            inorderTraversal(root -> left);
            cout << root -> data << " ";
            inorderTraversal(root -> right);
        }
    }
    void printTree(Node* root, int space)
    {
        if (root != nullptr)
        {
            space += 10;
            printTree(root -> right, space);
            cout << endl;
            for (int i = 10; i < space; i++)
            {
                cout << " ";
            }
            cout << root -> data << endl;
            printTree(root -> left, space);
        }
    }
    void print()
    {
        printTree(root, 0);
    }
    void inorder()
    {
        inorderTraversal(root);
    }
};
int main()
{
    RedBlackTree t;
    int arr[] = {1, 4, 6, 3, 5, 7, 8, 2, 9};
    for (int i = 0; i < 9; i++)
    {
        t.insert(arr[i]);
        cout << endl;
        t.inorder();
    // cout << "heloo";
    }
    t.print();
}