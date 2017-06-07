#include <iostream>
#include "bst.h"

using namespace std;

int main()
{


    cout << "BINARY SEARCH TREE" << endl;
    BinarySearchTree * bst = new BinarySearchTree();

    //Utilizes insert node function
    cout << "Inserting: 11, 1, 6, -1, -10, 100" << std::endl;
    bst->insert(11);
    bst->insert(1);
    bst->insert(6);
    bst->insert(-1);
    bst->insert(-10);
    bst->insert(100);

    cout<<std::endl;
    cout<<std::endl;

    cout << "Displaying Tree:" << std::endl;
    bst->displayGraphic(std::cout); //Display's BST


    cout<<std::endl;
    cout<<std::endl;

    //Displays binary search tree
    cout<<"BST Pre Order: ";
        bst->preorder(std::cout); //Utilizes preorder function
    cout<<"BST In Order: ";
        bst->inorder(std::cout); //Utilizes inorder function
    cout<<"BST Post Order: ";
        bst->postorder(std::cout); //Utilizes postorder function

    cout<<std::endl;
    cout<<std::endl;

    cout<<"BST Height: ";
        cout<<bst->getHeight()<<std::endl; //Display's BST height
    cout<<"BST Size: ";
        cout<<bst->getSize()<<std::endl; //Displays BST size
    cout<<"BST Max: ";
        cout<<bst->getMaximum()<<std::endl; //Display's BST height
    cout<<"BST Min: ";
        cout<<bst->getMinimum()<<std::endl;


    cout<<std::endl;
    cout<<std::endl;



    cout<<"Removing node 11: ";
    bst->remove(11); //Utilizing the remove node function

    cout << "Displaying Tree after node removed:" << std::endl;
    bst->displayGraphic(std::cout); //Display's BST

    cout<<std::endl;
    cout<<std::endl;

    BinarySearchTree * bst2 = bst;

    cout << "Displaying Binary Tree Copy:" << std::endl;
    bst2->displayGraphic(std::cout);


    cout<<std::endl;
    cout<<std::endl;

     cout<<"***** BONUS - LEVEL BY LEVEL ******"<< std::endl;;
        bst2->levelByLevel(std::cout);

     cout<<std::endl;
     cout<<std::endl;






    return 0;
}
