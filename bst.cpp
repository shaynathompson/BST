#include "bst.h"
#include <queue>

using namespace std;

/*****************************************************************************/
/********************** Constructors *****************************************/
/*****************************************************************************/

/**
* Construct a Binary Search Tree Object
*
* Precondition: None
* Postcondition: An empty BST has been constructed
*
* Worst-Case Time Complexity: O(1)
*/

BinarySearchTree::BinarySearchTree()
{
	_root = NULL;
}

/**
* Copy consructor for a Binary Search Tree Object
*
* Precondition: Original is a Binary Search Tree
* Postcondition: An empty BST has been constructed
*
* Worst-Case Time Complexity: O(1)
*/

BinarySearchTree::BinarySearchTree(BinarySearchTree& original)
{
	_root = new Node();
	//std::cout << original._root << "||" << &original._root << "||" << original._root << std::endl;
	copyBinarySearchTree(original._root, _root);
}

/*****************************************************************************/
/********************** Destructor *******************************************/
/*****************************************************************************/

/**
* Destructor for a Binary Search Tree
*
* Precondition: The life of the binary search tree is over
* Postcondition: Memory used by the binary search tree is freed
*
* Worst-Case Time Complexity: O(n)
*/

BinarySearchTree::~BinarySearchTree()
{
	deleteBinarySearchTree(_root);
}

/*****************************************************************************/
/********************** Accessors ********************************************/
/*****************************************************************************/

/**
* Check if the Binary Search Tree is empty
*
* Precondition: None
* Postcondition: Return true if the Binary Search Tree is empty and false
*    otherwise
*
* Worst-Case Time Complexity
*/

bool BinarySearchTree::isEmpty() const
{
	return (_root==NULL);
}

/**
* Search the binary search tree for an item
*
* Precondition: None
* Postcondition: Returns true if item found, and false otherwise
*
* Worst-Case Time Complexity: O(h), where h is the height of the tree
*/

bool BinarySearchTree::search(const DataType& item) const
{

	// TODO
	Node * itemLocation;

	searchHelper(item, _root, itemLocation);

	if(itemLocation == NULL) { //item is not found
        return false;
	}
	return true; //item is found

}

/**
* Search the binary search tree for an item
*
* Precondition: subtreePtr points to a subtree of this binary search tree
* Postcondition: Set itemLocation to point to the item if it is found and to
*    NULL otherwise
*
* Worst-Case Time Complexity: O(h), where h is the height of the tree
*/

void BinarySearchTree::searchHelper(const DataType& item, Node * subtreePtr, Node * &itemLocation) const
{
	// if this is an empty binary search tree, return null
	if (subtreePtr==NULL) {
		itemLocation = NULL;
		return;
	}

	// if this is the item we are looking for, return this item
	if (subtreePtr->data==item) {
		itemLocation = subtreePtr;
		return;
	}

	// look for the parent of the specified item
	Node * parent = NULL;
	searchParent(item, subtreePtr, parent);

	// return the appropriate child
	if (item < parent->data) {
		itemLocation = parent->left;
	} else {
		itemLocation = parent->right;
	}
}

/**
* Search the binary tree for the parent for an item
*
* Precondition: subtreePtr points to a subtree of this binary search tree
* Postcondition: Sets itemLocation to point to the direct parent of the node
*    that contains item OR sets itemLocation to point to the node that will be
*    the parent of a node that contains item if item is inserted into the tree
*
* Worst-Case Time Complexity: O(h), where h is the height of the tree
*/

void BinarySearchTree::searchParent(const DataType& item, Node * subtreePtr, Node * &parentLocation) const
{
	// if this is an empty tree return NULL
	if (subtreePtr==NULL) {
		parentLocation = NULL;
		return;
	}

	// if we have found what we are looking for, then return
	if (item==subtreePtr->data) {
		parentLocation = subtreePtr->parent;
		return;
	}

	// holds a pointer to the next subtree that we will look at
	Node * nextSubtree = NULL;

	if (item < subtreePtr->data) { // smaller items in left subtree
		nextSubtree = subtreePtr->left;
	} else { // larger items in right subtree
		nextSubtree = subtreePtr->right;
	}

	if (nextSubtree==NULL) {
		parentLocation = subtreePtr;
	} else {
		searchParent(item,nextSubtree, parentLocation);
	}
}

