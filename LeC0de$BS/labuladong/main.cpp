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
        int res = max_value;//init once
        for(auto &coin : coins){
            auto temp = dp_coin(coins,amount-coin,memo);
            if(temp == -1)
                continue;
            res = min(res,temp+1);
        }
        //write into memo
        if(res != max_value)
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
    //!trackFunction
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
            char c = s[right];
            ++right;
            //update data in window
            /* */

            //print debug info..

            //whether the left window shrinks
            while(valid == (int)need.size()){
                char d = s[left];
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
    string minWindow(string s,string t){
        unordered_map<char,int> need,window;
        for(auto &c:t)
            ++need[c];
        int left=0,right=0,valid=0;
        int start=0,len=INT_MAX;
        while(right < (int)s.size()){
            static char c = s[right];
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
    //






private:
    static constexpr int max_value = -1u;

};






int main()
{
    //    cout << "Hello World!" << endl;
    auto p = new lbld_();


    vector<string> deadends = {"0009"};
    string target = "0008";
    cout<<"Number of times to unlock a password lock is "<< p->openLock(deadends,target);



    return 0;



}
