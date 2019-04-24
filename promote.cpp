//
//  promote.cpp
//  cs415Project3
//
//  Created by Will Lucic on 4/23/19.
//  Copyright © 2019 supersaiyansubtlety. All rights reserved.
//

#include "TT.h"

void TT::promoteHelper(node* t, node* last_p, node* last_t)
{
    if (last_p)
    {//if this is a recursive call
        if (last_t == t->left)
        {//previous call was on a left
            /*
                            t               pNode
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
                            t                 pNode
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
            //move t's middle to pNode's left
            pNode->left = t->middle;
            pNode->left->parent = pNode;
            //last_p becomes t's new middle
            t->middle = last_p;
            last_p->parent = t;
            //t's right becomes pNode's middle
            pNode->middle = t->right;
            pNode->middle->parent = pNode;
        }
        else if (last_t == t->right)
        {//previous call was on a right
            /*
                            t               pNode
                           ___               ___
                          |___|             |___|
                         /|    \
                        / |     \
                       /  |      \
                      /   |       \
                  ___/  __|   ___  \___
                 |___| |___| |___| |___|
                 t->l  t->m  last_p t->r
                      last_t
                                      __
                                     |  |
                                     |  |
                                   __|  |__
                                   \  TO  /
                                    \    /
                                     \  /
                                      \/
                            t                 pNode
                           ___                 ___
                          |___|               |___|
                         /    |               |    \
                        /     |               |     \
                       /      |               |      \
                      /       |               |       \
                  ___/       _|_           ___|        \___
                 |___|      |___|         |___|        |___|
                  t->l       t->m        last_p         t->r
                            last_t
             */
            //move t's right to pNode's middle
            pNode->middle = t->right;
            pNode->middle->parent = pNode;
            //last_t becomes pNode's left
            pNode->left = last_p;
            last_p->parent = pNode;
        }
        else
        {//previous call was on a middle
            /*
                            t               pNode
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
             
                            t                 pNode
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
            //move t's right to pNode's left
            pNode->left = t->right;
            pNode->left->parent = pNode;
            //last_p becomes pNode's middle
            pNode->middle = last_p;
            last_p->parent = pNode;
            
        }
        //in all cases, t is left with no right child
        t->right = NULL;
    }
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
    
    if ((t->parent)->keyR == "")
    {//there's room for simple promotion to existing parent
        t->keyR = pNode->keyL;
        t->linesR = pNode->linesL;
        //t == (t->parent)->right NOT POSSIBLE with keyR == ""
        //regardless, pNode's parent is t's parent
        pNode->parent = t->parent;
    }
    else if(t->parent)
    {
        promoteHelper(t->parent, sibling, t);
    }
    else
    {//we're splitting the root
        static node newRoot = *pNode;
        newRoot.left = t;
        newRoot.middle = sibling;
    }
}
