#pragma once
/*2.1.3字面值常量
十进制字面值是int，long，long long最小的那个，是一个带符号数
char 型字面值=单引号括起来的，string型字面值 = 双引号括起来的
转义序列 \n \r 或者泛化
指定字面值的值： L'a'  u8"hi" 42ULL 1E-3F 3.14L
*/

/*2.2变量（c++中数据类型决定了变量所占内存空间的大小和布局方式、该空间能存储的值的范围以及变量能参与的运算）
类型说明符比如int
对象：具有某种数据类型的内存空间
初始化和赋值：初始化是指对象在创建时获得了一个指定的值，赋值是把对象当前的值擦除，以一个新值代替
初始化的方式：
int i = 0;
int i = {0};
int i(0);
int i{0};
列表初始化：花括号，特点：初始值存在丢失信息的风险时编译器会报错。
默认初始化:定义于任何函数体外的变量被初始化为0，定于函数体内部的内置类型不被初始化uninitialized
2.2.2变量声明和定义的关系
声明：使名字为程序所知
定义：负责创建于名字关联的实体
*/

/*2.3.1引用(左值)：引用并非对象，他只是为一个已经存在的对象所起得另外一个名字,言外之意\
引用类型的初始值必须是一个对象(引用只能绑定在对象上)
左值和右值：左值是地址值，右值是真实值
--2.3.2指针
取地址符&
double dval; double *pd = &dval; double *pd2 = pd; int *pi = pd; pi = &dval;
指针的四种状态：1.指向一个对象 2.指向紧邻对象的下一个位置 3.空指针，没有指向任何对象 4.无效指针，上述情况的其他值
解引用符*
int ival = 42; int *p = &ival; cout << *p; *p = 0; cout<< *p;
&和*的含义(看上下文)：int i = 42; int &r = i; int *p; p = &i; *p = i; int &r2 = *p;
void *指针->一种特殊的指针
指向指针的指针：int ival = 1024; int *pi = &ival; int **ppi = &pi;
指向指针的引用(从右向左阅读)：int i = 42; int *p; int *&r = p; r = &i; *r = 0;
*/

/*2.4const限定 
默认状态下const对象仅在文件内有效，解决的办法：不管是声明和定义都添加extern关键字：
//file_1.cc
extern const int bufSize = fcn();
//file_1.h
extern const int bufSize;
2.4.1const的引用(常量引用)(非常量引用的初始值必须是左值)
const int ci =1024; const int &r1 = ci;//正确 r1 = 42;//错误 int &r2 = ci;//错误，试图让一个非常量引用指向一个常量对象
int i = 42; const int &r1 = i;//正确，允许讲const int&绑定到一个常量对象上 const int &r2 = 42;//yes  const int &r3 = r1 * 2;//yes   int &r4 = r1 * 2;//no
--double dval =3.14; const int &ri = dval;合法吗?合法。ri = 3 
--对const的引用可能引用一个非const对象
int i = 42; int &r1 = i; const int &r2 = i; r1 = 0; r2 = 0;
2.4.2指针和const
--const指针
int errNum = 0; int *const pi = &errNum;
const double pi = 3.14159; const double *const pd = &pi;
--顶层const--拷入和拷出的对象都必须具有相同的底层const资格
2.4.4constexpr和常量表达式
--常量表达式(值不会改变且在编译过程中就能得到计算结果的表达式)
--constexpr类型:一定是一个常量且用常量表达式初始化：在编译器由编译器验证变量的值是否是一个常量表达式。
它的好处：1.是一种很强的约束，来保证程序的正确语义不被破坏。2.编译器可以在编译时对constexpr的代码进行很大的优化 3.相比宏来说没有额外的开销，更安全可靠
指针和constexpr：在constexpr声明中如果定义了一个指针，限定符constexpr仅仅作用于指针本身，与指针指向的对象无关：
const int *p = nullptr;//p是一个指向整型常量的指针
constexpr int *q = nullptr;//q是一个指向整数的常量指针
与其他常量指针类似，constexpr指针既可以指向常量也可以指向非常量：
constexpr int *np =nullptr;
int j = 0;
constexpr int i = 42;
constexpr const int *p = &i;
constexpr int *p1 = &j;
*/

/*2.5处理类型
2.5.1类型别名typedef
typedef double wages;
typedef wages base, *p;//base 是double的同义词，p是double*的同义词
//别名声明： using UI = Sales_item；
指针、常量和类型别名：
typedef char *pstring；
const pstring cstr = 0;//不等于 const char *cstr = 0;
2.5.2auto类型说明符
1.auto会使用引用对象的值：int i = 0, &r = i; auto a = r;//a是r指向的对象的类型，即int
2.auto会忽略顶层const，保留底层const
3.设置一个类型的auto的引用时，顶层const会保留
2.5.3decltype类型指示符--选择并返回操作数的数据类型（分析表达式并得到它的类型却不实际计算表达式的值）
双层括号的结果是引用
处理顶层const和引用的方式与auto有所不同：
1.如果decltype使用的表达式是一个变量，则decltype返回该变量的类型（包括顶层const和引用在内）：
const int ci = 0, &cj = ci;
decltype(ci) x = 0;//x的类型是const int
decltype(cj) y = x;//y的类型是const int &，y绑定到x
decltype(cj) z;//错误，cj是const int & 必须初始化。
2.decltype和引用
decltype接收一个‘表达式’若表达式的结果能作为一条赋值语句的左值，则返回一个引用
*/
//$3 字符串 向量和数组
/*
3.1命名空间的using声明
头文件不应该包含using声明，是因为使用了该头文件的文件都会有这个声明，由于不经意间包含了一些名字，反而可能产生始料未及的名字冲突

*/

/*3.2标准库类型string
3.2.1定义和初始化string对象
--拷贝初始化和直接初始化
--3.2.3处理string对象中的字符
范围for语句--下标运算符[]接收参数是string::size_type类型的值
*/
/*3.3标准库类型vector
3.3.1定义和初始化vector的方式：
vector<T> v1;
vector<T>v2(v1);
vector<T> v2 = v1;
vector<T> v3(n,val)
vector<T> v4(n)
vector<T> v5{a,b,c...}
vector<T> v5 = {a,b,c...}
如果vector对象的元素是内置类型，则元素初始值默认初始化
支持的操作：empty、size、push_back、
--3.4迭代器 iterator和const_iterator--如果对象是常量则begin和end返回const_iterator，否则返回iterator
若只需读操作无需写操作则用cbegin()和cend()来返回const_iterator --引入箭头运算符->实现解引用和成员访问
某些对vector对象的操作会使迭代器失效1.任何使用了迭代器的循环体都不要向迭代器所属的容器添加元素。
--3.4.2迭代器运算，支持==和!=，string和vector支持< <= > >=，在for循环中为什么使用!=而不是<是因为标准库中不是所有容器都实现了<
迭代器相减 得到带符号数diffrent_type
迭代器的算术运算：可以令一个迭代器和一个整数值相加或者相减，其返回值是向前或向后移动了若干个位置的迭代器，要么指向容器中某一个元素要么指向尾元素的下一位置
使用迭代器运算：经典算法=二分查找
*/