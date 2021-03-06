/*labuladong8.23*/

#include <iostream>
#include <algorithm>
#include <sstream>
#include <stack>
#include <list>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

typedef struct _bTreeNode_{
    int data;
    _bTreeNode_ *left,*right;
    _bTreeNode_(int i):data(i),left(nullptr),right(nullptr){}
} tree_node;


class lbld_{
public:
    //P34 using DP table to purning
    int helper(std::vector<int> &memo,int n)
    {
        //base case
        if(n==1 || n==2)
            return 1;
        if(memo[n]!=0)
            return memo[n];
        memo[n] = helper(memo,n-1) + helper(memo,n-2);
        return memo[n];
    }
    int Fib(int N){//return F(N);
        if(N==0) return 0;
        vector<int> memo(N+1,0);
        //Recursive procedures with memo
        return helper(memo,N);
    }
    //note:best to learn draw the recursion tree.

    //DP array solution
    int fib(int N){
        if(N==0) return 0;
        if(N==1 || N==2) return 1;
        vector<int> dp(N+1,0);
        dp[1] = dp [2] = 1;
        for(int i=3;i<=N;++i)
            dp[i] = dp[i-1] + dp[i-2];
        return dp[N];
    }
    //P36 coinChange with DP table/memo..
    int dp_coin(vector<int> &coins,int amount,unordered_map<int,int> &memo)
    {
        //base case
        if(amount<0)
            return -1;
        if(memo.find(amount)!=memo.end())
            return memo.find(amount)->second;
        int res = INT_MAX;//init once
        for(auto &coin : coins){
            auto temp = dp_coin(coins,amount-coin,memo);
            if(temp == -1)
                continue;
            res = min(res,temp+1);
        }
        //write into memo
        if(res != INT_MAX)
            memo.insert({amount,res});
        else
            memo.insert({amount,-1});
        return memo[amount];
    }
    int coinChangeWithDPTable(vector<int> &coins, int amount){
        unordered_map<int,int> memo;
        memo.insert({0,0});
        return dp_coin(coins,amount,memo);
    }


    //P37 money problem  Direct use iterative solution for DP arrays
    int coinChange(vector<int> &coins,int amount)
    {
        //upstart method
        //DP arrays
        vector<int> dp(amount+1,amount+1);//dp[i] Represents the amount of coin to reach the amount of money.amount+1 is possible maximum
        //base case:$0 needs 0 coin.
        dp[0] = 0;
        //
        for(int i=1;i<(int)coins.size();++i){
            for(auto &coin : coins){
                if(i - coin < 0)
                    continue;
                else{
                    dp[i] = min(dp[i],dp[i-coin]+1);
                }
            }
        }
        return dp[amount] == amount+1 ? -1 : dp[amount];
    }

    //P45  Tree traversal frame
    //    void traverse(treeNode *root){
    //        for(treeNode *child : root.childern)
    //preOrder operations
    //            reaverse(child)
    //postOrder operations
    //    }

    //P47 permute problem  parameter= nums= vector<int> ,  res = vector<set<int>> , track =set<int>
    //trackFunction
    void permuteBackTrack(vector<int> &nums,vector<int> &track,vector<vector<int>> &res){
        //recursion function
        //end condition
        if(track.size() == nums.size()){
            res.push_back(track);
            return;
        }
        //make choices
        for(auto & num : nums){
            //select a num
            //if repeat then continue(Exclude illegal choices)
            if(std::find(track.begin(),track.end(),num) != track.end())
                continue;
            //recursion
            track.push_back(num);
            permuteBackTrack(nums,track,res);
            //revoke the choice
            track.pop_back();
        }
    }

    void permute(vector<int> &nums,vector<vector<int>> &res){
        //
        vector<int> track;
        return permuteBackTrack(nums,track,res);
        //!code in main(){}
        //        vector<int> nums{1,2,3};
        //        vector<vector<int>> res;
        //        p->permute(nums,res);
        //        for(auto &ivec:res){
        //            for(auto &e:ivec)
        //                cout << e << ' ';
        //            cout << endl;
        //        }
    }


    /*
 * N Queen Problem P48  vector<vector<string>> solveNQueens(int n);
 * Path: Those rows that are less than ROW have already placed the queen.
 * Select: All columns of the row are a choice
 * End: Row > Board's last line
*/
    //!recurison fuction
    bool isValid(vector<string> &board,int row,int col){
        if(row == 0)
            return true;
        if(row >=2){
            for(int i=0; i<row-1;++i){
                //Judging whether there is a queen in every column
                if(board[i][col] == 'Q')
                    return false;
            }
        }

        //row-1 lower right / lower left / below
        auto it = std::find(board[row-1].begin(),board[row-1].end(),'Q');
        if(it == board[row-1].begin()){
            if(col == 0 || col == 1)
                return false;
        }
        else if(it == board[row-1].end()-1){
            if(col == (int)board[row-1].size()-1 || col == (int)board[row-1].size()-2)
                return false;
        }
        else{
            auto col_it = board[row-1].begin() + col;
            if(col_it == it-1 || col_it == it || col_it == it+1)
                return false;
        }
        return true;
    }

