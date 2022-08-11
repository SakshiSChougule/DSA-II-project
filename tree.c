#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "tree.h"




TreeNode TreeNodeCreate(int c, int occ){
    assert(c >= INTERNAL_NODE_C);
    assert(occ >= 0);

    node* t = (node*) malloc(sizeof(node));
    assert(t != NULL);

    t->c = c;
    t->occ = occ;
    t->left = NULL;
    t->right = NULL;
    t->parent = NULL;

    return t;
}




node* TreeNodeDelete(node* t){
    if (t != NULL){
        t->left = TreeNodeDelete(t->left);
        t->right = TreeNodeDelete(t->right);

        free(t);
        t = NULL;
    }

    return t;
}



Tree TreeCreate(TreeNode root){
    assert(IsTreeNodeValid(root));
    assert(IsRootNode(root));

    Tree tr = (Tree) malloc(sizeof(_Tree));
    assert(tr != NULL);

    tr->root = root;
    return tr;
}


Tree TreeDestroy(Tree tr){
    assert(tr != NULL);

    tr->root = TreeNodeDelete(tr->root);
    
    free(tr);
    tr = NULL;
    
    return tr;
}

bool IsTreeNodeValid(node* t){
    return t != NULL && t->c >= INTERNAL_NODE_C && t->occ >= 0;
}



bool IsRootNode(node* t){
    assert(IsTreeNodeValid(t));
    return t->c == ROOT_NODE_C;
}


bool IsInternalNode(node* t){
    assert(IsTreeNodeValid(t));
    return t->c == INTERNAL_NODE_C;
}



bool IsLeafNode(node* t){
    assert(IsTreeNodeValid(t));
    return t->c >= 0 && t->left == NULL && t->right == NULL;
}



// true if t1 has smaller occurence than t2
bool IsOccSmaller(node* t1, node* t2){
    assert(IsTreeNodeValid(t1));
    assert(IsTreeNodeValid(t2));
    return t1->occ < t2->occ;
}


bool IsLeftChild(node* child, node* parent){
    assert(IsTreeNodeValid(child) && IsTreeNodeValid(parent));
    assert(child->parent == parent);

    return parent->left == child;
}


int GetC(node* t){
    assert(IsTreeNodeValid(t));
    return t->c;
}


int GetOcc(node* t){
    assert(IsTreeNodeValid(t));
    return t->occ;
}


void SetOcc(node* t, int occ){
    assert(IsTreeNodeValid(t));
    t->occ = occ;
    return;
}


int SumTwoOcc(node* t1, node* t2){
    assert(IsTreeNodeValid(t1));
    assert(IsTreeNodeValid(t2));

    return t1->occ + t2->occ;
}


void ConnectAsLeftChild(node* child, node* parent){
    assert(IsTreeNodeValid(child) && IsTreeNodeValid(parent));
    parent->left = child;
    child->parent = parent;
    return;
}


void ConnectAsRightChild(TreeNode child, TreeNode parent){
    assert(IsTreeNodeValid(child) && IsTreeNodeValid(parent));
    parent->right = child;
    child->parent = parent;
    return;
}




void ResetInternalNodeToRootNode(TreeNode t){
    assert(IsTreeNodeValid(t));
    assert(IsInternalNode(t));

    t->c = ROOT_NODE_C;
    return;
}


int TreeNodeGetDepth(TreeNode t){
    assert(IsTreeNodeValid(t));

    // while loop to trace upwards
    int depth = 0;

    if (! IsRootNode(t)){
        TreeNode current = t;
        while (! IsRootNode(current)){
            depth += 1;
            current = current->parent;
        }
    }


    return depth;
}



