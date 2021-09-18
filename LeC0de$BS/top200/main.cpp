#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>
#include <list>
#include <queue>
#include <unordered_map>
#include <pthread.h>
#include <thread>
#include <cstdlib>
#include <unistd.h>
#include <map>


using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
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

    //NC78
    ListNode* ReverseList(ListNode* pHead) {
        if(!pHead)
            return nullptr;
        ListNode *pre = nullptr;
        ListNode *cur = pHead;
        while(cur){
            ListNode *next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
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
    //
    int calcScore(vector<vector<int>> &kArr){
        //empty vector
        for(auto &vec:kArr)
            if(vec.empty())
                return -100;
        int sum = 0, sz = kArr.size();
        for(int i=0;i<sz;++i){
            for(auto &ai:kArr[i])
                sum += ai * (i+1);
        }
        return sum;
    }


    int maxScore(vector<int> &nums,int k){
        queue<vector<vector<int>>> q;
        q.push(vector<vector<int>>(k,vector<int>()));
        int score = -100;
        while(!q.empty()){
            //            if(nums.empty())
            //                return score;

            //
            int q_size = q.size();
            for(int b=0;b<q_size;++b){
                auto frontElement = q.front();
                q.pop();
                for(int i=0;i<k;++i){
                    if(nums.empty()){
                        int res = calcScore(frontElement);
                        score = res > score ? res : score;
                        for(auto &vec:frontElement){
                            for(auto &num : vec)
                                cout << num << ' ';
                            cout << endl;
                        }
                        continue;
                    }
                    auto frontElement_ = frontElement;
                    frontElement_[i].push_back(nums.back());
                    q.push(frontElement_);

                }
            }
            nums.pop_back();
        }
        return score;
    }


    //nc102 A
    bool dfs_102(TreeNode *&root,int &o,vector<int> &nodes){
        if(!root)
            return false;
        nodes.push_back(root->val);
        if(root->val == o)
            return true;
        if(dfs_102(root->left,o,nodes))
            return true;
        if(dfs_102(root->right,o,nodes))
            return true;
        nodes.pop_back();
        return false;
    }

    int lowestCommonAncestor(TreeNode* root, int o1, int o2) {
        // write code here
        vector<int> node_o1,node_o2;

        auto is_exist_o1 = dfs_102(root,o1,node_o1);
        auto is_exist_o2 = dfs_102(root,o2,node_o2);
        if(!is_exist_o1 || !is_exist_o2)
            return -1;
        int top;
        while(node_o1.front() == node_o2.front()){
            top = node_o1.front();
            node_o1.erase(node_o1.begin());
            node_o2.erase(node_o2.begin());
        }
        return top;
    }

    //NC8 A
    void dfs_8(vector<vector<int>> &res, vector<int> &track, int sum , TreeNode *&root){
        if(!root)
            return;
        track.push_back(root->val);
        if(!root->left && !root->right)
        {
            if(root->val == sum){
                res.push_back(track);
                track.pop_back();
                return;
            }
        }
        dfs_8(res,track,sum-root->val,root->left);
        dfs_8(res,track,sum-root->val,root->right);
        track.pop_back();
    }

    vector<vector<int> > pathSum(TreeNode* root, int sum) {
        // write code here
        vector<vector<int>> res;
        vector<int> track;
        dfs_8(res,track,sum,root);
        return res;
    }

    //NC3 {1,2},{3,4,5} 3 A
    ListNode* EntryNodeOfLoop(ListNode* pHead) {
        ListNode *slow =pHead,*fast = pHead;
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast){
                slow =pHead;
                while(slow != fast){
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;
            }
        }
        return nullptr;
    }

    //NC53  A
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // write code here
        ListNode *slow = head, *fast = head;
        for(int i=0;i<n;++i){
            fast = fast->next;
        }
        ListNode *pre = slow;
        while(fast){
            pre = slow;
            slow = slow->next;
            fast = fast->next;
        }
        if(pre == slow){
            auto temp = pre->next;
            delete  pre;
            return temp;
        }
        else{
            pre->next = slow->next;
            delete slow;
            return head;
        }
    }


    void createTree(TreeNode *&root,queue<int> &data){
        auto front = data.front();
        data.pop();
        if(front != -1){
            root = new TreeNode(front);
            createTree(root->left,data);
            createTree(root->right,data);
        }
        else{
            root = nullptr;
        }
        return;
    }
    //NC14
    vector<vector<int> > Print(TreeNode* pRoot) {
        if(!pRoot)
            return vector<vector<int>>();
        vector<vector<int>> res;
        vector<int> res_level;
        queue<TreeNode *> q;
        q.push(pRoot);
        //        res_level.push_back(pRoot->val);
        //        res.push_back(res_level);
        int level = 0;
        while(!q.empty()){
            int sz = q.size();
            ++level;
            res_level.clear();
            for(int i=0;i<sz;++i){
                auto front = q.front();
                q.pop();
                res_level.push_back(front->val);
                if(front->left)
                    q.push(front->left);
                if(front->right)
                    q.push(front->right);
            }
            if(level % 2 == 0)
            {
                std::reverse(res_level.begin(),res_level.end());
                res.push_back(res_level);
            }
            else
                res.push_back(res_level);
        }
        return res;
    }

    /*jzoffer p86*/
    int minInOrder(int *numbers,int index1,int index2);//todo
    int min_86(int *numbers,int length){
        if(numbers == nullptr || length <=0){
            //throw new std::exception("Invalid Parameters");
            return -1;
        }
        int index1=0,index2=length-1,indexMid=index1;
        while(numbers[index1] >= numbers[index2]){
            if(index2 - index1 == 1){
                indexMid = index2;
                break;
            }
            indexMid = index1 + (index2-index1)/2;
            //if numbers[index1] == numbers[index2] ==numbers[indexMid] then search by Order in [numbers[index1],numbers[index2]].
            if(numbers[index1] == numbers[index2] && numbers[index1] == numbers[indexMid])
                return minInOrder(numbers,index1,index2);
            //main code
            if(numbers[index1] >= numbers[indexMid])
                index2 = indexMid;
            else
                index1 = indexMid;
        }
        return numbers[indexMid];
    }
    /*jzoffer p88:PATH IN MATRIX*/
    bool hasPathCore(const char *matrix,int rows,int cols,int row,int col,const char *str,int &pathLength,bool *visited){
        //end condition  using backTrack!!
        if(str[pathLength] == '\0')
            return true;
        //make choices
        bool hasPath = false;
        if(matrix[row * cols + col] == str[pathLength] && !visited[row*cols+col] && row >=0 && row <= rows && col >=0 && col <=cols){
            ++pathLength;
            visited[row*cols+col] = true;
            hasPath = hasPathCore(matrix,rows,cols,row+1,col,str,pathLength,visited)
                    || hasPathCore(matrix,rows,cols,row-1,col,str,pathLength,visited)
                    || hasPathCore(matrix,rows,cols,row,col+1,str,pathLength,visited)
                    || hasPathCore(matrix,rows,cols,row,col-1,str,pathLength,visited);
            if(!hasPath){
                --pathLength;
                visited[row * cols + col] = false;
            }
        }
        return hasPath;
    }
    bool hasPath(char *matrix,int rows,int cols,char *str){
        if(matrix == nullptr || rows <= 0 || cols <= 0 || str == nullptr)
            return false;
        bool *visited = new bool[rows * cols];
        memset(visited,0,rows*cols);
        int pathLength = 0;
        for(int i=0;i<rows;++i){
            for(int j=0;j<cols;++j){
                if(hasPathCore(matrix,rows,cols,i,j,str,pathLength,visited))
                    return true;
            }
        }
        delete [] visited;
        return false;
    }
    /*jzoffer p92  trackback*/
    int getDigitSum(int num){
        int sum =0;
        while(num>0){
            sum+= num%10;
            num/=10;
        }
        return sum;
    }
    bool check(int threshold,int rows,int cols,int row,int col,bool *visited){
        if(row>=0 && col>=0 && row<=rows && col<=cols && getDigitSum(row)+getDigitSum(col)<=threshold && !visited[row*cols+col])
            return true;
        return false;
    }
    int movingCountCore(int threshold,int rows,int row,int cols,int col,bool *visited){
        int count=0;
        if(check(threshold,rows,cols,row,col,visited)){
            visited[row*cols+col] = true;
            count = 1+movingCountCore(threshold,rows,row+1,cols,col,visited)
                    +movingCountCore(threshold,rows,row-1,cols,col,visited)
                    +movingCountCore(threshold,rows,row,cols,col+1,visited)
                    +movingCountCore(threshold,rows,row,cols,col-1,visited);
        }
        return count;
    }
    int movingCount(int threshold,int rows,int cols){
        if(threshold<0||rows<=0||cols<=0)
            return 0;
        bool *visited = new bool[rows*cols];
        memset(visited,0,rows*cols);
        int count = movingCountCore(threshold,rows,0,cols,0,visited);
        delete [] visited;
        return count;
    }
    /*jz p96*/
    int maxProductAfterCutting_solution1(int length){
        //dp
        if(length<2)
            return 0;
        else if(length == 2)
            return 1;
        else if(length == 3)
            return 2;
        int *product = new int[length+1];
        product[0]=0;
        product[1]=1;
        product[2]=2;
        product[3]=3;
        int max =0;
        for(int i=4;i<=length;++i){
            max=0;
            for(int j=1;j<i/2;++j){
                if(product[j]*product[i-j] > max)
                    max = product[j]*product[i-j];
                product[i] =max;
            }
        }
        max=product[length];
        delete [] product;
        return max;
    }

    int maxProductAfterCutting_solution2(int length){
        if(length<2)
            return 0;
        else if(length ==2)
            return 1;
        else if(length ==3)
            return 2;
        int timeOf3 = length/3;
        if(length - timeOf3*3 == 1)
            --timeOf3;
        int timeOf2 = (length - 3*timeOf3)/2;
        return (int)pow(3,timeOf3) * (int)pow(2,timeOf2);
    }

    /*jz102*/
    int numberOf1(int n){
        int count=0;
        while(n){
            ++count;
            n = n & (n-1);
            /*
             * 1011 & 1010 = 1010,
             * 1010 & 1001 = 1000,
             * 1000 & 0111 = 0000,
             * so count =3;*/
        }
        return count;
    }
    //if an integer is power of 2:
    bool ifPowerOf2(int n){
        return (n & (n-1)) == 0 ?true:false;
    }
    /*lbd p93*/
    /*main
    string s("cbaebabacd"),t("abc");
    Solution *solution = new Solution();
    auto res = solution->findAnagrams(s,t);*/
    vector<int> findAnagrams(string s,string t){
        unordered_map<char,int> need,window;
        for(char e:t)
            ++need[e];
        int left=0,right=0,valid=0;
        vector<int> res;
        while(right<(int)s.size()){
            char c = s[right++];
            if(need.count(c)){
                ++window[c];
                if(need[c] == window[c])
                    ++valid;
            }
            while(right-left>=(int)t.size()){
                if(valid == (int)need.size()){
                    res.push_back(left);
                    //                    left = right;
                    //                    window.clear();
                    //                    valid = 0;
                    //                    break;
                }
                char d = s[left++];
                if(need.count(d)){
                    if(need[d] == window[d]--)
                        --valid;
                }
            }
        }
        return res;
    }

    //1.7.4 "aabab"->2
    int lengthOfLongestSubstring_dp(string &s){
        int max = 0;
        int d;
        int fi = 0;
        std::set<char> window;
        for(int i=0;i<(int)s.size();++i){
            if(window.insert(s[i]).second)
                ++fi;
            else{
                d = i;
                while(s[--d] != s[i]){}
                d = i-d;
                if(d > fi)
                    ++fi;
                else
                    fi = d;
            }
            if(fi > max)
                max = fi;
        }
        return max;
    }

    int lengthOfLongestSubstring_slidingWindow(string &s){
        unordered_map<char,int> window;
        int left=0,right=0,res=0;
        while(right < (int)s.size()){
            char c = s[right++];
            ++window[c];
            while(window[c]>1){
                char d = s[left++];
                --window[d];
            }
            res = max(res,right-left);
        }
        return res;
    }
    //lbd chapter2 dp p101
    int lengthOfLIS(vector<int> &source){
        int source_size = source.size();
        vector<int> dp(source_size,1);
        int length=0;
        for(int x=0;x<source_size;++x){//calc dp[x]
            int temp = -1;
            for(int y=0;y<x;++y){
                if(source[y] < source[x]){
                    if(dp[y] > temp)
                        temp = dp[y];
                }
            }
            if(temp == -1)
                dp[x] = 1;
            else
                dp[x] = temp+1;
            if(dp[x] > length)
                length = dp[x];
        }
        return length;
    }

    int lengthOfLIS_bs(vector<int> &source_data){
        /*auto so = new Solution();
    vector<int> source{6,3,5,10,11,2,9,14,13,7,4,8,12};
    cout << so->lengthOfLIS_bs(source);
    return 0;*/
        vector<int> top(source_data.size(),0);
        int piles = 0;
        for(int i=0;i<(int)source_data.size();++i){
            int poker = source_data[i];
            //find left-bound
            int left = 0,right = piles;
            while(left<right){
                int mid = left+(right-left)/2;
                if(top[mid] > poker){
                    right = mid;
                }
                else if(top[mid] < poker)
                    left = mid +1;
                else
                    right = mid;
            }
            if(left == piles)
                ++piles;
            top[left] = poker;
            for(auto e:top)
                cout <<e << ' ';
            cout <<endl;
        }
        return piles;
    }

    //dp[][]
    /*
     *1,8  2,3  5,4  5,2  6,7  6,4
     *2,3=> 5,4 => 6,7
    */
    static bool compare_w(vector<int> &first,vector<int> &second){
        return first[0] < second[0];
    }
    static bool compare_h(vector<int> &first,vector<int> &second){
        return first[1] > second[1];
    }
    int maxEnvelopes(){
        vector<vector<int>> data{{1,8},{5,4},{6,7},{5,2},{6,4},{2,3},{5,9}};
        //sore w + h
        std::sort(data.begin(),data.end(),compare_w);
        int current_index_val = 0;
        for(auto it = data.begin();it != data.end();++it){
            if(it->at(0) != current_index_val)
                current_index_val = it->at(0);
            else{
                vector<vector<int>>::iterator left = it - 1;
                vector<vector<int>>::iterator right = it;
                while(right != data.end() && right->at(0) == current_index_val)
                    ++right;
                it = right-1;
                std::sort(left,right,compare_h);//todo
            }
        }
        return 0;
    }

    //1
    void getData(std::vector<int> &data,int &M){
        int N=0;
        cin >> N;
        cin >> M;
        int temp;
        std::set<int> data_set;
        for(int i=0;i<N;++i){
            cin >> temp;
            data_set.insert(temp);
        }
        data.assign(data_set.begin(),data_set.end());
    }

    int getMaxOFFA(){
        std::vector<int> data;
        std::set<std::set<int>> resu;
        int M;
        int res=0;
        getData(data,M);
        int sz = data.size();
        if(sz < 3){
            cout << 0;
            return res;
        }
        int sumOf3 = data[sz-1]+data[sz-2]+data[sz-3];
        if(sumOf3 %M==0)
            ++res;
        for(int i=sz-4;i>=0;--i){
            sumOf3 -= data[i+3];
            sumOf3 += data[i];
            if((sumOf3)%M == 0)
                ++res;
        }
        return res;

    }

    //2





};