    void solveNQueensBackTrack(int row,vector<string> &board,vector<vector<string>> &res){
        //Set of our framework
        //end condiftion
        if(row == (int)board.size()){
            res.push_back(board);
            return;
        }
        //make choices
        int n = board[row].size();
        for(int col=0;col<n;++col){
            if(!isValid(board,row,col))
                continue;//exclude the incalid choice.
            //select one choice
            board[row][col] = 'Q';
            solveNQueensBackTrack(row+1,board,res);
            board[row][col] = '.';
        }
    }

    void solveNQueens(int n ,vector<vector<string>> &res){
        vector<string> board(n,string(n,'.'));//This is a chessboard
        solveNQueensBackTrack(0,board,res);
        //!test code in main()
        //        vector<vector<string>> res;
        //        int n = 4;
        //        p->solveNQueens(n,res);
        //        for(auto &board:res){
        //            for(auto &str:board){
        //                for(auto &ch:str)
        //                    cout<<ch<<' ';
        //                cout<<endl;
        //            }
        //            cout<<string(2*n,'-')<<endl;
        //        }

    }

    //!P54  chapter1.4.2 BFS framework
    int BFS(tree_node *start,tree_node *target){
        queue<tree_node*> q;//core data structure
        set<tree_node*> visited;//avoid go back
        q.push(start);//
        visited.insert(start);
        int step = 0;

        while(!q.empty()){
            int sz = q.size();
            for(int i=0;i<sz;++i){
                /*Judging whether to reach the end point*/
                auto front_element = q.front();
                q.pop();
                if(front_element == target)
                    return step;
                /*Add adjacent nodes to queues*/
                if(front_element->left && visited.find(front_element->left)==visited.end()){
                    q.push(front_element->left);
                    visited.insert(front_element->left);
                }
                if(front_element->right && visited.find(front_element->right)==visited.end()){
                    q.push(front_element->right);
                    visited.insert(front_element->right);
                }
            }
            ++step;
        }
        return step;
    }

    //1.4.2The smallest height of the binary tree
    //!function signature
    int minDepth(tree_node *root){
        //check parameter
        if(!root)
            return -1;
        if(!root->left && !root->right)
            return 1;
        //core data structure
        queue<tree_node*> q;
        set<tree_node*> visited;
        q.push(root);
        visited.insert(root);
        int length = 1;
        while(!q.empty()){
            int sz = q.size();
            for(int i=0;i<sz;++i){
                auto front_element = q.front();
                q.pop();
                //end condition
                if(front_element->left == nullptr && front_element->right == nullptr)
                    return length;
                //Diffuse Adjacent node
                if(front_element->left && visited.find(front_element->left) == visited.end()){
                    q.push(front_element->left);
                    visited.insert(front_element->left);
                }
                if(front_element->right && visited.find(front_element->right) == visited.end()){
                    q.push(front_element->right);
                    visited.insert(front_element->right);
                }
            }
            ++length;
        }
        return length;
        /*
    tree_node *root = nullptr;
    queue<int> memo;
    vector<int> memo_ = {1,2,4,-1,-1,5,6,-1,-1,7,-1,-1,3,-1,-1};
    for(auto &data:memo_)
        memo.push(data);
    p->create_tree_with_memo(root,memo);
    //pre_order_traversal
    p->preOrderTraversal(root);
    cout <<endl<<"tree's min depth = "<< p->min_depth(root)<<endl;
*/
    }

    void create_tree(tree_node*& root){
        int data;
        while(true){
            cout << "input:"<<endl;
            if(cin >> data){
                if(data == -1){
                    root = nullptr;
                    return;
                }
                else{
                    root = new tree_node(data);
                    create_tree(root->left);
                    create_tree(root->right);
                    return;
                }
            }
            else{
                cout << "invalid input..Retry?(y/n)"<<endl;
                char ch;
                cin.clear();
                cin.sync();
                cin >> ch;
                if(ch != 'y'){
                    cout<<"bye.";
                    exit(-1);
                }
            }
        }
    }

    void create_tree_with_memo(tree_node *&root,queue<int> &data_sequence){
        //leafNode->data = -1
        int front_element = data_sequence.front();
        data_sequence.pop();
        if(front_element == -1)
            root = nullptr;
        else{
            root = new tree_node(front_element);
            create_tree_with_memo(root->left,data_sequence);
            create_tree_with_memo(root->right,data_sequence);
        }
    }

    //tree traversal
    void preOrderTraversal(tree_node *root){
        if(!root)
            return;
        else{
            cout << root->data << ' ';
            preOrderTraversal(root->left);
            preOrderTraversal(root->right);
        }
    }

