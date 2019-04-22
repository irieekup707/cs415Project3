//
// Created by Ryan  Martino on 4/21/19.
//
#include"TT.h"
#include<iostream>
#include<vector>
#include<iomanip>

using namespace std;
/*
//check if a node is leaf
template <class elemType>
bool TT<elemType> :: isLeaf(nodeType<elemType>* n) const{
    //pre: a node pointer
    //post: return boolean of whether the node has no children at all
    return (n->left == NULL && n->right == NULL && n->middle == NULL);
}

//print out a node's value(s)
template <class elemType>
void TT<elemType> :: printNode(nodeType<elemType>* n) const{
    //pre: a node pointer
    //post: output the node's data item(s)
    if (n!= NULL){  //print guard
        if (n->numData == 1) cout << n->dataLeft << " ";
        else cout << n->dataLeft << " " << n->dataRight << " ";
    }
}

//print all nodes' values in the tree form
template <class elemType>
void TT<elemType> :: display() const{
    //pre: none
    //post: output the tree's values, in the form of their original hierarchies
    if (root == NULL) cout << "Empty tree.";    //print guard
    else {
        vector<nodeType<elemType>*> v;  //list to print
        vector<nodeType<elemType>*> c;  //list to hold children of v, for later use
        v.push_back(root);  //first level
        while (!v.empty()){
            for (int i = 0; i< v.size(); i++){  //print all nodes
                cout << setw(3); printNode(v[i]); cout << ", ";
            }
            cout << endl;   //end this level
            for (int i = 0; i < v.size(); i++){ //find children of nodes in v
                if(v[i]->left) c.push_back(v[i]->left);
                if(v[i]->middle) c.push_back(v[i]->middle);
                if(v[i]->right) c.push_back(v[i]->right);
            }
            v.clear(); v.swap(c); c.clear();    //clear v, make children print-ready
        }
    }
    cout << endl;
}

//output the inorder traversal of the tree
template <class elemType>
void TT<elemType> :: doInorder(nodeType<elemType>* n) const{
    //pre: a node pointer; function will do inorder starting from this node; recursively
    //post: an output of the inorder traversal result
    //left, parent, right
    if (root == NULL){  //print guard
        cout << "Empty tree." << endl;
    } else if (isLeaf(n)){    //the base case; if n is leaf
        printNode(n);
    } else {
        doInorder(n->left);  //inorder left child
        cout << n->dataLeft << " ";  //parent left data
        if (n->middle){
            doInorder(n->middle);    //inorder middle child
            cout << n->dataRight << " "; //parent right data
        }
        doInorder(n->right); //inorder right child
    }
}

//create a new node, initialize all crucial values
template <class elemType>
nodeType<elemType>* TT<elemType> :: instantiate(const elemType x){
    //pre: the initial value the node holds
    //post: a pointer to the newly created node
    nodeType<elemType> *node = new nodeType<elemType>;
    node->dataLeft = x;
    node->numData = 1;
    node->left = node->middle = node->right = node->parent = NULL;
    return node;
}

//insert an item to the tree
template <class elemType>
void TT<elemType> :: insert(const elemType x){
    //pre: the value to insert to the tree
    //post: value is inserted
    //if empty tree
    if (root == NULL){
        root = instantiate(x);
        //if has only 1 node
    } else if (isLeaf(root)){
        if (root->numData == 1){    //if it's a 2-node
            insertSecondItem(root, x);
        } else {    //it's a 3-node
            root = splitNode(root, instantiate(x), 0);
        }
        //other conditions
    } else {
        auxilary(root, x);
    }
}

//sort the three elements passed in
template <class elemType>
elemType* TT<elemType> :: promote(const elemType m, const elemType n, const elemType x){
    //pre: the three elements; m, n should be old node's values, x should be new value
    //post: a pointer to the sorted array
    elemType* middle = new elemType[3];
    if (x < m){ //m is the median
        middle[0] = x; middle[1] = m; middle[2] = n;
    } else if (x > n){  //n is the median
        middle[0] = m; middle[1] = n; middle[2] = x;
    } else{ //x is the median
        middle[0] = m; middle[1] = x; middle[2] = n;
    } return middle;
}

//split the node passed in
template <class elemType>
nodeType<elemType>* TT<elemType> :: splitNode(nodeType<elemType>* n, nodeType<elemType>* x, const int pos){
    //pre: a pointer to the node to split, the node that causes the split, and where the split causer comes from (left, middle, right = 0, 1, 2)
    //post: a pointer to the top-most node of manipulated subtree
    nodeType<elemType>* nodeCache[4];    //cache children of nodes passed in
    //rearrange the position of these children for later hook up
    if (pos == 0){   //x left, x right, n middle, n right
        nodeCache[0] = x->left; nodeCache[1] = x->right;
        nodeCache[2] = n->middle; nodeCache[3] = n->right;
    } else if (pos == 2){   //n left, n middle, x left, x right
        nodeCache[0] = n->left; nodeCache[1] = n->middle;
        nodeCache[2] = x->left; nodeCache[3] = x->right;
    } else {    //n left, x left, x right, n right
        nodeCache[0] = n->left; nodeCache[1] = x->left;
        nodeCache[2] = x->right; nodeCache[3] = n->right;
    }
    elemType *middle = promote(n->dataLeft, n->dataRight, x->dataLeft); //sort the passed nodes' values
    //reuse nodes to prevent memory leak
    nodeType<elemType> *promo = instantiate(middle[1]);   //new promoted node
    nodeType<elemType> *l = instantiate(middle[0]); //left child
    nodeType<elemType> *r = instantiate(middle[2]); //right child
    //parental relationship of first relative level
    promo->left = l; promo->right = r;
    l->parent = promo; r->parent = promo;
    //parental relationship of second relative level; hook up cached nodes
    if (nodeCache[0] != NULL){
        l->left = nodeCache[0]; l->right = nodeCache[1];
        nodeCache[0]->parent = nodeCache[1]->parent = l;
        r->left = nodeCache[2]; r->right = nodeCache[3];
        nodeCache[2]->parent = nodeCache[3]->parent = r;
    }
    return promo;
}

//insert a new item to a 2-node
template <class elemType>
void TT<elemType> :: insertSecondItem(nodeType<elemType>* n, const elemType x){
    //pre: a pointer to the 2-node, and the value to be inserted
    //post: value is inserted
    if (x < n->dataLeft){   //x should be on left
        n->dataRight = n->dataLeft;
        n->dataLeft = x;
    } else {    //x should be on right
        n->dataRight = x;
    } n->numData = 2;
}

//check if the node is parent's left, middle or right child
template <class elemType>
int TT<elemType> :: posChild(const nodeType<elemType>*parento, const nodeType<elemType>*n) const{
    //pre: a pointer to the parent, and a pointer to the node itself
    //post: return 0 for left, 1 for middle, 2 for right child
    if (parento->left == n) return 0;    //if left child
    else if (parento->middle == n) return 1; //if middle child
    else return 2;  //if right child
}

//recursive helper function for insert()
template <class elemType>
void TT<elemType> :: auxilary(nodeType<elemType> * n, const elemType x){
    //pre: a pointer to the node to start with, the value to insert
    //post: value is inserted to the tree
    if (isLeaf(n)){ //base case; if n is a leaf
        if (n->numData == 1){   //leaf has empty space
            insertSecondItem(n, x);
        } else {    //leaf is full; split it; promote the node to parent
            int pos = posChild(n->parent, n);
            nodeType<elemType> *promo = splitNode(n, instantiate(x), pos);  //split the node
            while (n->parent != root){    //if parent is not root
                if (n->parent->numData == 1){ //the parent is not full
                    insertSecondItem(n->parent, promo->dataLeft);   //insert value to parent
                    //rearrange leftover's linking
                    int pos = posChild(n->parent, n);
                    if (pos == 0){ //if n is left child
                        n->parent->left = promo->left;
                        n->parent->middle = promo->right;
                    } else if (pos == 2){   //if n is right child
                        n->parent->middle = promo->left;
                        n->parent->right = promo->right;
                    }
                    promo->left->parent = promo->right->parent = n->parent;
                    break;  //insertion complete
                } else {    //continue to split parent's parent and so on
                    pos = posChild(n->parent, n);   //direction the split request comes from
                    n = n->parent;  //go one level up
                    promo = splitNode(n, promo, pos);   //split parent's parent
                }
            }
            if (n->parent == root){ //when trace to root
                pos = posChild(n->parent, n);   //direction the split request comes from
                if (n->parent->numData == 1){   //the root is not full
                    insertSecondItem(n->parent, promo->dataLeft);
                    if (pos == 0){ //if n is left child
                        n->parent->left = promo->left;
                        n->parent->middle = promo->right;
                    } else if (pos == 2){   //if n is right child
                        n->parent->middle = promo->left;
                        n->parent->right = promo->right;
                    }
                    promo->left->parent = promo->right->parent = n->parent;
                } else {    //split the root
                    pos = posChild(n->parent, n);
                    n = n->parent;
                    root = splitNode(n, promo, pos);    //root will be updated
                }
            }
        }
    } else {    //non-base case
        if (n->numData == 1){   //2-node
            if (x < n->dataLeft) auxilary(n->left, x);  //go left subtree
            else auxilary(n->right, x);   //go right subtree
        } else {    //3-node
            if (x < n->dataLeft) auxilary(n->left, x);  //go left subtree
            else if (x > n->dataRight) auxilary(n->right, x);  //go left subtree
            else auxilary(n->middle, x);    //go middle subtree
        }
    }
}
*/