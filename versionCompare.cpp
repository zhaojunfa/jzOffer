/*0808
 * des:
 *      compare version a and b,if a>b return 1 else if a < b return -1,else if a ==b return 0;
 * input:
 *      1.1 1.001
 * output:
 *      0
*/
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
int main(){
    string s;//getline--
    getline(cin,s);
    istringstream in{s};
    string temp1,temp2;
    in >>temp1 >> temp2;//temp1 = 1.1 temp2 = 1.001
    for(auto &ch : temp1)
        if(ch == '.')
            ch = ' ';
    for(auto &ch : temp2)
        if(ch == '.')
            ch = ' ';
    vector<int> v1,v2;
    int tempInteger;
    in.clear();
    in = istringstream(temp1);
    while(!in.eof()){
        in >> tempInteger;
        v1.push_back(tempInteger);
    }//v1 init

    in.clear();
    in = istringstream(temp2);
    while(!in.eof()){
        in >> tempInteger;
        v2.push_back(tempInteger);
    }//v2 init

    int n = v1.size();
    for(int i = 0;i < n; ++i){
        if(v1[i] > v2[i]){
            cout << 1;
            return 0;
        }
        else if(v1[i] < v2[i]){
            cout << -1;
            return 0;
        }
    }
    cout << 0;
    return 0;
}
