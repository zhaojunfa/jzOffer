/*数组中重复的数字
 * 长度为n的数组所有数字都属于0~n-1。数组某些数字是重复的但是不知几个数字重复了也不知道每个数字重复几次。找出任意一个重复的数字即可。
 * input： {2,3,1,0,2,5,3}  | {0,1,2,3,4}  |  {-8,-7,2,3}   |{}
 * output：    2 或 3       |     -1       |      -1        |-1
 * 0810
*/
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void swap(int &a,int &b){
    int temp = a;
    a = b;
    b = temp;
}

/* {2310253}->{1320253}->{3120253}->{0123253}->return;
 * Time complexity = O(n)
 * Space complexity = 0
 * 100 0000次
 * real 0.7s
 * user 0.03s
 * sys 0.119s
 */
int hht(int numbers[],int length){
    //check numbers and length
    if(numbers == nullptr || length <= 0)
        return -1;
    //check elements' range
    for(auto i = 0;i < length; ++i)
        if(numbers[i] < 0 || numbers[i] > length - 1)
            return -1;
    //hash table
    for(int i = 0; i < length; ++i){
        while(numbers[i] != i){
            if(numbers[numbers[i]] == numbers[i])
                return numbers[i];
            swap(numbers[numbers[i]], numbers[i]);
        }
    }
    return -1;
}

/* 申请额外n个元素的数组初始为-1。按下标存元素更快找出重复的数字。
 * Time complexity = O(n)
 * Space complexity = O(n)
 * 100,0000次
 * real 0.8s
 * user 0.3s
 * sys 0.2s
 */
int my(vector<int> &vec){
    //check array
    if(vec.empty())
        return -1;
    //check elemets && hash table
    int length = (int) vec.size();
    vector<int> temp(length,-1);
    for(auto &i:vec){
        if(i < 0 || i > length - 1)
            return -1;
        if(temp[i] == i)
            return i;
        temp[i] = i;
    }
    return -1;
}
/*my内置数组版
 * 100,0000次
 * real 0.7s
 * user 0.1s
 * sys 0.15s
*/
int my_(int nums[],int length){
    //check nums[]
    if(nums == nullptr || length <= 0)
        return -1;
    //check elements
    for(int i = 0; i < length; ++i)
        if(nums[i] < 0 || nums[i] > length)
            return -1;
    //
    int *temp = new int[length];
    for(int i = 0; i < length; ++i)
        *(temp + i) = -1;
    for(int i = 0; i < length; ++i){
        if(*(temp + nums[i]) == nums[i])
            return nums[i];
        *(temp + nums[i]) = nums[i];
    }
    return -1;
}

/* 题目二:不修改数组 找出重复的数字:
 *      在一个长度为n+1的数组里所有的数字都在1~n的范围内，所以数组中至少有一个数字是重复的。找出任意一个重复的数字但不能修改数组
 * input:{2,3,5,4,3,2,6,7}
 * output:    2 或 3
 * 方法1:辅助数组 O(n) O(n)::略
 * 方法2:二分查找 O(nlogn) O(1)时间换空间::htt_(int nums[],int length);
*/

//hht_不能找出所有的重复数字，输入{2,3,5,4,3,2,6,7}一定会找到3而不是2。

//统计start 和 end范围之间出现的次数
int countRange(int nums[], int length, int start, int end){
    int tempCount = 0;
    for(int i = 0; i < length; ++i){
        if(start <= nums[i] && nums[i] <= end)
            ++tempCount;
    }
    return tempCount;
}

int htt_(int nums[],int length){
    //check
    if(nums == nullptr || length <= 0)
        return -1;
    //check elements
    for(int i = 0; i < length; ++i)
        if(nums[i] < 1 || nums[i] >= length)
            return -1;
    //do
    int count, start = 1, mid, end = length -1;
    while(end >= start){
        mid = ((end - start) >> 1) + start;
        count = countRange(nums,length,start,mid);
        if(end == start){
            if(count > 1)
                return start;
            else
                break;
        }//处理end = start的情况
        if(count > mid - start + 1)
            end = mid;
        else
            start = mid + 1;
    }
    return -1;
}



int main(){
    int nums[] = {2,3,1,0,2,5,3};//第一题的
    int nums_[] ={2,3,5,4,3,2,6,7};//第二题的
    //vector<int> numbers{2,3,1,0,2,5,3};
    return htt_(nums_,8);//第二题的

    return hht(nums,7);//第一题中的三个方法这个更快
    //return my(numbers);//
    //return my_(nums,7);
}
