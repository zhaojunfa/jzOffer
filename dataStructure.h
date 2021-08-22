#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

//not good
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
//using namespace std;
/*链表和相关函数
 * 05_02 链表添加和删除P56\
 *06_01从尾到头打印链表
*/
struct ListNode{
    int m_nValue;
    ListNode *m_pNext;
};

/*树和相关操作
 *
*/

//defination
typedef int valueType;
constexpr valueType leafValue = -1;//or '#'

//data structure
typedef struct A{
    valueType data;
     A *left,*right;
} bTreeNode;

//create (PreOrder)..
void createBTree(bTreeNode **ppBTreeNode){
    valueType data;
    std::cout <<"input:\n";
    std::cin >> data;
    if(data == leafValue)
        *ppBTreeNode = nullptr;
    else{
        *ppBTreeNode = new bTreeNode();
        (*ppBTreeNode)->data = data;
        createBTree(&(*ppBTreeNode)->left);
        createBTree(&(*ppBTreeNode)->right);
    }
    return;
}


//6 ways to print bTree

//preOrder-traversal: recursion + withStack
void preOrderTraversal(bTreeNode *pBtreeNode){
    if(!pBtreeNode)
        return;
    std::cout << pBtreeNode->data << ' ';
    preOrderTraversal(pBtreeNode->left);
    preOrderTraversal(pBtreeNode->right);
}

void preOrderTraversalWithStack_(bTreeNode *root){//push:cout
    if(!root)
        return;
    std::stack<bTreeNode *> nodes;
    while(root || !nodes.empty()){
        while(root){
            nodes.push(root);
            std::cout << root->data << ' ';
            root = root->left;
        }
        root = nodes.top()->right;
        nodes.pop();
    }
}



//inOrderTraversal-recursion + withStack
void inOrderTraversal(bTreeNode *pBTreeNode){
    if(pBTreeNode == nullptr)
        return;
    inOrderTraversal(pBTreeNode->left);
    std::cout<<pBTreeNode->data << ' ';
    inOrderTraversal(pBTreeNode->right);
}

void inOrderTraversalWithStack_(bTreeNode *root){
    if(!root)
        return;
    std::stack<bTreeNode *> nodes;
    while(root || !nodes.empty()){
        while(root){
            nodes.push(root);
            root = root->left;
        }
        root = nodes.top()->right;
        std::cout << nodes.top()->data << ' ';
        nodes.pop();
    }
}

//postOrder
void postOrderTraversal(bTreeNode *pBTreeNode){
    if(!pBTreeNode)
        return;
    postOrderTraversal(pBTreeNode->left);
    postOrderTraversal(pBTreeNode->right);
    std::cout << pBTreeNode->data << ' ';
}

void postOrderTraversalWith1Stack_(bTreeNode *root){
    if(!root)
        return;
    std::stack<bTreeNode *> nodes;
    bTreeNode *nextPop = nullptr;
    while(!nodes.empty() || root){
        while(root){
            while(root){
                nodes.push(root);
                root = root->left;
            }
            if(nodes.top()->right)
                root = nodes.top()->right;
        }//init
        if(nodes.top()->left == nextPop && nodes.top()->right)
            root = nodes.top()->right;
        else{
            nextPop = nodes.top();
            std::cout << nextPop->data << ' ';
            nodes.pop();
        }
    }
}

void postOrderWith2Stack(bTreeNode *pBTreeNode){
    if(!pBTreeNode)
        return;
    std::stack<bTreeNode *> stack, output;
    while(pBTreeNode || !stack.empty()){
        if(pBTreeNode){
            stack.push(pBTreeNode);
            output.push(pBTreeNode);
            pBTreeNode = pBTreeNode->right;
        }
        else{
            pBTreeNode = stack.top()->left;
            stack.pop();
        }
    }
    while(!output.empty()){
        std::cout << output.top()->data << ' ';
        output.pop();
    }
}

//levelOrderTraversal
void levelOrderTraversalWithQueue(bTreeNode *pBTreeNode){
    if(!pBTreeNode)
        return;
    std::queue<bTreeNode *> nodes;
    nodes.push(pBTreeNode);
    while(!nodes.empty()){
        bTreeNode *top = nodes.front();
        nodes.pop();
        std::cout<<top->data<<' ';
        if(top->left)
            nodes.push(top->left);
        if(top->right)
            nodes.push(top->right);
    }
}

//NC15 levelOrderTraversaltoVector
std::vector<std::vector<int>> levelOrderTraversalToVector(bTreeNode *pBTreeNode){
    if(!pBTreeNode)
        return std::vector<std::vector<int>>();
    std::queue<bTreeNode*> nodes;
    nodes.push(pBTreeNode);
    std::vector<std::vector<int>> res;
    std::vector<int> res_level;
    int sz = 1;
    while(!nodes.empty()){
        sz = nodes.size();
        res_level.resize(sz);
        for(int i = 0; i < sz; ++i){
            res_level[i] = nodes.front()->data;
            if(nodes.front()->left)
                nodes.push(nodes.front()->left);
            if(nodes.front()->right)
                nodes.push(nodes.front()->right);
            nodes.pop();
        }
        res.push_back(res_level);
    }
    //
//    for(auto &e:res){
//        for(auto &e_:e)
//            std::cout <<e_ <<' ';
//        std::cout<<std::endl;
//    //
//    }
    return res;
}




#endif // DATASTRUCTURE_H
