//
// Created by Ryan  Martino on 4/21/19.
//

#ifndef CS415PROJECT3_TT_H
#define CS415PROJECT3_TT_H
#include<iostream>
#include <string>
#include <vector>
#include <fstream>
#include <assert.h>
#include <queue>



using namespace std;
class TT {
public:
    TT();

    void contains() const;

    bool isEmpty();

    void printTree(ostream &out = cout) const;
    
    void printLevels(ostream &out = cout) const;

    void buildTree(ifstream &input);

private:
    struct node {
        node(const string &x = "", const string &y = "", node *l = NULL, node * m = NULL, node *r = NULL, node* p = NULL)
        : keyL(x), keyR(y), left(l),middle(m), right(r), parent(p)
        {
            linesL.resize(0);
            linesR.resize(0);
        }

        string keyL;
        string keyR;
        node *left;
        node *middle;
        node *right;
        node *parent;
        
        vector<int> linesL;
        vector<int> linesR;
        
        bool isLeaf()
        {
            return ((left == NULL) && (middle == NULL) && (right == NULL));
        }
        
        void swap(node* R)
        {
            keyL.swap(R->keyL);
            keyR.swap(R->keyR);
            
            auto* swap = left;
            //swap left
            left = R->left;
            R->left = swap;
            //swap middle
            swap = middle;
            middle = R->middle;
            R->middle = swap;
            //swap right
            swap = right;
            right = R->right;
            R->right = swap;
            //swap parent
            swap = parent;
            parent = R->parent;
            R->parent = swap ;
            
            linesL.swap(R->linesL);
            linesR.swap(R->linesR);
        }
    };

    node *root;
    
    void insertHelper(const string &X, int line, node *&t, int &distWords);

    bool containsHelper(const string &x, node *t, node *&result) const;

    void printTreeHelper(node *t, ostream &out) const;
    
    void printLevelsHelper(queue<node*> Q1, queue<node*> Q2, ostream &out) const;
    
    void promoteHelper(node* t, node* pNode, node* last_t = NULL, node* last_sib = NULL);
    
    int findHeight(node *t);
};
#endif //CS415PROJECT3_TT_H
