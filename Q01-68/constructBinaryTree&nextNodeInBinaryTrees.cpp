#include "dataStructure.h"

/*07construct binaryTree (preOrder + inOrder)
 *preOrder:12473568
 *inOrder:47215386
*/
bTreeNode *constructBTreeCore(int preOrder[],int inOrder[],int length){
    //root init
    if(length == 0)
        return nullptr;
    auto root = new bTreeNode();
    root->left = root->right = nullptr;
    root->data = *preOrder;
    if(length == 1)
        return root;
    //find subPre and subIn
    int leftLength = 0, rightLength = 0;
    while(leftLength < length){
        if(*(inOrder + leftLength) == *preOrder)
            break;
        ++leftLength;
    }
    rightLength = length - 1 - leftLength;
    root->left = constructBTreeCore(preOrder + 1, inOrder, leftLength);
    root->right = constructBTreeCore(preOrder + 1 + leftLength, inOrder + 1 + leftLength, rightLength);
    return root;
}

bTreeNode *constructBTree(int preOrder[], int inOrder[], int length){
    if(!preOrder || !inOrder || length <= 0)
        return nullptr;
    return constructBTreeCore(preOrder, inOrder, length);
}

/*08 binary tree's next node in inOrder
 * inOrder is {d,b,h,e,i,a,f,c,g}
 *              a
 *           /     \
 *           b     c
 *          / \   / \
 *         d  e  f  g
 *           / \
 *           h i
 * data  structure=
 * typedef struct A{
 *      valueType data;
 *      A *left,*right,*dad;
 * }bTreeNode;
*/
//typedef int valueType;
typedef struct AwithBase{
    valueType data;
    AwithBase *left,*right,*dad;
} bTreeWithDadNode;
//08
bTreeWithDadNode *nextNodeInorder(bTreeWithDadNode *pBTreeNodeWithDad, valueType data){
    //want to find data's next
    if(!pBTreeNodeWithDad)
        return nullptr;
    std::queue<bTreeWithDadNode *> nodes;
    nodes.push(pBTreeNodeWithDad);
    while(!nodes.empty()){
        pBTreeNodeWithDad = nodes.front();
        if(pBTreeNodeWithDad->data == data)
            break;
        nodes.pop();
        if(!pBTreeNodeWithDad->left)
            nodes.push(pBTreeNodeWithDad->left);
        if(!pBTreeNodeWithDad->right)
            nodes.push(pBTreeNodeWithDad->right);
    }//pbtreeNode -> data
    if(data != pBTreeNodeWithDad->data)
        return nullptr;//data not found
    //if data node has sub-left tree
    if(pBTreeNodeWithDad->right){
        pBTreeNodeWithDad = pBTreeNodeWithDad->right;
        while(pBTreeNodeWithDad){
            pBTreeNodeWithDad = pBTreeNodeWithDad->left;
        }
        return pBTreeNodeWithDad->dad;
    }
    else if(pBTreeNodeWithDad == pBTreeNodeWithDad->dad->left){
        return pBTreeNodeWithDad->dad;
    }
    else{
        while(!pBTreeNodeWithDad->dad->dad){
            if(pBTreeNodeWithDad->dad == pBTreeNodeWithDad->dad->dad->left){
                return pBTreeNodeWithDad->dad->dad;
            }
            else{
                pBTreeNodeWithDad = pBTreeNodeWithDad->dad;
            }
        }
        return nullptr;
    }
}



int main(){
    //bTreeNode *root = nullptr;
    //createBTree(&root);
    //preOrderTraversal(root);
    //preOrderWithStack(root);
    //inOrderTraversal(root);
    //inOrderTraversalWithStack(root);
    //postOrderTraversal(root);
    //postOrderWithStack(root);
    //postOrderWith2Stack(root);
    int pre[] = {1,2,4,7,3,5,6,8};
    int in[] = {4,7,2,1,5,3,8,6};
    constexpr int length = sizeof(pre)/sizeof(int);
    auto root = constructBTree(pre,in,length);
    inOrderTraversalWithStack(root);
    return 0;
}