/**
* Search the binary tree for the inorder successor of item. If the item is not
* present in the tree, then return a garbage value
*
* Precondition: None
* Postcondition: Returns the inorder successor of the node containing item.
*
* Worst-Case Time Complexity: O(h), where h is the height of the tree
*/

DataType BinarySearchTree::getSuccessor(const DataType& item) const
{
	// find the item in the tree
	Node * location = NULL;
	searchHelper(item,_root,location);

	if (location == NULL) { // item not in BST
		DataType garbage;
		return garbage;
	}

	Node * successor = NULL;
	getSuccessorHelper(location,successor);

	if (successor != NULL) {
		return successor->data;
	} else {
		DataType garbage;
		return garbage;
	}
}

/**
* Search the binary tree for the inorder successor of the node, item
*
* Precondition: item points to a node in the binary search tree.
*    succLocation points to NULL
* Postcondition: succLocation points to the inorder successor of item in the
*    binary search tree
*
* Worst-Case Time Complexity: O(h), where h is the height of the tree
*/

void BinarySearchTree::getSuccessorHelper(Node * item, Node * &succLocation) const
{
	if (item->right==NULL) { // successor is an ancestor
		succLocation = item->parent;
		while (succLocation!=NULL && succLocation->data<item->data) {
			succLocation=succLocation->parent;
		}
	} else { // successor is a descendant
		getMinimumHelper(item->right,succLocation);
	}
}

/**
* Search the binary tree for the inorder predecessor of item. If the item is
* not present in the tree, then return a garbage value
*
* Precondition: None
* Postcondition: Returns the inorder predecessor of item
*
* Worst-Case Time Complexity: O(h), where h is the height of the tree
*/

DataType BinarySearchTree::getPredecessor(const DataType& item) const
{
	// find the item in the tree
	Node * location = NULL;
	searchHelper(item,_root,location);

	if (location == NULL) { // item not in BST
		DataType garbage;
		return garbage;
	}

	Node * predecessor = NULL;
	getPredecessorHelper(location,predecessor);

	if (predecessor != NULL) {
		return predecessor->data;
	} else {
		DataType garbage;
		return garbage;
	}
}

/**
* Search the binary tree for the inorder predecessor of the node, item
*
* Precondition: item points to a node in the binary search tree.
*    predLocation points to NULL
* Postcondition: predLocation points to the inorder predecessor of item in the
*    binary search tree
*
* Worst-Case Time Complexity: O(h), where h is the height of the tree
*/

void BinarySearchTree::getPredecessorHelper(Node * item, Node * &predLocation) const
{
	if (item->left==NULL) { // predecessor is an ancestor
		predLocation = item->parent;
		while (predLocation!=NULL && predLocation->data>item->data) {
			predLocation=predLocation->parent;
		}
	} else { // predecessor is a descendant
		getMaximumHelper(item->left,predLocation);
	}
}

/**
* Determine the maximum item in the binary search tree
*
* Precondition: None
* Postcondition: Return the maximum value held in the binary search. If the
*    tree is empty then a garbage value is returned
*
* Worst-case time Complexity: O(h), where h is the height of the tree
*/

DataType BinarySearchTree::getMaximum() const
{
	// TODO

	Node * maxLocation = NULL;
	getMaximumHelper(_root, maxLocation);

	if(maxLocation != NULL) {
        return maxLocation->data; //returns the max value in the BST
	}
	else { //returns garbage value if BST is empty
        DataType garbage;
        return garbage;
	}
}

/**
* Determine the maximum item for the subtree rooted at subtreeRoot
*
* Precondition: subtreeRoot is a node in the binary seach tree.
*    maxLocation points to null
* Postcondition: maxLocation points to the maximum item in the subtree
*    rooted at subtreeRoot (points to NULL for an empty subtree)
*
* Worst-case time Complexity: O(h), where h is the height of the tree
*/

void BinarySearchTree::getMaximumHelper(Node * subtreeRoot, Node * &maxLocation) const
{
	// TODO
	if ( subtreeRoot->right == 0) { // maximum is found
        maxLocation = subtreeRoot;
        return;
	}
	else getMaximumHelper(subtreeRoot->right, maxLocation); // search the right of the tree for maximum
}

/**
* Determine the minimum item in the binary search tree
*
*    tree is empty then a garbage value is returned
*
* Worst-case time Complexity: O(h), where h is the height of the tree
*/