    //P56 Number of times to unlock a password lock "0000"->target
    string operateLock(string before,int serial,int how){
        //serial means which lock
        //how indicates + or -
        //check
        if(serial >= (int)before.size())
            return string(before.size(),'0');
        //operate
        if(how == 0){
            //-
            if(before[serial] == '0')
                before[serial] = '9';
            else
                --before[serial];
        }
        else if(how == 1){
            //+
            if(before[serial] == '9')
                before[serial] = '0';
            else
                ++before[serial];
        }
        return before;
    }

    int openLock(vector<string> &deadends,string target){
        //BFS
        /* code in main
    vector<string> deadends = {"0009"};
    string target = "0008";
    cout<<"Number of times to unlock a password lock is "<< p->openLock(deadends,target);
*/
        int res = 0;
        queue<string> q;
        set<string> invalid;
        for(auto &str:deadends)
            invalid.insert(str);
        q.push(string(target.size(),'0'));
        invalid.insert(string(target.size(),'0'));
        //
        while(!q.empty()){

            int sz = q.size();
            for(int i=0;i<sz;++i){
                string front_element = q.front();
                q.pop();
                //cout<<front_element<<endl;
                //end condition
                if(front_element == target)
                    return res;
                //Diffuse Adjacent node
                for(int i=0;i<(int)target.size()*2;++i){
                    string next = operateLock(front_element,i/2,i%2);
                    if(invalid.insert(next).second == true){
                        q.push(next);
                        cout <<next<<endl;
                    }
                }
            }
            ++res;
        }
        return -1;
    }
    /*

      As long as the array is ordered, you should think of double pointers.
*/
    //P69 Sum of two numbers
    vector<int> twoSum(vector<int> &nums,int target){
        //two pointer
        int left =0;
        int right =nums.size()-1;
        int sum = nums[left]+nums[right];
        while(left < right){
            if(sum == target)
                return vector<int>{nums[left],nums[right]};
            else if(sum < target){
                ++left;//let sum be larger
            }
            else{
                --right;//make sum smaller
            }
        }
        return vector<int>{-1,-1};
    }

    //1.5.2.3 Invert array
    void reverse(vector<int> &arr){
        int left = 0;
        int right = arr.size()-1;
        while(left<right){
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            ++left;
            --right;
        }
    }
    //Sliding window algorithm to slovle Substring matching problem
    /*1.6.1binary search framework*/
    /*1.6.2 search a num (basic binary search)*/
    int binarySearch(vector<int> nums,int target){//Untested
        int begin = 0, end = nums.size()-1;
        int mid = begin + (end-begin)/2;
        while(mid != end && target != nums[mid]){
            if(target > nums[mid])
                begin = mid+1;
            else if (target < nums[mid])
                end = mid;
            mid = begin + (end - begin) /2;
        }
        if(nums[mid] == target)
            return mid;
        else
            return -1;
    }
    //lbld's algorithm-basic binary search
    int binarySearch_p73(vector<int> nums,int target){
        int left=0;
        int right = nums.size()-1;
        while(left <= right){//notice
            int mid =left + (right -left) / 2;
            if(nums[mid] == target)
                return mid;
            else if(nums[mid] < target)
                left = mid + 1;
            else if(nums[mid] > target)
                right = mid - 1;
        }
        return -1;
    }
    //left bound-untested
    int left_bound(vector<int> &nums,int target){
        int beg = 0,end = nums.size()-1;
        int mid = beg + (end - beg)/2;
        while(end != mid){
            if(target <= nums[mid])
                end = mid;
            else if(target > nums[mid])
                beg = mid + 1;
        }
        if(nums[mid] == target)
            return mid;
        else
            return -1;
    }
    //left bound-lbld
    int left_bound_p75(vector<int> &nums,int target){
        if(nums.empty())
            return -1;
        int beg = 0;
        int end = nums.size();//notice
        int mid = beg + (end - beg) / 2;
        while(beg < end){//notice || end condition: beg == end
            if(nums[mid] > target)
                end = mid;
            else if(nums[mid] < target)
                beg = mid + 1;
            else if(nums[mid] == target)
                end = mid;
        }
        return beg;//this means there are beg numbers in nums < target;
    }
    //right bound..

