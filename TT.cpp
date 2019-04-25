//
// Created by Ryan  Martino on 4/21/19.
//
#include"TT.h"
#include "time.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <assert.h>

using namespace std;

//Constructor
TT::TT()
{
    root = NULL;
    
}

//Returns true if there are no nodes in the tree
bool TT::isEmpty(){
    return root == NULL;
}

//Used to implement the search function in the main
//program.
void TT::contains() const{
    string input;
    node *foundNode = NULL;
    cout << "Search word: ";
    cin >> input;
    if(containsHelper(input, root, foundNode))
    {
        vector<int>* lines;
        if (input == foundNode->keyL)
        {
            lines = &foundNode->linesL;
        }
        else
        {
            lines = &foundNode->linesR;
        }
        cout << "Line Numbers: " << (*lines)[0];
        for(int i = 1; i < (*lines).size(); i++)
        {
            cout << ", " << (*lines)[i];
        }
        cout << '\n';
    }
    else
        cout << '\"' << input <<"\" is not in the document\n";
}

//Prints the index to the supplied receiver, either
//cout or the output file
void TT::printTree(ostream & out) const {
    out << "2-3 Tree Index:\n-------------------------\n";
    printTreeHelper(root, out);
}

//Receives the specified input file and constructs
//the actual tree. Prints a message when finished.
void TT::buildTree(ifstream & input){
    int line = 1, numWords = 0, distWords = 0, treeHeight = 0;
    stringstream tempWord;
    double totalTime, finishTime, startTime = clock();
    while (!input.eof()) {
        string tempLine, tempWord;
        
        //Read a whole line of text from the file
        getline(input, tempLine);
        for (int i = 0; i < tempLine.length(); i++) {
            //Insert valid chars into tempWord until a delimiter( newline or space) is found
            while (tempLine[i] != ' '&& tempLine[i] != '\n' && i < tempLine.length() ) {
                tempWord.insert(tempWord.end(), tempLine[i]);
                i++;
            }
            
            //Trim any punctuation off end of word. Will leave things like apostrophes
            //and decimal points
            while(tempWord.length() > 0 && !isalnum(tempWord[tempWord.length() - 1]))
                tempWord.resize(tempWord.size() -1);
            
            if (tempWord.length() > 0)
            {
                //Once word is formatted,call insert with the word, the line of the input
                //file it came from, the root of our tree, and the distinct word counter
                cout << "tree height: " << findHeight(root) << endl;
                printTree();
                insertHelper(tempWord, line, root, distWords);
                //Increment our total number of words inserted
                numWords++;
                //Clear out tempWord so we can use it again
                tempWord.clear();
            }
            
        }
        line++;
    }
    //Do time and height calculation
    finishTime = clock();
    totalTime = (double) (finishTime - startTime)/CLOCKS_PER_SEC;
    treeHeight = findHeight(root);
    
    //Print output
    cout << setw(40) << std::left;
    cout << "Total number of words: " << numWords<< endl;
    
    cout << setw(40) << std::left
    << "Total number of distinct words: " << distWords << endl;
    
    cout << setw(40) << std::left
    <<"Total time spent building index: " << totalTime << endl;
    
    cout << setw(40) << std::left
    <<"Height of TT is : " << treeHeight << endl;
    
}