int main(){
    //vector<vector<int>> mhz{{3,2,2},{0,1,0},{1,1,1}};
    //cout << movingCount_dp(M,N,mhz);

    auto so = new Solution();
    //vector<int> source{6,3,5,10,11,2,9,14,13,7,4,8,12};
    cout << so->getMaxOFFA();
    // vector<int> source{6,3,5,10,11,2,9,14,13,7,4,8,12};
    // cout << so->lengthOfLIS_bs(source);

    //so->maxEnvelopes();
    //    int n;
    //    cin >> n;
    //    vector<int> vec(n);
    //    unordered_map<double,int> map;
    //    for(int i=0;i<n;++i){
    //        cin >> vec[i];
    //        double x = 1/(double)vec[i];
    //        unordered_map<double,int> nmap = map;
    //        ++map[x];
    //        for(auto iter = nmap.begin();iter != nmap.end();++iter){
    //            if(iter->first+x<=1)
    //                ++map[iter->first+x];
    //        }
    //    }
    //    if(map[1]!=0){
    //        cout <<map[1]<<endl;
    //    }
    //    else{
    //        cout << "No solution!"<<endl;
    //    }

    return 0;
}


//huawei1
typedef struct my_tree{
    int data;
    int ID;
    my_tree *left,*right,*dad;
    my_tree(int data_,int id):data(data_),ID(id),left(nullptr),right(nullptr),dad(nullptr){}
} trNode;