    //summay: three functions:
    //1
    int binary_search_p83(vector<int> &nums,int target){
        int beg = 0;
        int end = nums.size() - 1;
        int mid = beg + (end - beg) / 2;
        while(beg <= end){
            if(nums[mid] < target)
                beg = mid + 1;
            else if(nums[mid] > target)
                end = mid - 1;
            else if(nums[mid] == target)
                return mid;
        }
        return -1;
    }
    //2
    int left_bound_p83(vector<int> &nums,int target){
        int beg = 0;
        int end = nums.size();
        int mid = beg + (end - beg) / 2;
        while(beg <= end){
            if(nums[mid] == target)
                end = mid - 1;
            else if(nums[mid] > target)
                end = mid - 1;
            else if(nums[mid] < target)
                beg = mid + 1;
        }
        //check whether cross the border
        if(beg >= (int)nums.size() || nums[beg] != target)
            return -1;
        else
            return beg;
    }
    //3
    int right_bound_p83(vector<int> &nums,int target){
        int beg = 0;
        int end = nums.size();
        int mid = beg + (end - beg) / 2;
        while(beg <= end){
            if(target < nums[mid])
                end = mid - 1;
            else if(target > nums[mid])
                beg = mid + 1;
            else if(target == nums[mid])
                beg = mid + 1;
        }
        //check
        if(end < 0 || nums[end] != target)
            return -1;
        else
            return end;
    }
    //1.7 slide window framework p86
    void slidingWindow(string s,string t){
        unordered_map<char,int> need,window;
        for(auto c:t)
            ++need[c];
        int left = 0,right = 0,valid = 0;
        //main code
        while(right < (int)s.size()){
            //c
            //char c = s[right];
            ++right;
            //update data in window
            /* */

            //print debug info..

            //whether the left window shrinks
            while(valid == (int)need.size()){
                //char d = s[left];
                ++left;
                //update data in window
            }
        }
    }
    /*1.7.1 minimun covering substring,eg.s = EBBANCF,t = ABC,res = BANC.we think about 4 questions:
     * 1:what data should be updated when ++right?
     * 2:when should stop ++right and start ++left?
     * 3:what data should be updated when ++left?
     * 4:when the result we want should be updated?(++right or ++left?)
     * unordered_map<char,int> need,window.*/
    string minWindow(string &s,string &t){
        unordered_map<char,int> need,window;
        for(auto &c:t)
            ++need[c];
        int left=0,right=0,valid=0;
        int start=0,len=INT_MAX;
        while(right < (int)s.size()){
            char c = s[right];
            ++right;
            //update data
            if(need.count(c)){
                ++window[c];
                if(window[c] == need[c])
                    ++valid;
            }
            //whether left window shrinks
            while(valid == (int)need.size()){
                //update the start & len:
                if(right - left < len){
                    start = left;
                    len = right - left;
                }
                char d = s[left];
                ++left;
                if(need.count(d)){
                    if(window[d] == need[d])
                        --valid;
                    --window[d];
                }
            }
        }
        if(len == INT_MAX)
            return "";
        else
            return s.substr(start,len);
    }

    //    string minWindow_(string &s,string &t){
    //        if(s.empty()||t.empty())
    //            return string();
    //        unordered_map<char,int> need,window;
    //        for(auto ch:t)
    //            ++need[ch];
    //        int left=0,right=0;
    //        int length=INT_MAX;
    //        int valid=0;
    //        int start=0;
    //        while(right<static_cast<int>(s.size())){
    //            char ch1=s[right++];
    //            if(need.count(ch1))
    //                if(++window[ch1]==need[ch1])
    //                    ++valid;
    //            while(valid==static_cast<int>(need.size())){
    //                if(left-right<length){
    //                    start=left;
    //                    length=left-right;
    //                }
    //                char ch2=s[left];
    //                ++left;
    //                if(need.count(ch2))
    //                    if(need[ch2]==window[ch2]--)
    //                        --valid;
    //            }
    //        }
    //        if(length==INT_MAX)
    //            return string();
    //        else
    //            return s.substr(start,length);
    //    }
    /*1.7.2 input string s & string t,does s contains the arrangement of t?
    *eg. s = "helloworld",t = "oow",return true.*/
    bool checkIncursion(string &s,string &t){
        //
        if(s.empty()||t.empty())
            return false;
        unordered_map<char,int> window,need;
        for(char ch:t)
            ++need[ch];
        int s_size=s.size(),t_size=t.size();
        int left=0,right=0;
        int valid=0;
        //int start=0;
        while(right<s_size){
            char ch_right=s[right++];
            if(need.count(ch_right)){
                if(need[ch_right]==++window[ch_right])
                    ++valid;
            }
            while(right-left>=t_size){
                if(valid==static_cast<int>(need.size()))
                    return true;
                char ch_left=s[left++];
                if(need.count(ch_left))
                    if(need[ch_left]==window[ch_left]--)
                        --valid;
            }
        }
        return false;
    }
    /*1.7.3??????S????????????T????????????-????????????*/
    vector<int> findAnagrams(string &s,string &t){
        if(s.empty()||t.empty())
            return vector<int>();
        unordered_map<char,int> window,need;
        for(char ch:t)
            ++need[ch];
        int left=0,right=0;
        int valid=0;
        int s_size=s.size(),t_size=t.size();
        vector<int> res;
        while(right<s_size){
            char ch_right=s[right++];
            if(need.count(ch_right)&&need[ch_right]==++window[ch_right])
                ++valid;
            while(right-left>=t_size){
                if(valid==static_cast<int>(need.size()))
                    res.push_back(left);
                char ch_left=s[left++];
                if(need.count(ch_left) && need[ch_left]==window[ch_left]--)
                    --valid;
            }
        }
        return res;
    }
    /*1.7.4?????????????????????*/
    int lengthOfLongestSubstring(string &s){
        if(s.empty())
            return 0;
        int left=0,right=0;
        int length=INT_MIN;
        int s_size=s.size();
        unordered_map<char,int> window;
        while(right<s_size){
            char ch_right=s[right++];
            ++window[ch_right];
            while(window[ch_right]>1)
                --window[s[left++]];
            length = max(right-left,length);
        }
        return length;
    }
    /*2.1.1??????????????????-?????????????????????LIS=longest increasing subsequence
    14342->1,2,2,3,2->max=3*/
    int lengthOfLIS(vector<int> &num){
        if(num.empty())
            return 0;
        int num_size = num.size();
        vector<int> dp(num_size,1);
        for(int i=0;i<num_size;++i){
            int max_dp=0;
            for(int j=0;j<i;++j){
                if(num[j] < num[i])
                    max_dp = dp[j] > max_dp ? dp[j] : max_dp;
            }
            dp[i] = max_dp+1;
        }
        int res=0;
        for(auto i:dp){
            if(i > res)
                res = i;
        }
        return res;
    }
    /*2.2??????????????????
    envelopes(int[][] envelopes);
    54,64,67,23->return 3 aka (23-54-67)*/
    int maxEnvelopes(vector<vector<int>> &envelopes){
        if(envelopes.empty())
            return 0;
        int sz = envelopes.size();
        std::sort(envelopes.begin(),envelopes.end(),
                  [](vector<int> v1,vector<int> v2){return v1[0] < v2[0];});
        int left = 0,right = 0;
        while(left<sz){
            while(envelopes[right][0] == envelopes[left][0]){
                ++right;
                if(right == sz)
                    break;
            }
            std::sort(envelopes.begin()+left,envelopes.begin()+right,
                      [](vector<int> v1,vector<int> v2){ return v1[1] > v2[1];});
            left = right;
        }
        int dp_result = 0;
        int envelopes_size = envelopes.size();
        vector<int> dp(envelopes_size,1);
        for(int i=0;i<envelopes_size;++i){
            int max_dp = 0;
            for(int j = 0; j < i;++j){
                if(envelopes[j][0] < envelopes[i][0] && dp[j] > max_dp)
                    max_dp = dp[j];
            }
            dp[i] = max_dp + 1;
            dp_result = dp[i] > dp_result ? dp[i] : dp_result;
        }
        return dp_result;
    }

