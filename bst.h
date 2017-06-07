#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <iomanip>

const int INDENT_VALUE = 8;
typedef int DataType;
/**
 * Class to hold binary search trees
 *
 * Note that this binary search requires that all items be unique
 */

class BinarySearchTree {
   private:
      class Node {
         public:
            DataType data;
            Node * left;
            Node * right;
            Node * parent;

            Node():left(NULL),right(NULL),parent(NULL) {};
            Node(const DataType& item) {
               data=item;
               left=NULL;
               right=NULL;
               parent=NULL;
            };
      };
   public:
      BinarySearchTree();
      BinarySearchTree(BinarySearchTree&);

      ~BinarySearchTree();

      bool isEmpty() const;
      bool search(const DataType&) const;

      DataType getSuccessor(const DataType&) const;
      DataType getPredecessor(const DataType&) const;
      DataType getMinimum() const;
      DataType getMaximum() const;
      int getHeight() const;
      int getSize() const;

      void inorder(std::ostream&) const;
      void postorder(std::ostream&) const;
      void preorder(std::ostream&) const;

      bool insert(const DataType&);
      bool remove(const DataType&);

      void displayGraphic(std::ostream&) const;

      BinarySearchTree& operator=(const BinarySearchTree& rhs);

      void levelByLevel(std::ostream&); //BONUS level order

   private:
      Node * _root;

      void getHeightHelper(Node *, int *, int *) const;
      void getSizeHelper(Node * , int * ) const;
      void searchHelper(const DataType&, Node *, Node * &) const;
      void searchParent(const DataType&, Node *, Node * &) const;
      void getMaximumHelper(Node *, Node * &) const;
      void getMinimumHelper(Node *, Node * &) const;

      void inorderHelper(std::ostream&, Node *) const;
      void preorderHelper(std::ostream&, Node *) const;
      void postorderHelper(std::ostream&, Node *) const;

      void displayGraphicHelper(std::ostream&, const int&, Node *) const;


      void getSuccessorHelper(Node *, Node * &) const;
      void getPredecessorHelper(Node *, Node * &) const;

      void copyBinarySearchTree(Node *, Node * &);
      void deleteBinarySearchTree(Node * &);
};



#endif /* BST_H_ */
