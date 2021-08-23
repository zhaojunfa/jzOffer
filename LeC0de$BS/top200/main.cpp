#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>
#include <list>
#include <queue>
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
        //judge if the key existed.
        auto it = lru_map.find(key);
        if(it != lru_map.end()){//duplicated
            //update value
            it->second->value = value;
            //put tail
            if(head->value == 1)
                return;//only one node has data.return
            auto tail_valid_node = head;//1
            for(int i=0;i<head->value;++i)
                tail_valid_node = tail_valid_node->next;
            auto first_empty_node = tail_valid_node->next;
            auto pre_node = it->second->pre;
            //
            pre_node->next = it->second->next;
            it->second->pre = pre_node;
            //
            tail_valid_node->next = it->second;
            it->second->pre = tail_valid_node;
            //
            it->second->next = first_empty_node;
            first_empty_node->pre = it->second;
        }

        //single key.not repeated.
        if(head->value != head->key){//not full
            auto tempPListNode = head->next;
            for(int i=0;i<head->value;++i)
                tempPListNode = tempPListNode->next;
            tempPListNode->key = key;
            tempPListNode->value = value;
            ++head->value;
            lru_map.insert({key,tempPListNode});
        }
        else{//full
            int key_toremove = head->next->key;
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

            pListNode node_addr = nullptr;
            it = lru_map.find(key_toremove);
            if(it != lru_map.end()){
                node_addr = it->second;
                lru_map.erase(it);
            }
            lru_map.insert({key,node_addr});
        }
    }

    int get(std::unordered_map<int,pListNode> lru_map, pListNode &head,int key){
        auto it = lru_map.find(key);
        if(it != lru_map.end()){
            if(head->value == head->key){//full
                auto curr_node = it->second;
                //
                auto tail_node = head->pre;
                auto next_node = curr_node->next;
                head->next = next_node;
                next_node->pre = head;
                tail_node->next = curr_node;
                curr_node->pre = tail_node;
                curr_node->next = head;
                head->pre = curr_node;
            }
            else{//notfull
                auto tempPListNode = head->next;
                for(int i=0;i<head->value;++i)
                    tempPListNode = tempPListNode->next;
                auto last_node = tempPListNode->pre;
                auto pre_node = it->second->pre;
                auto next_node = it->second->next;
                pre_node->next = next_node;
                next_node->pre = pre_node;
                last_node->next = it->second;
                it->second->pre = last_node;
                it->second->next = tempPListNode;
                tempPListNode->pre = it->second;
            }
            return it->second->value;
        }
        else
            return -1;
    }

    vector<int> LRU(vector<vector<int> >& operators, int k) {
        // write code here
        pListNode head = new listNode(); head->key=k; head->value = 0;
        pListNode pre = head;
        //        pListNode next = head->next;
        for(int i=0;i<k;++i){
            pre->next = new listNode();
            if(i==k-1){
                pre->next->next = head;
                head->pre = pre->next;
            }
            pre->next->pre = pre;
            pre = pre->next;
        }//k+1 nodes
        //
        std::unordered_map<int,pListNode> lru_map;
        std::vector<int> result;
        for(auto &vec:operators){
            if(vec[0] == 1)
                set(head,lru_map,vec[1],vec[2]);
            else
                result.push_back(get(lru_map,head,vec[1]));
        }
        return result;
    }

    //NC40  Add two linked lists to a new list
    ListNode* addInList(ListNode* head1, ListNode* head2) {
        // two statck
        std::list<int> list_1,list_2;
        while(head1 || head2){
            if(!head1)
                list_1.push_front(0);
            else{
                list_1.push_back(head1->val);
                head1 = head1->next;
            }
            if(!head2)
                list_2.push_front(0);
            else{
                list_2.push_back(head2->val);
                head2 = head2->next;
            }
        }//list_1 and list_2 has the same size;
        std::stack<int> sum_step_1;//may has 10.11..12...
        for(auto it_1=list_1.begin(),it_2=list_2.begin();
            it_1!=list_1.end();++it_1,++it_2){
            sum_step_1.push(*it_1 + *it_2);
        }
        //%10
        std::vector<int> sum_step_2;//%10
        int top_element;
        bool flag;
        while(!sum_step_1.empty()){
            top_element = sum_step_1.top();
            sum_step_1.pop();
            flag = top_element/10 > 0 ? true : false;
            if(flag && !sum_step_1.empty())
                ++sum_step_1.top();
            sum_step_2.push_back(top_element%10);
        }
        if(flag)
            sum_step_2.push_back(1);
        //make a list to return
        ListNode *sum_step_3 = new ListNode(-1);
        auto temp = sum_step_3;
        for(auto it = sum_step_2.rbegin();it!=sum_step_2.rend();++it){
            temp->next = new ListNode(*it);
            temp = temp->next;
        }
        temp = sum_step_3;
        sum_step_3 = sum_step_3->next;
        delete  temp;
        return sum_step_3;
    }


    //NC7 The best time trading stock
    int maxProfit(vector<int>& prices) {
        // write code here
        //dp[i] means saling the stock at the i day;
        int size = prices.size();
        int dp = 0;
        int max=0;
        for(int i=1;i<size;++i){
            dp = dp>=0?dp + prices[i]-prices[i-1]:prices[i]-prices[i-1];
            max = dp > max ? dp : max;
        }
        return max;
    }

    //NC1  Large number addition
    string solve__(string s, string t) {
        //
        std::reverse(s.begin(),s.end());
        std::reverse(t.begin(),t.end());
        std::queue<int> resultWithQueue;
        int sLength = s.size();
        int tLength = t.size();
        for(int i=0;i<min(sLength,tLength);++i){
            resultWithQueue.push(s[i]-'0'+t[i]-'0');
        }
        if(sLength > tLength){
            for(int i=tLength;i<sLength;++i)
                resultWithQueue.push(s[i]-'0');
        }
        else{
            for(int i = sLength;i<tLength;++i){
                resultWithQueue.push(t[i]-'0');
            }
        }//resultWithStack fin
        bool flag;
        int topElement;
        std::string resultWithString;
        while(!resultWithQueue.empty()){
            topElement = resultWithQueue.front();
            resultWithQueue.pop();
            flag = topElement/10 > 0 ? true : false;
            resultWithString.push_back(topElement%10 + '0');
            if(flag && !resultWithQueue.empty()){
                ++resultWithQueue.front();
            }
        }
        if(flag)
            resultWithString.push_back('1');
        std::reverse(resultWithString.begin(),resultWithString.end());
        return resultWithString;
    }
};








int main()
{
    cout << "Hello World!" << endl;
    Solution *s = new Solution();

    string s1 = "1";
    string s2 = "99";
    s->solve__(s1,s2);



}