//x is the word to insert, line is the line in the text file
//the word was found at, node is the node of the tree being
//examined, and distWord is incremented if a new word is created
//and used by buildTree
void TT::insertHelper(const string &x, int line, node *& t, int &distWord){
    assert((t == NULL) || (t->keyR == "") || (t->keyL < t->keyR));
    if(t == NULL)
    {
        t = new node(x, "", NULL, NULL, NULL, NULL);
        t->linesL.push_back(line);
        distWord++;
    }
    else if(t->isLeaf())
    {
        assert((t->keyR == "") || (t->keyL < t->keyR));
        if (x == t->keyL)
        {
            t->linesL.push_back(line);
        }
        else if (t->keyR == "")
        {
            distWord++;
            t->keyR = x;
            t->linesR.push_back(line);
            
            if (t->keyL > t->keyR)
            {
                t->keyL.swap(t->keyR);
                t->linesL.swap(t->linesR);
            }
            assert(t->keyL < t->keyR);
        }
        else if (x == t->keyR)
        {
            t->linesR.push_back(line);
        }
        else
        {
            distWord++;
            node* pNode = new node(x);
            pNode->linesL.push_back(line);
            
            assert(t->keyL < t->keyR);
            assert(pNode->keyR == "");
            
            assert(pNode->keyR == "");
            promoteHelper(t, pNode);
        }
    }
    else
    {
        assert((t->keyR == "") || (t->keyL < t->keyR));
        if (x.compare(t->keyL) == 0)
        {
            t->linesL.push_back(line);
        }
        else if (x.compare(t->keyR) == 0)
        {
            t->linesR.push_back(line);
        }
        else if (x < t->keyL)
        {
            insertHelper(x, line, t->left, distWord);
        }
        else if (x > t->keyR)
        {
            insertHelper(x, line, t->right, distWord);
        }
        else
        {
            insertHelper(x, line, t->middle, distWord);
        }
    }
}


//Used by contains() to see if a words is present or not. Will
//give contains() a pointer to the found node so that contains()
//can prints the lines the word was found on.
bool TT::containsHelper(const string & x, node * t, node * &result) const{
    if (t == NULL)
        return false;
    if ((t->keyL.compare(x) == 0)||(t->keyL.compare(x) == 0)){
        result = t;
        return true;
    }
    else if (x < t->keyL)
        return containsHelper(x, t->left, result);
    else if (x > t-> keyR)
        return containsHelper(x, t->right, result);
    else
        return containsHelper(x, t->middle, result);
}

//Called by printTree(), does the actual formatted printing
void TT::printTreeHelper(node *t, ostream & out) const{
    if(t == NULL)
    {
        out << "null tree" << endl;
    }
    else if(t->isLeaf())
    {
        out << setw(30) << std::left;
        out << t->keyL << " " << t->linesL[0];
        for (int i = 1; i < t->linesL.size(); i++)
            out << ", " << t->linesL[i];
        out << endl;
        if(t->keyR != "")
        {
            out << setw(30) << std::left;
            out << t->keyR << " " << t->linesR[0];
            for (int i = 1; i < t->linesR.size(); i++)
                out << ", " << t->linesR[i];
            out << endl;
        }
    }
    else
    {
        printTreeHelper(t->left, out);
        out << setw(30) << std::left;
        out << t->keyL << " " << t->linesL[0];
        for (int i = 1; i < t->linesL.size(); i++)
            out << ", " << t->linesL[i];
        out << endl;
        
        if(t->middle)
        {
            printTreeHelper(t->middle, out);
        }
        if(t->keyR != "")
        {
            out << setw(30) << std::left;
            out << t->keyR << " " << t->linesR[0];
            for (int i = 1; i < t->linesR.size(); i++)
                out << ", " << t->linesR[i];
            out << endl;
            
        }

        printTreeHelper(t->right, out);
    }
}

