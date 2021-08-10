/*04_01二维数组中的查找
 * 题目：在一个二维数组中，每一行和每一列都是递增的。判断某个整数是否在这个二维数组中
 * input:
 * 1,2,8 ,9
 * 2,4,9 ,12
 * 4,7,10,13
 * 6,8,11,15
 *output: true or false(0/1)
 * 0810
*/

#include <vector>
#include <iostream>

using namespace std;

//
bool Find(int *matrix,int rows,int columns,int number){
    //check
    if(matrix == nullptr ||rows < 1 || columns < 1){
        return false;
    }
    //check elements

    //
    int row = 0, col = columns - 1;
    while(row <= rows - 1 && col >= 0){
        if(*(matrix + row * columns + col) == number)
            return true;
        else if(*(matrix + row * columns + col) > number)
            --col;
        else
            ++row;
    }
    return false;
}

int main(){

    int matrix [4][4] ={
        {1,2,8,9},
        {2,4,9,12},
        {4,7,10,13},
        {6,8,11,15}
    };
    int number = 7, rows = 4, columns = 4;
    return Find(matrix[0],rows,columns,number);
}//一维数组参数形式应该变为数组名。

/*
 * 传二维数组当参数方式。总结：
 * 1.f(int (*arr)[constexpr int columns],int rows)
 * 2.f(int [][constexpr int columns],int rows)
 * 3.f(int *ptr,int rows,int columns)//used
 * 4.f(int *[],int rows,int columns)
*/
