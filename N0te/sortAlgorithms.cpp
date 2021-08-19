/*
 *sort algorithm(s)
*/
#include "dataStructure.h"
using namespace std;

void bubbleSort(vector<int> &vec){
    if(vec.empty())
        return;
    int length = vec.size();
    int location = length - 1;//
    for(int j = length - 1; j > 0; --j){
        bool isSorted = true;//optimization 1 /..Not necessarily useful
        for(int i = 0; i < j; ++i){
            if(vec[i] > vec[i + 1]){
                location = i;
                isSorted = false;
                auto temp = vec[i];
                vec[i] = vec[i + 1];
                vec[i + 1] = temp;
            }
            if(i > location) break;//optimization 2/Record the ordered part of the tail
        }
        if(isSorted)
           ;//return;
    }
}

void selectionSort(vector<int> &arr){
    if(arr.empty())
        return;
    //Looking for the biggest elements,Put it to the last element
    int length = arr.size();
    for(int j = length - 1; j > 0; --j){
        int maxIndex = 0;
        for(int i = 0; i <= j; ++i){
            if(arr[i] >= arr[maxIndex])//In fact, it cannot guarantee stability.<= Can only increase some stability
                maxIndex = i;
        }
        auto temp = arr[j];
        arr[j] = arr[maxIndex];
        arr[maxIndex] = temp;
    }
}
// 'Select Sort' has Optimized Space:heapSort!
void heapSort(vector<int> arr){

}

void insertionSort(vector<int> &arr){
    //Insert sorting likes playing card.arr[0] = 0(Sentinel node)
    //053462
    int length = arr.size();
    for(int i = 2; i < length; ++i){
        if(arr[i] <arr[i-1]){//
            arr[0] = arr[i];
            auto temp = i-1;
            while(arr[temp] > arr[0]){
                arr[temp+1] = arr[temp];
                --temp;
            }
            arr[temp+1] = arr[0];
        }
    }
}

void shellSort(std::vector<int> arr){
/*
 * length = 9 r[10] = {0,9,1,5,8,3,7,4,6,2}     0 is guard node.
 * increment =
*/
    int increment = arr.size();
    int j = 0;
    do{
        increment = increment / 3 + 1;
        for(int i = increment;i != (int)arr.size(); ++i){
            if(arr[i] < arr[i - increment]){
                arr[0] = arr[i];
                for(j = i - increment;j>0 && arr[0] < arr[j];j-=increment)
                    arr[j+increment] = arr[j];
                arr[j+increment] = arr[0];
            }
        }
    }while(increment > 1);
}


int main(){


    bTreeNode *root = nullptr;
    createBTree(&root);
    //inOrderTraversalWithStack_(root);//213
    //postOrderTraversalWith1Stack_(root);
    vector<int> arr = {8,9,5,7,1,4,3,2};
    vector<int> arr_ = {1,2,3,4,5,6,7,8,9};
    //bubbleSort(arr);
    //selectionSort(arr);
    //selectionSort(arr);
    //for(auto e:arr)
        //cout << e << ' ';
}