int node_sum(trNode* root){
    if(!root)
        return 0;
    std::queue<trNode*> q;
    q.push(root);
    int sum =0;
    while(!q.empty()){
        auto front_ele = q.front();
        q.pop();
        sum += front_ele->data;
        if(front_ele->left)
            q.push(front_ele->left);
        if(front_ele->right)
            q.push(front_ele->right);
    }
    return sum;
}

int huawei_1(){
    //return
    /*4
4 9 -7 -8
0 1
0 3
1 2*/
    int node_num = 0;
    cin >> node_num;
    vector<trNode *>node_array(node_num,nullptr);
    int temp=0;
    for(int i=0;i<node_num;++i){
        cin >>temp;
        node_array[i] = new trNode(temp,i);//init the node_array;
    }
    int temp1,temp2;
    unordered_map<int,int> hasleft;
    while(cin >> temp1 >> temp2){
        // cin >> temp1 >> temp2;
        if(hasleft.count(temp1)){
            //this is right node
            node_array[temp1]->right = node_array[temp2];
            node_array[temp2]->dad = node_array[temp1];
        }
        else{
            //this left node
            ++hasleft[temp1];
            node_array[temp1]->left = node_array[temp2];
            node_array[temp2]->dad = node_array[temp1];
        }
    }
    //we did init the tree
    //traversal n-1 node
    map<int,int> result;//<reslut,ID>
    for(int i=1;i<node_num;++i){
        //node_array[i]
        if(node_array[i]->dad){
            bool is_left = true;
            auto node_dad = node_array[i]->dad;
            if(node_dad->left == node_array[i]){
                //left
                node_dad->left = nullptr;
            }
            else{
                node_dad->right = nullptr;
                is_left = false;
            }
            int sum1 = node_sum(node_array[0]);//root 0
            int sum2 = node_sum(node_array[i]);
            if(is_left){
                node_dad->left = node_array[i];
            }
            else
            {
                node_dad->right = node_array[i];
            }
            int res = sum1 - sum2;
            if(res < 0)
                res *= -1;
            if(!result.count(res)){
                result[res] = i;
            }

        }
    }
    cout<< result.rbegin()->second;
    for(int i=0;i<node_num;++i){
        delete node_array[i];
    }
    return 0;
}
//huawei2
bool check(int x,int y,int M,int N,bool *visited,vector<vector<int>> &mhz){
    if(x>=0 &&y>=0 &&x<M && y <N && !visited[x*M+y] && mhz[x][y] !=0)
        return true;
    return false;
}