    //#include<bits/stdc++.h>
    //using namespace std;


public:
};

void getData_0923(vector<int> &vec,int &length){
    cin >> length;
    int temp=0;
    for(int i=0;i<length;++i){
        cin >> temp;
        vec.push_back(temp);
    }
}

void func_0923(vector<int> &vec){
    if(vec.empty())
        return;
    int sz = vec.size();
    vector<int> res;
    //res.push_back(vec[0]);
    cout << vec[0]<<' ';
    int ji_sum = vec[0];
    int ou_sum =0;
    int curr =0;
    for(int i=1;i<sz;++i){
        if(i%2==1){
            curr=ji_sum - ou_sum - vec[i];
            ou_sum += curr;
        }
        else{
            curr = vec[i] + ou_sum - ji_sum;
            ji_sum += curr;

        }
        cout << curr <<' ';
    }
}

int calc_week(double c,double y,double m,double d){
    if(m==1){
        m=13;
        --y;
    }
    if(m==2){
        m=14;--y;
    }
    int w = (int)(y+(int)(y/4) + (int)(c/4)-2*c+(int)(13*(m+1)/5) +d -1 )%7;
    return w;
}
int calWeek(int y,int m,int d){
    if(m<1 ||m>12 || d<1 ||d>31)
        return -1;
    if(m==1){
        m=13;
        --y;
    }
    if(m==2){
        m=14;--y;
    }
    int c = y / 100;

    y = y - c * 100;

    int week = y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + d - 1;

    week %= 7;

    week = week < 0 ? week + 7 : week;

    return week;
}




int Mon(int A,int B){
    if(A>2100 || A<1900 || B>2100 || B <1900)
        return 0;
    int res =0;
    for(int i=A;i<=B;++i){
        for(int j=1;j<=12;++j){
            int y = i % 100;
            int c = i / 100;
            int wek = calc_week(c,y,j,1);
            if(wek==1)
                ++res;
        }
    }
    return res;
}


void get_data_0923_3(int &n,int &m,int &x,int &y,vector<vector<int>> &vec,string &inst){
    cin >> n >> m >> x >> y;
    int temp_int;
    for(int i = 0;i<n;++i){
        vector<int> temp;
        for(int j=0;j<m;++j){
            cin >> temp_int;
            temp.push_back(temp_int);
        }
        vec.push_back(temp);
    }
    char ch;
    while(cin >> ch){
        inst.push_back(ch);
    }
}







//1
void get_data_1(vector<int> &data,int &N){
    cin >> N;
    data.push_back(INT_MAX);//left
    for(int i=0;i<N;++i){
        int temp=0;
        cin >> temp;
        data.push_back(temp);
    }
    data.push_back(INT_MAX);//right
}


