/*BST*/

#include "dataStructure.h"

//insertBST
bool insertBST(bTreeNode **pBtreeNode,valueType data){
    if(!(*pBtreeNode)){
        *pBtreeNode = new bTreeNode;
        (*pBtreeNode)->data = data;
        (*pBtreeNode)->right = (*pBtreeNode)->left = nullptr;
        return true;
    }
    else if((*pBtreeNode)->data < data)
        return insertBST(&(*pBtreeNode)->right,data);
    else if((*pBtreeNode)->data > data)
        return insertBST(&(*pBtreeNode)->left,data);
    return false;//repeat insert
}
//searchBST
//bTreeNode *searchBST(bTreeNode *pNode,valueType data,bTreeNode *f){
//    //isroot
//    if(data == pNode->data)
//    //
//}

//deleteBST

//quickSort
int partition(std::vector<int> &arr,int low,int high){
    int pivotKey = arr[low];
    while(low<high){
        while(low<high && arr[high]>=pivotKey)
            --high;
        arr[low] = arr[high];
        while(low<high && arr[low]<=pivotKey)
            ++low;
        arr[high] = arr[low];
    }
    arr[low] = pivotKey;
    return low;
}
void QSort(std::vector<int> &arr,int low,int high){
    int pivot;
    if(low<high){
        pivot = partition(arr,low,high);
        QSort(arr,low,pivot-1);
        QSort(arr,pivot+1,high);
    }
}

//
void insertionSort(std::vector<int> &arr){
        int length = arr.size();
        int temp = 0;
        for(int i = 1;i<length;++i){
            if(arr[i] < arr[i-1]){
                temp = arr[i];
                int j = i-1;
                while(j!=-1 && arr[j] > temp){
                    arr[j+1] = arr[j];
                    --j;
                }
                arr[j+1] = temp;
            }
        }
    }



//merging sort
//void mergeSort2(Sqlist *L){
//    int *TR= (int *)malloc(sizeof(int) * L->length);
//    int k =1;
//    while(KK<L->length){
//        mergepass(l->r,TR,k,l_.length);
//        k*=2;
//        mergepass(TR,l->r,k,L>length);
//        k*=2;
//    }
//}

int main(){
    bTreeNode *root = nullptr;
    createBTree(&root);
//    levelOrderTraversalWithQueue(root);
    //levelOrderTraversalToVector(root);
}
