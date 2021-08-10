/*0808 
 * description:
 *      给定一个数组nums判断nums中是否存在三元组和=0
 *      思路：2层循环选一对数字i、j判断相反数-(i+j)是否在数组中、注意去重。
 * input:
 *      nums = [-1,0,1,2,-1,-4]
 * output:
 *      [[-1,-1,2],[-1,0,1]]
 *
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

bool isExist(vector<int> &v,int a,int index1,int index2){
    int n = v.size();
    for(int i = index1+1;i < n;++i){
        if(v[i] == a && i != index1 && i != index2){
            //cout<<"v[i] ::"<<v[i];
            //v[i] = 99;
            return true;
        }
    }
    return false;
}

void insertVec(vector<vector<int> > &res,vector<int> vec){
    if(!res.empty()){
        for(auto data : res)
            if(data == vec)
                return;
    }
    res.push_back(vec);
    return;
}


int main(){
    string s;
    getline(cin,s);
    istringstream in(s);
    for(int i = 0;i < 3; ++i)
        in >> s;
    for(auto &i : s){
        if(i == ',')
            i = ' ';
    }
    s.erase(std::begin(s));
    s.erase(std::end(s)-1);
    //cout<<s<<endl;
    istringstream in1(s);
    vector<int> v;
    int temp = 0;
    while(!in1.eof()){
        in1 >> temp;
        v.push_back(temp);
    }
    sort(v.begin(),v.end());
    int n = v.size();
    vector<vector<int> > result;
    for(int i = 0; i < n-1; ++i){
        if(v[i]>0)
            break;
        for(int j = i+1;j<n;++j){
            if(isExist(v,-v[i]-v[j],i,j)){
                vector<int> tmp{v[i],v[j],-v[i]-v[j]};
                sort(tmp.begin(),tmp.end());
                insertVec(result,tmp);
            }
        }
    }
    //print res
    cout<<'[';
    if(result.empty())
        cout<<']';
    else if(result.size() == 1){
        cout<<'['<<result[0][0]<<','<<result[0][1]<<','<<result[0][2]<<']'<<']';
    }
    else{
        for(auto pvec = result.cbegin();pvec != result.cend() - 1; ++pvec){
            cout<<'['<<pvec->at(0)<<','<<pvec->at(1)<<','<<pvec->at(2)<<']'<<',';
        }
        auto pend = result.cend() - 1;
        cout<<'['<<pend->at(0)<<','<<pend->at(1)<<','<<pend->at(2)<<']'<<']';
    }
    return 0;
}














