//
// Created by Ryan  Martino on 4/20/19.
//

#ifndef CS415PROJECT3_BST_H
#define CS415PROJECT3_BST_H
//Description: Prototypes for the binary search tree class.


#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

class BST{
public:
    BST();
    void contains() const;
    bool isEmpty();
    void printTree(ostream & out = cout) const;
    void buildTree(ifstream & input);
    void buildTreeNoOut(ifstream & input);
    double getFinalTime();
    void setFinalTime(double t){finalTime = t;}

private:
    struct node{
        node(const string &x, node *l, node *r)
                :key(x), left(l), right(r){
            lines.resize(0);
        }
        string key;
        node * left;
        node * right;
        vector<int> lines;
    };
    node * root;
    double long finalTime{0.0};
    void insertHelper(const string &X, int line, node *& t, int &distWords);
    bool containsHelper(const string & x, node * t, node* &result) const;
    void printTreeHelper(node *t, ostream & out) const;
    int findHeight(node *t);
};

//#endif




#endif //CS415PROJECT3_BST_H
