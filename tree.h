#include <iostream>
#include <vector>
#include <algorithm>

// node
struct node
{
    int data;
    node *left;
    node *right;
};

class Tree
{
private:
    std::vector<node *> children;
    node *root = nullptr;

public:
    void insert(int value);
    bool empty() const;
    void balanceTree();
    int size() const;
    int getHeight(bool side) const;
    void display() const;
};

// get size of tree
int Tree::size() const
{
    int leftHeight = getHeight(0);  // left subtree
    int rightHeight = getHeight(1); // right subtree

    int sum = leftHeight + rightHeight;

    if (root)
        sum += 1;

    return sum;
}

// check if tree is empty
bool Tree::empty() const
{
    return root ? false : true;
}

// get height of subtrees
// if side = 1 that means right substree
// if side = 0 that means left substree
int Tree::getHeight(bool side) const
{
    int count = 0;
    node *pre = root;
    node *cur = root;

    while (cur != nullptr)
    {
        pre = cur;
        if (side == 0)
            cur = cur->left;
        else
            cur = cur->right;

        if (pre != root)
            count++;
        if (cur == nullptr)
        {
            cur = pre;
            if (cur == root)
                cur = nullptr;
            else
            {
                if (side == 0)
                    cur = cur->right;
                else
                    cur = cur->left;
            }
        }
    }

    return count;
}

// display children of trees
void Tree::display() const
{
    node *cur = root;

    std::cout << "Right subtree" << std::endl;
    while (cur != nullptr)
    {
        std::cout << cur->data << "->";
        cur = cur->right;
    }
    std::cout << std::endl
              << std::endl;

    cur = root;

    std::cout << "Left subtree" << std::endl;
    while (cur != nullptr)
    {
        std::cout << cur->data << "->";
        cur = cur->left;
    }
    std::cout << std::endl;
}

// function for std::sort
bool pComp(node *a, node *b) { return a->data < b->data; }

// insert node to tree
void Tree::insert(const int value)
{

    node *temp = new node;
    temp->data = value;

    if (root == nullptr)
        root = temp;
    else
    {
        node *cur = root;
        node *pre = root;

        if (value > root->data)
        {
            while (cur != nullptr)
            {
                pre = cur;
                cur = cur->right;
            }
        }
        else
        {
            while (cur != nullptr)
            {
                pre = cur;
                cur = cur->left;
            }
        }

        if (value > pre->data)
            pre->right = temp;
        else
            pre->left = temp;
    }
    children.push_back(temp);

    int leftHeight = getHeight(0);  // get height of left subtree
    int rightHeight = getHeight(1); // get height of right subtree

    node *pre = root;
    node *cur = root;

    std::sort(children.begin(), children.end(), pComp); // sort vector of pointers

    if (rightHeight - leftHeight == 2 || leftHeight - rightHeight == 2)
    {
        balanceTree();
    }
};

void Tree::balanceTree()
{
    root = nullptr;
    std::vector<node *> copy;

    for (int i = 0; i < children.size(); i++)
        copy.push_back(children[i]);

    while (children.size() > 0)
    {
        int mid = children.size() / 2;
        children[mid]->left = nullptr;
        children[mid]->right = nullptr;

        if (root == nullptr)
        {
            root = children[mid];
        }
        else
        {
            node *cur = root;
            node *pre = root;

            if (children[mid]->data > root->data)
            {
                while (cur != nullptr)
                {
                    pre = cur;
                    cur = cur->right;
                }
            }
            else
            {
                while (cur != nullptr)
                {
                    pre = cur;
                    cur = cur->left;
                }
            }

            if (children[mid]->data > pre->data)
                pre->right = children[mid];
            else
                pre->left = children[mid];
        }

        children.erase(children.begin() + mid);
    }
    children = copy;
}