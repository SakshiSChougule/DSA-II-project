#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// pseudo values for root nodes and internal nodes because only leaf nodes store actual characters
#define ROOT_NODE_C -2
#define INTERNAL_NODE_C -3


typedef struct node{
    int c;
    int occ;
    struct node *left;
    struct node *right;
    struct node *parent;
}node;

typedef node* TreeNode;

typedef struct _Tree{
    TreeNode root;
}_Tree;

typedef _Tree* Tree;


node* TreeNodeCreate(int c, int occ);
node* TreeNodeDelete(TreeNode);


Tree TreeCreate(TreeNode root);
Tree TreeDestroy(Tree);


bool IsTreeNodeValid(TreeNode);
bool IsRootNode(TreeNode);
bool IsInternalNode(TreeNode);
bool IsLeafNode(TreeNode);
bool IsOccSmaller(TreeNode trn1, TreeNode trn2);

bool IsLeftChild(TreeNode child, TreeNode parent);

int GetC(TreeNode);
int GetOcc(TreeNode);

void SetOcc(TreeNode trn, int occ);
int SumTwoOcc(TreeNode trn1, TreeNode trn2);

void ConnectAsLeftChild(TreeNode child, TreeNode parent);
void ConnectAsRightChild(TreeNode child, TreeNode parent);


void ResetInternalNodeToRootNode(TreeNode);

int TreeNodeGetDepth(TreeNode trn);




#endif // TREE_H_INCLUDED