DataType BinarySearchTree::getMinimum() const
{
	// TODO
    Node * minLocation = NULL;
	getMinimumHelper(_root, minLocation);

	if(minLocation != NULL) { //minimum value in BST is found
        return minLocation->data;
	}
	else { //BST is empty so return garbage value
        DataType garbage = 0;
        return garbage;
	}
}

/**
* Determine the minimum item for the subtree rooted at subtreeRoot
*
* Precondition: subtreeRoot is a node in the binary seach tree.
*    minLocation points to null
* Postcondition: minLocation points to the minimum item in the subtree
*    rooted at subtreeRoot (points to NULL for an empty subtree)
*
* Worst-case time Complexity: O(h), where h is the height of the tree
*/

void BinarySearchTree::getMinimumHelper(Node * subtreeRoot, Node * &minLocation) const
{
	// TODO
	if ( subtreeRoot->left == 0) { // minimum is found
        minLocation = subtreeRoot;
        return;
	}
	else getMinimumHelper(subtreeRoot->left, minLocation); // search the left for data


}

/**
* Determine the number of levels in a binary search tree. For example,
* a binary tree with a single node has height 1 and a binary tree
* with a root and a single child has height 2
*
* Precondition: none
* Postcondition: Return the number of levels in this binary search tree
*
* Worst-Case Time Complexity: O(n)
*/

int BinarySearchTree::getHeight() const
{
	// TODO
	int curHeight = 0; //initializes temp variable currentHeight
	int totHeight = 0; //initializes total height variable

	getHeightHelper(_root, &curHeight, &totHeight);

	return totHeight; //returns total height
}

void BinarySearchTree::getHeightHelper(Node * subtreeRoot, int * curHeight, int * totHeight) const
{
    *curHeight = *curHeight + 1; //add one to each call of the function

	if ( subtreeRoot != 0) { //if the BST is not empty
        if ( *curHeight > *totHeight) {
            *totHeight = *curHeight; //set to maximum height found
        }

        getHeightHelper(subtreeRoot->left, curHeight, totHeight);//height of left subtree
        getHeightHelper(subtreeRoot->right, curHeight, totHeight);//height of right subtree
	}
	*curHeight = *curHeight - 1; //remove auto increment from the start
}

/**
* Determine the number of vertices in the binary search tree.
*
* Precondition: none
* Postcondition: Return the number of vertices in this binary search tree
*
* Worst-Case Time Complexity: O(n)
*/

int BinarySearchTree::getSize() const
{
	// TODO
	int treeSize = 0;
	getSizeHelper(_root, &treeSize); //uses helper function to get size
	return treeSize;
}

void BinarySearchTree::getSizeHelper(Node * subtreeRoot, int * treeSize) const
{
    if ( subtreeRoot != 0 ) { //if BST is not empty
      getSizeHelper( subtreeRoot->left , treeSize); //gets size of left subtree
      *treeSize = *treeSize + 1;
      getSizeHelper( subtreeRoot->right , treeSize ); //gets size of right subtree
   }
}
/*****************************************************************************/
/********************** Traversals *******************************************/
/*****************************************************************************/

/**
* Inorder traversal of Binary Search Tree
*
* Precondition: ostream out is open
* Postcondition: Binary Search Tree has been inorder traversed and values in
*    nodes have been output to out
*
* Worst-Case Time Complexity: O(n)
*/

void BinarySearchTree::inorder(std::ostream& out) const
{
	// TODO
    inorderHelper(out, _root);
    out << std::endl;
}

/**
* Inorder traversal helper function
*
* Precondition: ostream out is open. subtreePtr points to a subtree of
*    this binary search tree
* Postcondition: subtree with root pointed to by subtreePtr has been output
*    to output
*
* Worst-Case Time Complexity: O(n)
*/

void BinarySearchTree::inorderHelper(std::ostream& out, Node * subtreePtr) const
{
	// TODO
    if ( subtreePtr != 0 ) {
      inorderHelper( out, subtreePtr->left ); //traverses the left subtrees
      out << subtreePtr->data << ", ";
      inorderHelper( out, subtreePtr->right ); //traverses the right subtrees
   }
}

/**
* Preorder traversal of Binary Search Tree
*
* Precondition: ostream out is open
* Postcondition: Binary Search Tree has been preorder traversed and values in
*    nodes have been output to out
*
* Worst-Case Time Complexity: O(n)
*/

void BinarySearchTree::preorder(std::ostream& out) const
{
	// TODO
	preorderHelper( out, _root );
	out << std::endl;
}