int movingCount(int x,int y,int &M,int &N,int &count,int &step,bool *visited,vector<vector<int>>& mhz){

    if(check(x,y,M,N,visited,mhz)){
        visited[x*M+y] = true;
        count++;
        if(x==M-1 && y == N-1){//end condition
            cout << "curr count : "<<count<<endl;
            if(step == -1){
                step = count;

            }
            if(step > count){
                step = count;

            }
            --count;
            visited[x*M+y] = false;
            return 0;
        }
        for(int i=1;i<mhz[x][y]+1;++i){
            movingCount(x,y+i,M,N,count,step,visited,mhz);
            movingCount(x+i,y,M,N,count,step,visited,mhz);
        }
        visited[x*M+y] = false;
        --count;
    }
    return 0;
}

int leastStep(){
    int M=3,N=3;
    //cin >> M >> douhao >> N;
    //vector<vector<int>> mhz(M,vector<int>(N,-1));
    vector<vector<int>> mhz={{3,2,2},{0,1,0},{1,1,1}};


    //    for(int i=0;i<M;++i){
    //        for(int j=0;j<N;++j){
    //            cin >>temp;
    //            mhz[i][j] = temp;
    //        }
    //    }
    //mhz init done
    //0,0
    bool *visited = new bool[M*N];
    memset(visited,0,M*N);
    int step = -1;
    int count = -1;

    movingCount(0,0,M,N,count,step,visited,mhz);
    return step;
}
//huawei2_dp
int smallestStep(vector<vector<int>> &mhz,vector<vector<int>> &dp,int M,int N,int x,int y){
    if(mhz[x][y] == 0)
        return INT_MAX-1;
    int temp_step = dp[x][y];
    for(int i =1;i<mhz[x][y]+1;++i){
        //down
        if(x+i>=0&&y>=0&&x+i<M&&y<N){
            if(temp_step > dp[x+i][y])
                temp_step = dp[x+i][y];
        }
        //right
        if(x>=0&&y+i>=0&&x<M&&y+i<N){
            if(temp_step > dp[x][y+i])
                temp_step = dp[x][y+i];
        }
    }
    return temp_step;
}