int maxyoushui(){
    //    vector<int> data;
    //    int N;

    vector<int> data{100,5,1,2,1,5,100};
    int N=5;

    //get_data_1(data,N);
    if(data.empty())
        return 0;//invalid input
    //
    vector<int> dp(N+2,1);
    dp[0] = 0;
    dp[N+1] =0;
    int result=1;
    for(int i=1;i<=N;++i){
        //get dp[i]
        int currentNum = data[i];
        //left
        int leftNum=0;
        int leftcurrMax = currentNum;
        for(int j=i-1;j>=0;--j){
            if(data[j] < leftcurrMax){
                ++leftNum;
                leftcurrMax = data[j];
            }
            else
                break;
        }
        //right
        int rightNum=0;
        int rightcurrMax = currentNum;
        for(int k=i+1;k<N+2;++k){
            if(data[k] < rightcurrMax){
                ++rightNum;
                rightcurrMax = data[k];
            }
            else
                break;
        }
        //1+
        dp[i] = dp[i] + leftNum + rightNum;
        result = dp[i] > result ? dp[i] : result;
    }
    return result;
}


void getdata2(int &N,vector<int> &data){
    cin >>N;
    for(int i=0;i<N;++i){
        int t;
        cin >> t;
        data.push_back(t);
    }
}

int saf(){
    //    vector<int> data;
    //    int N;
    //    getdata2(N,data);

    vector<int> data{6,6,6,6,2,3,3,3};
    //int N=8;
    //    getdata2(N,data);



    if(data.empty())
        return 0;

    int sz = data.size();
    int curMax=data[sz-1];
    int lastindex=sz-1;
    for(int j=sz-2;j>=0;--j)
    {
        if(data[j] <= curMax){
            curMax = data[j];
            lastindex = j;
            continue;
        }
        else
            break;
    }
    vector<int> target;
    //int currmaxp=data[0];

    target.push_back(data[0]);
    for(int i=1;i<lastindex;++i){
        int s=0;
        if(data[0]-i > data[i])
            s=data[i];
        else if(data[0]-i <= data[i])
            s=data[0]-i;
        if(data[sz-1]-s == sz-1 -lastindex)
            s = s + 1;
        target.push_back(s);
    }
    int sum=0;
    for(int j=0;j<lastindex;++j){
        sum = sum + (data[j] - target[j]);
    }

    return sum;
}

vector<string> x_X(vector<char> sid,int size){
    //
    queue<pair<string,int>> que;
    int n = sid.size();
    for(int i=0;i<n;++i){
        string s;
        s += sid[i];
        que.emplace(s,1<<i);
    }
    vector<string> res;
    while(!que.empty()){
        string s = que.front().first;
        int x = que.front().second;
        que.pop();
        if((int)s.size() == size){
            res.emplace_back(s);
            continue;
        }
        for(int i=0;i<n;++i){
            int t=x;
            string st =s;
            if((t | 1<<i) == t)
                continue;
            else{
                st += sid[i];
                t = t|1<<i;
                que.emplace(st,t);
            }
        }

    }
    set<string> st(res.begin(),res.end());
    res.assign(st.begin(),st.end());
    return res;
}

int main23()
{
    int n;
    cin >> n;
    unordered_map<double,int> map;
    while(n--){
        int x;
        cin >> x;
        double t = 1 / (double)x;
        unordered_map<double,int> tmp = map;
        for(auto iter = tmp.begin();iter!=tmp.end();++iter){
            if(iter->first + t < 1){
                map[iter->first+t]=1;
            }
            if(iter->first+t==1){
                map[1]++;
            }
        }
        //map.insert({t,1});
        map[t]=1;
    }
    int x = map[1];
    if(x == 0){
        cout << "No Solution!" <<endl;
    }
    else
        cout <<x <<endl;

    return 0;
}



//27
void get_data_27_1(int &N,int &M,vector<int> &vec){
    cin >> N;
    cin >> M;
    int t;
    std::set<int> set;
    for(int i=0;i<N;++i){
        cin >> t;
        if(!set.insert(t).second == false)
            vec.push_back(t);
    }
}


int x(vector<int> &sid,int size,int M){
    //
    queue<pair<vector<int>,int>> que;
    int n = sid.size();
    for(int i=0;i<n;++i){
        vector<int> s;
        s.push_back(sid[i]);
        que.emplace(s,1<<i);
    }
    vector<vector<int>> res;
    std::set<vector<int>> res_;
    while(!que.empty()){
        vector<int> s = que.front().first;
        int x = que.front().second;
        que.pop();
        if((int)s.size() == size && (s[0]+s[1]+s[2])%M==0){
            //res.emplace_back(s);
            vector<int> t ;
            t.assign(s.begin(),s.end());
            std::sort(t.begin(),t.end());
            res_.insert(t);
            continue;
        }
        for(int i=0;i<n;++i){
            int t=x;
            vector<int> st =s;
            if((t | 1<<i) == t)
                continue;
            else{
                st.push_back(sid[i]);
                t = t|1<<i;
                que.emplace(st,t);
            }
        }

    }
    //    for(auto &ch:res){
    //        std::sort(ch.begin(),ch.end());
    //    }
    //    set<vector<int>> st(res.begin(),res.end());
    //    res.assign(st.begin(),st.end());
    //    int sz = 0;
    //    for(auto ch:res){
    //        if((ch[0]+ch[1]+ch[2]) % M == 0)
    //            ++sz;
    //    }
    return res_.size();
}


