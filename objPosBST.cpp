#include "objPosBST.h"

#include <iostream>
using namespace std;

objPosBST::objPosBST()
{
    // Constructor (Check Lecture Notes for Implementation, Simple)
    root = nullptr;
}

objPosBST::~objPosBST()
{
    // Destructor
    // Invoke delete tree, then set root to NULL
    deleteTree();
    root = nullptr;
}

void objPosBST::deleteTree(const TNode *thisNode)
{
    // Delete all nodes in the tree
    if (thisNode == nullptr)
    {
        return;
    }
    deleteTree(thisNode->left);
    deleteTree(thisNode->right);
    delete thisNode;
    // Question from Class - Which Traversal Order should you use for this method?
    //   WARNING - using the wrong one will result in potential heap error.
}

// Public Interface, Implemented
void objPosBST::deleteTree()
{
    deleteTree(root); // recursive call on the private helper function
    root = nullptr;
}

bool objPosBST::isEmptyTree() const
{
    // Check if tree is empty
    //  Really simple, think about how.
    return (root == nullptr);
}

bool objPosBST::isLeaf(const objPos &thisPos, const TNode *thisNode) const
{
    // Check if thisPos in a Leaf Node.
    //  Remember, tree nodes are inserted using the Prefix member of objPos
    if (thisNode == nullptr) // 1. if the node is NULL, just return false
    {
        return false;
    }
    if (thisPos.getPF() < thisNode->data.getPF()) // 2. Otherwise, compare Prefix of the data of the current node against the Prefix of thisPos
    {
        return isLeaf(thisPos, thisNode->left); // - If not equal, follow the BST search rules
    }
    else if (thisPos.getPF() > thisNode->data.getPF())
    {
        return isLeaf(thisPos, thisNode->right); // - If not equal, follow the BST search rules
    }
    else // - If equal, check if the node is a leaf node
    {
        return (thisNode->left == nullptr && thisNode->right == nullptr); // leaf nodes do not have children nodes
    }
}

bool objPosBST::isLeaf(const objPos &thisPos) const
{
    return isLeaf(thisPos, root);
}

void objPosBST::printTree(const TNode *thisNode) const // private recursive
{
    // Print the entire tree content using **In-Order Traversal**
    if (thisNode == nullptr)
    {
        return;
    }
    // print in the format of Prefix + Number
    // e.g.  N30 P25 etc.
    printTree(thisNode->left);
    cout << thisNode->data.getPF() << thisNode->data.getNum() << " ";
    printTree(thisNode->right);

    // DO NOT use printObjPos() as it will mess up the game display.
}

void objPosBST::printTree() const // public interface
{
    if (root == NULL)
    {
        cout << "[Empty]";
        return;
    }
    printTree(root);
}

int objPosBST::getHeight(const TNode *thisNode) const
{
    // Tree Height Calculation Algorithm

    // 1. If thisNode is null, height is zero.
    if (thisNode == nullptr)
    {
        return 0;
    }

    // 2. Otherwise, recursively invoke getHeight for the left and right subtree, and save
    //    the returned heights.
    int leftHeight = getHeight(thisNode->left);
    int rightHeight = getHeight(thisNode->right);

    // 3. Compare the two returned heights, and return the larger one.
    if (leftHeight > rightHeight)
    {
        return leftHeight + 1; // add 1 for the current node
    }
    else
    {
        return rightHeight + 1; // add 1 for the current node
    }
}

void objPosBST::printCurrentLevel(const TNode *thisNode, const int level) const
{
    // Recursive Level-Order Tree-Printing Algorithm

    // 1. First check if at leaf node.  If yes, do not print anything

    // 2. Then, check if level is 1.  If yes, print the Prefix field only (specified in manual)

    // 3. Otherwise, invoke recursively printCurrentLevel for left subtree with one less level, then
    //                                                        right subtree with one less level
    //    "if I'm not at the level, keep on searching into the left and the right subtrees"

    // You may add other character formatting features to make the tree more readable.
    // (you will be asked to demo this feature during the lab demo!!)
}

// Public Interface.
void objPosBST::printTreeLevel() const
{
    // Interface to the Recursive Version of Level-Order Tree-Printing Algorithm

    // 1. Get the height of the tree
    // 2. For each level (bounded by height), invoke the recursive tree-printing algorithm.

    // You may add other character formatting features to make the tree more readable.
    // (you will be asked to demo this feature during the lab demo!!)
}