int movingCount_dp(int M,int N,vector<vector<int>> &mhz){
    if(M <=0 || N<=0 || mhz.empty())
        return -1;
    vector<vector<int>> dp(M,vector<int>(N,INT_MAX));//dp array
    dp[M-1][N-1]=-1;
    for(int i=M-1;i!=-1;--i){
        for(int j=N-1;j!=-1;--j){
            dp[i][j] = 1 + smallestStep(mhz,dp,M,N,i,j);
            cout << "dp["<<i<<"]["<<j<<"]="<<dp[i][j]<<endl;
        }
    }
    return dp[0][0];
}


//baidu3
void permuteCount(vector<vector<char>> &res,vector<char> &data,int index,vector<char> &temp_data,int n,int k){
    //abcde c52 -> ab ac ad ae bc .....10 combinations
    /*main:
     * vector<char> data{'a','b','c','d','e','f'};
    vector<vector<char>> res;
    int n= data.size();
    int k =3;
    vector<char> temp_data;
    for(int i=0;i<n;++i){
        permuteCount(res,data,i,temp_data,n,k);
    }*/
    if(index>=0 && index <n && k<=n && n-index >= k-(int)temp_data.size()){
        temp_data.push_back(data[index]);
        if((int)temp_data.size() == k){//end condition
            res.push_back(temp_data);
            temp_data.pop_back();
            return;
        }
        for(int i=index+1;i<n;++i){
            permuteCount(res,data,i,temp_data,n,k);
        }
        temp_data.pop_back();
    }
}






