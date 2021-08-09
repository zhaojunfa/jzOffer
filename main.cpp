/*0808
 * des:
 *      you get a linkedList head and a int k. let elements in list >> k times;
 * note:
 *      notice that k may larger than the list SIZE.
 * input:
 *      [1,2,3,4,5] 2
 * output:
 *      [4,5,1,2,3]
 *
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

int main(){
    string s;//used for getline.
    getline(cin,s);
    string nums;
    int k;
    istringstream in{s};
    in >> nums >> k;
    //handle nums
    nums.erase(nums.cbegin());//'['
    nums.pop_back();//']'
    for(auto &ch : nums)
        if(ch == ',')
            ch = ' ';
    in = istringstream(nums);
    vector<int> numVec;
    int tempInteger = 0;
    while(!in.eof()){
        in >> tempInteger;
        numVec.push_back(tempInteger);
    }//numVec init
    //move elements
    if(numVec.empty()){
        cout << endl;
        return 0;
    }
    vector<int> res;
    k = k % numVec.size();//avoid loop over 1 time
    for(int i = numVec.size() - k;i < (int)numVec.size();++i)
        res.push_back(numVec[i]);
    if(k==0){
        res = numVec;
    }
    else
        for(int i = 0;i < numVec.size() - k ;++i)
            res.push_back(numVec[i]);
    //handle output
    cout << '[';
    for(auto it = res.cbegin();it != res.cend() - 1;++it)
        cout << *it <<',';
    cout << *(res.cend()-1)<<']';
    return 0;
}
