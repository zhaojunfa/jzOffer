/*09_queue with two stacks
 *appendTail
 *deleteHead
*/
#include <dataStructure.h>


//bsearch
int bSearch(vector<int> &v,int sought = 5) {
    //v 必须是有序的
    auto beg = v.cbegin(), end = v.cend(), mid = beg + (end - beg) / 2;
    while (mid != end && *mid != sought) {
        if (sought < *mid)
            end = mid;
        else
            beg = mid + 1;
        mid = beg + (end - beg) / 2;
    }
    if (*mid == sought)
        return 1;
    else
        return -1;
}
//12345555678 11个数字 0-10
int myBSearch(vector<int>& v, int sought) {
    auto beg = v.cbegin(), end = v.cend()-1, mid = beg + (end - beg) / 2;
    while (mid != end) {
        if (sought <= *mid)
            end = mid;
        if (sought > *mid)
            beg = mid + 1;
        mid = beg + (end - beg) / 2;
    }
    if (*mid == sought)
        return mid - v.cbegin();
    else
        return -1;
}








template<typename T>
class CQueue{
public:
    CQueue();
    ~CQueue();

    void appendTail(const T &);
    T deleteHead();
private:
    std::stack<T> s1;//append
    std::stack<T> s2;//delete
};




int main(){

    std::vector<int> vec;
    return 0;
}


//appendTail
template<typename T>
void CQueue<T>::appendTail(const T &data)
{
    s1.push(data);
}
//deleteHead
template<typename T>
T CQueue<T>::deleteHead()
{
    if(s2.empty() && !s1.empty()){
        while(!s1.empty()){
            s2.push(s1.top());
            s1.pop();
        }
    }
    auto temp = s2.top();
    s2.pop();
    return temp;
}

template <typename T>
CQueue<T>::CQueue(){

}