bool objPosBST::isInTree(const objPos &thisPos, const TNode *thisNode) const
{
    // Check if thisPos in in the tree.
    //  Remember, tree nodes are inserted using the Prefix member of objPos
    if (thisNode == nullptr) // 1. if the node is NULL, just return false
    {
        return false;
    }
    if (thisPos.getPF() < thisNode->data.getPF()) // 2. Otherwise, compare Prefix of the data of the current node against the Prefix of thisPos
    {
        return isInTree(thisPos, thisNode->left); // - If not equal, follow the BST search rules
    }
    else if (thisPos.getPF() > thisNode->data.getPF())
    {
        return isInTree(thisPos, thisNode->right); // - If not equal, follow the BST search rules
    }
    else // - If equal, return true
    {
        return true;
    }
}

// Public Interface, Implemented
bool objPosBST::isInTree(const objPos &thisPos) const
{
    return isInTree(thisPos, root); // recursive call on the private helper function
}

// insert OR update!!
void objPosBST::insert(const objPos &thisPos, TNode *&thisNode)
{
    // Insert objPos as a Node into the BST
    if (thisNode == nullptr)
    {
        thisNode = new TNode(thisPos);
        return;
    }
    if (thisPos.getPF() < thisNode->data.getPF())
    {
        insert(thisPos, thisNode->left);
    }
    else if (thisPos.getPF() > thisNode->data.getPF())
    {
        insert(thisPos, thisNode->right);
    }
    else
    {
        // If the node is already in the tree (i.e. Prefix match found)
        // Add the number member of thisPos to the number member of the objPos data at the node
        int combinedNum = thisNode->data.getNum() + thisPos.getNum();
        thisNode->data.setNum(combinedNum);
    }

    // Check Lecture Notes for general implementation
    //  Hint: Algorithm similar to isInTree.

    // Modification:
    //   If the node is already in the tree (i.e. Prefix match found)
    //   Add the number member of thisPos to the number member of the objPos data at the node
    //   (DO NOT JUST IGNORE.  ADD NUMBERS!!)
}

// Public Interface, Implemented
void objPosBST::insert(const objPos &thisPos)
{
    insert(thisPos, root); // recursive call on the private helper function
}

const TNode *objPosBST::findMin(const TNode *thisNode) const
{
    // Find the node with the smallest prefix in the subtree from thisNode
    if (thisNode == nullptr)
    {
        return nullptr;
    }

    // Used as part of remove() algorithm
    while (thisNode->left != nullptr)
    {
        thisNode = thisNode->left;
    }

    return thisNode; // return the node with the smallest prefix
}

void objPosBST::remove(const objPos &thisPos, TNode *&thisNode)
{
    if (thisNode == nullptr)
    {
        return; // Node not found, do nothing
    }

    if (thisPos.getPF() < thisNode->data.getPF())
    {
        remove(thisPos, thisNode->left); // Search in the left subtree
    }
    else if (thisPos.getPF() > thisNode->data.getPF())
    {
        remove(thisPos, thisNode->right); // Search in the right subtree
    }
    else
    {
        if (thisNode->left != nullptr && thisNode->right != nullptr)
        {
            // CASE 3:Node with two children: Get the inorder successor (smallest in the right subtree)
            const TNode *successor = findMin(thisNode->right);
            thisNode->data = successor->data;         // Copy the inorder successor's content to this node
            remove(successor->data, thisNode->right); // Delete the inorder successor
        }
        else
        {
            // Node with one child or no child, CASE 1 and CASE 2
            TNode *temp = thisNode;
            if (thisNode->left != nullptr)
            {
                thisNode = thisNode->left; // Replace with left child
            }
            else
            {
                thisNode = thisNode->right; // Replace with right child or nullptr
            }
            delete temp; // Free memory of the removed node
        }
    }
}

// Public Interface, Implemented
void objPosBST::remove(const objPos &thisPos)
{
    remove(thisPos, root); // recursive call on the private helper function
}

bool objPosBST::findGreater(const int numThreshold, const TNode *thisNode) const
{
    // Determine whether any nodes in the tree has the NUMBER field of objPos data member greater than numThreshold

    // WARNING - this one is not as straightforward.

    // Algorithm Suggestion
    //  1. If tree empty, just return false
    //  2. Recursively check if the any number on the LEFT subtree is greater than numThreshold
    //  3. Recursively check if the any number on the RIGHT subtree is greater than numThreshold
    //  4. Then, check if the number field of the objPos data in the current node is greater than numThreshold
    //  5. If any of the results from item 2, 3, and 4 is TRUE, return true.
    //     Otherwise, return false.

    // HINT:  If you do this right, the algorithm is less than 10 lines.
}

bool objPosBST::findGreater(const int numThreshold) const
{
    return findGreater(numThreshold, root);
}
