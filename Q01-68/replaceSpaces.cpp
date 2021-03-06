/*05_01替换空格
 * 请实现一个函数，把字符串的每个空格替换成"%20"(在原来的字符串上修改假设内存足够)
 * input: We are happy.
 * output: We%20are%20happy.
 *0810
*/

#include <iostream>

using namespace std;

//O(n)
void replaceBlank(char string[],int length){
    //check
    if(string == nullptr || length <= 0)
        return;
    //handle
    int numOfBlank = 0,strLength = 0;
    char *temp = string;
    while(*temp != '\0'){
        ++strLength;
        if(*temp == ' ')
            ++numOfBlank;
        ++temp;
    }
    ++strLength;//把'\0'加上去
    int resLength = strLength + numOfBlank*2;
    if(length < resLength)
        return;//给定的内存不够用
    for(int i = strLength - 1; i >= 0 ; --i){
        if(string[i] == ' '){
            string[--resLength] = '0';
            string[--resLength] = '2';
            string[--resLength] = '%';
        }
        else
            string[--resLength] = string[i];
    }
}

int main(){
    char str[] = {'h','e',' ','l',' ','l','o','\0','x','x','x','x','x','x'};//he l lo->he%20l%20lo,str总长度=14。
    char str1[] = {' ','h','e','l',' ','l','o','\0','x','x','x','x','x','x'};//空格在开头
    char str2[] = {'h','e',' ',' ','l','l','o','\0','x','x','x','x','x','x'};//连续空格
    char str3[] = {'h','e',' ','l',' ','l',' ','\0','x','x','x','x','x','x'};//空格在结尾 ->"he%20l%20l%20 "
    char str4[] = {' ','\0','x','x'};//字符串只有一个空格
    constexpr int length = sizeof(str);
    replaceBlank(str4,length);
    return 0;
}


