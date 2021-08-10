/*0809  q01 
 * CMyString operator =
 * class CMyString{
 *      public:
 *          CMyString(char *pData = nullptr);
 *          CMyString(const CMyString &str);
 *          ~CMyString(void);
 *      private:
 *          char *m_pData;
 * };
*/
/* ·return type should be ref&
 * ·parameter should be const &
 * ·remember release memory
 * ·determine if parameter is equal to 'this'
 * ·'new' may throw 'bad_alloc'
*/
#include <cstring>
#include <iostream>
using namespace std;
class CMyString{
public:
    CMyString(char *pData = nullptr);
    CMyString(const CMyString &);
    ~CMyString();
    CMyString& operator=(const CMyString &);
private:
    char *m_pData;
};

CMyString::CMyString(char *pData)
{
    this->m_pData = pData;
}

CMyString::CMyString(const CMyString &str)
{
    if(&str == this)
        return;
    if(str.m_pData == nullptr)
        this->m_pData = nullptr;
    else{
        this->m_pData = new char[strlen(str.m_pData) + 1];
        strcpy(m_pData,str.m_pData);
    }
}

CMyString::~CMyString()
{
    delete [] this->m_pData;
}

CMyString& CMyString::operator=(const CMyString &str){
//    if(this == &str)
//        return *this;
//    delete [] m_pData;
//    m_pData = nullptr;
//    m_pData = new char[strlen(str.m_pData) + 1];
//    strcpy(m_pData,str.m_pData);
//    return *this;//new may throw an except
    if(this == &str)
        return *this;
    CMyString tempStr(str);//先创建一个临时实例再交换this和临时实例中的pData内容
    char *tempP = tempStr.m_pData;
    tempStr.m_pData = this->m_pData;
    this->m_pData = tempP;
    return *this;
}

int main(){
    char str[] = {'h','e','l','l','o','\0'};
    CMyString s1(str);
    s1 = s1;//自己对自己赋值
    CMyString s2 = s1;
    CMyString s3(s1);
    CMyString s4;
    s3 = s1;//一个实例赋给另一个实例
    s4 = s2 = s1;//连续赋值
    //test operator =
    return 0;
}
