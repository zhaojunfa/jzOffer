#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>
#include <list>
#include <unordered_map>

using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(!head)
            return false;
        auto fast = head,slow = fast;
        while(fast->next){
            slow = slow->next;
            if(fast->next)
                fast = fast->next->next;
            if(fast == slow)
                return true;
        }
        return false;
    }

    int search(vector<int>& nums, int target) {
        // write code here
        if(nums.empty())
            return -1;
        int beg = 0,end = nums.size()-1,mid = beg + (end-beg)/2;
        while(end != beg){
            if(target <= nums[mid])
                end = mid;
            if(target > nums[mid])
                beg = mid + 1;
            mid = beg + (end - beg)/2;
        }
        if(nums[mid] == target)
            return mid;
        else
            return -1;
    }

    //NC68
    int jumpFloor(int number) {
        int i = 1,j=2;
        if(number < 0) return -1;
        if(number == 1) return i;
        if(number == 2) return j;
        int temp;
        for(int k = 0;k < number - 3; ++k){
            temp = j;
            j += i;
            i = temp;
        }
        return i+j;
    }

    //NC41
    bool isDuplicated(std::set<int> &subArr,int &data){
        int sz = static_cast<int>(subArr.size());
        subArr.insert(data);
        if(sz == static_cast<int>(subArr.size()))
            return true;
        return false;
    }

    int maxLength(vector<int>& arr) {
        //arr.empty()
        if(arr.empty())
            return 0;
        int max = 1;
        int fi = 0;
        int distance = 0;
        std::set<int> nodes;
        for(int i = 0; i < static_cast<int>(arr.size()); ++i){
            if(isDuplicated(nodes,arr[i])){
                distance = i;
                while(arr[--distance] != arr[i]){}
                distance = i - distance;
                fi = distance <= fi ? distance : fi+1;
            }
            else
                ++fi;
            max = fi > max ? fi : max;
        }
        return max;
    }
    //NC22
    void merge(int A[], int m, int B[], int n) {
        //a.size = m + n  b.size = n
        int i = m+n;
        --m;
        --n;
        while(m >= 0 && n >=0)
            if(A[m] > B[n]){
                A[--i] = A[m--];

            }
            else{
                A[--i] = B[n--];
            }
        if(m==-1){
            while(n>=0)
                A[--i] = B[n--];
        }
    }

    //NC88
    int partition(std::vector<int> &arr,int low,int high){
        int pivotKey = arr[low];
        while(low < high){
            while(low < high && arr[high] >= pivotKey)
                --high;
            arr[low] = arr[high];
            while(low < high && arr[low] <= pivotKey)
                ++low;
            arr[high] = arr[low];
        }
        arr[low] = pivotKey;
        return low;
    }
    void qsort(std::vector<int> &arr,int low,int high){
        int pivot = 0;
        if(low < high){
            pivot = partition(arr,low,high);
            qsort(arr,low,pivot-1);
            qsort(arr,pivot+1,high);
        }
    }
    void swap(int &a,int &b){
        auto temp = a;
        a = b;
        b = temp;
    }
    void heapAdjust(std::vector<int> &arr,int s,int m){//start from 0
        //node has child
        int sData = arr[s];
        int j;
        for(j = s*2+1;j<=m;j=j*2+1){
            if(j<m && arr[j] < arr[j+1])
                ++j;
            if(arr[j] <= sData)
                break;
            arr[s] = arr[j];
            s = j;
        }
        arr[s] = sData;
    }
    //NC88
    void heapSort(std::vector<int> &arr){
        //check
        if(arr.empty())
            return;
        int length = arr.size(), i;
        for(i = length/2-1;i>=0;--i)
            heapAdjust(arr,i,length-1);
        for(i = length-1;i>0;--i){
            swap(arr[0],arr[i]);
            heapAdjust(arr,0,i-1);
        }
    }


    //NC19
    int maxsumofSubarray(vector<int>& arr) {
        // write code here
        if(arr.empty())
            return 0;
        int max=0,currSum = 0;
        for(auto e:arr){
            currSum+=e;
            if(currSum<0)
                currSum=0;
            else{
                max = currSum>max?currSum:max;
            }
        }
        return max;
    }

    //NC103
    string solve(string str) {
        // write code here
        reverse(str.begin(),str.end());
        return str;
    }

    //NC17
    int getLongestPalindrome(string A, int n) {
        // write code here
        //dp[i][j]
        int dp[n][n];
        int max_length = 0;
        for(auto &ar:dp)
            for(auto &e:ar)
                e=0;//init dp
        for(int i =n-1;i>=0;--i){
            for(int j = i;j<n;++j){
                int len = j-i+1;
                if(A[i]==A[j]){
                    if(len <=2)
                        dp[i][j]=1;
                    else
                        dp[i][j]=dp[i+1][j-1];
                }
                if(dp[i][j]){
                    if(len > max_length)
                        max_length=len;
                }
            }
        }
        return max_length;
    }

    //NC137
    void searchAndReplace(std::string &value,const std::string &search,const std::string &replace){
        auto next = value.find(search);
        while(next!=std::string::npos){
            value.replace(next,search.length(),replace);
            next = value.find(search,next+replace.length());
        }
    }


    int solve_(string s) {
        // write code here
        std::vector<string> L;
        //L.push_back("0");
        std::stack<char> opts;
        stringstream stream;
        searchAndReplace(s,"(-","(0-");
        searchAndReplace(s,"(+","(0+");
        //remove ' '
        s.erase(remove(s.begin(),s.end(),' '),s.end());
        for(auto it = s.begin();it!=s.end();++it){
            //1.'(' opts.push
            if(*it == '(' || *it == '*')
                opts.push(*it);
            else if(*it == ')'){
                while(opts.top()!='('){
                    stream.clear();
                    stream.str("");
                    stream << opts.top();
                    L.push_back(stream.str());
                    opts.pop();
                }
                opts.pop();//(
            }
            else if(*it == '+' || *it == '-'){
                while(!opts.empty() && opts.top() != '(' && opts.top()!=')'){
                    stream.clear();
                    stream.str("");
                    stream << opts.top();
                    L.push_back(stream.str());
                    opts.pop();
                }
                opts.push(*it);
            }
            else{
                //num
                int num =0;
                while(*it>='0' && *it<='9' && it!=s.end()){
                    num = num*10 + *(it++) - '0';
                }
                --it;
                stream.clear();
                stream.str("");
                stream << num;
                L.push_back(stream.str());
            }
        }
        while(!opts.empty()){
            stream.clear();
            stream.str("");
            stream << opts.top();
            L.push_back(stream.str());
            opts.pop();
        }
        //calc
        std::stack<int> int_stack;
        for(auto &e:L){
            stream.clear();
            stream.str("");
            stream << e;
            int num;
            stream >> num;
            if(num!=0)
                int_stack.push(num);
            else{
                int r = int_stack.top();
                int_stack.pop();
                int l = int_stack.top();
                int_stack.pop();
                if(e == "+")
                    int_stack.push(r+l);
                else if(e == "-")
                    int_stack.push(l-r);
                else
                    int_stack.push(l*r);
            }
        }
        return int_stack.top();
    }

    //NC93 LRU
    typedef struct list_node{
        int key;//when head node key = max length
        int value;//when head node value = currlength
        list_node *next,*pre;
        list_node(){key = -1;value=-1;next=pre=nullptr;}
    } listNode,*pListNode;

    void set(pListNode &head,std::unordered_map<int,pListNode> &lru_map, int key,int value){
        if(head->value != head->key){//not full
            auto tempPListNode = head->next;
            for(int i=0;i<head->value;++i)
                tempPListNode = tempPListNode->next;
            tempPListNode->value = value;
            lru_map.insert({key,tempPListNode});
        }
        else{//full
            auto curr_node = head->next;
            curr_node->key = key;
            curr_node->value = value;
            if(head->key > 1){
                auto tail_node = head->pre;
                auto next_node = curr_node->next;
                head->next = next_node;
                next_node->pre = head;
                tail_node->next = curr_node;
                curr_node->pre = tail_node;
                curr_node->next = head;
                head->pre = curr_node;
            }
            //map
            int key_toremove = head->next->key;
            pListNode node_addr = nullptr;
            auto it = lru_map.find(key_toremove);
            if(it != lru_map.end()){
                node_addr = it->second;
                lru_map.erase(it);
            }
            lru_map.insert({key,node_addr});
        }
    }

    int get(std::unordered_map<int,pListNode> lru_map, pListNode &head,int key){

    }

    vector<int> LRU(vector<vector<int> >& operators, int k) {
        // write code here
        pListNode head = new listNode(); head->key=k; head->value = 0;
        pListNode pre = head;
        pListNode next = pre->next;
        for(int i=0;i<k;++i){
            next = new listNode();
            next->pre = pre;
            pre = next;
            next = next->next;
        }//k+1 nodes
        //
        std::unordered_map<int,pListNode> lur_map;

    }
};








int main()
{
    cout << "Hello World!" << endl;
    Solution *s = new Solution();
    s->solve_("3+2*3*4-1");




}