//29
int getIndexFromHourAndMinute(int hour,int minute){
    return hour*60+minute;
}

void printYingyeInfo(int hour,int minute){
    int t1,t2,t3,t4;
    t1=hour/10;
    t2=hour%10;
    t3=minute/10;
    t4=minute%10;
    cout<<t1<<t2<<':'<<t3<<t4;
}




void getdata291(vector<int> &day_minutes){
    int isyingye;
    while(cin >> isyingye){

        char ch;
        cin >> ch;//,
        int t1,t2,start_hour,start_minute,end_hour,end_minute;
        cin >> t1 >> t2;
        start_hour = 10*t1+t2;
        cin >> ch;//:
        cin >> t1 >> t2;
        start_minute = 10*t1+t2;
        cin >> ch;//-
        cin >> t1 >> t2;
        end_hour = 10*t1+t2;
        cin >> ch;//:
        cin >> t1 >> t2;
        cin >> ch ;
        end_minute = 10*t1+t2;
        if(isyingye == 1){
            int start_index = start_hour*60+start_minute;
            int end_index = end_hour*60+end_minute;
            for(int i = start_index;i<=end_index;++i)
                day_minutes[i]=1;
        }
        else{
            int start_index = start_hour*60+start_minute+1;
            int end_index = end_hour*60+end_minute;
            for(int i = start_index;i<=end_index;++i)
                day_minutes[i]=0;
        }
        if(ch!=';')
            break;

    }
    //
    int tt = 60*24;
    int time=0;
    for(int kk=0;kk<tt;++kk){

        int startindex;
        int endindex;
        if(day_minutes[kk]==0)
            continue;
        else{
            if(time!=0){
                cout<<';';
            }
            ++time;
            startindex = kk;
            while(kk < tt && day_minutes[kk]==1){
                ++kk;
            }
            //            --kk;
            endindex=kk-1;
            int start_hour,start_minute,end_hour,end_minute;
            start_hour = startindex/60;
            start_minute = startindex%60;
            end_hour = endindex/60;
            end_minute = endindex%60;
            printYingyeInfo(start_hour,start_minute);
            cout<<'-';
            printYingyeInfo(end_hour,end_minute);

        }

    }
}
//0930_1
int getDa_1(){
    unordered_map<char,int> map;
    map['T']=-1;
    map['R']=1;
    map['I']=-1;
    map['P']=1;
    int n;
    cin >> n;
    char temp;
    string data;
    for(int i=0;i<n;++i){
        cin >> temp;
        data.push_back(temp);
    }
    //vector<string> subString;
    int res = 0;
    pair<int,int> zerozero;
    for(int i=0;i<n;++i){
        //string sub;
        zerozero.first=0;
        zerozero.second=0;
        for(int j=i;j<n;++j){
            if(data[j]=='T' || data[j]=='R')
                zerozero.first+=map[data[j]];
            else
                zerozero.second+=map[data[j]];
            if(zerozero.first==0 && zerozero.second==0)
                ++res;
        }
    }

    return res;
}

//0930_2
std::set<vector<int>> x_30(vector<int> &sid,long long size){
    //
    queue<pair<vector<int>,long long>> que;
    long long n = sid.size();
    for(long long i=0;i<n;++i){
        vector<int> s;
        s.push_back(sid[i]);
        que.emplace(s,1<<i);
    }
    vector<vector<int>> res;
    std::set<vector<int>> res_;
    while(!que.empty()){
        vector<int> s = que.front().first;
        long long x = que.front().second;
        que.pop();
        if((long long)s.size() == size){
            //res.emplace_back(s);
            vector<int> t ;
            t.assign(s.begin(),s.end());
            std::sort(t.begin(),t.end());
            res_.insert(t);
            continue;
        }
        for(long long i=0;i<n;++i){
            long long t=x;
            vector<int> st =s;
            if((t | 1<<i) == t)
                continue;
            else{
                st.push_back(sid[i]);
                t = t|1<<i;
                que.emplace(st,t);
            }
        }

    }

    //    set<vector<int>> st(res.begin(),res.end());
    //    res.assign(st.begin(),st.end());
    //    int sz = 0;

    return res_;
}



int getD_2(){
    int res=0;
    int n,m;
    cin>>n>>m;
    int temp;
    vector<int> w;
    int L,R;
    //cin
    vector<int> index;
    for(int i=0;i<n;++i){
        cin>>temp;
        w.push_back(temp);
        index.push_back(i);
    }
    cin >>L>>R;
    std::set<vector<int>> res_poss;
    res_poss = x_30(index,(long long)m);
    for(auto ch:res_poss){
        int sum=0;
        for(auto ch2:ch){
            sum+=w[ch2];
        }
        if(sum <=R && sum>=L)
            ++res;
    }
    return res;
}