/**
* Preorder traversal helper function
*
* Precondition: ostream out is open. subtreePtr points to a subtree of
*    this binary search tree
* Postcondition: subtree with root pointed to by subtreePtr has been output
*    to output
*
* Worst-Case Time Complexity: O(n)
*/

void BinarySearchTree::preorderHelper(std::ostream& out, Node * subtreePtr) const
{
	// TODO
   if ( subtreePtr != 0 ) {
      out << subtreePtr->data << ", ";
      preorderHelper( out, subtreePtr->left ); //traverses left subtrees
      preorderHelper( out, subtreePtr->right );//traverses right subtrees
   }
}

/**
* Postorder traversal of Binary Search Tree
*
* Precondition: ostream out is open
* Postcondition: Binary Search Tree has been postorder traversed and values in
*    nodes have been output to out
*
* Worst-Case Time Complexity: O(n)
*/

void BinarySearchTree::postorder(std::ostream& out) const
{
	// TODO
	postorderHelper( out, _root );
	out << std::endl;
}

/**
* Postorder traversal helper function
*
* Precondition: ostream out is open. subtreePtr points to a subtree of
*    this binary search tree
* Postcondition: subtree with root pointed to by subtreePtr has been output
*    to output
*
* Worst-Case Time Complexity: O(n)
*/

void BinarySearchTree::postorderHelper(std::ostream& out, Node * subtreePtr) const
{
	// TODO
	if ( subtreePtr != 0 ) {
      postorderHelper( out, subtreePtr->left ); //traverses left subtree
      postorderHelper( out, subtreePtr->right ); //traverses right subtree
      out << subtreePtr->data << ", ";
   }
}

/*****************************************************************************/
/********************** Operations *******************************************/
/*****************************************************************************/

/**
* Insert item into the binary search tree
*
* Precondition: item is not present in the binary search tree
* Postcondition: Binary search tree has been modified with the item inserted
*    at the proper position to maintain the binary search tree property.
*    Returns true if item is inserted into the tree and false otherwise
*
* Worst-Case Time Complexity: O(h), where h is the height of the tree
*/

bool BinarySearchTree::insert(const DataType& item)
{
	// create a  new node
	Node * newNode = new Node(item);

	// if we are inserting into an empty tree
	if (_root==NULL) {
		_root = newNode;
		return true;
	}

	// if the item is the root of the tree
	if (_root->data==item) {
		delete newNode;
		return false;
	}

	// find the parent of the item
	Node * parentLocation = NULL;
	searchParent(item,_root,parentLocation);

	// add the new node to the tree, if it is not already there
	if (item < parentLocation->data) { // left child
		if (parentLocation->left!=NULL) {
			delete newNode;
			return false;
		}
		parentLocation->left = newNode;
	} else { // right child
		if (parentLocation->right!=NULL) {
			delete newNode;
			return false;
		}
		parentLocation->right = newNode;
	}

	// set the parent of the new node
	newNode->parent = parentLocation;

	return true;
}

/**
* Remove item from the binary search tree
*
* Precondition: none
* Postcondition: binary search tree has been modified with  the item
*    removed, if present. binary search tree property is maintained.
*    returns true if insertion is successful and false otherwise.
*
* Worst-Case Time Complexity: O(h), where h is the height of the tree
*/

bool BinarySearchTree::remove(const DataType& item)
{
	// find the item in the binary search tree
	Node * itemLocation = NULL;
	searchHelper(item,_root,itemLocation);

	// determine the item is in the binary search tree
	if (itemLocation==NULL) {
		return false;
	}

	// get the parent of the item to be deleted
	Node * itemParent = itemLocation->parent;

	// The node containing item has 2 children
	if (itemLocation->left != NULL && itemLocation->right!=NULL) {
		// Find the inorder successor node of item
		Node * itemSuccessor = NULL;
		getSuccessorHelper(itemLocation, itemSuccessor);

		// copy the data
		itemLocation->data = itemSuccessor->data;

		// redirect the itemLocation pointer to the successor
		// since that is now what will be deleted
		itemParent = itemSuccessor->parent;
		itemLocation = itemSuccessor;

		itemLocation->data = DataType();
	}

	// We now know that the item being deleted has 0 or 1 children

	// determine which subtree, if any, has children
	Node * itemSubtree = itemLocation->left;
	if (itemSubtree == NULL) {
		itemSubtree = itemLocation->right;
	}

	if (itemParent == NULL) { // root being deleted
		_root = itemSubtree;
		if (_root!=NULL) {
			_root->parent=NULL;
		}
	} else if (itemParent->left == itemLocation) {
		itemParent->left = itemSubtree;
	} else {
		itemParent->right = itemSubtree;
	}

	if (itemSubtree!=NULL) {
		itemSubtree->parent = itemParent;
	}

	// free the memory for this item
	delete itemLocation;

	return true;
}