void TT::promoteHelper(node* t, node* pNode, node* last_t, node* last_sib)
{
    assert((pNode->left == NULL) && (pNode->middle == NULL) && (pNode->right == NULL));
    assert((t->keyR == "") || (t->keyL < t->keyR));
    assert(pNode->keyR == "");
    assert((t == NULL) || (t->parent == NULL) || (t->parent->keyR == "") || (t->parent->keyL < t->parent->keyR));
    
    
    //make new sibling
    node* sibling = new node();
    
    if (pNode->keyL < t->keyL)
    {//less than left, current left is mid-key
        (t->keyL).swap(pNode->keyL);
        (t->linesL).swap(pNode->linesL);
    }
    else if(pNode->keyL > t->keyR)
    {//greater than right, current right is mid-key
        t->keyR.swap(pNode->keyL);
        t->linesR.swap(pNode->linesL);
    }
    //now t->keyL < pNode->keyL < t->keyR
    (t->keyR).swap(sibling->keyL);
    (t->linesR).swap(sibling->linesL);
    
    assert(pNode->keyL < sibling->keyL);
    assert(t->keyL < pNode->keyL);
    assert((t->keyR == "") || (t->keyL < t->keyR));
    assert(sibling->keyR == "");
    assert(pNode->keyR == "");
    assert((t == NULL) || (t->parent == NULL) || (t->parent->keyR == "") || (t->parent->keyL < t->parent->keyR));

    
    if (last_sib)
    {//if this is a recursive call
        if (last_t == t->left)
        {//previous call was on a left
            /*
                        t              sibling
                       ___               ___
                      |___|             |___|
                     /    |\
                    /     | \
                   /      |  \
                  /       |   \
              ___/  ___   |__  \___
             |___| |___| |___| |___|
             t->l last_p  t->m  t->r
            last_t
                           __
                          |  |
                          |  |
                        __|  |__
                        \  TO  /
                         \    /
                          \  /
                           \/
                         t                sibling
                        ___                 ___
                       |___|               |___|
                      /    |               |    \
                     /     |               |     \
                    /      |               |      \
                   /       |               |       \
               ___/       _|_           ___|        \___
              |___|      |___|         |___|        |___|
              t->l      last_p          t->m         t->r
             last_t
             */
            //move t's middle to sibling's left
            sibling->left = t->middle;
            sibling->left->parent = sibling;
            //last_p becomes t's new middle
            t->middle = last_sib;
            last_sib->parent = t;
            //t's right becomes sibling's middle
            sibling->middle = t->right;
            sibling->middle->parent = sibling;
            
            assert((pNode->left == NULL) && (pNode->middle == NULL) && (pNode->right == NULL));
            assert((t->keyR == "") || (t->keyL < t->keyR));
            assert(sibling->keyR == "");
            assert(pNode->keyR == "");
            assert((t == NULL) || (t->parent == NULL) || (t->parent->keyR == "") || (t->parent->keyL < t->parent->keyR));

        }
        else if (last_t == t->right)
        {//previous call was on a right
            /*
                        t              sibling
                       ___               ___
                      |___|             |___|
                     / |  |
                    /  |  |
                   /   |  |
                  /    |  |
              ___/  ___|  |__   ___
             |___| |___| |___| |___|
             t->l  t->m  t->r  last_p
            last_t
                             __
                            |  |
                            |  |
                          __|  |__
                          \  TO  /
                           \    /
                            \  /
                             \/
             
                        t                sibling
                       ___                 ___
                      |___|               |___|
                     /    |               |    \
                    /     |               |     \
                   /      |               |      \
                  /       |               |       \
              ___/       _|_           ___|        \___
             |___|      |___|         |___|        |___|
             t->l       t->m          t->r         last_p
            last_t
             */
            //move t's right to sibling's left
            sibling->left = t->right;
            sibling->left->parent = sibling;
            //last_p becomes sibling's middle
            sibling->middle = last_sib;
            last_sib->parent = sibling;
            
            assert((pNode->left == NULL) && (pNode->middle == NULL) && (pNode->right == NULL));
            assert((t->keyR == "") || (t->keyL < t->keyR));
            assert(sibling->keyR == "");
            assert(pNode->keyR == "");
            assert((t == NULL) || (t->parent == NULL) || (t->parent->keyR == "") || (t->parent->keyL < t->parent->keyR));

        }
        else
        {//previous call was on a middle
             /*
                        t              sibling
                       ___               ___
                      |___|             |___|
                     / |  |
                    /  |  |
                   /   |  |
                  /    |  |
              ___/  ___|  |__   ___
             |___| |___| |___| |___|
             t->l  t->m  t->r  last_p
            last_t
                             __
                            |  |
                            |  |
                          __|  |__
                          \  TO  /
                           \    /
                            \  /
                             \/
             
                        t                sibling
                       ___                 ___
                      |___|               |___|
                     /    |               |    \
                    /     |               |     \
                   /      |               |      \
                  /       |               |       \
              ___/       _|_           ___|        \___
             |___|      |___|         |___|        |___|
             t->l       t->m          t->r         last_p
            last_t
             */
            //move t's right to sibling's left
            sibling->left = t->right;
            sibling->left->parent = sibling;
            //last_p becomes sibling's middle
            sibling->middle = last_sib;
            last_sib->parent = sibling;
            
            assert((pNode->left == NULL) && (pNode->middle == NULL) && (pNode->right == NULL));
            assert((t->keyR == "") || (t->keyL < t->keyR));
            assert(sibling->keyR == "");
            assert(pNode->keyR == "");
            assert((t == NULL) || (t->parent == NULL) || (t->parent->keyR == "") || (t->parent->keyL < t->parent->keyR));

        }
        //in all cases, t is left with no right child
        t->right = NULL;
        assert((t->keyR == "") || (t->keyL < t->keyR));
        assert(sibling->keyR == "");
        assert(pNode->keyR == "");
        assert((t == NULL) || (t->parent == NULL) || (t->parent->keyR == "") || (t->parent->keyL < t->parent->keyR));
    }
    
    assert((t->keyR == "") || (t->keyL < t->keyR));
    assert(sibling->keyR == "");
    assert(pNode->keyR == "");
    assert((t == NULL) || (t->parent == NULL) || (t->parent->keyR == "") || (t->parent->keyL < t->parent->keyR));
    
    if (t->parent == NULL)
    {//we're splitting the root
        node* newRoot = new node(*pNode);
        root = newRoot;
        
        assert((newRoot->left == NULL) && (newRoot->middle == NULL) && (newRoot->right == NULL));
        //these should already be sorted
        assert((t->keyL < pNode->keyL) && (pNode->keyL < sibling->keyL));
        
        newRoot->left = t;
        t->parent = newRoot;
        newRoot->middle = sibling;
        t->parent = newRoot;
        assert((t->keyL < pNode->keyL) && (pNode->keyL < sibling->keyL));
        
        assert((t->keyR == "") || (t->keyL < t->keyR));
        assert(sibling->keyR == "");
        assert(pNode->keyR == "");
        assert((t == NULL) || (t->parent == NULL) || (t->parent->keyR == "") || (t->parent->keyL < t->parent->keyR));
    }
    else if (t->parent->keyR == "")
    {//there's room for simple promotion to existing parent
        t->parent->keyR = pNode->keyL;
        t->parent->linesR = pNode->linesL;
        
        if(t->parent->keyL > t->parent->keyR)
        {
            t->parent->keyL.swap(t->parent->keyR);
            t->parent->linesL.swap(t->parent->linesR);
            if ((t->parent->left) && (t->parent->middle) && (t->parent->left->keyL > t->parent->middle->keyL))
            {
                t->parent->left->swap(t->parent->middle);
            }
            if ((t->parent->middle) && (t->parent->right) && (t->parent->middle->keyL > t->parent->right->keyL))
            {
                t->parent->middle->swap(t->parent->right);
            }
        }
        
        t->parent->right = sibling;
        
        //t == (t->parent)->right NOT POSSIBLE with keyR == ""
        assert(t != (t->parent)->right);
        //regardless, sibling's parent is t's parent
        sibling->parent = t->parent;
        assert((t->keyL < pNode->keyL) && (pNode->keyL < sibling->keyL));
        
        assert((t->keyR == "") || (t->keyL < t->keyR));
        assert(sibling->keyR == "");
        assert(pNode->keyR == "");
        assert((t == NULL) || (t->parent == NULL) || (t->parent->keyR == "") || (t->parent->keyL < t->parent->keyR));
    }
    else
    {//complicated promotion
        assert((t->keyR == "") || (t->keyL < t->keyR));
        assert(sibling->keyR == "");
        assert(pNode->keyR == "");
        assert((t->keyL < pNode->keyL) && (pNode->keyL < sibling->keyL));
        assert((t == NULL) || (t->parent == NULL) || ((t->parent->keyR == "") || (t->parent->keyL < t->parent->keyR)));
        
        promoteHelper(t->parent, pNode, t, sibling);
    }
}

//Returns height of tree. If tree has only one node, height is 1
int TT::findHeight(node *t){
    if((t == NULL) || (t->isLeaf()))
    {
        return 0;
    }
    else{
        int leftHeight = findHeight(t->left) + 1, middleHeight = findHeight(t->middle) + 1, rightHeight = findHeight(t->right) + 1;
        assert(leftHeight == middleHeight);
//        if(t->right)
//        {
//            assert(middleHeight == rightHeight);
//        }
        return leftHeight;
    }
}