void printChar(int index,string &res){
    char c = 'A'+index;
    res.push_back(c);
    //cout<<c;
}

void ha(vector<int> &line){//size =26
    string res;
    int sum=0;
    for(auto s:line)
        sum+=s;
    int justcout_index=-1;
    while(sum!=0){
        bool isbig=false;
        for(int i=0;i<26;++i){
            if(line[i]>sum/2){
                isbig=true;
                if(line[i]==sum){
                    if(sum==1 && justcout_index==-1)
                    {

                        res.clear();
                        res.push_back('!');
                        sum=0;
                        break;
                    }
                }
                printChar(i,res);
                --line[i];
                --sum;
                justcout_index =i;
                break;
            }
        }
        if(isbig==false){
            for(int i=0;i<26;++i){
                if(line[i]==0 || i==justcout_index)
                    continue;
                printChar(i,res);
                --line[i];
                --sum;
                justcout_index = i;
                break;
            }
        }
    }
    cout <<res<<endl;
}



void insertSort(std::vector<int> &list){
    int i,j;
    int sz = list.size();
    for(i=2;i<sz;++i){
        if(list[i] < list[i-1]){
            list[0] = list[i];
            for(j=i-1;list[j]>list[0];--j)
                list[j+1]=list[j];
            list[j+1]=list[0];
        }
    }
}

void heapAdjust(std::vector<int> &list,int s,int m){
    //adjust range[s,m] in heap;
    int temp,j;
    temp = list[s];
    for(j=2*s;j<=m;j*=2){
        if(j<m && list[j] < list[j+1])
            ++j;
        if(temp >= list[j])
            break;
        list[s] = list[j];
        s=j;
    }
    list[s] = temp;
}

void heapSort(std::vector<int> &list){
    int i;
    std::vector<int> listWithTenNums;//in fact the size is 11 because there is a node 0;
    listWithTenNums.assign(list.begin(),list.begin()+11);
    int length = 10;
    for(i=length/2;i>0;--i)
        heapAdjust(listWithTenNums,i,length);//make a 10-elements max-heap;
    for(i=11;i<(int)list.size();++i){
        if(list[i] >= listWithTenNums[1])
            continue;//list[i] is not a good element
        listWithTenNums[1] = list[i];
        heapAdjust(listWithTenNums,1,length);
    }
    std::sort(listWithTenNums.begin(),listWithTenNums.end());
    for(i=10;i>0;--i)
        cout << listWithTenNums[i]<<' ';
}

void lru(std::vector<std::pair<int,int>> &sequence){
    std::unordered_map<int,int> key_index;
    std::vector<pair<int,int>> LRU;
    int sz = sequence.size();
    for(int i=0;i<sz;++i){
        int key = sequence[i].first;
        int value = sequence[i].second;
        if(key_index.count(key)){
            if((int)LRU.size() !=3){//not full
                if(LRU[0].first == key){
                    LRU[0].first = LRU[1].first;
                    LRU[0].second = LRU[1].second;
                    key_index[LRU[1].first] = 0;
                    LRU[1].first = key;
                    LRU[1].second = value;
                    key_index[key] = 1;
                }
                else{
                    LRU[1].second = value;
                    key_index[key] = 1;
                }
            }
            else{//full
                if(LRU[0].first == key){
                    key_index[LRU[1].first] = 0;
                    key_index[LRU[2].first] = 1;
                    key_index[LRU[0].first] = 2;
                    LRU.erase(LRU.begin());
                    LRU.push_back(make_pair(key,value));

                }
                else if(LRU[1].first == key){
                    key_index[LRU[2].first] = 1;
                    key_index[LRU[1].first] = 2;
                    LRU.erase(LRU.begin()+1);
                    LRU.push_back(make_pair(key,value));
                }
                else
//                    key_index[LRU[2].first] = 1;
                    LRU[2].second = value;
            }
        }
        else{//not dupicated
            if((int)LRU.size() !=3){
                //not full
                key_index[key] = LRU.size();
                LRU.push_back(make_pair(key,value));
            }
            else{
                key_index[LRU[1].first] = 0;
                key_index[LRU[2].first] = 1;
                key_index[key] = 2;
                LRU.erase(LRU.begin());
                LRU.push_back(make_pair(key,value));
            }

        }
    }
    for(int i =LRU.size()-1;i>=0;--i){
        auto it = LRU[i];
        int key = it.first;
        int value = it.second;
        cout << '{' << key << ':' << value << '}' << ' ';
    }

}




int main()
{
    int temp1,temp2;
    std::vector<pair<int,int>> array;
    while(cin >> temp1 >> temp2)
        array.push_back(make_pair(temp1,temp2));
    lru(array);
    return 0;
}
