/*****************************************************************************/
/********************** Input/Output *****************************************/
/*****************************************************************************/

/**
* Graphic output of binary search tree
*
* Precondition: ostream out is open
* Postcondition: Graphical representation of binary search tree has been
*    output to out.
*
* Worst-Case Time Complexity: O(n)
*/

void BinarySearchTree::displayGraphic(std::ostream& out) const
{
	displayGraphicHelper(out,0,_root);
}

/**
* Graphic output of binary search tree helper function
*
* Precondition: ostream out is open. subtreePtr points to a subtree of
*    this binary search tree
* Postcondition: Graphical representation of subtree with root pointed to
*    by subtreePtr has been output to out, indented indent spaces.
*
* Worst-Case Time Complexity: O(n)
*/

void BinarySearchTree::displayGraphicHelper(std::ostream& out, const int& indent, Node * subtreePtr) const
{
	if (subtreePtr==NULL) {
		return;
	}

	displayGraphicHelper(out,indent+INDENT_VALUE, subtreePtr->right);
	out << std::setw(indent) << " " << subtreePtr->data << std::endl;
	displayGraphicHelper(out,indent+INDENT_VALUE, subtreePtr->left);
}

/*****************************************************************************/
/********************** Operators ********************************************/
/*****************************************************************************/

/**
* Assign a copy of a binary search tree object to the current object
*
* Preconditions: N/A
* Postconditions: A copy of rhs has been assigned to this object. A const
*    reference to this binary search tree is returned.
*
* Worst-Case Time Complexity: O(n)
*/

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& rhs)
{
	if (this == &rhs) {
		return *this;
	}

	copyBinarySearchTree(rhs._root, _root);

	return *this;
}

/*****************************************************************************/
/********************** Functions ********************************************/
/*****************************************************************************/

/**
* Copy the Binary Search Tree rooted at original
*
* Preconditions: original is a Binary Search Tree
* Postcondition: copy holds a copy of the Binary Search Tree
*
* Worst-Case Time Complexity: O(n)
*/

void BinarySearchTree::copyBinarySearchTree(Node * original, Node * &copy)
{
	// ensure that any memory allocated by the copy is properly freed
	deleteBinarySearchTree(copy);

	// TODO
	if(original != NULL) {

       insert(original->data); //inserts node

       if(original->left != NULL)
        copyBinarySearchTree(original->left,copy->left); //copies left subtree nodes
       if(original->right != NULL)
        copyBinarySearchTree(original->right,copy->right); //copies right subtree nodes
   }
   else   {
       copy = new Node;
   }
}

/**
* Delete the Binary Search Tree rooted at bstRoot
*
* Preconditions: The life of the Binary Search Tree rooted at bstRoot is over
* Postconditions: Memory used by the Binary Search Tree rooted at bstRoot is
*    freed
*
* Worst-Case Time Complexity: O(n)
*/

void BinarySearchTree::deleteBinarySearchTree(Node * &bstRoot)
{
	// TODO

    if( bstRoot != NULL )
            remove(bstRoot->data); //utilizes the remove function to delete the binary search tree


}

/*BONUS - levelByLevel() to traverse a tree level by level;
that is, first visit the root, then all nodes on level 1 (children of the root), then all nodes on level 2, and so on.
Nodes on the same level should be visited in order from left to right*/

void BinarySearchTree::levelByLevel(std::ostream& out)
{

    if (_root == NULL) //if BST is not empty
        return;


    queue <Node *> q; //creates queue


    q.push(_root); //pushs root node in the queue

    while (q.empty() == false) // repeats once queue is empty
    {

        Node * subtreePtr = q.front();
        //out << std::setw(indent) << " " << subtreePtr->data << std::endl;
        out << subtreePtr->data << ", "; //prints the node in front of the queue

        q.pop(); //removes node from queue after printing it

        /*Puts left subtree in queue if not empty*/
        if (subtreePtr->left != NULL)
            q.push(subtreePtr->left);

        /*Puts right subtree in queue if not empty*/
        if (subtreePtr->right != NULL)
            q.push(subtreePtr->right);
    }
}


