//
// Created by Ryan  Martino on 4/21/19.
//

#ifndef CS415PROJECT3_TT_H
#define CS415PROJECT3_TT_H
#include<iostream>
#include <string>
#include <vector>
#include <fstream>
#include<assert.h>

using namespace std;
class TT {
public:
    //BST();

    void contains() const;

    bool isEmpty();

    void printTree(ostream &out = cout) const;

    void buildTree(ifstream &input);

private:
    struct node {
        node(const string &x, node *l, node * m, node *r)
                : key(x), left(l),middle(m), right(r) {
            lines.resize(0);
        }

        string key;
        node *left;
        node* middle;
        node *right;
        vector<int> lines;
    };

    node *root;

    void insertHelper(const string &X, int line, node *&t, int &distWords);

    bool containsHelper(const string &x, node *t, node *&result) const;

    void printTreeHelper(node *t, ostream &out) const;

    int findHeight(node *t);
// 2-3 tree node (complete)
/*template <class elemType>
struct nodeType {
    elemType dataLeft;             // data item on "left" side of node
    elemType dataRight;            // data item on "right" side of node
    short numData;                 // number of data items (1 or 2)
    nodeType<elemType> *left;      // pointer to left subtree
    nodeType<elemType> *middle;    // pointer to middle subtree
    nodeType<elemType> *right;     // pointer to right subtree
    nodeType<elemType> *parent;    // pointer to parent (may not need)
};

// 2-3 tree class (start)
template <class elemType>
class TT {
    nodeType<elemType> *root;
    void doInorder (nodeType<elemType> *) const;

    // add in other methods here, if needed
    void auxilary(nodeType<elemType> *, const elemType);  //recursive helper for insertion
    elemType* promote(const elemType, const elemType, const elemType);   //sort the three elements passed in
    nodeType<elemType>* splitNode(nodeType<elemType>*, nodeType<elemType>*, const int); //split node
    void insertSecondItem(nodeType<elemType>*, const elemType); //insert a new item to a 2-node
    bool isLeaf(nodeType<elemType>*) const;   //check if the node is leaf
    int posChild(const nodeType<elemType>*, const nodeType<elemType>*) const;  //check if a node is parent's left, middle, or right child
    void printNode(nodeType<elemType>*) const;   //print a node's value(s)
    nodeType<elemType>* instantiate(const elemType); //create a new node, initialize all crucial values

public:
    TT () {root = NULL;};              // constructor
    void insert (const elemType);                // insert an item
    void inorder () const {doInorder (root);     // inorder traversal
        cout << endl;};
    void display () const;                       // display the tree
};
*/
};
#endif //CS415PROJECT3_TT_H
